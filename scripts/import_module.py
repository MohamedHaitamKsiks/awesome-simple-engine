import os
import sys
import shutil
import pathlib

# project template path
engineRootFolder = str(pathlib.Path(__file__).parent.parent);
modulesPath = engineRootFolder + "/modules"

# arguments: project name
assert(len(sys.argv) == 2)
moduleName = sys.argv[1]

# import module
shutil.copytree(f"{modulesPath}/{moduleName}/src", f"src/modules/{moduleName}")
