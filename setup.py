import sys
import shutil
import subprocess
import os
from build import compile

def createDirectory(dirPath: str):
    if not os.path.isdir(dirPath):
        os.mkdir(dirPath)


# setup result
setupResult = 0

# define paths
CLI_ASENGINE_PATH = "cli/asengineCLI/resources/.asengine"
CLI_ASENGINE_BUILD_PATH = CLI_ASENGINE_PATH + "/build"
CLI_ASENGINE_INCLUDE_PATH = CLI_ASENGINE_BUILD_PATH + "/include"
CLI_ASENGINE_LIB_PATH = CLI_ASENGINE_BUILD_PATH + "/lib"
CLI_ASENGINE_LIB_LINUX_PATH = CLI_ASENGINE_LIB_PATH + "/linux"
CLI_ASENGINE_LIB_WINDOWS_PATH = CLI_ASENGINE_LIB_PATH + "/windows"
CLI_ASENGINE_SOURCE_PATH = CLI_ASENGINE_PATH + "/src"

CLI_PLATFORMS_PATH = "cli/asengineCLI/resources/.platforms"
CLI_TEMPLATE_PATH = "cli/asengineCLI/resources/.project_template"

# compile the engine
setupResult |= compile(["linux"])

# copy platform & template
shutil.copytree("platforms", CLI_PLATFORMS_PATH, dirs_exist_ok=True)
shutil.copytree("project_template", CLI_TEMPLATE_PATH, dirs_exist_ok=True)

# create engine dir in cli
createDirectory(CLI_ASENGINE_PATH)

# create build
createDirectory(CLI_ASENGINE_BUILD_PATH)

# copy include
shutil.copytree("asengine/build/include", CLI_ASENGINE_INCLUDE_PATH, dirs_exist_ok=True)

# copy libs
createDirectory(CLI_ASENGINE_LIB_PATH)
createDirectory(CLI_ASENGINE_LIB_LINUX_PATH)
createDirectory(CLI_ASENGINE_LIB_WINDOWS_PATH)

shutil.copy("asengine/build/lib/linux/asengine.a", CLI_ASENGINE_LIB_LINUX_PATH + "/asengine.a")
#shutil.copy("asengine/build/lib/windows/asengine.a", CLI_ASENGINE_LIB_WINDOWS_PATH + "/asengine.a")

#copy source
shutil.copytree("asengine/engine", CLI_ASENGINE_SOURCE_PATH, dirs_exist_ok=True)

#install/reinstall cli
os.chdir("cli")
setupResult |= subprocess.call([sys.executable, "-m", "pip", "install", "-e", "."])
os.chdir("..")

#run engine's unit tests
os.chdir("tests")
setupResult |= subprocess.call(["asengine-cli", "build", "headless"])
os.chdir("..")

sys.exit(setupResult)