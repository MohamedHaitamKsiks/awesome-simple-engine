import sys
import os

# returns true if projet is valid
# returns false +  if missing requirements
def getProjectIsValid(projectPath: str) -> tuple[bool, list[str]]:
    #file requirement
    requirements = [
        "assets",
        "src",
        "src/CMakeLists.txt",
        "src/registry.h",
        "src/registry.cpp",
        "assets/project.settings.json",
    ]

    isValid = True
    missingRequirements: list[str] = []

    for requirement in requirements:
        if not os.path.exists(f"{projectPath}/{requirement}"):
            isValid = False
            missingRequirements.append(requirement)
            
        
    return isValid, missingRequirements


def getProjectStatus(projectPath: str) -> str:
    isValid, missingRequirements = getProjectIsValid(projectPath)

    if isValid:
        return "OK"
    else:
        return "Missing the following requirements:\n-" + '\n-'.join(missingRequirements)

if __name__ == "__main__":
    assert(len(sys.argv) == 2)
    projectPath = sys.argv[1]

    print(getProjectStatus(projectPath))