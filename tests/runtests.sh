#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libexe/.libs/libexe.1.dylib" ] && [ -f ./pyexe/.libs/pyexe.so ]
then
    install_name_tool -change /usr/local/lib/libexe.1.dylib "${PWD}/libexe/.libs/libexe.1.dylib" ./pyexe/.libs/pyexe.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

