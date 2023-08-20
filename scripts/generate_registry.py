import pathlib
import os

def save_if_changed(filePath, value):
    #read registry code
    original = ""
    with open(filePath, "r") as file:
        original = file.read()
    
    #save registry code
    if original == value:
        return
    
    with open(filePath, "w") as file:
        file.write(value)


def generate_registry(projectPath: str):

    #registry code start
    registryIncludeCode = []

    registrySourceCode = ['#include "registry.h"']
    registrySourceCode.append("\nvoid ECSRegistry()")
    registrySourceCode.append("{")

    #components
    componentsPath = pathlib.Path(f"{projectPath}/src/components")
    componentsFileList = list(componentsPath.rglob("*.h"))
    
    for componentFile in componentsFileList:
        componentName = componentFile.name.split(".")[0]
        componentString = '"' + componentName + '"'
        componentFileString = '"components/' + str(componentFile.relative_to(f"{projectPath}/src/components")) + '"'

        registryIncludeCode.append(f"#include {componentFileString}")
        registrySourceCode.append(f"\tComponentManager::RegisterComponent<{componentName}>(UniqueString({ componentString }));")

    #systems
    systemsPath = pathlib.Path(f"{projectPath}/src/systems")
    systemsFileList = list(systemsPath.rglob("*.h"))
    
    for systemFile in systemsFileList:
        systemName = systemFile.name.split(".")[0]
        systemFileString = '"systems/' + str(systemFile.relative_to(f"{projectPath}/src/systems")) + '"'

        registryIncludeCode.append(f"#include {systemFileString}")
        registrySourceCode.append(f"\tSystemManager::RegisterSystem<{systemName}>();")

    registrySourceCode.append("}")

    registryHeaderCode = ["#ifndef ASENGINE_ECS_REGISTRY_H"]
    registryHeaderCode.append("#define ASENGINE_ECS_REGISTRY_H\n")

    registryHeaderCode.append('#include "ASEngine.h"')
    registryHeaderCode.append("using namespace ASEngine;\n")

    registryHeaderCode += registryIncludeCode

    registryHeaderCode.append("\n// register ecs\nvoid ECSRegistry();\n")
    registryHeaderCode.append("#endif")

    #read registry code
    save_if_changed(f"{projectPath}/src/registry.h", '\n'.join(registryHeaderCode))
    save_if_changed(f"{projectPath}/src/registry.cpp", '\n'.join(registrySourceCode))
    

if __name__ == "__main__":
    generate_registry("test-project")