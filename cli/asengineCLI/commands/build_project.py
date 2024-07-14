#imports
import sys
import os
import shutil
import json
import pathlib

from asengineCLI.commands.status import *
from asengineCLI.commands.script_path import *
from asengineCLI.commands.compile_shaders import scanAndCompileShaders

def removeIfExists(filePath: str):
    if os.path.exists(filePath):
        os.remove(filePath)

def buildProject(configPath: str, projectPath: str, platform: str, debug: bool = False) -> int:
    #debug mode
    debugMode = "debug" if debug else "release"

    # error return
    error = 0 
    projectPath = relativeTo(projectPath, "")

    # check project validity
    isValid, missingRequirements = getProjectIsValid(projectPath)
    if not isValid:
        print('\n'.join(missingRequirements))
        return 1

    #load config 
    config = {}
    with open(configPath) as file:
        config = json.loads(file.read())
        
    assert(config != {})

    # check platform validity
    assert (platform in ("windows", "linux", "headless", "web"))

    # get config directory
    configDir = dirPath(configPath)

    #get asengine path
    asenginePath = config["asengine"]["buildPath"]
    cmakeWindowsToolChain = config["cmakeToolchains"]["windows"]
    emsdkPath = config["targets"]["web"]["emsdkPath"]
    platformOS = config["targets"][platform]["os"]
    platformPath = relativeTo(config["platformsPath"], config["targets"][platform]["type"])

    #generated tmp folder name
    tmpFileName = f".tmp.{ platform }.{debugMode}"
    tmpPath = relativeTo(projectPath, tmpFileName)

    #create and copy platfrom to .tmp
    shutil.copytree(platformPath, tmpPath, dirs_exist_ok=True)

    #copy project assets
    assetsPath = relativeTo(tmpPath, "./build/assets")
    shutil.copytree(relativeTo(projectPath, "./assets"), assetsPath, dirs_exist_ok=True)

    #scan and compile shaders
    print("Compiling shaders to SPIR-V")
    glslangPath = relativeTo(configDir, config["glslang"])
    error |= scanAndCompileShaders(assetsPath, glslangPath)


    ###################### COMPILING #########################


    #engine paths
    includePath = relativeTo(asenginePath, "./include")

    #project source path 
    projectSourcePath = relativeTo(projectPath, "./src");
    libPath = relativeTo(asenginePath, f"./lib/{platformOS}/{debugMode}") 

    #game build
    buildPath = relativeTo(tmpPath, "./build")
    
    # compile and run
    os.chdir(buildPath)

    #remove old builds
    if platformOS == "linux":
        removeIfExists("build")

    elif platformOS == "windows":
        removeIfExists("build.exe")

    elif platformOS == "web":
        removeIfExists("index.wasm")
        removeIfExists("index.html")
    
    #cmake 
    cmakeBuildCommand = ["cmake"]
    
    # add toolchains
    if platformOS == "windows":
        cmakeBuildCommand.append(f"-DCMAKE_TOOLCHAIN_FILE={cmakeWindowsToolChain}")
    
    #compile with emcmake for web
    elif platformOS == "web":
        emcmakePath = relativeTo(emsdkPath, "./upstream/emscripten/emcmake")
        cmakeBuildCommand = [emcmakePath] + cmakeBuildCommand


    # debug mode 
    if debug:
        cmakeBuildCommand.append("-DCMAKE_BUILD_TYPE=Debug")

    # add paths
    cmakeBuildCommand.append(f"-DASENGINE_INCLUDE_PATH={includePath}")
    cmakeBuildCommand.append(f"-DASENGINE_LIB_PATH={libPath}")
    cmakeBuildCommand.append(f"-DASENGINE_PROJECT_PATH={projectSourcePath}")
    
    # add build path
    cmakeBuildCommand.append("..")

    # run compilation
    error |= os.system(' '.join(cmakeBuildCommand))

    if platformOS == "web":
        emmakePath = relativeTo(emsdkPath, "./upstream/emscripten/emmake")
        error |= os.system(f"{emmakePath} make")
    else:
        error |= os.system("make")

    # copy dynamic libraries for linux and windows
    if platformOS in ["windows", "linux"]:
        dynamicLibraryExt = ".so" if platformOS == "linux" else ".dll" 
        libsToCopy = pathlib.Path(libPath).rglob(f"*{dynamicLibraryExt}")

        for lib in libsToCopy:
            shutil.copy2(lib, buildPath)

    # run output
    if platformOS == "linux":
        error |= os.system("./build")

    elif platformOS == "windows":
        error |= os.system(f"wine {relativeTo(buildPath, './build.exe')}")

    elif platformOS == "web":
        os.system("python3 -m http.server 8080")

    #end
    os.chdir(projectPath)

    return error


if __name__ == "__main__":
    # expect 3 arguments
    assert(len(sys.argv) == 3)

    # get project path
    projectPath = relativeTo(os.getcwd(), sys.argv[1])

    # get platform
    platform = sys.argv[2]

    # build project
    buildProject(relativeToScriptPath("../resources/build.config.json"), projectPath, platform)
