/*
 * Library section_descriptor type test program
 *
 * Copyright (C) 2011-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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

#include "../libexe/libexe_section_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT )

/* Tests the libexe_section_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int exe_test_section_descriptor_initialize(
     void )
{
	libcerror_error_t *error                        = NULL;
	libexe_section_descriptor_t *section_descriptor = NULL;
	int result                                      = 0;

#if defined( HAVE_EXE_TEST_MEMORY )
	int number_of_malloc_fail_tests                 = 1;
	int number_of_memset_fail_tests                 = 1;
	int test_number                                 = 0;
#endif

	/* Test regular cases
	 */
	result = libexe_section_descriptor_initialize(
	          &section_descriptor,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "section_descriptor",
	 section_descriptor );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libexe_section_descriptor_free(
	          &section_descriptor,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section_descriptor",
	 section_descriptor );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libexe_section_descriptor_initialize(
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

	section_descriptor = (libexe_section_descriptor_t *) 0x12345678UL;

	result = libexe_section_descriptor_initialize(
	          &section_descriptor,
	          &error );

	section_descriptor = NULL;

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_EXE_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libexe_section_descriptor_initialize with malloc failing
		 */
		exe_test_malloc_attempts_before_fail = test_number;

		result = libexe_section_descriptor_initialize(
		          &section_descriptor,
		          &error );

		if( exe_test_malloc_attempts_before_fail != -1 )
		{
			exe_test_malloc_attempts_before_fail = -1;

			if( section_descriptor != NULL )
			{
				libexe_section_descriptor_free(
				 &section_descriptor,
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
			 "section_descriptor",
			 section_descriptor );

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
		/* Test libexe_section_descriptor_initialize with memset failing
		 */
		exe_test_memset_attempts_before_fail = test_number;

		result = libexe_section_descriptor_initialize(
		          &section_descriptor,
		          &error );

		if( exe_test_memset_attempts_before_fail != -1 )
		{
			exe_test_memset_attempts_before_fail = -1;

			if( section_descriptor != NULL )
			{
				libexe_section_descriptor_free(
				 &section_descriptor,
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
			 "section_descriptor",
			 section_descriptor );

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
	if( section_descriptor != NULL )
	{
		libexe_section_descriptor_free(
		 &section_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libexe_section_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int exe_test_section_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libexe_section_descriptor_free(
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

/* Tests the libexe_section_descriptor_get_data_size function
 * Returns 1 if successful or 0 if not
 */
int exe_test_section_descriptor_get_data_size(
     void )
{
	libcerror_error_t *error                        = NULL;
	libexe_section_descriptor_t *section_descriptor = NULL;
	size64_t data_size                              = 0;
	int result                                      = 0;

	/* Initialize test
	 */
	result = libexe_section_descriptor_initialize(
	          &section_descriptor,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "section_descriptor",
	 section_descriptor );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libexe_section_descriptor_get_data_size(
	          section_descriptor,
	          &data_size,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libexe_section_descriptor_get_data_size(
	          NULL,
	          &data_size,
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

	result = libexe_section_descriptor_get_data_size(
	          section_descriptor,
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

	/* Clean up
	 */
	result = libexe_section_descriptor_free(
	          &section_descriptor,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section_descriptor",
	 section_descriptor );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( section_descriptor != NULL )
	{
		libexe_section_descriptor_free(
		 &section_descriptor,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT )

	EXE_TEST_RUN(
	 "libexe_section_descriptor_initialize",
	 exe_test_section_descriptor_initialize );

	EXE_TEST_RUN(
	 "libexe_section_descriptor_free",
	 exe_test_section_descriptor_free );

/* TODO implement
	EXE_TEST_RUN(
	 "libexe_section_descriptor_get_data_size",
	 exe_test_section_descriptor_get_data_size );
*/

	/* TODO: add tests for libexe_section_descriptor_get_data_range */

	/* TODO: add tests for libexe_section_descriptor_set_data_range */

#endif /* defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

