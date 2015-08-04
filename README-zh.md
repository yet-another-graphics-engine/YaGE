# YaGE (Yet Another Graphics Engine)

## 介绍

YaGE 是一套基于 Cairo / GTK+ 的跨平台图形库。

## 状态

|Windows|Linux|OS X|
|------|-------|----|
|[![Build status](https://img.shields.io/appveyor/ci/xdqi/yage.svg)](https://ci.appveyor.com/project/xdqi/yage)|[![Build Status](https://img.shields.io/travis/yet-another-graphics-engine/YaGE.svg)](https://travis-ci.org/yet-another-graphics-engine/YaGE)|[![Build Status](https://img.shields.io/jenkins/s/https/ci.kirito.me/YaGE.svg)](https://ci.kirito.me/job/YaGE/)|

## 许可证

[![LGPL v3](https://www.gnu.org/graphics/lgplv3-147x51.png)](https://www.gnu.org/licenses/)

## 安装

### Ubuntu 及其衍生发行版

```
sudo apt-get install software-properties-common  # 或者 python-software-properties (使用 Ubuntu 12.04)
sudo add-apt-repository ppa:qxd/yage
sudo apt-get update
sudo apt-get install yage
```

### Fedora, RHEL 7 及其衍生版

请按照[这里](https://copr.fedoraproject.org/coprs/xdqi/YaGE/) 的指示安装

### Arch Linux

```
yaourt -S yage
```
或者手动安装 AUR 上的 `yage` 包

### Mac OS X 上使用 Homebrew

```
brew tap yet-another-graphics-engine/yage
brew install --HEAD yage
```

## 编译方法

### Microsoft Windows

#### 使用 Microsoft Visual Studio

本项目使用了可变参数宏(Variadic Macros)，请确认你安装了 Visual Studio 2005 或更高版本。(可以使用 Express 版本的 Visual C++)

下载安装 [CMake](http://www.cmake.org/download/) (Win32 Installer) 和 [GTK+ 3](http://www.gtk.org/download/win32.php) (All-in-one bundles) 并添加其中 `bin` 目录到系统 `PATH` 变量。

安装后，启动 Visual Studio 命令行(32 位) 后，切换到本项目根目录

```
X:\> cd YaGE
X:\YaGE> md build
X:\YaGE> cd build
X:\YaGE\build> cmake ..
```

使用以上命令在项目 `build` 文件夹下生成 Visual Studio 解决方案。

最后打开 `build` 文件夹中生成的 `YaGE.sln` 进行项目的生成。

项目库文件将生成在 `build\lib` 文件夹中，名为 `yage.lib`，将其复制到 VS 安装目录的 `VC\Lib` 中即可使用。然后复制 `include` 文件夹内所有文件到 VS 安装目录下的 `include` 文件夹中，即可使用头文件。

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

项目库文件将生成在 `build\lib` 文件夹中，名为 `libyage.a`，将其复制到 MinGW 安装目录的 `lib` 中即可使用。然后复制 `include` 文件夹内所有文件到 MinGW 安装目录下的 `include` 文件夹中，即可使用头文件。

#### 使用 Cygwin

打开 Cygwin 安装程序然后安装以下包:

`git make gcc-g++ cmake libgtk3-devel pkg-config libgstreamer0.10-devel`

然后按照 UNIX 构建方法构建

### UNIX 及类 UNIX 系统

#### 安装依赖包

##### Debian / Ubuntu 及其衍生发行版

`sudo apt-get install -y build-essential git libgtk-3-dev cmake pkg-config libgstreamer-plugins-base0.10-dev`

##### RHEL / CentOS 7 及其衍生版, Fedora 21 及早期版本

`sudo yum -y install git cmake pkgconfig gcc-c++ gtk3-devel gstreamer-devel`

##### Fedora 22

`sudo dnf -y install git cmake pkgconfig gcc-c++ gtk3-devel gstreamer-devel`

##### Arch Linux

`sudo pacman -S base-devel git gtk3 cmake pkg-config gstreamer0.10`

##### FreeBSD 10

`sudo pkg install git cmake pkgconf gtk3 gstreamer`

##### Mac OS X 上使用 [Homebrew](http://brew.sh/)

`brew install git cmake gtk+3 cairo pkg-config`

##### Mac OS X 上使用 [MacPorts](https://www.macports.org/)

`sudo port install git cmake gtk3 cairo pkgconfig`

#### 构建

```
$ git clone https://github.com/yet-another-graphics-engine/YaGE.git
$ cd YaGE
$ mkdir build
$ cd build
$ cmake ..
$ make
```

#### 安装

```
$ sudo make install
```
