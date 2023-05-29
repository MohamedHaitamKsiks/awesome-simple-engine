#build a porject to the platform given by the user
import sys
import os
import shutil

#expect 3 arguments
assert(len(sys.argv) == 3)

#get project path
projectPath = sys.argv[1]

#get platform
platform = sys.argv[2]

#check platform validity
assert(platform in ("windows", "linux", "android"))

#remove .tmp if exists
if ".tmp" in os.listdir(os.getcwd()):
    shutil.rmtree(".tmp")

#craete and copy platfrom to .tmp
shutil.copytree(f"platforms/{ platform }", ".tmp")

#copy project + engine + dependencies to .tmp
if platform == "android":
    shutil.copytree("engine", ".tmp/app/src/main/cpp/engine")
    
