import os
import pathlib

def compileShader(shaderFile: str, glslangPath: str) -> int:
    spirvShaderFile = shaderFile + '.spv'

    if not os.path.isfile(spirvShaderFile) or os.path.getmtime(spirvShaderFile) < os.path.getmtime(shaderFile):
        return os.system(f"{glslangPath} -V -o {spirvShaderFile} {shaderFile}")
    
    return 0

def scanAndCompileShaders(shaderDirectory: str, glslangPath: str) -> int:
    scanPath = pathlib.Path(shaderDirectory)
    errorCode = 0

    #scan vertex shaders
    for shaderFile in scanPath.glob("**/*.vert"):
        errorCode |= compileShader(str(shaderFile), glslangPath)

    #scan fragment shaders
    for shaderFile in scanPath.glob("**/*.frag"):
        errorCode |= compileShader(str(shaderFile), glslangPath)


    return errorCode