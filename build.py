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
        if pathlib.Path(f"{str(folder)}/include").is_dir():
            shutil.copytree(f"{str(folder)}/include", "build/include/dependencies/" + str(folder.name), dirs_exist_ok=True)

    #entrypoint for include file (include it to include all the asengine)
    entryPointList = ["#ifndef __ASENGINE_INCLUDE_H\n#define __ASENGINE_INLUDE_H\n"]

    #get all header files
    enginePath = pathlib.Path("asengine")
    headerFileList = list(enginePath.rglob("*.h")) + list(enginePath.rglob("*.hpp"))

    for headerFile in headerFileList:
        destFile = headerFile.relative_to("asengine")
        #add file to entry point

        #ignore hidden files
        if destFile.name.startswith("."):
            continue
        
        isHidden = False
        for i, p in enumerate(destFile.parents):
            if i < len(destFile.parents) + 1 and p.name.startswith("."):
                isHidden = True
                break

        if isHidden:
            continue

        includeToEntryPoint = f'#include "{str(destFile)}"\n'
        entryPointList.append(includeToEntryPoint)
        #copy file
        os.makedirs("build/include/asengine/" + str(destFile.parent), exist_ok=True)
        
        destPath = "build/include/asengine/" + str(destFile)
        
        shutil.copy(str(headerFile),destPath)
        shutil.copystat(str(headerFile),destPath)


    #create asengine.h
    entryPointList.append("#endif")

    oldEntryPointList = ""
    newEntryPointList = ''.join(entryPointList)

    if (pathlib.Path("build/include/asengine/ASEngine.h").is_file()):
        #get old entry file value
        entryPointFile = open("build/include/asengine/ASEngine.h", "r")
        oldEntryPointList = entryPointFile.read()
        entryPointFile.close()
        #skip if same
        if oldEntryPointList == newEntryPointList:
            return
    
    entryPointFile = open("build/include/asengine/ASEngine.h", "w")
    entryPointFile.write(newEntryPointList)
    entryPointFile.close()

# compile asengine 
def compileEngineFor(plarform, graphicsAPI = "") -> int:
    #asengine path
    enginePath = os.getcwd()
    #cmake toolchains path
    cmakeToolChainsPath = str(pathlib.Path(enginePath).parent) + "/cli/asengineCLI/resources/cmake-toolchains"
    print(cmakeToolChainsPath)
    #create build folder
    buildFolderPath = "build/lib/" + plarform
    os.makedirs(buildFolderPath, exist_ok=True)
    #compile the asengine
    os.chdir(buildFolderPath)

    # keep track of compilation result
    compilationResult = 0

    #cmake
    if plarform == "linux":
        compilationResult += os.system(f"cmake {enginePath}")
    elif plarform == "windows":
        windowsCmakeToolchain = f"{cmakeToolChainsPath}/mingw-w64-x86_64.cmake"
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

    os.chdir(enginePath)

    return compilationResult

#compile asengine given arguments (os)
def compile(platforms: list[str]) -> int:
    #generate include
    generateIncludeFiles()

    #compile the asengine
    compilationResult = 0
    for platform in platforms:
        compilationResult |= compileEngineFor(platform)

    return compilationResult

#main
if __name__ == "__main__":
    sys.exit(compile(sys.argv[1:]) % 255)        