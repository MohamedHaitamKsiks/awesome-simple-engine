import os
import sys

def generateResourceCode(name: str) -> tuple[str, str]:
    #guard
    guardFlag = f"ASENGINE_RESOURCE_{name.upper()}_H"

    # generate header code
    headerCode = f'''#ifndef {guardFlag}
#define {guardFlag}

#include "ASEngine.h"

using namespace ASEngine;

class {name} : public Resource
{'{'}
public:
    {name}();
    ~{name}();

private:
    // ...
{'}'};

#endif // {guardFlag}
'''

    #generate source code
    sourceCode = f'''#include "{name}.h"

{name}::{name}()
{'{'}
    // write code ...
{'}'}

{name}::~{name}()
{'{'}
    // write code ...
{'}'}

// serialization
template <>
Json Serializer<{name}>::Serialize(const {name} &value)
{'{'}
    return Json({'{}'});
{'}'}

template <>
void Serializer<{name}>::Deserialize(const Json &object, {name} &dest)
{'{'}
    // write code ...
{'}'}
'''

    return headerCode, sourceCode

def generateResource(name: str):
    headerCode, sourceCode = generateResourceCode(name)

    #save header code
    with open(f"{resourceName}.h", "w") as resourceFile:
        resourceFile.write(headerCode)

    #save source code
    with open(f"{resourceName}.cpp", "w") as resourceFile:
        resourceFile.write(sourceCode)


if __name__ == "__main__":
    assert(len(sys.argv) == 2)

    resourceName = sys.argv[1]
    generateResource(resourceName)



