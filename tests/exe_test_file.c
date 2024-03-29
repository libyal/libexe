/*
 * Library file type test program
 *
 * Copyright (C) 2011-2024, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "exe_test_functions.h"
#include "exe_test_getopt.h"
#include "exe_test_libbfio.h"
#include "exe_test_libcerror.h"
#include "exe_test_libexe.h"
#include "exe_test_macros.h"
#include "exe_test_memory.h"

#include "../libexe/libexe_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make exe_test_file generate verbose output
#define EXE_TEST_FILE_VERBOSE
 */

#if !defined( LIBEXE_HAVE_BFIO )

LIBEXE_EXTERN \
int libexe_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_open_file_io_handle(
     libexe_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libexe_error_t **error );

#endif /* !defined( LIBEXE_HAVE_BFIO ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int exe_test_file_open_source(
     libexe_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "exe_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libexe_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libexe_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBEXE_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libexe_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int exe_test_file_close_source(
     libexe_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "exe_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libexe_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libexe_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libexe_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libexe_file_t *file             = NULL;
	int result                      = 0;

#if defined( HAVE_EXE_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libexe_file_initialize(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libexe_file_free(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libexe_file_initialize(
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

	file = (libexe_file_t *) 0x12345678UL;

	result = libexe_file_initialize(
	          &file,
	          &error );

	file = NULL;

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
		/* Test libexe_file_initialize with malloc failing
		 */
		exe_test_malloc_attempts_before_fail = test_number;

		result = libexe_file_initialize(
		          &file,
		          &error );

		if( exe_test_malloc_attempts_before_fail != -1 )
		{
			exe_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libexe_file_free(
				 &file,
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
			 "file",
			 file );

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
		/* Test libexe_file_initialize with memset failing
		 */
		exe_test_memset_attempts_before_fail = test_number;

		result = libexe_file_initialize(
		          &file,
		          &error );

		if( exe_test_memset_attempts_before_fail != -1 )
		{
			exe_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libexe_file_free(
				 &file,
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
			 "file",
			 file );

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
	if( file != NULL )
	{
		libexe_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libexe_file_free function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libexe_file_free(
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

/* Tests the libexe_file_open function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libexe_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = exe_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libexe_file_initialize(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libexe_file_open(
	          file,
	          narrow_source,
	          LIBEXE_OPEN_READ,
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
	result = libexe_file_open(
	          NULL,
	          narrow_source,
	          LIBEXE_OPEN_READ,
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

	result = libexe_file_open(
	          file,
	          NULL,
	          LIBEXE_OPEN_READ,
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

	result = libexe_file_open(
	          file,
	          narrow_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libexe_file_open(
	          file,
	          narrow_source,
	          LIBEXE_OPEN_READ,
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
	result = libexe_file_free(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libexe_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libexe_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libexe_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = exe_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libexe_file_initialize(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libexe_file_open_wide(
	          file,
	          wide_source,
	          LIBEXE_OPEN_READ,
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
	result = libexe_file_open_wide(
	          NULL,
	          wide_source,
	          LIBEXE_OPEN_READ,
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

	result = libexe_file_open_wide(
	          file,
	          NULL,
	          LIBEXE_OPEN_READ,
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

	result = libexe_file_open_wide(
	          file,
	          wide_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libexe_file_open_wide(
	          file,
	          wide_source,
	          LIBEXE_OPEN_READ,
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
	result = libexe_file_free(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libexe_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libexe_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libexe_file_t *file              = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libexe_file_initialize(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libexe_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBEXE_OPEN_READ,
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
	result = libexe_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBEXE_OPEN_READ,
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

	result = libexe_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBEXE_OPEN_READ,
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

	result = libexe_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
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

	/* Test open when already opened
	 */
	result = libexe_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBEXE_OPEN_READ,
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
	result = libexe_file_free(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

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
	if( file != NULL )
	{
		libexe_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libexe_file_close function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libexe_file_close(
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

/* Tests the libexe_file_open and libexe_file_close functions
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libexe_file_t *file      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libexe_file_initialize(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libexe_file_open_wide(
	          file,
	          source,
	          LIBEXE_OPEN_READ,
	          &error );
#else
	result = libexe_file_open(
	          file,
	          source,
	          LIBEXE_OPEN_READ,
	          &error );
#endif

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libexe_file_close(
	          file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libexe_file_open_wide(
	          file,
	          source,
	          LIBEXE_OPEN_READ,
	          &error );
#else
	result = libexe_file_open(
	          file,
	          source,
	          LIBEXE_OPEN_READ,
	          &error );
#endif

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libexe_file_close(
	          file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libexe_file_free(
	          &file,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

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
	if( file != NULL )
	{
		libexe_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libexe_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_signal_abort(
     libexe_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libexe_file_signal_abort(
	          file,
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
	result = libexe_file_signal_abort(
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

/* Tests the libexe_file_get_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_get_ascii_codepage(
     libexe_file_t *file )
{
	libcerror_error_t *error  = NULL;
	int ascii_codepage        = 0;
	int ascii_codepage_is_set = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libexe_file_get_ascii_codepage(
	          file,
	          &ascii_codepage,
	          &error );

	EXE_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	ascii_codepage_is_set = result;

	/* Test error cases
	 */
	result = libexe_file_get_ascii_codepage(
	          NULL,
	          &ascii_codepage,
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

	if( ascii_codepage_is_set != 0 )
	{
		result = libexe_file_get_ascii_codepage(
		          file,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libexe_file_set_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_set_ascii_codepage(
     libexe_file_t *file )
{
	int supported_codepages[ 15 ] = {
		LIBEXE_CODEPAGE_ASCII,
		LIBEXE_CODEPAGE_WINDOWS_874,
		LIBEXE_CODEPAGE_WINDOWS_932,
		LIBEXE_CODEPAGE_WINDOWS_936,
		LIBEXE_CODEPAGE_WINDOWS_949,
		LIBEXE_CODEPAGE_WINDOWS_950,
		LIBEXE_CODEPAGE_WINDOWS_1250,
		LIBEXE_CODEPAGE_WINDOWS_1251,
		LIBEXE_CODEPAGE_WINDOWS_1252,
		LIBEXE_CODEPAGE_WINDOWS_1253,
		LIBEXE_CODEPAGE_WINDOWS_1254,
		LIBEXE_CODEPAGE_WINDOWS_1255,
		LIBEXE_CODEPAGE_WINDOWS_1256,
		LIBEXE_CODEPAGE_WINDOWS_1257,
		LIBEXE_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBEXE_CODEPAGE_ISO_8859_1,
		LIBEXE_CODEPAGE_ISO_8859_2,
		LIBEXE_CODEPAGE_ISO_8859_3,
		LIBEXE_CODEPAGE_ISO_8859_4,
		LIBEXE_CODEPAGE_ISO_8859_5,
		LIBEXE_CODEPAGE_ISO_8859_6,
		LIBEXE_CODEPAGE_ISO_8859_7,
		LIBEXE_CODEPAGE_ISO_8859_8,
		LIBEXE_CODEPAGE_ISO_8859_9,
		LIBEXE_CODEPAGE_ISO_8859_10,
		LIBEXE_CODEPAGE_ISO_8859_11,
		LIBEXE_CODEPAGE_ISO_8859_13,
		LIBEXE_CODEPAGE_ISO_8859_14,
		LIBEXE_CODEPAGE_ISO_8859_15,
		LIBEXE_CODEPAGE_ISO_8859_16,
		LIBEXE_CODEPAGE_KOI8_R,
		LIBEXE_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = libexe_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		EXE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		EXE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libexe_file_set_ascii_codepage(
	          NULL,
	          LIBEXE_CODEPAGE_ASCII,
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

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = libexe_file_set_ascii_codepage(
		          file,
		          codepage,
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
	}
	/* Clean up
	 */
	result = libexe_file_set_ascii_codepage(
	          file,
	          LIBEXE_CODEPAGE_WINDOWS_1252,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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
	return( 0 );
}

/* Tests the libexe_file_get_number_of_sections function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_get_number_of_sections(
     libexe_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_sections   = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libexe_file_get_number_of_sections(
	          file,
	          &number_of_sections,
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
	result = libexe_file_get_number_of_sections(
	          NULL,
	          &number_of_sections,
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

	result = libexe_file_get_number_of_sections(
	          file,
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

/* Tests the libexe_file_get_section function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_get_section(
     libexe_file_t *file )
{
	libcerror_error_t *error  = NULL;
	libexe_section_t *section = NULL;
	int result                = 0;

	/* Test regular cases
	 */
	result = libexe_file_get_section(
	          file,
	          0,
	          &section,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "section",
	 section );

	result = libexe_section_free(
	          &section,
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
	result = libexe_file_get_section(
	          NULL,
	          0,
	          &section,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section",
	 section );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libexe_file_get_section(
	          file,
	          -1,
	          &section,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section",
	 section );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libexe_file_get_section(
	          file,
	          0,
	          NULL,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section",
	 section );

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
	if( section != NULL )
	{
		libexe_section_free(
		 &section,
		 NULL );
	}
	return( 0 );
}

/* Tests the libexe_file_get_section_by_index function
 * Returns 1 if successful or 0 if not
 */
int exe_test_file_get_section_by_index(
     libexe_file_t *file )
{
	libcerror_error_t *error  = NULL;
	libexe_section_t *section = NULL;
	int result                = 0;

	/* Test regular cases
	 */
	result = libexe_file_get_section_by_index(
	          file,
	          0,
	          &section,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "section",
	 section );

	result = libexe_section_free(
	          &section,
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
	result = libexe_file_get_section_by_index(
	          NULL,
	          0,
	          &section,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section",
	 section );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libexe_file_get_section_by_index(
	          file,
	          -1,
	          &section,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section",
	 section );

	EXE_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libexe_file_get_section_by_index(
	          file,
	          0,
	          NULL,
	          &error );

	EXE_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EXE_TEST_ASSERT_IS_NULL(
	 "section",
	 section );

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
	if( section != NULL )
	{
		libexe_section_free(
		 &section,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libexe_file_t *file              = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = exe_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( EXE_TEST_FILE_VERBOSE )
	libexe_notify_set_verbose(
	 1 );
	libexe_notify_set_stream(
	 stderr,
	 NULL );
#endif

	EXE_TEST_RUN(
	 "libexe_file_initialize",
	 exe_test_file_initialize );

	EXE_TEST_RUN(
	 "libexe_file_free",
	 exe_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		EXE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        EXE_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        EXE_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		EXE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        EXE_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libexe_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		EXE_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		EXE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_open",
		 exe_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_open_wide",
		 exe_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_open_file_io_handle",
		 exe_test_file_open_file_io_handle,
		 source );

		EXE_TEST_RUN(
		 "libexe_file_close",
		 exe_test_file_close );

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_open_close",
		 exe_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = exe_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		EXE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		EXE_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		EXE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_signal_abort",
		 exe_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT )

		/* TODO: add tests for libexe_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT ) */

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_get_ascii_codepage",
		 exe_test_file_get_ascii_codepage,
		 file );

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_set_ascii_codepage",
		 exe_test_file_set_ascii_codepage,
		 file );

#if defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT )

		/* TODO: add tests for libexe_file_get_offset_by_relative_virtual_address */

#endif /* defined( __GNUC__ ) && !defined( LIBEXE_DLL_IMPORT ) */

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_get_number_of_sections",
		 exe_test_file_get_number_of_sections,
		 file );

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_get_section",
		 exe_test_file_get_section,
		 file );

		EXE_TEST_RUN_WITH_ARGS(
		 "libexe_file_get_section_by_index",
		 exe_test_file_get_section_by_index,
		 file );

		/* TODO: add tests for libexe_file_get_section_by_name */

		/* Clean up
		 */
		result = exe_test_file_close_source(
		          &file,
		          &error );

		EXE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		EXE_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		EXE_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		EXE_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		EXE_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        EXE_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libexe_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

