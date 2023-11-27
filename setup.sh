#!/bin/bash
# setup asengine workspace
./build.sh
mkdir -p cli/asengine/resources/asengine
cp -r asengine/build cli/asengine/resources/asengine/build
cp -r asengine/engine cli/asengine/resources/asengine/src