@echo off
setlocal enabledelayedexpansion
rem This script runs on AppVeyor builder for building YaGE

rem Variables used for iteration
set generator1="Visual Studio 12 2013"
set generator2="Visual Studio 11 2012"
set generator3="Visual Studio 10 2010"
set generator4="Visual Studio 9 2008"

set builddir1=build-vc12
set builddir2=build-vc11
set builddir3=build-vc10
set builddir4=build-vc9

set PATH=C:\GTK\bin;C:\Doxygen;C:\QINIU;%PATH%

set buildno=1
:build
if %buildno% leq 4 (
    set /a buildno+=1
    rem note that buildno variable is pre-evaled in block
    md !builddir%buildno%!
    cd !builddir%buildno%!
    echo "Configuring for !generator%buildno%! ..."
    cmake .. -G !generator%buildno%!
    echo "Building for !generator%buildno%! (Debug, Release) ..."
    cmake --build . --config Debug -- /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"
    cmake --build . --config Release -- /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"
    cd ..
    md build-bin\!builddir%buildno%!
    echo "Copying built files to binary directory"
    xcopy /s !builddir%buildno%!\bin build-bin\!builddir%buildno%!\bin\
    xcopy /s !builddir%buildno%!\lib build-bin\!builddir%buildno%!\lib\
    goto build
)

C:\MinGW\msys\1.0\bin\sh.exe --login %cd%\pkg\AppVeyor\avmingw.sh

:: C:\Cygwin\bin\sh.exe --login %cd%\pkg\AppVeyor\avcygwin.sh

echo Building NSIS installer for YaGE

"C:\Program Files (x86)\NSIS\makensis.exe" /V3 pkg\NSIS\yage.nsi

echo Uploading to private server
curl -T build-bin.tar.gz -u %ftpinfo%:%ftpinfo% ftp://kirito.me:21212/build-%RANDOM%.tar.gz
curl -T pkg\NSIS\yageinst.exe -u %ftpinfo%:%ftpinfo% ftp://kirito.me:21212/yageinst-%RANDOM%.exe

C:\MinGW\msys\1.0\bin\sh.exe --login %cd%\pkg\AppVeyor\avupload.sh
