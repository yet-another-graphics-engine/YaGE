# AppVeyor Cygwin build script

export PATH=/usr/local/bin:/usr/bin
cd `dirname $0`/../../

mkdir build-cygwin
cd build-cygwin

echo Configuring for Cygwin ...
cmake .. -G "Unix Makefiles"

echo Building for Cygwin ...
make

cd ..
mkdir -p build-bin/build-cygwin

echo Copying to binary directory
cp -r build-cygwin/bin/ build-bin/build-cygwin
cp -r build-cygwin/lib/ build-bin/build-cygwin

echo Packing files
tar czvf build-bin.tar.gz build-bin
