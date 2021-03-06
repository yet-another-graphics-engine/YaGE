@echo off
setlocal enabledelayedexpansion
rem This script runs on AppVeyor builder for preparing environment

rem Configure environment (install GTK)
if not exist C:\GTK (
    echo "Downloading GTK..."
    curl -O http://win32builder.gnome.org/gtk+-bundle_3.6.4-20130921_win32.zip
    echo "Extracting GTK ..."
    7z x gtk+-bundle_3.6.4-20130921_win32.zip -oC:\GTK > nul
    echo "Configuring GTK ..."
    C:\GTK\bin\gdk-pixbuf-query-loaders.exe > C:\GTK\lib\gdk-pixbuf-2.0\2.10.0\loaders.cache
)

if not exist "C:\Program Files (x86)\NSIS" (
    echo "Installing NSIS ..."
    choco install nsis -version 2.46.0.20150406 -y
    echo "Installing XML Plugin for NSIS"
    curl -O http://nsis.sourceforge.net/mediawiki/images/5/55/Xml.zip
    7z x Xml.zip
    copy Plugin\xml.dll "C:\Program Files (x86)\NSIS\Plugins"
    copy Include\XML.nsh "C:\Program Files (x86)\NSIS\Include"
    echo "Installing ExecDos Plugin for NSIS"
    curl -O http://nsis.sourceforge.net/mediawiki/images/0/0f/ExecDos.zip
    7z x ExecDos.zip
    copy Plugins\x86-ansi\ExecDos.dll "C:\Program Files (x86)\NSIS\Plugins"
)

if not exist "C:\Doxygen" (
    md C:\Doxygen
    echo "Installing Doxygen"
    curl -O http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.10.windows.x64.bin.zip
    7z x doxygen-1.8.10.windows.x64.bin.zip
    copy doxygen.exe C:\Doxygen
)

if not exist "C:\QINIU" (
    md C:\QINIU
    echo "Installing Qiniu development tools"
    curl -O -L http://devtools.qiniu.io/qiniu-devtools-windows_amd64-current.zip
    7z x qiniu-devtools-windows_amd64-current.zip
    copy qrsctl.exe C:\QINIU
)

:: echo "Preparing Cygwin packages ..."
:: C:\cygwin\setup-x86.exe -qnNdO -R C:/cygwin -s http://cygwin.mirror.constant.com -P libgtk3-devel -P cmake -P libgstreamer0.10-devel
