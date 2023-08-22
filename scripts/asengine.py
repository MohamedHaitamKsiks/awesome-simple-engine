#! /usr/bin/python3

#imports...
import sys
import os
import pathlib

#script folder
scriptFolder = str(pathlib.Path(__file__).parent)

#get command
argumentNumber = len(sys.argv)
assert(argumentNumber >= 2)

command = sys.argv[1]

#execute command

if command == "help":
    os.system(f"python3 {scriptFolder}/help.py")

elif command == "status":
    os.system(f"python3 {scriptFolder}/status.py {os.getcwd()}")
    
elif command == "run":
    os.system(f"python3 {scriptFolder}/build_project.py {os.getcwd()} linux debug")

elif command == "build":
    assert(argumentNumber == 4)
    platform = sys.argv[2]
    mode = sys.argv[3]
    os.system(f"python3 {scriptFolder}/build_project.py {os.getcwd()} {platform} {mode}")

elif command == "generate-project":
    assert(argumentNumber == 3)
    projectName = sys.argv[2]
    os.system(f"python3 {scriptFolder}/generate_project.py {projectName}")


elif command == "generate-component":
    assert(argumentNumber == 3)
    componentName = sys.argv[2]
    os.system(f"python3 {scriptFolder}/generate_component.py {componentName} {os.getcwd()}")

elif command == "generate-system":
    assert(argumentNumber == 3)
    systemName = sys.argv[2]
    os.system(f"python3 {scriptFolder}/generate_system.py {systemName} {os.getcwd()}")

#os.system(f"python3 {scriptFolder}/build_project.py test-project linux debug")
