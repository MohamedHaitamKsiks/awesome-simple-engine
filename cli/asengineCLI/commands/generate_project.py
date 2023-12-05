import os
import sys
import shutil
from asengineCLI.commands.script_path import *
from asengineCLI.commands.generate_module import generateModule


def generateProject(projectName: str, projectTemplatePath: str):
    # generate projects
    shutil.copytree(projectTemplatePath, projectName)

    #create game module
    os.chdir(projectName)
    os.chdir("src")

    os.mkdir("modules")

    projectModuleName = f"{projectName}Module"
    os.mkdir(projectModuleName)
    os.chdir(projectModuleName)
    generateModule(projectModuleName)

if __name__ == "__main__":
    # arguments: project name
    assert(len(sys.argv) == 2)
    projectName = sys.argv[1]

    generateProject(projectName, relativeToScriptPath("../resources/project_template"))