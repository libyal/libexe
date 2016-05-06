/*
 * Library read testing program
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
#include "exe_test_libcthreads.h"
#include "exe_test_libexe.h"
#include "exe_test_unused.h"

/* Define to make exe_test_read generate verbose output
#define EXE_TEST_READ_VERBOSE
 */

#define EXE_TEST_READ_BUFFER_SIZE		4096
#define EXE_TEST_READ_NUMBER_OF_THREADS		4

/* Tests libexe_section_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_seek_offset(
     libexe_section_t *section,
     off64_t input_offset,
     int input_whence,
     off64_t expected_offset )
{
	libcerror_error_t *error = NULL;
	off64_t result_offset    = 0;
	int result               = 0;

	if( section == NULL )
	{
		return( -1 );
	}
	result_offset = libexe_section_seek_offset(
	                 section,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
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

/* Tests libexe_section_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_read_buffer(
     libexe_section_t *section,
     size64_t input_size,
     size64_t expected_size )
{
	uint8_t buffer[ EXE_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	size64_t remaining_size  = 0;
	size64_t result_size     = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	if( section == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = EXE_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libexe_section_read_buffer(
			      section,
			      buffer,
			      read_size,
			      &error );

		if( read_count <= 0 )
		{
			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
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

/* Tests libexe_section_read_buffer_at_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_read_buffer_at_offset(
     libexe_section_t *section,
     off64_t input_offset,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	uint8_t buffer[ EXE_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	off64_t result_offset    = 0;
	size64_t remaining_size  = 0;
	size64_t result_size     = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	if( section == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 " and size: %" PRIu64 "\t",
	 input_offset,
	 input_size );

	while( remaining_size > 0 )
	{
		read_size = EXE_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libexe_section_read_buffer_at_offset(
			      section,
			      buffer,
			      read_size,
			      input_offset,
			      &error );

		if( read_count <= 0 )
		{
			break;
		}
		input_offset   += (size64_t) read_count;
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( libexe_section_get_offset(
	     section,
	     &result_offset,
	     &error ) != 1 )
	{
		result = -1;
	}
	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( result == 1 )
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

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_seek_offset_and_read_buffer(
     libexe_section_t *section,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	const char *whence_string = NULL;
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
	 "Testing reading buffer at offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = exe_test_seek_offset(
	          section,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = exe_test_read_buffer(
				  section,
				  input_size,
				  expected_size );
		}
	}
	if( result == 1 )
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

	return( result );
}

/* Tests reading data from a section
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_read_from_section(
     libexe_section_t *section,
     size64_t section_size )
{
	off64_t read_offset = 0;
	size64_t read_size  = 0;
	int result          = 0;

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
	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <section_size>
	 * Expected result: offset: 0 size: <section_size>
	 */
	read_offset = 0;
	read_size   = section_size;

	result = exe_test_seek_offset_and_read_buffer(
	          section,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	result = exe_test_seek_offset_and_read_buffer(
	          section,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 1: test buffer at offset read
	 */

	/* Test: offset: <section_size / 7> size: <section_size / 2>
	 * Expected result: offset: <section_size / 7> size: <section_size / 2>
	 */
	read_offset = (off64_t) ( section_size / 7 );
	read_size   = section_size / 2;

	result = exe_test_seek_offset_and_read_buffer(
	          section,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	result = exe_test_seek_offset_and_read_buffer(
	          section,
	          read_offset,
	          SEEK_SET,
	          read_size,
	          read_offset,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 2: test read beyond section size
	 */
	read_offset = (off64_t) ( section_size - 1024 );
	read_size   = 4096;

	if( section_size < 1024 )
	{
		/* Test: offset: <section_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = exe_test_seek_offset_and_read_buffer(
		          section,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
		result = exe_test_seek_offset_and_read_buffer(
		          section,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: offset: <section_size - 1024> size: 4096
		 * Expected result: offset: <section_size - 1024> size: 1024
		 */
		result = exe_test_seek_offset_and_read_buffer(
		          section,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          read_offset,
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			return( result );
		}
		result = exe_test_seek_offset_and_read_buffer(
		          section,
		          read_offset,
		          SEEK_SET,
		          read_size,
		          read_offset,
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	/* Case 3: test buffer at offset read
	 */

	/* Test: offset: <section_size / 7> size: <section_size / 2>
	 * Expected result: offset: < ( section_size / 7 ) + ( section_size / 2 ) > size: <section_size / 2>
	 */
	read_offset = (off64_t) ( section_size / 7 );
	read_size   = section_size / 2;

	result = exe_test_read_buffer_at_offset(
	          section,
	          read_offset,
	          read_size,
	          read_offset + read_size,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	result = exe_test_read_buffer_at_offset(
	          section,
	          read_offset,
	          read_size,
	          read_offset + read_size,
	          read_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	return( 1 );
}

/* Tests reading a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_read(
     libcstring_system_character_t *source,
     libcerror_error_t **error )
{
	libexe_file_t *file       = NULL;
	libexe_section_t *section = NULL;
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
	for( section_index = 0;
	     section_index < number_of_sections;
	     section_index++ )
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
		 "Section: %d size: %" PRIu64 " bytes\n",
		 section_index,
		 section_size );

		result = exe_test_read_from_section(
		          section,
		          section_size );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to read from section: %d.\n",
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
		if( result != 1 )
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

#if defined( HAVE_MULTI_THREAD_SUPPORT )

/* The thread pool callback function
 * Returns 1 if successful or -1 on error
 */
int exe_test_read_callback_function(
     libexe_section_t *section,
     void *arguments EXE_TEST_ATTRIBUTE_UNUSED )
{
	uint8_t buffer[ EXE_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "exe_test_read_callback_function";
	size_t read_size         = EXE_TEST_READ_BUFFER_SIZE;
	ssize_t read_count       = 0;
	int number_of_iterations = 3;

	EXE_TEST_UNREFERENCED_PARAMETER( arguments )

	if( section == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section.",
		 function );

		goto on_error;
	}
	while( number_of_iterations > 0 )
	{
		read_count = libexe_section_read_buffer(
		              section,
		              buffer,
		              read_size,
		              &error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read from section.",
			 function );

			goto on_error;
		}
		number_of_iterations--;

		if( number_of_iterations > 0 )
		{
			if( libexe_section_seek_offset(
			     section,
			     (off64_t) -read_size,
			     SEEK_CUR,
			     &error ) == -1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_SEEK_FAILED,
				 "%s: unable to seek in section.",
				 function );

				goto on_error;
			}
		}
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );

		libcerror_error_free(
		 &error );
	}
	return( -1 );
}

/* Tests reading data from a section in multiple threads
 * This test requires multi-threading support
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_read_from_section_multi_thread(
     libexe_section_t *section,
     size64_t media_size,
     int number_of_threads )
{
	libcerror_error_t *error               = NULL;
	libcthreads_thread_pool_t *thread_pool = NULL;
	static char *function                  = "exe_test_read_from_section_multi_thread";
	off64_t expected_offset                = 0;
	off64_t result_offset                  = 0;
	int iteration                          = 0;
	int number_of_iterations               = 0;
	int result                             = 0;

	if( section == NULL )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section.",
		 function );

		goto on_error;
	}
	if( libexe_section_seek_offset(
	     section,
	     0,
	     SEEK_SET,
	     &error ) == -1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek in section.",
		 function );

		goto on_error;
	}
	if( number_of_threads > 1 )
	{
		number_of_iterations = number_of_threads * 32;

		expected_offset = (off64_t) number_of_iterations * EXE_TEST_READ_BUFFER_SIZE;

		if( (size64_t) expected_offset > media_size )
		{
			expected_offset = media_size;

			number_of_iterations = media_size / EXE_TEST_READ_BUFFER_SIZE;

			if( ( media_size % EXE_TEST_READ_BUFFER_SIZE ) != 0 )
			{
				number_of_iterations += 1;
			}
		}
		if( libcthreads_thread_pool_create(
		     &thread_pool,
		     NULL,
		     number_of_threads,
		     number_of_iterations,
		     (int (*)(intptr_t *, void *)) &exe_test_read_callback_function,
		     NULL,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create thread pool.",
			 function );

			goto on_error;
		}
		for( iteration = 0;
		     iteration < number_of_iterations;
		     iteration++ )
		{
			if( libcthreads_thread_pool_push(
			     thread_pool,
			     (intptr_t *) section,
			     &error ) == -1 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to push section onto queue.",
				 function );

				goto on_error;
			}
		}
		if( libcthreads_thread_pool_join(
		     &thread_pool,
		     &error ) != 1 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to join thread pool.",
			 function );

			goto on_error;
		}
	}
	if( libexe_section_get_offset(
	     section,
	     &result_offset,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset.",
		 function );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Testing multi-threaded read buffer at offset: 0\t" );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	if( result == 1 )
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

	return( result );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );

		libcerror_error_free(
		 &error );
	}
	if( thread_pool != NULL )
	{
		libcthreads_thread_pool_join(
		 &thread_pool,
		 NULL );
	}
	return( -1 );
}

/* Tests reading a file in multiple threads
 * Returns 1 if successful, 0 if not or -1 on error
 */
int exe_test_read_multi_thread(
     libcstring_system_character_t *source,
     libcerror_error_t **error )
{
	libexe_file_t *file       = NULL;
	libexe_section_t *section = NULL;
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
	for( section_index = 0;
	     section_index < number_of_sections;
	     section_index++ )
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
		 "Section: %d size: %" PRIu64 " bytes\n",
		 section_index,
		 section_size );

		if( section_size == 0 )
		{
			result = 1;
		}
		else
		{
			result = exe_test_read_from_section_multi_thread(
				  section,
				  section_size,
				  EXE_TEST_READ_NUMBER_OF_THREADS );

			if( result == -1 )
			{
				fprintf(
				 stderr,
				 "Unable to read from file in multiple threads.\n" );

				goto on_error;
			}
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
		if( result != 1 )
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

#endif /* defined( HAVE_MULTI_THREAD_SUPPORT ) */

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

#if defined( HAVE_DEBUG_OUTPUT ) && defined( EXE_TEST_READ_VERBOSE )
	libexe_notify_set_verbose(
	 1 );
	libexe_notify_set_stream(
	 stderr,
	 NULL );
#endif
	if( exe_test_read(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to read file.\n" );

		goto on_error;
	}
/* TODO disabled for now
#if defined( HAVE_MULTI_THREAD_SUPPORT )
	if( exe_test_read_multi_thread(
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to read file in multiple threads.\n" );

		goto on_error;
	}
#endif
*/
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

