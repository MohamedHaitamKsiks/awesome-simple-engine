import os
import sys

def generate_component_code(name: str):
    # list of code lines
    codeLines = []

    # generate guard
    guardFlag = f"COMPONENT_{name.upper()}_H"
    codeLines.append(f"#ifndef {guardFlag}")
    codeLines.append(f"#define {guardFlag}")

    # generate imports
    codeLines.append('\n#include "ASEngine.h"\n')
    # use asengine namespace
    codeLines.append("using namespace ASEngine;\n")

    #generate component struct
    structName = name
    codeLines.append(f"struct {structName}: public TComponent<{structName}>")
    codeLines.append("{\n\t// add fields...\n};")


    #end guard
    codeLines.append(f"\n#endif // {guardFlag}")

    return '\n'.join(codeLines)

#main
if __name__ == "__main__":
    assert(len(sys.argv) == 3)

    #get comoponent name
    componentName = sys.argv[1]

    #get project path
    projectPath = sys.argv[2]

    # generate code
    code = generate_component_code(componentName)

    #save header code
    with open(f"components/{componentName}.h", "w") as componentFile:
        componentFile.write(code)

    #save source code
    with open(f"components/{componentName}.cpp", "w") as componentFile:
        componentFile.write(f'#include "{componentName}.h"\n\nEXPORT({componentName}, /*fields...*/)')
