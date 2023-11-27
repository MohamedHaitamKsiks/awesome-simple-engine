import os
import sys

def generateSystemCode(name: str) -> tuple[str, str]:
    #header gard
    guardFlag = f"ASENGINE_SYSTEM_{name.upper()}_H"

    #header code
    headerCode = f"""#ifndef {guardFlag}
#define {guardFlag}

#include "ASEngine.h"

using namespace ASEngine;

class {name}: public ISystem
{'{'}
public:
    // ...

private:
    void OnCreate();
    void OnUpdate(float delta);
    void OnFixedUpdate(float delta);
    void OnRender2D();
    void OnUIRender2D();
    void OnInputEvent(const InputEvent& event);
{'}'};

#endif // {guardFlag}
"""
    
    #source code
    sourceCode = f"""#include "{name}.h"

void {name}::OnCreate()
{'{'}
    // insert code...
{'}'}

void {name}::OnUpdate(float delta)
{'{'}
    // insert code...
{'}'}

void {name}::OnFixedUpdate(float delta)
{'{'}
    // insert code...
{'}'}

void {name}::OnRender2D()
{'{'}
    // insert code...
{'}'}

void {name}::OnUIRender2D()
{'{'}
    // insert code...
{'}'}

void {name}::OnInputEvent(const InputEvent& event)
{'{'}
    // insert code...
{'}'}
"""
    return headerCode, sourceCode

def generateSystem(name: str):
    # generate code
    headerCode, sourceCode = generateSystemCode(name)

    #save header code
    with open(f"{name}.h", "w") as systemFile:
        systemFile.write(headerCode)

    #save source code
    with open(f"{name}.cpp", "w") as systemFile:
        systemFile.write(sourceCode)

if __name__ == "__main__":
    #main
    assert(len(sys.argv) == 2)

    #get comoponent name
    systemName = sys.argv[1]
    
    generateSystem(systemName)
