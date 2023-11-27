from commands.script_path import *

def showDocumentation(documentationPath: str):
    with open(documentationPath, "r") as docFile:
        print(docFile.read())

if __name__ == "__main__":
    showDocumentation(relativeToScriptPath("../resources/documentation.txt"))