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

#expect 4 arguments
assert(len(sys.argv) == 4)

#get project path
projectPath = sys.argv[1]

#genearte registry.cpp
generate_registry.generate_registry(projectPath)

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
    pass

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


os.chdir(f"{workingDirectory}/{tmpFileName}/build")

#compile for linux
if platform == "linux":
    os.system("cmake .. ")
    os.system("make")
    os.system("./build")

elif platform == "windows":
    os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={scriptFolder}/../cmake-toolchains/mingw-w64-x86_64.cmake ..")
    os.system("make")
    os.system(f"wine {workingDirectory}/{tmpFileName}/build/build.exe")
    
os.chdir(workingDirectory)
