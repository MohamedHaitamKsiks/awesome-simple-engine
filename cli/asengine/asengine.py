#! /usr/bin/python3

#imports...
import sys

from commands.generate_project import generateProject
from commands.generate_component import generateComponent
from commands.generate_module import generateModule
from commands.generate_system import generateSystem
from commands.generate_resource import generateResource
from commands.documentation import showDocumentation
from commands.status import getProjectStatus
from commands.build_project import buildProject
from commands.script_path import *


def executeCommand(command: str, args: list[str] = []):
    scriptPath = dirPath(__file__)
    
    match command:
        case "help":
            showDocumentation(relativeTo(scriptPath, "./resources/documentation.txt"))

        case "status":
            getProjectStatus("./")

        case "run":
            buildProject(relativeTo(scriptPath, "./resources/build.config.json"), ".", "linux")

        case "build":
            assert(len(args) == 1)
            buildProject(relativeTo(scriptPath, "./resources/build.config.json"), ".", args[0])

        case "generate-project":
            assert(len(args) == 1)
            generateProject(args[0], relativeTo(scriptPath, "./resources/project_template"))

        case "generate-component":
            assert(len(args) == 1)
            generateComponent(args[0])

        case "generate-system":
            assert(len(args) == 1)
            generateSystem(args[0])

        case "generate-module":
            assert(len(args) == 1)
            generateModule(args[0])

        case "genetate-resource":
            assert(len(args) == 1)
            generateResource(args[0])

        case _:
            print(f"The command '{command}' is invalid!\n")
            showDocumentation(relativeTo(scriptPath, "./resources/documentation.json"))

def main():
    #get command
    argumentNumber = len(sys.argv)
    assert(argumentNumber >= 2)

    command = sys.argv[1]
    executeCommand(command, args=sys.argv[2:])

if __name__ == "__main__":
    main()


