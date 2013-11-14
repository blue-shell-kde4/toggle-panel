#!/bin/sh


VERSION=$1
PW=$2
PROJECT=plasma-applet-paneltoggle
ROOT="."
COPY=${ROOT}/../${PROJECT}-${VERSION}
ORIG=${ROOT}/../${PROJECT}

# update version
sed -i s/X-KDE-PluginInfo-Version.*/X-KDE-PluginInfo-Version=$VERSION/g ${PROJECT}.desktop

# create a new copy
cp -r ${ORIG} ${COPY}

# remove garbage
echo $PW | sudo -S rm -r ${COPY}/build
echo $PW | sudo -S rm -r ${COPY}/auto_build
rm ${COPY}/CMakeLists.txt.user


# tar
tar -cvjpf ${COPY}.tar.bz2 ${COPY}


echo "\n\n"
echo "---------------------------------------------------"
echo "Release:           $VERSION"
echo "Archive:           ${COPY}.tar.bz2"
echo "---------------------------------------------------"


