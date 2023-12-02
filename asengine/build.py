#imports
import os
import pathlib
import shutil
import sys

# generate include files
def generateIncludeFiles():
    #add dependencies
    dependenciesFolder = pathlib.Path("dependencies").iterdir()
    for folder in dependenciesFolder:
        shutil.copytree(f"{str(folder)}/include", "build/include/dependencies/" + str(folder.name), dirs_exist_ok=True)

    #entrypoint for include file (include it to include all the engine)
    entryPointList = ["#ifndef ASENGINE_H\n#define ASENGINE_H\n"]

    #get all header files
    enginePath = pathlib.Path("engine")
    headerFileList = list(enginePath.rglob("*.h")) + list(enginePath.rglob("*.hpp"))

    for headerFile in headerFileList:
        destFile = headerFile.relative_to("engine")
        #add file to entry point
        includeToEntryPoint = f'#include "{str(destFile)}"\n'
        entryPointList.append(includeToEntryPoint)
        #copy file
        os.makedirs("build/include/engine/" + str(destFile.parent), exist_ok=True)
        
        destPath = "build/include/engine/" + str(destFile)
        
        shutil.copy(str(headerFile),destPath)
        shutil.copystat(str(headerFile),destPath)


    #create asengine.h
    entryPointList.append("#endif")

    oldEntryPointList = ""
    newEntryPointList = ''.join(entryPointList)

    if (pathlib.Path("build/include/engine/ASEngine.h").is_file()):
        #get old entry file value
        entryPointFile = open("build/include/engine/ASEngine.h", "r")
        oldEntryPointList = entryPointFile.read()
        entryPointFile.close()
        #skip if same
        if oldEntryPointList == newEntryPointList:
            return
    
    entryPointFile = open("build/include/engine/ASEngine.h", "w")
    entryPointFile.write(newEntryPointList)
    entryPointFile.close()

# compile engine 
def compileEngineFor(plarform):
    #engine path
    enginePath = os.getcwd()
    #cmake toolchains path
    cmakeToolChainsPath = str(pathlib.Path(enginePath).parent) + "/cli/asengine/resources/cmake-toolchains"
    print(cmakeToolChainsPath)
    #create build folder
    buildFolderPath = "build/lib/" + plarform
    os.makedirs(buildFolderPath, exist_ok=True)
    #compile the engine
    os.chdir(buildFolderPath)
    #cmake
    if plarform == "linux":
        os.system(f"cmake {enginePath}")
    elif plarform == "windows":
        os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={cmakeToolChainsPath}/mingw-w64-x86_64.cmake {enginePath}")
    #make
    print("Compilation result:", os.system("make"))

    #combine into one static librarty
    #create .mri file
    if pathlib.Path("asengine.a").exists():
        os.remove("asengine.a")

    mriCode = ["create asengine.a"]

    libFilesList = list(pathlib.Path().rglob("*.a"))

    for libFile in libFilesList:
        if (libFile.name == "asegnine.a"):
            continue
        mriCode.append(f"addlib {str(libFile)}")
    
    mriCode.append("save")
    mriCode.append("end")


    #save .mri file
    mriFile = open("asengine.mri", "w")
    mriFile.write('\n'.join(mriCode))
    mriFile.close()

    #generate asengine.a
    os.system("ar -M <asengine.mri")

    os.chdir(enginePath)

#main
generateIncludeFiles()

if len(sys.argv) == 2 and sys.argv[1]:
    compileEngineFor(sys.argv[1])

else:
    compileEngineFor("linux")
    compileEngineFor("windows")