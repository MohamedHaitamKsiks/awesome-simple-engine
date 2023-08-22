import os
import pathlib

scriptFolder = str(pathlib.Path(__file__).parent);

with open(f"{scriptFolder}/documentation.txt", "r") as docFile:
    print(docFile.read())