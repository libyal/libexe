#!/bin/sh
# Script to build a MacOS pkg
#
# Version: 20241015

set -e

make install DESTDIR=${PWD}/osx-pkg
mkdir -p ${PWD}/osx-pkg/usr/share/doc/libexe
cp AUTHORS COPYING COPYING.LESSER NEWS README ${PWD}/osx-pkg/usr/share/doc/libexe

VERSION=`sed '5!d; s/^  \[//;s/\],$//' configure.ac`
pkgbuild --root osx-pkg --identifier com.github.libyal.libexe --version ${VERSION} --ownership recommended ../libexe-${VERSION}.pkg

