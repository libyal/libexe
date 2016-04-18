#!/usr/bin/env python
#
# Python-bindings seek testing program
#
# Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

from __future__ import print_function
import argparse
import os
import sys

import pyexe


def get_whence_string(whence):
  """Retrieves a human readable string representation of the whence."""
  if whence == os.SEEK_CUR:
    whence_string = "SEEK_CUR"
  elif whence == os.SEEK_END:
    whence_string = "SEEK_END"
  elif whence == os.SEEK_SET:
    whence_string = "SEEK_SET"
  else:
    whence_string = "UNKNOWN"
  return whence_string


def pyexe_test_seek_offset(
    exe_section, input_offset, input_whence, expected_offset):

  print("Testing seek of offset: {0:d} and whence: {1:s}\t".format(
      input_offset, get_whence_string(input_whence)), end="")

  error_string = ""
  result = True
  try:
    exe_section.seek(input_offset, input_whence)

    result_offset = exe_section.get_offset()
    if expected_offset != result_offset:
      result = False

  except Exception as exception:
    error_string = str(exception)
    if expected_offset != -1:
      result = False

  if not result:
    print("(FAIL)")
  else:
    print("(PASS)")

  if error_string:
    print(error_string)
  return result


def pyexe_test_seek(exe_section):
  section_size = exe_section.size

  # Test: SEEK_SET offset: 0
  # Expected result: 0
  if not pyexe_test_seek_offset(exe_section, 0, os.SEEK_SET, 0):
    return False

  # Test: SEEK_SET offset: <section_size>
  # Expected result: <section_size>
  if not pyexe_test_seek_offset(
      exe_section, section_size, os.SEEK_SET, section_size):
    return False

  # Test: SEEK_SET offset: <section_size / 5>
  # Expected result: <section_size / 5>
  seek_offset, _ = divmod(section_size, 5)
  if not pyexe_test_seek_offset(
      exe_section, seek_offset, os.SEEK_SET, seek_offset):
    return False

  # Test: SEEK_SET offset: <section_size + 987>
  # Expected result: <section_size + 987>
  seek_offset = section_size + 987
  if not pyexe_test_seek_offset(
      exe_section, seek_offset, os.SEEK_SET, seek_offset):
    return False

  # Test: SEEK_SET offset: -987
  # Expected result: -1
  seek_offset = -987
  if not pyexe_test_seek_offset(exe_section, seek_offset, os.SEEK_SET, -1):
    return False

  # Test: SEEK_CUR offset: 0
  # Expected result: <section_size + 987>
  if not pyexe_test_seek_offset(exe_section, 0, os.SEEK_CUR, section_size + 987):
    return False

  # Test: SEEK_CUR offset: <-1 * (section_size + 987)>
  # Expected result: 0
  if not pyexe_test_seek_offset(
      exe_section, -1 * (section_size + 987), os.SEEK_CUR, 0):
    return False

  # Test: SEEK_CUR offset: <section_size / 3>
  # Expected result: <section_size / 3>
  seek_offset, _ = divmod(section_size, 3)
  if not pyexe_test_seek_offset(
      exe_section, seek_offset, os.SEEK_CUR, seek_offset):
    return False

  if section_size == 0:
    # Test: SEEK_CUR offset: <-2 * (section_size / 3)>
    # Expected result: 0
    seek_offset, _ = divmod(section_size, 3)
    if not pyexe_test_seek_offset(exe_section, -2 * seek_offset, os.SEEK_CUR, 0):
      return False

  else:
    # Test: SEEK_CUR offset: <-2 * (section_size / 3)>
    # Expected result: -1
    seek_offset, _ = divmod(section_size, 3)
    if not pyexe_test_seek_offset(
        exe_section, -2 * seek_offset, os.SEEK_CUR, -1):
      return False

  # Test: SEEK_END offset: 0
  # Expected result: <section_size>
  if not pyexe_test_seek_offset(exe_section, 0, os.SEEK_END, section_size):
    return False

  # Test: SEEK_END offset: <-1 * section_size>
  # Expected result: 0
  if not pyexe_test_seek_offset(exe_section, -1 * section_size, os.SEEK_END, 0):
    return False

  # Test: SEEK_END offset: <-1 * (section_size / 4)>
  # Expected result: <section_size - (section_size / 4)>
  seek_offset, _ = divmod(section_size, 4)
  if not pyexe_test_seek_offset(
      exe_section, -1 * seek_offset, os.SEEK_END, section_size - seek_offset):
    return False

  # Test: SEEK_END offset: 542
  # Expected result: <section_size + 542>
  if not pyexe_test_seek_offset(exe_section, 542, os.SEEK_END, section_size + 542):
    return False

  # Test: SEEK_END offset: <-1 * (section_size + 542)>
  # Expected result: -1
  if not pyexe_test_seek_offset(
      exe_section, -1 * (section_size + 542), os.SEEK_END, -1):
    return False

  # Test: UNKNOWN (88) offset: 0
  # Expected result: -1
  if not pyexe_test_seek_offset(exe_section, 0, 88, -1):
    return False

  return True


def pyexe_test_seek_file(filename):
  exe_file = pyexe.file()

  exe_file.open(filename, "r")

  result = True
  for section_index in range(0, exe_file.number_of_sections):
    exe_section = exe_file.get_section(section_index)
    result = pyexe_test_seek(exe_section)
    if not result:
      break

  exe_file.close()

  return result


def pyexe_test_seek_file_object(filename):
  file_object = open(filename, "rb")
  exe_file = pyexe.file()

  exe_file.open_file_object(file_object, "r")

  result = True
  for section_index in range(0, exe_file.number_of_sections):
    exe_section = exe_file.get_section(section_index)
    result = pyexe_test_seek(exe_section)
    if not result:
      break

  exe_file.close()

  return result


def main():
  args_parser = argparse.ArgumentParser(description=(
      "Tests seek."))

  args_parser.add_argument(
      "source", nargs="?", action="store", metavar="FILENAME",
      default=None, help="The source filename.")

  options = args_parser.parse_args()

  if not options.source:
    print("Source value is missing.")
    print("")
    args_parser.print_help()
    print("")
    return False

  if not pyexe_test_seek_file(options.source):
    return False

  if not pyexe_test_seek_file_object(options.source):
    return False

  return True


if __name__ == "__main__":
  if not main():
    sys.exit(1)
  else:
    sys.exit(0)

