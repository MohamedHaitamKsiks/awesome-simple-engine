#!/bin/bash
# compile the engine
cd asengine
python3 build.py
cd ..

cp -r platforms cli/asengine/resources/platforms
cp -r project_template cli/asengine/resources/project_template

CLI_ASENGINE_PATH="cli/asengine/resources/asengine"

#create asengine folder in cli
rm -r $CLI_ASENGINE_PATH
mkdir -p $CLI_ASENGINE_PATH

# copy include
mkdir -p "${CLI_ASENGINE_PATH}/build"
cp -r asengine/build/include "${CLI_ASENGINE_PATH}/build/include"

#copy lib
mkdir -p "${CLI_ASENGINE_PATH}/build/lib"
mkdir -p "${CLI_ASENGINE_PATH}/build/lib/linux"
mkdir -p "${CLI_ASENGINE_PATH}/build/lib/windows"

cp asengine/build/lib/linux/asengine.a "${CLI_ASENGINE_PATH}/build/lib/linux/asengine.a"
cp asengine/build/lib/windows/asengine.a "${CLI_ASENGINE_PATH}/build/lib/windows/asengine.a"

#copy source code
cp -r asengine/engine "${CLI_ASENGINE_PATH}/src"

#reinstall/install cli
cd cli
pip install -e .
cd ..

# run tests
cd tests
asengine-cli run
cd ..