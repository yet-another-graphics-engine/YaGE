# AppVeyor YaGE advanced uploading script

mount C:\MinGW /mingw
export PATH=/usr/local/bin:/mingw/bin:/bin:/c/mingw/bin:$PATH
cd `dirname $0`/../../

export YAGE_VERSION=0.1.0-`TZ=CST-8 date +%Y%m%d.%H%M --date=@$(git log HEAD -1 --format=%ct)`-`git rev-parse --short HEAD`

echo "Uploading to Qiniu Cloud Storage (http://www.qiniu.com/)"
qrsctl login $QINIU_CREDENTIAL
qrsctl put -c yage yage-$YAGE_VERSION.exe pkg/NSIS/yageinst.exe

echo "Uploading to Bintray (https://bintray.com/)"
curl -u $BINTRAY_TOKEN -H "Content-Type: application/json" -d "{\"name\": \"$YAGE_VERSION\", \"desc\": \"`git log HEAD -1 --format=%s`\"}" https://bintray.com/api/v1/packages/xdqi/YaGE/yage-win32/versions
curl -u $BINTRAY_TOKEN -X PUT -T pkg/NSIS/yageinst.exe "https://bintray.com/api/v1/content/xdqi/YaGE/yage-win32/$YAGE_VERSION/yage-$YAGE_VERSION.exe?publish=1"
