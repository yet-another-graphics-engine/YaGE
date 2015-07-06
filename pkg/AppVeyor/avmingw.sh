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

echo Building Documentation ...
make doc-chinese
make doc-english

cd ..
mkdir -p build-bin/build-mingw

echo Copying to binary directory
cp -r build-mingw/bin/ build-bin/build-mingw
cp -r build-mingw/lib/ build-bin/build-mingw
cp -r build-mingw/doc/ build-bin/

if ! [ -f "/C/Program Files (x86)/NSIS/Plugins/path.dll" ] || [ "/C/Program Files (x86)/NSIS/Plugins/path.dll" -ot "pkg/NSIS/plugin/path.c" ]
then
    cd pkg/NSIS/plugin
    make
    cp path.dll "/C/Program Files (x86)/NSIS/Plugins/"
    cd ../../..
fi

echo Packing files
tar czvf build-bin.tar.gz build-bin
