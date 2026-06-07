#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libexe/.libs/libexe.1.dylib && test -f ./pyexe/.libs/pyexe.so
then
	install_name_tool -change /usr/local/lib/libexe.1.dylib ${PWD}/libexe/.libs/libexe.1.dylib ./pyexe/.libs/pyexe.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

