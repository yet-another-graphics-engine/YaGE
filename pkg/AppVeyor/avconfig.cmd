@echo off
setlocal enabledelayedexpansion
rem This script runs on AppVeyor builder for preparing environment

rem Configure environment (install GTK)
echo "Installing GTK ..."
if not exist C:\GTK (
    echo "Downloading GTK..."
    curl -O http://win32builder.gnome.org/gtk+-bundle_3.6.4-20130921_win32.zip
    echo "Extracting GTK ..."
    7z x gtk+-bundle_3.6.4-20130921_win32.zip -oC:\GTK > nul
    echo "Configuring GTK ..."
    C:\GTK\bin\gdk-pixbuf-query-loaders.exe > C:\GTK\lib\gdk-pixbuf-2.0\2.10.0\loaders.cache
)
echo "Preparing Cygwin packages ..."
C:\cygwin\setup-x86.exe -qnNdO -R C:/cygwin -s http://cygwin.mirror.constant.com -P libgtk3-devel -P cmake -P libgstreamer0.10-devel
