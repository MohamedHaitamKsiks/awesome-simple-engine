#imports
import os
import pathlib
import shutil
import sys
import json
from stat import S_IREAD, S_IRGRP, S_IROTH


# add header files
def retrieveHeaders(root: pathlib.Path, excludedHeaders: set) -> list[pathlib.Path]:
    #ignore if hidden
    if root.name.startswith(".") or str(root) in excludedHeaders:
        return []

    #add .h and .hpp file
    if  root.is_file():
        if root.match("*.h") or root.match("*.hpp"):
            return [root]
        else:
            return []

    # add directory and look foch sub directories
    paths = list(root.glob("*"))
    headers = [root]
    for path in paths:
        headers += retrieveHeaders(path, excludedHeaders)
        
    return headers

# generate include files (all read only)
def generateIncludeFiles():
    includedHeaders = []
    excludedHeaders = set()
    #open headers.json
    with open("headers.json") as headersFile:
        headers = json.load(headersFile)
        includedHeaders = headers["include"]
        excludedHeaders = set(headers["exclude"])


    #entrypoint for include file (include it to include all the asengine)
    entryPointList = ["#ifndef __ASENGINE_INCLUDE_H\n#define __ASENGINE_INLUDE_H\n"]

    #add all included folders
    headers: list[pathlib.Path] = []
    for headerToInclude in includedHeaders:
        headerPath = pathlib.Path(headerToInclude)
        headers += retrieveHeaders(headerPath, excludedHeaders)

    for header in headers:
        relativeHeader = header.relative_to("./asengine")
        if header.is_dir():
            os.makedirs(f"build/include/{str(relativeHeader)}", exist_ok=True)
            continue
        
        includeToEntryPoint = f'#include "{str(relativeHeader)}"\n'
        entryPointList.append(includeToEntryPoint)
        #copy file
        destPath = f"build/include/{str(relativeHeader)}"
        shutil.copy(str(header), destPath)
        shutil.copystat(str(header), destPath)
        # os.chmod(destPath, S_IREAD | S_IRGRP | S_IROTH) # TODO

    #create asengine.h
    entryPointList.append("#endif")
    entryPointPath = "build/include/ASEngine.h"

    oldEntryPointList = ""
    newEntryPointList = ''.join(entryPointList)

    #don't save if value didn't change (avoid recompiling)
    if (pathlib.Path(entryPointPath).is_file()):
        #get old entry file value
        with open(entryPointPath, "r")  as entryPointFile:
            oldEntryPointList = entryPointFile.read()

            #return 
            if oldEntryPointList == newEntryPointList:
                return

    #save 
    with open(entryPointPath, "w") as entryPointFile:
        entryPointFile.write(newEntryPointList)
        
    #set entry point as read only
    # os.chmod(entryPointPath, S_IREAD | S_IRGRP | S_IROTH) TODO

# compile asengine 
def compileEngineFor(plarform) -> int:
    #asengine path
    enginePath = os.getcwd()
    #create build folder
    buildFolderPath = f"build/.tmplib/{plarform}"
    os.makedirs(buildFolderPath, exist_ok=True)
    #compile the asengine
    os.chdir(buildFolderPath)

    # keep track of compilation result
    compilationResult = 0

    #cmake
    if plarform == "linux":
        compilationResult += os.system(f"cmake {enginePath}")
    elif plarform == "windows":
        windowsCmakeToolchain = "cmake_toolchains/mingw-w64-x86_64.cmake"
        compilationResult += os.system(f"cmake -DCMAKE_TOOLCHAIN_FILE={windowsCmakeToolchain} {enginePath}")
    
    #make
    compilationResult += os.system("make")

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

    #copy asengine.a to lib
    os.chdir(enginePath)

    libPath = f"build/lib/{plarform}"
    os.makedirs(libPath, exist_ok=True)
    shutil.copy(f"{buildFolderPath}/asengine.a", f"{libPath}/libasengine.a")


    return compilationResult

#compile asengine given arguments (os)
def compileASEngine(platforms: list[str]) -> int:
    #generate include
    generateIncludeFiles()

    #compile the asengine
    compilationResult = 0
    for platform in platforms:
        compilationResult |= compileEngineFor(platform)

    return compilationResult

#main
if __name__ == "__main__":
    sys.exit(compileASEngine(sys.argv[1:]) % 255)