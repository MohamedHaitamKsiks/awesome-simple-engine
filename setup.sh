#!/bin/sh
#setup work enviroment

#link engine to android project
ln -sf "$PWD/engine" platforms/android/app/src/main/cpp
ln -sf "$PWD/freetype" platforms/android/app/src/main/cpp
ln -sf "$PWD/project-template/objects" platforms/android/app/src/main/cpp
ln -sf "$PWD/project-template/assets" platforms/android/app/src/main