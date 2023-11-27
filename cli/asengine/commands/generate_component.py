import os
import sys

def generateComponentCode(name: str) -> tuple[str, str]:
    #header gard
    guardFlag = f"ASENGINE_COMPONENT_{name.upper()}_H"

    #header code
    headerCode = f"""#ifndef {guardFlag}
#define {guardFlag}

#include "ASEngine.h"

using namespace ASEngine;

struct {name}: public TComponent<{name}>
{'{'}
    // add data fields...
{'}'};

#endif // {guardFlag}
"""
    
    #source code
    sourceCode = f"""#include "{name}.h"

EXPORT({name}, /*fields...*/)
"""
    return headerCode, sourceCode

def generateComponent(name: str):
    # generate code
    headerCode, sourceCode = generateComponentCode(name)

    #save header code
    with open(f"{name}.h", "w") as componentFile:
        componentFile.write(headerCode)

    #save source code
    with open(f"{name}.cpp", "w") as componentFile:
        componentFile.write(sourceCode)

#main
if __name__ == "__main__":
    assert(len(sys.argv) == 2)

    #get comoponent name
    componentName = sys.argv[1]
    generateComponent(componentName)

