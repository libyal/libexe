/*
 * Library io_handle type test program
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "exe_test_libcerror.h"
#include "exe_test_libexe.h"
#include "exe_test_macros.h"
#include "exe_test_memory.h"
#include "exe_test_unused.h"

#include "../libexe/libexe_io_handle.h"

#if defined( __GNUC__ )

/* Tests the libexe_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int exe_test_io_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libexe_io_handle_t *io_handle   = NULL;
	int result                      = 0;

#if defined( HAVE_EXE_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libexe_io_handle_initialize(
	          &io_handle,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EXE_TEST_ASSERT_IS_NOT_NULL(
         "io_handle",
         io_handle );

        EXE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libexe_io_handle_free(
	          &io_handle,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EXE_TEST_ASSERT_IS_NULL(
         "io_handle",
         io_handle );

        EXE_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libexe_io_handle_initialize(
	          NULL,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EXE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	io_handle = (libexe_io_handle_t *) 0x12345678UL;

	result = libexe_io_handle_initialize(
	          &io_handle,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EXE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	io_handle = NULL;

#if defined( HAVE_EXE_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libexe_io_handle_initialize with malloc failing
		 */
		exe_test_malloc_attempts_before_fail = test_number;

		result = libexe_io_handle_initialize(
		          &io_handle,
		          &error );

		if( exe_test_malloc_attempts_before_fail != -1 )
		{
			exe_test_malloc_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libexe_io_handle_free(
				 &io_handle,
				 NULL );
			}
		}
		else
		{
			EXE_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			EXE_TEST_ASSERT_IS_NULL(
			 "io_handle",
			 io_handle );

			EXE_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libexe_io_handle_initialize with memset failing
		 */
		exe_test_memset_attempts_before_fail = test_number;

		result = libexe_io_handle_initialize(
		          &io_handle,
		          &error );

		if( exe_test_memset_attempts_before_fail != -1 )
		{
			exe_test_memset_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libexe_io_handle_free(
				 &io_handle,
				 NULL );
			}
		}
		else
		{
			EXE_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			EXE_TEST_ASSERT_IS_NULL(
			 "io_handle",
			 io_handle );

			EXE_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_EXE_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( io_handle != NULL )
	{
		libexe_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libexe_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int exe_test_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libexe_io_handle_free(
	          NULL,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        EXE_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc EXE_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] EXE_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc EXE_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] EXE_TEST_ATTRIBUTE_UNUSED )
#endif
{
	EXE_TEST_UNREFERENCED_PARAMETER( argc )
	EXE_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ )

	EXE_TEST_RUN(
	 "libexe_io_handle_initialize",
	 exe_test_io_handle_initialize );

	EXE_TEST_RUN(
	 "libexe_io_handle_free",
	 exe_test_io_handle_free );

	/* TODO: add tests for libexe_io_handle_clear */

	/* TODO: add tests for libexe_io_handle_read_file_header */

	/* TODO: add tests for libexe_io_handle_read_mz_header */

	/* TODO: add tests for libexe_io_handle_read_extended_header */

	/* TODO: add tests for libexe_io_handle_read_le_header */

	/* TODO: add tests for libexe_io_handle_read_ne_header */

	/* TODO: add tests for libexe_io_handle_read_pe_header */

	/* TODO: add tests for libexe_io_handle_read_coff_header */

	/* TODO: add tests for libexe_io_handle_read_coff_optional_header */

	/* TODO: add tests for libexe_io_handle_read_section_table */

	/* TODO: add tests for libexe_io_handle_read_segment_data */

	/* TODO: add tests for libexe_io_handle_seek_segment_offset */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

