#imports
import sys
import os
import shutil
import pathlib
import json
from glob import glob
import generate_registry

#script folder
scriptFolder = str(pathlib.Path(__file__).parent);

#load config 
config = {}
with open(f"{scriptFolder}/build.config.json") as file:
    config = json.loads(file.read())
assert(config != {})

#get asengine path
asenginePath = config["asenginePath"]
asengineSourcePath = config["asengineSourcePath"]

#expect 4 arguments
assert(len(sys.argv) == 4)

#get project path
projectPath = sys.argv[1]

#genearte registry.cpp
#generate_registry.generate_registry(projectPath)

#get platform
platform = sys.argv[2]

# check platform validity
assert (platform in ("windows", "linux", "android"))
platformPath = config["targets"][platform]["platformPath"]

#debug / release
buildMode = sys.argv[3]
# check buildMode validity
assert (buildMode in ("debug", "release"))

#get working directory
workingDirectory = os.getcwd()


#generated tmp folder name
tmpFileName = f".tmp.{ platform }.{ projectPath.split('/')[-1] }"
#craete and copy platfrom to .tmp
shutil.copytree(platformPath, tmpFileName, dirs_exist_ok=True)

#we are going to compile from source for android
if platform == "android":
    #copy engine source
    shutil.copytree(f"{asengineSourcePath}", f"{tmpFileName}/app/src/main/cpp/asengine", dirs_exist_ok=True, ignore=shutil.ignore_patterns("build"))
    shutil.copytree(f"{asengineSourcePath}/build/include", f"{tmpFileName}/app/src/main/cpp/asengine/include", dirs_exist_ok=True)

    #copy project code to by compiled
    shutil.copytree(f"{projectPath}/src", f"{tmpFileName}/app/src/main/cpp/project-src", dirs_exist_ok=True)

#desktop build 
else:
    #copy compiled engine to temp project
    shutil.copytree(f"{asenginePath}/include", f"{tmpFileName}/asengine/include", dirs_exist_ok=True)

    if not os.path.isdir(f"{tmpFileName}/asengine/lib"):
        os.mkdir(f"{tmpFileName}/asengine/lib")

    shutil.copy(f"{asenginePath}/lib/{platform}/asengine.a", f"{tmpFileName}/asengine/lib/libasengine.a")

    #copy project code to by compiled
    shutil.copytree(f"{projectPath}/src", f"{tmpFileName}/project-src", dirs_exist_ok=True)

#copy project assets
assetsPath = ""
if platform == "android":
    assetsPath = f"{tmpFileName}/app/src/main/assets"
else:
    assetsPath = f"{tmpFileName}/build/assets"

shutil.copytree(f"{projectPath}/assets", assetsPath, dirs_exist_ok=True)

# create import.json file
"""os.chdir(assetsPath)
fonts = glob("**/*.font.json", recursive=True)
sprites = glob("**/*.sprite.json", recursive=True)
shaders = glob("**/*.glsl", recursive=True)
materials = glob("**/*.material.json", recursive=True)
scenes = glob("**/*.scene.json", recursive=True)
audios =glob("**/*.wav", recursive=True)
#create import all json
importAll = {
    "Sprites": sprites,
    "Shaders": shaders,
    "Scenes": scenes,
    "Materials": materials,
    "Fonts": fonts,
    "Audios": audios
}
os.chdir(workingDirectory)
#save import.json
importFile = open(f"{assetsPath}/import.json", "w")
importFile.write(json.dumps(importAll, indent=4))
importFile.close()
"""

if platform == "linux":
    os.chdir(f"{workingDirectory}/{tmpFileName}/build")
    #remove old build
    if os.path.exists("build"):
        os.remove("build")

    os.system("cmake .. ")
    os.system("make")
    os.system("./build")
    os.chdir(workingDirectory)

elif platform == "windows":
    os.chdir(f"{workingDirectory}/{tmpFileName}/build")
    #remove old build
    if os.path.exists("build.exe"):
        os.remove("build.exe")

    os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={scriptFolder}/../cmake-toolchains/mingw-w64-x86_64.cmake ..")
    os.system("make")
    os.system(f"wine {workingDirectory}/{tmpFileName}/build/build.exe")
    os.chdir(workingDirectory)

elif platform == "android":
    # find sdk tools
    sdkPath = config["targets"]["android"]["sdkPath"]
    emulatorPath = f"{sdkPath}/tools"
    adbPath = f"{sdkPath}/platform-tools"
    avdName = config["targets"]["android"]["avdName"]

    #build debug
    os.chdir(f"{workingDirectory}/{tmpFileName}")

    #set local.properties for android
    os.system(f"echo 'sdk.dir = {sdkPath}' > local.properties")

    os.system("./gradlew assembleDebug")
    os.chdir(workingDirectory)

    #install apk
    os.chdir(adbPath)
    os.system(f"./adb install {workingDirectory}/{tmpFileName}/app/build/outputs/apk/debug/app-debug.apk")
    os.system(f"./adb shell am start -n com.example.androidsimpleengine/com.example.androidsimpleengine.MainActivity")
    os.chdir(workingDirectory)