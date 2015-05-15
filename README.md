# YaGE (Yet Another Graphics Engine)

## 介绍

YaGE 是一套基于 Cairo / GTK+ 的跨平台图形库。

## 状态

Windows 静态库：[![Build status](https://img.shields.io/appveyor/ci/xdqi/yage.svg)](https://ci.appveyor.com/project/xdqi/yage)

Linux 静态库：[![Build Status](https://img.shields.io/travis/yet-another-graphics-engine/YaGE.svg)](https://travis-ci.org/yet-another-graphics-engine/YaGE)

## 许可证

[![LGPL v3](https://www.gnu.org/graphics/lgplv3-147x51.png)](https://www.gnu.org/licenses/)

## 编译方法

### Microsoft Windows

#### 使用 Microsoft Visual Studio

本项目使用了 C++ 11，请确认你安装了 Visual Studio 2012 或以上版本。

下载安装 [CMake](http://www.cmake.org/download/) (Win32 Installer) 和 [GTK+ 3](http://www.gtk.org/download/win32.php) (All-in-one bundles) 并添加其中 `bin` 目录到系统 `PATH` 变量。

安装后，启动 Visual Studio 命令行(32 位)后，切换到本项目根目录

```
X:\> cd YaGE
X:\YaGE> md build
X:\YaGE> cd build
X:\YaGE\build> cmake ..
```

使用以上命令在项目 `build` 文件夹下生成 Visual Studio 解决方案。

最后打开 `build` 文件夹中生成的 `YaGE.sln` 进行项目的生成。

项目库文件将生成在 `build\lib` 文件夹中，名为 `yage.lib`，将其复制到 VS 安装目录的 `VC\Lib` 中即可使用。

#### 使用 MinGW / MSYS

同样的，安装 CMake 和 GTK+ 3 并添加到 `PATH`。

打开 MSYS Shell，切换到本项目根目录，执行以下命令

```
/ $ cd YaGE
/YaGE $ mkdir build
/YaGE $ cd build
/YaGE/build $ cmake .. -G "MSYS Makefiles"
/YaGE/build $ make
```

项目库文件将生成在 `build\lib` 文件夹中，名为 `libyage.a`，将其复制到 MinGW 安装目录的 `lib` 中即可使用。

### GNU/Linux

#### Debian / Ubuntu 及其衍生发行版

安装必要包

`sudo apt-get install -y build-essential git libgtk-3-dev cmake pkg-config libgstreamer-plugins-base0.10-dev`

安装后，运行以下命令

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```
项目库文件将生成在 `build/lib` 文件夹中，名为 `libyage.a`，将其复制到 `/usr/local/lib` 中即可使用。


#### RHEL / CentOS 7 及其衍生版, Fedora

安装必要包

`yum install git cmake pkgconfig gcc-c++ gtk3-devel gstreamer-devel`

安装后，运行以下命令

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```
项目库文件将生成在 `build/lib` 文件夹中，名为 `libyage.a`，将其复制到 `/usr/local/lib` 中即可使用。

#### Arch Linux

安装必要包

`sudo pacman -S gtk3 cmake pkg-config gstreamer0.10-ugly`

安装后，运行以下命令

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```
项目库文件将生成在 `build/lib` 文件夹中，名为 `libyage.a`，将其复制到 `/usr/local/lib` 中即可使用。

### Mac OS X

#### 使用 Homebrew

安装 [Xcode](https://developer.apple.com/xcode/)

安装 [Homebrew](http://brew.sh/): `ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`

安装必要包：`brew install git cmake gtk+3 cairo pkg-config`

安装后，运行以下命令

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```
项目库文件将生成在 `build/lib` 文件夹中，名为 `libyage.a`，将其复制到 `/usr/local/lib` 中即可使用。

#### 使用 MacPorts

安装 [Xcode](https://developer.apple.com/xcode/)

安装 [MacPorts](https://www.macports.org/install.php)

安装必要包：`port install git cmake gtk3 cairo pkgconfig`

安装后，运行以下命令

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```
项目库文件将生成在 `build/lib` 文件夹中，名为 `libyage.a`，将其复制到 `/usr/local/lib` 中即可使用。
