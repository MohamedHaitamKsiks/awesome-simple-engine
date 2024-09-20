#! /usr/bin/python3

#imports...
import sys

from asengineCLI.commands.generate_project import generateProject
from asengineCLI.commands.generate_component import generateComponent
from asengineCLI.commands.generate_module import generateModule
from asengineCLI.commands.generate_system import generateSystem
from asengineCLI.commands.generate_resource import generateResource
from asengineCLI.commands.documentation import showDocumentation
from asengineCLI.commands.status import getProjectStatus
from asengineCLI.commands.build_project import buildProject
from asengineCLI.commands.script_path import *

def executeCommand(command: str, args: list[str] = []) -> int:
    scriptPath = dirPath(__file__)
    error = 0

    match command:
        case "help":
            showDocumentation(relativeTo(scriptPath, "./resources/documentation.txt"))

        case "status":
            print(getProjectStatus("./"))

        case "run":
            error |= buildProject(relativeTo(scriptPath, "./resources/.asengine.config.json"), ".", "linux", False, args)

        case "build":
            assert(len(args) >= 1)
            isDebug = len(args) > 1 and args[1] == "debug"

            error |= buildProject(relativeTo(scriptPath, "./resources/.asengine.config.json"), ".", args[0], isDebug, args[2:])

        case "generate-project":
            assert(len(args) == 1)
            generateProject(args[0], relativeTo(scriptPath, "./resources/.asengine.config.json"))

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
            executeCommand("help", [])

    return error

def main() -> None:
    #get command
    argumentNumber = len(sys.argv)
    assert(argumentNumber >= 2)

    command = sys.argv[1]
    sys.exit(executeCommand(command, args=sys.argv[2:]) % 255)

if __name__ == "__main__":
    main()
