/*
 * Library section type test program
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

#include "../libexe/libexe_section.h"

/* Tests the libexe_section_free function
 * Returns 1 if successful or 0 if not
 */
int exe_test_section_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libexe_section_free(
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

#if defined( __GNUC__ )

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

	/* TODO: add tests for libexe_section_initialize */

#endif /* defined( __GNUC__ ) */

	EXE_TEST_RUN(
	 "libexe_section_free",
	 exe_test_section_free );

#if defined( __GNUC__ )

	/* TODO: add tests for libexe_section_get_name_size */

	/* TODO: add tests for libexe_section_get_name */

	/* TODO: add tests for libexe_section_get_utf8_name_size */

	/* TODO: add tests for libexe_section_get_utf8_name */

	/* TODO: add tests for libexe_section_get_utf16_name_size */

	/* TODO: add tests for libexe_section_get_utf16_name */

	/* TODO: add tests for libexe_section_read_buffer */

	/* TODO: add tests for libexe_section_read_buffer_at_offset */

	/* TODO: add tests for libexe_section_seek_offset */

	/* TODO: add tests for libexe_section_get_offset */

	/* TODO: add tests for libexe_section_get_size */

	/* TODO: add tests for libexe_section_get_start_offset */

	/* TODO: add tests for libexe_section_get_virtual_address */

	/* TODO: add tests for libexe_section_get_data_file_io_handle */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

