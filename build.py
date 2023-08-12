#build a porject to the platform given by the user

#imports
import sys
import os
import shutil
import json
from glob import glob

#read config
config = {}
with open("build.config.json") as file:
    config = json.loads(file.read())
assert(config != {})

#expect 4 arguments
assert(len(sys.argv) == 4)
#get project path
projectPath = sys.argv[1]
#get platform
platform = sys.argv[2]
# check platform validity
assert (platform in ("windows", "linux", "android"))
platformType = config[platform]["type"]
#debug / release
buildMode = sys.argv[3]
# check buildMode validity
assert (buildMode in ("debug", "release"))


#get working directory
workingDirectory = os.getcwd()
#generated tmp folder name
tmpFileName = f".tmp.{ platform }.{ projectPath.split('/')[-1] }"
#craete and copy platfrom to .tmp
shutil.copytree(f"platforms/{ platformType }", tmpFileName, dirs_exist_ok=True)

def copyProjectToTemp():
    # copy project + engine + dependencies to .tmp
    if platform == "android":
        shutil.copytree("asengine", f"{tmpFileName}/app/src/main/cpp/asengine", dirs_exist_ok=True)
        shutil.copytree(f"{projectPath}/ecs", f"{tmpFileName}/app/src/main/cpp/ecs", dirs_exist_ok=True)
        shutil.copytree(f"{projectPath}/assets", f"{tmpFileName}/app/src/main/assets", dirs_exist_ok=True)
    else:
        shutil.copytree("asengine", f"{tmpFileName}/asengine", dirs_exist_ok=True)
        shutil.copytree(f"{projectPath}/ecs", f"{tmpFileName}/ecs", dirs_exist_ok=True)
        shutil.copytree(f"{projectPath}/assets", f"{tmpFileName}/build/assets", dirs_exist_ok=True)
    
    assetsPath = ""
    if platform == "android":
        assetsPath = f"{tmpFileName}/app/src/main/assets"
    else:
        assetsPath = f"{tmpFileName}/build/assets"

    # create import.json file
    os.chdir(assetsPath)
    fonts = glob("**/*.font.json", recursive=True)
    sprites = glob("**/*.sprite.json", recursive=True)
    shaders = glob("**/*.glsl", recursive=True)
    materials = glob("**/*.material.json", recursive=True)
    scenes = glob("**/*.scene.json", recursive=True)
    #create import all json
    importAll = {
        "Sprites": sprites,
        "Shaders": shaders,
        "Scenes": scenes,
        "Materials": materials,
        "Fonts": fonts
    }
    os.chdir(workingDirectory)
    #save import.json

    importFile = open(f"{assetsPath}/import.json", "w")
    importFile.write(json.dumps(importAll, indent=4))
    importFile.close()
    

#build for android
if platform == "android":
    # find sdk tools
    sdkPath = config["android"]["sdkPath"]
    emulatorPath = f"{sdkPath}/tools"
    adbPath = f"{sdkPath}/platform-tools"
    avdName = config["android"]["avdName"]

    copyProjectToTemp()

    #build debug
    os.chdir(tmpFileName)

    #set local.properties for android
    os.system(f"echo 'sdk.dir = {sdkPath}' > local.properties")

    os.system("./gradlew assembleDebug")
    os.chdir(workingDirectory)

    #install apk
    os.chdir(adbPath)
    os.system(f"./adb install {workingDirectory}/{tmpFileName}/app/build/outputs/apk/debug/app-debug.apk")
    os.system(f"./adb shell am start -n com.example.androidsimpleengine/com.example.androidsimpleengine.MainActivity")
    os.chdir(workingDirectory)

#build for linux
elif platform == "linux":
    copyProjectToTemp()
    # build for linux
    os.chdir(f"{workingDirectory}/{tmpFileName}/build")
    os.system("cmake .. ")
    os.system("make")
    os.system("./build")
    os.chdir(workingDirectory)

    # build for linux
elif platform == "windows":
    # copy project + engine + dependencies to .tmp
    copyProjectToTemp()
    # build for windows
    os.chdir(f"{workingDirectory}/{tmpFileName}/build")
    os.system(
        f"cmake -DCMAKE_TOOLCHAIN_FILE={workingDirectory}/cmake-toolchains/mingw-w64-x86_64.cmake ..")
    os.system("make")
    os.system(f"wine {workingDirectory}/{tmpFileName}/build/build.exe")
    os.chdir(workingDirectory)
