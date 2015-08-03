#!/bin/bash

echo $DEPLOY_PASSPHRASE | gpg --passphrase-fd 0 ppa.asc
gpg --no-tty --import ppa

python ppa.py
cd build
for dist in `ls`
    do
    cd $dist
    cp -r ../../../../../{CMakeLists.txt,doc,include,src} .
    debuild -S -k1AD62102
    cd ..
done
for sdeb in `ls *.changes`
do
    dput ppa:qxd/yage $sdeb
done
