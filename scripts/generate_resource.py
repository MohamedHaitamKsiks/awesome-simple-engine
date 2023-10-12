import os
import sys

assert(len(sys.argv) == 2)

#get comoponent name
resourceName = sys.argv[1]

# generate code
headerCode = f'''#ifndef RESOURCE_{resourceName.upper()}_H
#define RESOURCE_{resourceName.upper()}_H

#include "ASEngine.h"

using namespace ASEngine;

class {resourceName} : public Resource
{'{'}
public:
    {resourceName}();
    ~{resourceName}();

private:
    // ...
{'}'};

#endif // RESOURCE_{resourceName.upper()}_H
'''

#save header code
with open(f"resources/{resourceName}.h", "w") as resourceFile:
    resourceFile.write(headerCode)

sourceCode = f'''#include "{resourceName}.h"

{resourceName}::{resourceName}()
{'{'}
    // write code ...
{'}'}

{resourceName}::~{resourceName}()
{'{'}
    // write code ...
{'}'}

// serialization
template <>
Json Serializer<{resourceName}>::Serialize(const {resourceName} &value)
{'{'}
    return Json({'{}'});
{'}'}

template <>
void Serializer<{resourceName}>::Deserialize(const Json &object, {resourceName} &dest)
{'{'}
    // write code ...
{'}'}
'''

#save source code
with open(f"resources/{resourceName}.cpp", "w") as resourceFile:
    resourceFile.write(sourceCode)
