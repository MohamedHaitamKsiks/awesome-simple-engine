#build a porject to the platform given by the user

#imports
import sys
import os
import shutil
import json
import subprocess

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

#remove .tmp if exists
#if ".tmp" in os.listdir(os.getcwd()):
#    shutil.rmtree(".tmp." + platform)

#craete and copy platfrom to .tmp
shutil.copytree(f"platforms/{ platformType }", tmpFileName, dirs_exist_ok=True)


#build for android
if platform == "android":
    # find sdk tools
    sdkPath = config["android"]["sdkPath"]
    emulatorPath = f"{sdkPath}/tools"
    adbPath = f"{sdkPath}/platform-tools"
    avdName = config["android"]["avdName"]

    #copy project + engine + dependencies to .tmp
    shutil.copytree("engine", f"{tmpFileName}/app/src/main/cpp/engine", dirs_exist_ok=True)
    shutil.copytree(f"{projectPath}/objects", f"{tmpFileName}/app/src/main/cpp/objects", dirs_exist_ok=True)
    shutil.copytree(f"{projectPath}/assets", f"{tmpFileName}/app/src/main/assets", dirs_exist_ok=True)

    #build debug
    os.chdir(tmpFileName)
    os.system("./gradlew assembleDebug")
    os.chdir(workingDirectory)

    #install apk
    os.chdir(adbPath)
    os.system(f"./adb install {workingDirectory}/{tmpFileName}/app/build/outputs/apk/debug/app-debug.apk")
    os.system(f"./adb shell am start -n com.example.androidsimpleengine/com.example.androidsimpleengine.MainActivity")
    os.chdir(workingDirectory)

#build for linux
elif platform == "linux":
    # copy project + engine + dependencies to .tmp
    shutil.copytree("engine", f"{tmpFileName}/engine", dirs_exist_ok=True)
    shutil.copytree(f"{projectPath}/objects", f"{tmpFileName}/objects", dirs_exist_ok=True)
    shutil.copytree(f"{projectPath}/assets", f"{tmpFileName}/build/assets", dirs_exist_ok=True)

    # install apk
    os.chdir(f"{workingDirectory}/{tmpFileName}/build")
    os.system("cmake ..")
    os.system("make")
    os.system("./build")
    os.chdir(workingDirectory)
