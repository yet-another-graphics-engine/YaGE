# AppVeyor MinGW/MSYS build script

mount C:\MinGW /mingw
export PATH=/usr/local/bin:/mingw/bin:/bin:/c/mingw/bin:$PATH
cd `dirname $0`/../../

mkdir build-mingw
cd build-mingw

echo Configuring for MinGW/MSYS ...
cmake .. -G "MSYS Makefiles"

echo Building for MinGW/MSYS ...
make

cd ..
mkdir -p build-bin/build-mingw

echo Copying to binary directory
cp -r build-mingw/bin/ build-bin/build-mingw
cp -r build-mingw/lib/ build-bin/build-mingw
