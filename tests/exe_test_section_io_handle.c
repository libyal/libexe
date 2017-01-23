/*
 * Library section_io_handle type test program
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

#include "../libexe/libexe_section_io_handle.h"

#if defined( __GNUC__ )

/* Tests the libexe_section_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int exe_test_section_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libexe_section_io_handle_free(
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

	/* TODO: add tests for libexe_section_io_handle_initialize */

	EXE_TEST_RUN(
	 "libexe_section_io_handle_free",
	 exe_test_section_io_handle_free );

	/* TODO: add tests for libexe_section_io_handle_clone */

	/* TODO: add tests for libexe_section_io_handle_read */

	/* TODO: add tests for libexe_section_io_handle_write */

	/* TODO: add tests for libexe_section_io_handle_seek_offset */

	/* TODO: add tests for libexe_section_io_handle_exists */

	/* TODO: add tests for libexe_section_io_handle_is_open */

	/* TODO: add tests for libexe_section_io_handle_get_size */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

