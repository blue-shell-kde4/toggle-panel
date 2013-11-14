#!/bin/sh

PREFIX=$(kde4-config --prefix)
BUILD_TYPE="Release"

echo "Install prefix?"
echo "1: $PREFIX"
echo "2: Custom"
echo "1 or 2?"
read choice

clear

if [ "$choice" != 1 ]; then
   echo "Path:"
   read PREFIX
   if [ "$PREFIX" = "" ]; then
      echo "Invalid Install Prefix..."
      exit 1
   fi
fi

if [ "$(id -u)" != "0" ] && [ "$choice" = "1" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

clear

echo "Build Type?"
echo "1: Release"
echo "2: RelWithDebInfo"
echo "3: Debug"
echo "1, 2, or 3?"
read choice

if [ "$choice" = "1" ]
   then BUILD_TYPE="Release"
   else if [ "$choice" = "2" ]
           then BUILD_TYPE="RelWithDebInfo"
           else BUILD_TYPE="Debug"
        fi
fi

clear

echo "---------------------------------"
echo "Install Prefix: $PREFIX"
echo "Build Type:     $BUILD_TYPE"
echo "---------------------------------"
echo "Continue? (y/n)"
read choice

if [ "$choice" != "y" ]
   then exit 0
fi


mkdir auto_build
cd auto_build
if [ "$?" != "0" ]; then echo "cd auto_build: failed!"; exit 1; fi
clear

cmake -DCMAKE_INSTALL_PREFIX=$PREFIX CMAKE_BUILD_TYPE=$BUILD_TYPE ..
if [ "$?" != "0" ]; then echo "cmake: failed!"; exit 1; fi
clear

make -I auto_build/
if [ "$?" != "0" ]; then echo "make: failed!"; exit 1; fi
clear

make install
if [ "$?" != "0" ]; then echo "make install: failed!"; exit 1; fi
clear

echo "Installation successfull, please run kbuildsycoca4 to update your plasmoid list!"
