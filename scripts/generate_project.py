import os
import sys
import shutil

# project template path
projectTemplatePath = "project-template"

# arguments: project name
assert(len(sys.argv) == 2)
projectName = sys.argv[1]

# generate projects
shutil.copytree(projectTemplatePath, projectName)