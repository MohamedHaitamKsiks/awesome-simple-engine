import os
import sys
import json
import shutil
from asengineCLI.commands.script_path import *
from asengineCLI.commands.generate_module import generateModule


def generateProject(projectName: str, configPath: str):
    config = {}
    with open(configPath) as file:
        config = json.loads(file.read())
    projectTemplatePath = config["projectTemplatePath"]
    # generate projects
    shutil.copytree(projectTemplatePath, projectName)
