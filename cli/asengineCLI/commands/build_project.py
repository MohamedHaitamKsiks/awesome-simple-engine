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
    assert (platform in ("windows", "linux", "android", "headless"))

    # get config directory
    configDir = dirPath(configPath)

    #get asengine path
    platformPath = relativeTo(configDir, config["targets"][platform]["platformPath"])
    asenginePath = relativeTo(configDir, config["asenginePath"])
    asengineSourcePath = relativeTo(configDir, config["asengineSourcePath"])
    cmakeWindowsToolChain = relativeTo(configDir, config["cmakeWindowsToolchain"])
    platformOS = config["targets"][platform]["os"]

    #generated tmp folder name
    tmpFileName = f".tmp.{ platform }"
    tmpPath = relativeTo(projectPath, tmpFileName)
    #craete and copy platfrom to .tmp
    shutil.copytree(platformPath, tmpPath, dirs_exist_ok=True)

    #we are going to compile from source for android
    if platform == "android":
        #copy asengine source
        shutil.copytree(asengineSourcePath, 
                        relativeTo(tmpPath, "./app/src/main/cpp/asengine"), 
                        dirs_exist_ok=True, 
                        ignore=shutil.ignore_patterns("build"))
        
        shutil.copytree(relativeTo(asenginePath, "./include"), 
                        relativeTo(tmpPath, "./app/src/main/cpp/asengine/include"), 
                        dirs_exist_ok=True)

        #copy project code to by compiled
        shutil.copytree(relativeTo(projectPath, "./src"), 
                        relativeTo(tmpPath, "./app/src/main/cpp/project-src"), 
                        dirs_exist_ok=True)

    #desktop/headless build 
    else:
        #copy compiled asengine to temp project
        shutil.copytree(relativeTo(asenginePath, "./include"), 
                        relativeTo(tmpPath, "./asengine/include"), 
                        dirs_exist_ok=True)

        if not os.path.isdir(relativeTo(tmpPath, "./asengine/lib")):
            os.mkdir(relativeTo(tmpPath, "./asengine/lib"))

        shutil.copy(relativeTo(asenginePath, f"./lib/{platformOS}/asengine.a"), 
                    relativeTo(tmpPath, "./asengine/lib/libasengine.a"))

        #copy project code to by compiled
        shutil.copytree(relativeTo(projectPath, "./src"), 
                        relativeTo(tmpPath, "./project-src"), 
                        dirs_exist_ok=True)

    #copy project assets
    assetsPath = relativeTo(tmpPath, "./app/src/main/assets") if platform == "android" else relativeTo(tmpPath, "./build/assets")
    shutil.copytree(relativeTo(projectPath, "./assets"), assetsPath, dirs_exist_ok=True)

    #scan and compile shaders
    print("Compiling shaders to SPIR-V")
    glslangPath = relativeTo(configDir, config["glslang"])
    error |= scanAndCompileShaders(assetsPath, glslangPath)

    # compile and run
    if platform in ["linux", "headless"]:
        os.chdir(relativeTo(tmpPath, "./build"))
        #remove old build
        if os.path.exists("build"):
            os.remove("build")

        error |= os.system("cmake .. ")
        error |= os.system("make")
        
        # run app
        error |= os.system("./build")
        os.chdir(projectPath)

    elif platform == "windows":
        os.chdir(relativeTo(tmpPath, "./build"))
        #remove old build
        if os.path.exists("build.exe"):
            os.remove("build.exe")

        error |= os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={cmakeWindowsToolChain} ..")
        error |= os.system("make")
        error |= os.system(f"wine {relativeTo(tmpPath, './build/build.exe')}")
        os.chdir(projectPath)

    elif platform == "android":
        # find sdk tools
        sdkPath = relativeTo(configDir, config["targets"]["android"]["sdkPath"])
        emulatorPath = relativeTo(sdkPath, "./tools")
        adbPath = relativeTo(sdkPath, "./platform-tools")
        avdName = config["targets"]["android"]["avdName"]

        #build debug
        os.chdir(tmpPath)

        #set local.properties for android
        os.system(f"echo 'sdk.dir = {sdkPath}' > local.properties")

        os.system("./gradlew assembleDebug")
        os.chdir(projectPath)

        #install apk
        os.chdir(adbPath)
        os.system(f"./adb install {relativeTo(tmpPath, './app/build/outputs/apk/debug/app-debug.apk')}")
        os.system(f"./adb shell am start -n com.example.androidsimpleengine/com.example.androidsimpleengine.MainActivity")
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
