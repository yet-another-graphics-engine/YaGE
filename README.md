# YaGE (Yet Another Graphics Engine)

[中文](https://github.com/yet-another-graphics-engine/YaGE/blob/master/README-zh.md)

## Intro

YaGE is a cross-platform graphics library based on Cairo / GTK+.

## Status

|Windows|Linux|OS X|
|------|-------|----|
|[![Build status](https://img.shields.io/appveyor/ci/xdqi/yage.svg)](https://ci.appveyor.com/project/xdqi/yage)|[![Build Status](https://img.shields.io/travis/yet-another-graphics-engine/YaGE.svg)](https://travis-ci.org/yet-another-graphics-engine/YaGE)|[![Build Status](https://img.shields.io/jenkins/s/https/ci.kirito.me/YaGE.svg)](https://ci.kirito.me/job/YaGE/)|

## License

[![LGPL v3](https://www.gnu.org/graphics/lgplv3-147x51.png)](https://www.gnu.org/licenses/)

## Installation

### Ubuntu and its derivatives

```
sudo apt-get install software-properties-common  # or python-software-properties for Ubuntu 12.04
sudo add-apt-repository ppa:qxd/yage
sudo apt-get update
sudo apt-get install yage
```

### Arch Linux

```
yaourt -S yage
```
or you can install `yage` from AUR manually.

### Mac OS X via Homebrew

```
brew tap yet-another-graphics-engine/yage
brew install --HEAD yage
```

## Build

### Microsoft Windows

#### Build with Microsoft Visual Studio

Because variadic macros are used in the project, make sure that you have installed install Visual Studio 2005 or later. (Express version of Visual C++ is also OK.)

Install [CMake](http://www.cmake.org/download/) (Win32 Installer) and [GTK+ 3](http://www.gtk.org/download/win32.php) (All-in-one bundles), add the `bin` directory of CMake and GTK+ 3 into `PATH` environment variable.

After installation, launch `VS201? x86 Native Tools Command Prompt`, switch to the root directory of YaGE, then run following command:

```
X:\> cd YaGE
X:\YaGE> md build
X:\YaGE> cd build
X:\YaGE\build> cmake ..
```

The command above will generate Visual Studio Solution inside `build` folder.

Finally, open `YaGE.sln` solution in `build` folder to build the library.

Library will be built in `build\lib` directory called `yage.lib`, copy it to `VC\lib` directory in VS installation folder to use it. After that, copy everything in `include` directory to `include` directory in VS installation folder to use headers.

#### Build with MinGW / MSYS

Similarly, install CMake and GTK+ 3 and add them into `PATH`.

Open MSYS Shell, switch to the project root directory, execute the following command:

```
/ $ cd YaGE
/YaGE $ mkdir build
/YaGE $ cd build
/YaGE/build $ cmake .. -G "MSYS Makefiles"
/YaGE/build $ make
```

Library will be built in `build/lib` directory called `libyage.a`, copy it to `lib` directory in MinGW installation folder to use it. After that, copy everything in `include` directory to `include` directory in MinGW installation folder to use headers.

#### Build with Cygwin

Open Cygwin installer and install following packages:

`git make gcc-g++ cmake libgtk3-devel pkg-config libgstreamer0.10-devel`

Then follow UNIX build instructions

### UNIX and UNIX-like Systems

#### Install Dependencies

##### Debian / Ubuntu and derivatives

`sudo apt-get install -y build-essential git libgtk-3-dev cmake pkg-config libgstreamer-plugins-base0.10-dev`

##### RHEL / CentOS 7 and derivatives, Fedora 21 and earlier

`sudo yum -y install git cmake pkgconfig gcc-c++ gtk3-devel gstreamer-devel`

##### Fedora 22

`sudo dnf -y install git cmake pkgconfig gcc-c++ gtk3-devel gstreamer-devel`

##### Arch Linux

`sudo pacman -S base-devel git gtk3 cmake pkg-config gstreamer0.10`

##### FreeBSD 10

`sudo pkg install git cmake pkgconf gtk3 gstreamer`

##### Mac OS X via [Homebrew](http://brew.sh/)

`brew install git cmake gtk+3 cairo pkg-config`

##### Mac OS X via [MacPorts](https://www.macports.org/)

`sudo port install git cmake gtk3 cairo pkgconfig`

#### Build

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```

#### Install

```
$ sudo make install
```
