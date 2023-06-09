#!/bin/sh
#setup work enviroment

#link engine to android project
ln -sf "$PWD/asengine" platforms/android/app/src/main/cpp
ln -sf "$PWD/project-template/objects" platforms/android/app/src/main/cpp
ln -sf "$PWD/project-template/assets" platforms/android/app/src/main

#link engine to desktop project
ln -sf "$PWD/asengine" platforms/desktop/src
ln -sf "$PWD/project-template/objects" platforms/desktop/src
ln -sf "$PWD/project-template/assets" platforms/desktop/build