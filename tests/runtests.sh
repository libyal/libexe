#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libexe/.libs/libexe.1.dylib && test -f ./pyexe/.libs/pyexe.so;
then
	install_name_tool -change /usr/local/lib/libexe.1.dylib ${PWD}/libexe/.libs/libexe.1.dylib ./pyexe/.libs/pyexe.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

