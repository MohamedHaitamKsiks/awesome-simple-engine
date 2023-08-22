import sys
import os

assert(len(sys.argv) == 2)
projectPath = sys.argv[1]

requirements = [
    "assets",
    "src",
    "src/CMakeLists.txt",
    "src/components",
    "src/systems",
    "src/registry.h",
    "src/registry.cpp",
    "assets/project.settings.json",
]

for requirement in requirements:
     if not os.path.exists(f"{projectPath}/{requirement}"):
        print(f"Missing {requirement}")
        exit()

print("OK")