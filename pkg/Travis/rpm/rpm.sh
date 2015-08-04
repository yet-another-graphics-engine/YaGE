#!/usr/bin/env bash

python rpm.py
mkdir -p rpmbuild/SPECS rpmbuild/SOURCES
mv yage.spec rpmbuild/SPECS/
wget https://github.com/yet-another-graphics-engine/YaGE/archive/`git rev-parse HEAD`.zip -P rpmbuild/SOURCES
HOME=`pwd` rpmbuild -bs rpmbuild/SPECS/yage.spec
export RPM_NAME=`ls rpmbuild/SRPMS`
curl -T rpmbuild/SRPMS/$RPM_NAME -u $FTPINFO:$FTPINFO ftp://kirito.me:21212/
curl -u $COPR_CREDENTIAL -d "pkgs=https://kirito.me/srpms/$RPM_NAME" https://copr.fedoraproject.org/api/coprs/xdqi/YaGE/new_build/
# TODO: Fedora Copr credential will expire at 2016-01-30.