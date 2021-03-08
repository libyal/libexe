#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20161009

TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="nowrc_test.dll wrc_test.dll";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://github.com/libyal/testdata/blob/main/pe_coff/${TEST_FILE}?raw=true";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

