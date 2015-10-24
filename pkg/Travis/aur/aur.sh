#!/bin/bash
python aur.py
echo $DEPLOY_PASSPHRASE | openssl rsa -in deploy.key -out deploy -passin stdin
chmod 600 deploy
GIT_SSH=./aurssh git clone ssh+git://aur@aur.archlinux.org/yage.git/ yage-aur
mv PKGBUILD .SRCINFO yage-aur/
cd yage-aur
git config user.name "Bot of Xiaodong Qi"
git config user.email qxd@bupt.edu.cn
git commit -am "Update to `cat .SRCINFO | grep pkgver | cut -c 11-`"
GIT_SSH=../aurssh git push
cd ../../../
