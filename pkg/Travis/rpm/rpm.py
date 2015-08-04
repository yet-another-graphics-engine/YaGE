#!/usr/bin/env python2.7
import subprocess

RPMSPEC_FORMAT = '''Name: yage
Version: 0.1.0
Release: {date}git{gitrev}%{{?dist}}

Summary: Yet another Graphics Engine
License: LGPLv3+
Group: Development/Libraries
URL: https://github.com/yet-another-graphics-engine/YaGE
Source0: {gitbuild}.zip

BuildRequires: cmake
BuildRequires: pkgconfig
BuildRequires: gcc-c++
BuildRequires: gtk3-devel
BuildRequires: gstreamer-devel

Requires: gtk3-devel
Requires: gstreamer-devel

%description
Yet another Graphics Engine

%prep
%autosetup -n YaGE-{gitbuild}

%build
%cmake .
make %{{?_smp_flags}}

%install
%make_install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%{{_includedir}}/*
%{{_libdir}}/*
'''

if __name__ == '__main__':
    rpm_info = {}
    rpm_info['gitbuild'] = subprocess.check_output('git rev-parse HEAD', shell=True)[:-1]
    rpm_info['gitrev'] = subprocess.check_output('git rev-parse --short HEAD', shell=True)[:-1]
    rpm_info['date'] = subprocess.check_output('TZ=Asia/Shanghai date +%Y%m%d.%H%M --date=@`git log HEAD -1 --format=%ct`', shell=True)[:-1]
    with open('yage.spec', 'wb') as rpmspec_file:
        rpmspec_file.write(RPMSPEC_FORMAT.format(**rpm_info))
