import os
import sys

def generate_system_header_code(name: str):
    # list of code lines
    codeLines = []

    # generate guard
    guardFlag = f"SYSTEM_{name.upper()}_H"
    codeLines.append(f"#ifndef {guardFlag}")
    codeLines.append(f"#define {guardFlag}")

    # generate imports
    codeLines.append('\n#include "ASEngine.h"\n')
    # use asengine namespace
    codeLines.append("using namespace ASEngine;\n")

    #generate system class
    structName = name
    codeLines.append(f"class {structName}: public ISystem")
    codeLines.append("{\n")

    codeLines.append("\tvoid OnCreate();")
    codeLines.append("\tvoid OnUpdate(float delta);")
    codeLines.append("\tvoid OnFixedUpdate(float delta);")
    codeLines.append("\tvoid OnRender2D();")
    codeLines.append("\tvoid OnUIRender2D();")
    codeLines.append("\tvoid OnInputEvent(const InputEvent& event);")

    codeLines.append("\n};")

    #end guard
    codeLines.append(f"\n#endif // {guardFlag}")

    return '\n'.join(codeLines)

def generate_system_source_code(name: str):
    codeLines = [f'#include "{name}.h"\n']

    codeLines.append(f"void {name}::OnCreate()")
    codeLines.append("{\n\t// insert code ...\n};\n")

    codeLines.append(f"void {name}::OnUpdate(float delta)")
    codeLines.append("{\n\t// insert code ...\n};\n")

    codeLines.append(f"void {name}::OnFixedUpdate(float delta)")
    codeLines.append("{\n\t// insert code ...\n};\n")

    codeLines.append(f"void {name}::OnRender2D()")
    codeLines.append("{\n\t// insert code ...\n};\n")

    codeLines.append(f"void {name}::OnUIRender2D()")
    codeLines.append("{\n\t// insert code ...\n};\n")

    codeLines.append(f"void {name}::OnInputEvent(const InputEvent& event)")
    codeLines.append("{\n\t// insert code ...\n};\n")

    return '\n'.join(codeLines)


if __name__ == "__main__":
    #main
    assert(len(sys.argv) == 3)

    #get comoponent name
    systemName = sys.argv[1]

    #get project path
    projectPath = sys.argv[2]

    # generate code
    headerCode = generate_system_header_code(systemName)
    sourceCode = generate_system_source_code(systemName)

    #save header code
    with open(f"systems/{systemName}.h", "w") as systemFile:
        systemFile.write(headerCode)

    #save source code
    with open(f"systems/{systemName}.cpp", "w") as systemFile:
        systemFile.write(sourceCode)
