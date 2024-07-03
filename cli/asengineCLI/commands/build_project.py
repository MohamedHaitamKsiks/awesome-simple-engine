#imports
import sys
import os
import shutil
import json
from asengineCLI.commands.status import *
from asengineCLI.commands.script_path import *
from asengineCLI.commands.compile_shaders import scanAndCompileShaders

def buildProject(configPath: str, projectPath: str, platform: str) -> int:
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
    assert (platform in ("windows", "linux", "headless"))

    # get config directory
    configDir = dirPath(configPath)

    #get asengine path
    asenginePath = config["asengine"]["buildPath"]
    asengineSourcePath = config["asengine"]["sourcePath"]
    cmakeWindowsToolChain = config["cmakeToolchains"]["windows"]
    platformOS = config["targets"][platform]["os"]
    platformPath = relativeTo(config["platformsPath"], config["targets"][platform]["type"])

    #generated tmp folder name
    tmpFileName = f".tmp.{ platform }"
    tmpPath = relativeTo(projectPath, tmpFileName)
    #craete and copy platfrom to .tmp
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
    libPath = relativeTo(asenginePath, f"./lib/{platformOS}") 
    
    #game build
    buildPath = relativeTo(tmpPath, "./build")
    
    # compile and run
    if platform in ["linux", "headless"]:

        os.chdir(buildPath)
        #remove old build
        if os.path.exists("build"):
            os.remove("build")

        error |= os.system(f"cmake -DCMAKE_BUILD_TYPE=Debug -DASENGINE_INCLUDE_PATH={includePath} -DASENGINE_LIB_PATH={libPath} -DASENGINE_PROJECT_PATH={projectSourcePath} .. ")
        error |= os.system("make")
        
        # run app
        error |= os.system("./build")
        os.chdir(projectPath)

    elif platform == "windows":
        os.chdir(buildPath)
        
        #copy libasengine.dll
        shutil.copy(relativeTo(libPath, "./libasengine.dll"), relativeTo(buildPath, "./libasengine.dll"))

        #remove old build
        if os.path.exists("build.exe"):
            os.remove("build.exe")

        error |= os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={cmakeWindowsToolChain} -DASENGINE_INCLUDE_PATH={includePath} -DASENGINE_LIB_PATH={libPath} -DASENGINE_PROJECT_PATH={projectSourcePath} .. ")
        error |= os.system("make")
        
        #run with wine
        error |= os.system(f"wine {relativeTo(buildPath, './build.exe')}")
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
