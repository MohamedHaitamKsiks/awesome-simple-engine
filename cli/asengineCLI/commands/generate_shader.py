import os
import sys
import shutil
import pathlib

from asengineCLI.commands.script_path import relativeTo

def generateFragmentShader(shaderFile, shaderTemplates, type):
    shaderTemplateFile = relativeTo(shaderTemplates, f"./{type}/default{type}.frag")
    shutil.copy(shaderTemplateFile, shaderFile)

def generateVertexShader(shaderFile, shaderTemplates, type):
    shaderTemplateFile = relativeTo(shaderTemplates, f"./{type}/default{type}.vert")
    shutil.copy(shaderTemplateFile, shaderFile)

def generateShader(shaderName, shaderTemplates,  type):
    assert(type in ["2D", "3D"])
    
    pathlib.Path(shaderName).mkdir(exist_ok=True) # create shader folder

    #generate glsl shaders
    generateVertexShader(f"{shaderName}/{shaderName}.vert", shaderTemplates, type)
    generateFragmentShader(f"{shaderName}/{shaderName}.frag", shaderTemplates, type)

    # craete shader resource file
    shaderResource = f'''{"{"}
    "Vertex": "{shaderName}.vert",
    "Fragment": "{shaderName}.frag"
{"}"}
'''

    with open(f"{shaderName}/{shaderName}.shader.json", "w") as shaderResourceFile:
        shaderResourceFile.write(shaderResource)

    return 0

#main
if __name__ == "__main__":
    assert(len(sys.argv) == 3)

    #get params
    shaderName = sys.argv[1]
    type = sys.argv[2]

    generateShader(shaderName)

