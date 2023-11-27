#imports
import sys
import os
import shutil
import json
from asengine.commands.status import *
from asengine.commands.script_path import *

def buildProject(configPath: str, projectPath: str, platform: str) -> bool:
    # check project validity
    isValid, missingRequirements = getProjectIsValid(projectPath)
    if not isValid:
        print('\n'.join(missingRequirements))
        return False

    #load config 
    config = {}
    with open(configPath) as file:
        config = json.loads(file.read())
        
    assert(config != {})

    # check platform validity
    assert (platform in ("windows", "linux", "android"))
    platformPath = config["targets"][platform]["platformPath"]

    # get config directory
    configDir = dirPath(configPath)

    #get asengine path
    asenginePath = relativeTo(configDir, config["asenginePath"])
    asengineSourcePath = relativeTo(configDir, config["asengineSourcePath"])
    cmakeWindowsToolChain = relativeTo(configDir, config["cmakeWindowsToolchain"])

    #generated tmp folder name
    tmpFileName = f".tmp.{ platform }"
    tmpPath = relativeTo(configDir, tmpFileName)
    #craete and copy platfrom to .tmp
    shutil.copytree(platformPath, tmpPath, dirs_exist_ok=True)

    #we are going to compile from source for android
    if platform == "android":
        #copy engine source
        shutil.copytree(asengineSourcePath, 
                        relativeTo(tmpPath, "./app/src/main/cpp/asengine"), 
                        dirs_exist_ok=True, 
                        ignore=shutil.ignore_patterns("build"))
        
        shutil.copytree(relativeTo(asengineSourcePath, "./build/include"), 
                        relativeTo(tmpPath, "./app/src/main/cpp/asengine/include"), 
                        dirs_exist_ok=True)

        #copy project code to by compiled
        shutil.copytree(relativeTo(projectPath, "./src"), 
                        relativeTo(tmpPath, "./app/src/main/cpp/project-src"), 
                        dirs_exist_ok=True)

    #desktop build 
    else:
        #copy compiled engine to temp project
        shutil.copytree(relativeTo(asenginePath, "./include"), 
                        relativeTo(tmpPath, "./asengine/include"), 
                        dirs_exist_ok=True)

        if not os.path.isdir(relativeTo(tmpPath, "./asengine/lib")):
            os.mkdir(relativeTo(tmpPath, "./asengine/lib"))

        shutil.copy(relativeTo(asenginePath, f"./lib/{platform}/asengine.a"), 
                    relativeTo(tmpPath, "./asengine/lib/libasengine.a"))

        #copy project code to by compiled
        shutil.copytree(relativeTo(projectPath, "./src"), 
                        relativeTo(tmpPath, "./project-src"), 
                        dirs_exist_ok=True)

    #copy project assets
    assetsPath = relativeTo(tmpPath, "./app/src/main/assets") if platform == "android" else relativeTo(tmpPath, "./build/assets")
    shutil.copytree(relativeTo(projectPath, "./assets"), assetsPath, dirs_exist_ok=True)

    # compile and run
    if platform == "linux":
        os.chdir(relativeTo(tmpPath, "./build"))
        #remove old build
        if os.path.exists("build"):
            os.remove("build")

        os.system("cmake .. ")
        os.system("make")
        os.system("./build")
        os.chdir(projectPath)

    elif platform == "windows":
        os.chdir(relativeTo(tmpPath, "./build"))
        #remove old build
        if os.path.exists("build.exe"):
            os.remove("build.exe")

        os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={cmakeWindowsToolChain} ..")
        os.system("make")
        os.system(f"wine {relativeTo(tmpPath, './build/build.exe')}")
        os.chdir(projectPath)

    elif platform == "android":
        # find sdk tools
        sdkPath = relativeTo(configDir, config["targets"]["android"]["sdkPath"])
        emulatorPath = relativeTo(sdkPath, "./tools")
        adbPath = relativeTo(sdkPath, "./platform-tools")
        avdName = config["targets"]["android"]["avdName"]

        #build debug
        os.chdir(f"{projectPath}/{tmpFileName}")

        #set local.properties for android
        os.system(f"echo 'sdk.dir = {sdkPath}' > local.properties")

        os.system("./gradlew assembleDebug")
        os.chdir(projectPath)

        #install apk
        os.chdir(adbPath)
        os.system(f"./adb install {relativeTo(tmpPath, './app/build/outputs/apk/debug/app-debug.apk')}")
        os.system(f"./adb shell am start -n com.example.androidsimpleengine/com.example.androidsimpleengine.MainActivity")
        os.chdir(projectPath)
        
    return True


if __name__ == "__main__":
    # expect 3 arguments
    assert(len(sys.argv) == 3)

    # get project path
    projectPath = relativeTo(os.getcwd(), sys.argv[1])

    # get platform
    platform = sys.argv[2]

    # build project
    buildProject(relativeToScriptPath("../resources/build.config.json"), projectPath, platform)
