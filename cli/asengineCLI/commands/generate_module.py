import os
import sys
import pathlib
import shutil

# generate module name in working dir
def generateModule(moduleName: str):
    #generate folders
    os.mkdir("components")
    os.mkdir("systems")
    os.mkdir("resources")

    #header file
    headerContent = f"""#ifndef { moduleName.upper() }_H
#define { moduleName.upper() }_H

#include "ASEngine.h"

using namespace ASEngine;

class { moduleName } : public IModule
{ '{' }
    // register components
    void RegisterComponents();

    // register systems
    void RegisterSystems();

    // init resources managers
    void InitResourceManagers();

    // terminate resource managers
    void TerminateResourceManagers();
{ '}' };

#endif // { moduleName.upper() }_H
"""
    #save file
    with open(f"{ moduleName }.h", "w") as moduleFile:
        moduleFile.write(headerContent)

    #source file
    sourceContent = f'''#include "{ moduleName }.h"

void {moduleName}::RegisterComponents() 
{'{'}
    // register components
{'}'}

void {moduleName}::RegisterSystems()
{'{'}
    // register systems
{'}'}

void {moduleName}::InitResourceManagers()
{'{'}
    // init resource managers
{'}'}

void {moduleName}::TerminateResourceManagers()
{'{'}
    // terminate resource managers
{'}'}
'''
    with open(f"{ moduleName }.cpp", "w") as moduleFile:
        moduleFile.write(sourceContent)

    #cmake
    cmakeContent = f"""cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 23)

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

    # generate module
    os.mkdir(moduleName)
    os.chdir(moduleName)

    os.mkdir("demos")
    os.mkdir("src")

    # generate source files
    os.chdir("src")

    generateModule(moduleName)

