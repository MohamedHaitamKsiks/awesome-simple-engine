# run emulator
import os
import json
from commands.script_path import *

def startAndroidEmulator(configPath: str):
    # get working directory
    workingDirectory = os.getcwd()

    # read config
    config = {}
    with open(configPath) as file:
        config = json.loads(file.read())

    # find sdk tools
    sdkPath = config["targets"]["android"]["sdkPath"]
    emulatorLocalPath = config["targets"]["android"]["emulatorPath"]
    emulatorPath = relativeTo(sdkPath, {emulatorLocalPath})
    avdName = config["targets"]["android"]["avdName"]

    #start emulator
    os.chdir(emulatorPath)
    os.system(f"./emulator @{avdName}")
    os.chdir(workingDirectory)

if __name__ == "__main__":
    startAndroidEmulator(relativeToScriptPath("../resources/build.config.json"))
