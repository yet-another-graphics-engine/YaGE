# YaGE (Yet Another Graphics Engine)

[中文](https://github.com/yet-another-graphics-engine/YaGE/blob/master/README-zh.md)

## Intro

YaGE is a cross-platform graphics library based on Cairo / GTK+. It works under windows, linux and macos.
Based on this graphics library, one can write graphic programs using turbo-c like interfaces.

for example, to draw a circle at point (100,200) with radius 50:

    #include <graphics.h>
    int main() {
      initgraph();
      circle(100,200,50);
      closegraph();
    }

## Status

Windows static library: [![Build status](https://img.shields.io/appveyor/ci/xdqi/yage.svg)](https://ci.appveyor.com/project/xdqi/yage)

Linux static library: [![Build Status](https://img.shields.io/travis/yet-another-graphics-engine/YaGE.svg)](https://travis-ci.org/yet-another-graphics-engine/YaGE)

## License

[![LGPL v3](https://www.gnu.org/graphics/lgplv3-147x51.png)](https://www.gnu.org/licenses/)

## Build

### Microsoft Windows

#### Build with Microsoft Visual Studio

Because C++ 11 is used in the project, make sure that you has installed install Visual Studio 2012 or later.

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

### GNU/Linux

#### Debian / Ubuntu and its derivatives

Install neccessary packages:

`sudo apt-get install -y build-essential git libgtk-3-dev cmake pkg-config libgstreamer-plugins-base0.10-dev`

Execute following command after installation:

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Library will be built in `build/lib` directory called `libyage.a`, copy it to `/usr/local/lib` to use it. After that, copy everything in `include` directory to `/usr/local/include` directory to use headers.


#### RHEL / CentOS 7 and its its derivatives, Fedora

Install neccessary packages:

`sudo yum install git cmake pkgconfig gcc-c++ gtk3-devel gstreamer-devel`

Execute following command after installation:

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Library will be built in `build/lib` directory called `libyage.a`, copy it to `/usr/local/lib` to use it. After that, copy everything in `include` directory to `/usr/local/include` directory to use headers.

#### Arch Linux

Install neccessary packages:

`sudo pacman -S gtk3 cmake pkg-config gstreamer0.10-ugly`

Execute following command after installation:

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Library will be built in `build/lib` directory called `libyage.a`, copy it to `/usr/local/lib` to use it. After that, copy everything in `include` directory to `/usr/local/include` directory to use headers.

### Mac OS X

#### Use Homebrew

Install [Xcode](https://developer.apple.com/xcode/).

Install [Homebrew](http://brew.sh/): `ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`.

Install neccessary packages: `brew install git cmake gtk+3 cairo pkg-config`

Execute following command after installation:

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Library will be built in `build/lib` directory called `libyage.a`, copy it to `/usr/local/lib` to use it. After that, copy everything in `include` directory to `/usr/local/include` directory to use headers.

#### Use MacPorts

Install [Xcode](https://developer.apple.com/xcode/).

Install [MacPorts](https://www.macports.org/install.php).

Install neccessary packages: `sudo port install git cmake gtk3 cairo pkgconfig`

Execute following command after installation:

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Library will be built in `build/lib` directory called `libyage.a`, copy it to `/usr/local/lib` to use it. After that, copy everything in `include` directory to `/usr/local/include` directory to use headers.
