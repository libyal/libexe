/*
 * Library seek testing program
 *
 * Copyright (C) 2011-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "exe_test_libcerror.h"
#include "exe_test_libcstring.h"
#include "exe_test_libcsystem.h"
#include "exe_test_libexe.h"
#include "exe_test_unused.h"

/* Define to make exe_test_seek generate verbose output
#define EXE_TEST_SEEK_VERBOSE
 */

/* Tests libexe_section_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_seek_offset(
     libexe_section_t *section,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	libcerror_error_t *error  = NULL;
	const char *whence_string = NULL;
	off64_t result_offset     = 0;
	int result                = 0;

	if( section == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libexe_section_seek_offset(
	                 section,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == output_offset )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		if( result != 1 )
		{
			libcerror_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libcerror_error_free(
		 &error );
	}
	return( result );
}

/* Tests seeking in a section
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_seek(
     libexe_section_t *section,
     size64_t section_size )
{
	int result = 0;

	if( section == NULL )
	{
		return( -1 );
	}
	if( section_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Section size exceeds maximum.\n" );

		return( -1 );
	}
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	result = exe_test_seek_offset(
	          section,
	          0,
	          SEEK_SET,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <section_size>
	 * Expected result: <section_size>
	 */
	result = exe_test_seek_offset(
	          section,
	          (off64_t) section_size,
	          SEEK_SET,
	          (off64_t) section_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <section_size / 5>
	 * Expected result: <section_size / 5>
	 */
	result = exe_test_seek_offset(
	          section,
	          (off64_t) ( section_size / 5 ),
	          SEEK_SET,
	          (off64_t) ( section_size / 5 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: <section_size + 987>
	 * Expected result: <section_size + 987>
	 */
	result = exe_test_seek_offset(
	          section,
	          (off64_t) ( section_size + 987 ),
	          SEEK_SET,
	          (off64_t) ( section_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	result = exe_test_seek_offset(
	          section,
	          -987,
	          SEEK_SET,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <section_size + 987>
	 */
	result = exe_test_seek_offset(
	          section,
	          0,
	          SEEK_CUR,
	          (off64_t) ( section_size + 987 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <-1 * (section_size + 987)>
	 * Expected result: 0
	 */
	result = exe_test_seek_offset(
	          section,
	          -1 * (off64_t) ( section_size + 987 ),
	          SEEK_CUR,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_CUR offset: <section_size / 3>
	 * Expected result: <section_size / 3>
	 */
	result = exe_test_seek_offset(
	          section,
	          (off64_t) ( section_size / 3 ),
	          SEEK_CUR,
	          (off64_t) ( section_size / 3 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	if( section_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (section_size / 3)>
		 * Expected result: 0
		 */
		result = exe_test_seek_offset(
		          section,
		          -2 * (off64_t) ( section_size / 3 ),
		          SEEK_CUR,
		          0 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (section_size / 3)>
		 * Expected result: -1
		 */
		result = exe_test_seek_offset(
		          section,
		          -2 * (off64_t) ( section_size / 3 ),
		          SEEK_CUR,
		          -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			return( result );
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <section_size>
	 */
	result = exe_test_seek_offset(
	          section,
	          0,
	          SEEK_END,
	          (off64_t) section_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * section_size>
	 * Expected result: 0
	 */
	result = exe_test_seek_offset(
	          section,
	          -1 * (off64_t) section_size,
	          SEEK_END,
	          0 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (section_size / 4)>
	 * Expected result: <section_size - (section_size / 4)>
	 */
	result = exe_test_seek_offset(
	          section,
	          -1 * (off64_t) ( section_size / 4 ),
	          SEEK_END,
	          (off64_t) section_size - (off64_t) ( section_size / 4 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <section_size + 542>
	 */
	result = exe_test_seek_offset(
	          section,
	          542,
	          SEEK_END,
	          (off64_t) ( section_size + 542 ) );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: SEEK_END offset: <-1 * (section_size + 542)>
	 * Expected result: -1
	 */
	result = exe_test_seek_offset(
	          section,
	          -1 * (off64_t) ( section_size + 542 ),
	          SEEK_END,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	result = exe_test_seek_offset(
	          section,
	          0,
	          88,
	          -1 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		return( result );
	}
	return( result );
}

/* Tests seeking in a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_seek_file(
     libcstring_system_character_t *source,
     libcerror_error_t **error )
{
	libexe_section_t *section = NULL;
	libexe_file_t *file       = NULL;
	size64_t section_size     = 0;
	int number_of_sections    = 0;
	int result                = 0;
	int section_index         = 0;

	if( libexe_file_initialize(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libexe_file_open_wide(
	     file,
	     source,
	     LIBEXE_OPEN_READ,
	     error ) != 1 )
#else
	if( libexe_file_open(
	     file,
	     source,
	     LIBEXE_OPEN_READ,
	     error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open file.\n" );

		goto on_error;
	}
	if( libexe_file_get_number_of_sections(
	     file,
	     &number_of_sections,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve number of sections.\n" );

		goto on_error;
	}
	for( section_index = number_of_sections - 1;
	     section_index >= 0;
	     section_index-- )
	{
		if( libexe_file_get_section(
		     file,
		     section_index,
		     &section,
		     error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to retrieve section: %d.\n",
			 section_index );

			goto on_error;
		}
		if( libexe_section_get_size(
		     section,
		     &section_size,
		     error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to retrieve section size.\n" );

			goto on_error;
		}
		fprintf(
		 stdout,
		 "Section: %d section size: %" PRIu64 " bytes\n",
		 section_index,
		 section_size );

		result = exe_test_seek(
		          section,
		          section_size );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to seek in section: %d.\n",
			 section_index );

			goto on_error;
		}
		if( libexe_section_free(
		     &section,
		     error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to free section: %d.\n",
			 section_index );

			goto on_error;
		}
		if( result == 0 )
		{
			break;
		}
	}
	if( libexe_file_close(
	     file,
	     error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close file.\n" );

		goto on_error;
	}
	if( libexe_file_free(
	     &file,
	     error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	return( result );

on_error:
	if( section != NULL )
	{
		libexe_section_free(
		 &section,
		 NULL );
	}
	if( file != NULL )
	{
		libexe_file_close(
		 file,
		 NULL );
		libexe_file_free(
		 &file,
		 NULL );
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error              = NULL;
	libcstring_system_character_t *source = NULL;
	libcstring_system_integer_t option    = 0;
	int result                            = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( EXE_TEST_SEEK_VERBOSE )
	libexe_notify_set_verbose(
	 1 );
	libexe_notify_set_stream(
	 stderr,
	 NULL );
#endif
	result = exe_test_seek_file(
	          source,
	          &error );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek in file.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

