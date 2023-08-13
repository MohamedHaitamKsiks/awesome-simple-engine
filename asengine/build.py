#imports
import os
import pathlib
import shutil

# generate include files
def generate_include_files():
    #entrypoint for include file (include it to include all the engine)
    entryPointList = ["#ifndef ASENGINE_H\n#define ASENGINE_H\n"]

    #get all header files
    enginePath = pathlib.Path("engine")
    headerFileList = list(enginePath.rglob("*.h"))

    for headerFile in headerFileList:
        destFile = headerFile.relative_to("engine")
        #add file to entry point
        includeToEntryPoint = f'#include "{str(destFile)}"\n'
        entryPointList.append(includeToEntryPoint)
        #copy file
        os.makedirs("include/" + str(destFile.parent), exist_ok=True)
        shutil.copy(str(headerFile),"include/" + str(destFile))

    #create asengine.h
    entryPointList.append("#endif")
    
    entryPointFile = open("include/asengine.h", "w")
    entryPointFile.write(''.join(entryPointList))
    entryPointFile.close()

# compile engine 
def compile_engine_for(plarform):
    #engine path
    enginePath = os.getcwd()
    #cmake toolchains path
    cmakeToolChainsPath = enginePath + "/../cmake-toolchains"
    #create build folder
    buildFolderPath = "build/" + plarform
    os.makedirs(buildFolderPath, exist_ok=True)
    #compile the engine
    os.chdir(buildFolderPath)
    #cmake
    if plarform == "linux":
        os.system(f"cmake {enginePath}")
    elif plarform == "windows":
        os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={cmakeToolChainsPath}/mingw-w64-x86_64.cmake {enginePath}")
    #make
    os.system("make")
    os.chdir(enginePath)

#main
generate_include_files()

compile_engine_for("windows")
compile_engine_for("linux")