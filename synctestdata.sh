#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20251217

REPOSITORY="libyal/testdata";
TEST_DATA_PATH="pe_coff";
TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="nowrc_test.dll wrc_test.dll";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://raw.githubusercontent.com/${REPOSITORY}/refs/heads/main/${TEST_DATA_PATH}/${TEST_FILE}";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

