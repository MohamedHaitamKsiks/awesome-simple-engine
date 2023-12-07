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
def compileEngineFor(plarform) -> int:
    #engine path
    enginePath = os.getcwd()
    #cmake toolchains path
    cmakeToolChainsPath = str(pathlib.Path(enginePath).parent) + "/cli/asengineCLI/resources/cmake-toolchains"
    print(cmakeToolChainsPath)
    #create build folder
    buildFolderPath = "build/lib/" + plarform
    os.makedirs(buildFolderPath, exist_ok=True)
    #compile the engine
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

#compile engine given arguments (os)
def compile(platforms: list[str]) -> int:
    os.chdir("asengine")

    #generate include
    generateIncludeFiles()

    #compile the engine
    compilationResult = 0
    for platform in platforms:
        compilationResult |= compileEngineFor(platform)

    os.chdir("..")

    return compilationResult

#main
if __name__ == "__main__":
    sys.exit(compile(sys.argv[1:]) % 255)        