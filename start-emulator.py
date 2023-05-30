# run emulator
import os
import json

# get working directory
workingDirectory = os.getcwd()

# read config
config = {}
with open("build.config.json") as file:
    config = json.loads(file.read())

# find sdk tools
sdkPath = config["android"]["sdkPath"]
emulatorPath = f"{sdkPath}/tools"
avdName = config["android"]["avdName"]

#start emulator
os.chdir(emulatorPath)
os.system(f"./emulator @{avdName}")
os.chdir(workingDirectory)
