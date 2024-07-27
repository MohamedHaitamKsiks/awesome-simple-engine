python3 build.py $2 release
cd demos
cd $1
asengine-cli build $2 release
