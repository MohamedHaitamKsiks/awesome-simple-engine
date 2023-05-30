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

#debug / release
buildMode = sys.argv[3]
# check buildMode validity
assert (buildMode in ("debug", "release"))


#get working directory
workingDirectory = os.getcwd()


#remove .tmp if exists
if ".tmp" in os.listdir(os.getcwd()):
    shutil.rmtree(".tmp")

#craete and copy platfrom to .tmp
shutil.copytree(f"platforms/{ platform }", ".tmp")


#build for android
if platform == "android":
    # find sdk tools
    sdkPath = config["android"]["sdkPath"]
    emulatorPath = f"{sdkPath}/tools"
    adbPath = f"{sdkPath}/platform-tools"
    avdName = config["android"]["avdName"]

    #copy project + engine + dependencies to .tmp
    shutil.copytree("engine", ".tmp/app/src/main/cpp/engine", dirs_exist_ok=True)
    shutil.copytree(f"{projectPath}/objects", ".tmp/app/src/main/cpp/objects", dirs_exist_ok=True)
    shutil.copytree(f"{projectPath}/assets", ".tmp/app/src/main/assets", dirs_exist_ok=True)

    #build debug
    os.chdir(".tmp")
    os.system("./gradlew assembleDebug")
    os.chdir(workingDirectory)

    #install apk
    os.chdir(adbPath)
    os.system(f"./adb install {workingDirectory}/.tmp/app/build/outputs/apk/debug/app-debug.apk")
    os.system(f"./adb shell am start -n com.example.androidsimpleengine/com.example.androidsimpleengine.MainActivity")
    os.chdir(workingDirectory)

