import os
import sys

def generateFragmentShader(shaderFileName, type):
    pass

def generateVertexShader(shaderFileName, type):
    pass

def generateShader(shaderName, type):
    pass

#main
if __name__ == "__main__":
    assert(len(sys.argv) == 3)

    #get params
    shaderName = sys.argv[1]
    type = sys.argv[2]

    generateShader(shaderName)

