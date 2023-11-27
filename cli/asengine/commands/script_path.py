import os

# get director parent of a file
def dirPath(filePath: str):
    return os.path.dirname(os.path.realpath(filePath))

# get script path
def scriptPath() -> str:
    return os.path.dirname(os.path.realpath(__file__))

# get path relative to a directory
def relativeTo(dirPath: str, relativePath: str) -> str:
    return os.path.realpath(f"{dirPath}/{relativePath}")

# get path relative to the script path
def relativeToScriptPath(relativePath: str) -> str:
    return relativeTo(scriptPath(), relativePath)