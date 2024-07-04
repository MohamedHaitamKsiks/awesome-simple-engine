import os
import sys
import pathlib
import shutil

# generate module name in working dir
def generateModule(moduleName: str):
     # generate module
    os.mkdir(moduleName)
    os.chdir(moduleName)

    os.mkdir("demos")
    os.mkdir("src")

    # generate source files
    os.chdir("src")

    #guard
    guardName = f"__ASENGINE_MODULE_{ moduleName.upper() }_H"

    #header file
    headerContent = f"""#ifndef {guardName}
#define {guardName}

#include "ASEngine.h"

using namespace ASEngine;

class { moduleName } : public IModule
{ '{' }
    void Registry() override;
{ '}' };

#endif // { moduleName }
"""
    #save file
    with open(f"{ moduleName }.h", "w") as moduleFile:
        moduleFile.write(headerContent)

    #source file
    sourceContent = f'''#include "{ moduleName }.h"

void {moduleName}::Registry() 
{'{'}
    // regiter systems, components and resource types
{'}'}
'''
    with open(f"{ moduleName }.cpp", "w") as moduleFile:
        moduleFile.write(sourceContent)

    #cmake
    cmakeContent = f"""cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)

project({ moduleName })

add_library(
    { moduleName }
    STATIC
    { moduleName }.cpp
    # add source files ...
)

target_link_libraries(
    { moduleName }
)"""
    with open("CMakeLists.txt", "w") as cmakeFile:
        cmakeFile.write(cmakeContent) 


if __name__ == "__main__":
    # arguments: module name
    assert(len(sys.argv) == 2)
    moduleName = sys.argv[1]

    generateModule(moduleName)

