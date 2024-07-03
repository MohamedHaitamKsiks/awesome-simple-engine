import sys
import shutil
import subprocess
import os
import json

from build import compileASEngine

#create directory if not exist
def createDirectory(dirPath: str):
    if not os.path.isdir(dirPath):
        os.mkdir(dirPath)


#setup
def setup(configPath: str):
    #compile engine
    compileASEngine(["linux", "windows"])

    #read config path
    config = {}
    with open(configPath, "r") as configFile:
        config = json.load(configFile)
    
    #set paths to absolute
    config["projectTemplatePath"] = os.path.realpath(config["projectTemplatePath"])
    config["platformsPath"] = os.path.realpath(config["platformsPath"])
    config["cmakeToolchains"]["windows"] = os.path.realpath(config["cmakeToolchains"]["windows"])
    config["asengine"]["buildPath"] = os.path.realpath(config["asengine"]["buildPath"])
    config["asengine"]["sourcePath"] = os.path.realpath(config["asengine"]["sourcePath"])

    # create config
    CLI_ASENIGNE_CONFIG_PATH = "cli/asengineCLI/resources/.asengine.config.json"
    with open(CLI_ASENIGNE_CONFIG_PATH, "w") as configFile:
        json.dump(config, configFile);


    #install/reinstall cli
    os.chdir("cli")
    if subprocess.call([sys.executable, "-m", "pip", "install", "-e", "."]):
        return 1
    
    os.chdir("..")

    #run asengine's unit tests
    os.chdir("tests")
    if subprocess.call(["asengine-cli", "build", "headless"]):
        return 1
    
    os.chdir("..")
    return 0


if __name__ == "__main__":
    sys.exit(setup("asengine.default.config.json"))