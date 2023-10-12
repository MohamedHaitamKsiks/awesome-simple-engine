import os
import sys
import shutil
import pathlib
from generate_module import generateModuleFiles

scriptFolder = str(pathlib.Path(__file__).parent)

# project template path
engineRootFolder = str(pathlib.Path(__file__).parent.parent);
projectTemplatePath = engineRootFolder + "/project-template"

# arguments: project name
assert(len(sys.argv) == 2)
projectName = sys.argv[1]

# generate projects
shutil.copytree(projectTemplatePath, projectName)

#create game module
os.chdir(projectName)
os.chdir("src")

os.mkdir("modules")

projectModuleName = f"{projectName}Module"
os.mkdir(projectModuleName)
os.chdir(projectModuleName)
generateModuleFiles(projectModuleName)