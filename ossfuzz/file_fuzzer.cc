/*
 * OSS-Fuzz target for libexe file type
 *
 * Copyright (C) 2011-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libexe.h"

#if !defined( LIBEXE_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBEXE_EXTERN \
int libexe_file_open_file_io_handle(
      libexe_file_t *file,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libexe_error_t **error );

/* Determines if a file contains an EXE file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBEXE_EXTERN \
int libexe_check_file_signature_file_io_handle(
      libbfio_handle_t *file_io_handle,
      libexe_error_t **error );

/* Retrieves the section data file io handle
 * Returns 1 if successful or -1 on error
 */
LIBEXE_EXTERN \
int libexe_section_get_data_file_io_handle(
      libexe_section_t *section,
      libbfio_handle_t **file_io_handle,
      libexe_error_t **error );

#endif /* !defined( LIBEXE_HAVE_BFIO ) */

/* The ASCII codepages that are supported by libexe_file_set_ascii_codepage
 */
static const int supported_ascii_codepages[ 15 ] =
{
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
	LIBEXE_CODEPAGE_WINDOWS_1258
};

/* The maximum number of sections to process for a specific input
 */
#define FILE_FUZZER_MAXIMUM_NUMBER_OF_SECTIONS	8

/* The maximum size of a name buffer
 */
#define FILE_FUZZER_MAX_NAME_SIZE	256

/* Retrieves a read size (buffer size) from the input
 */
size_t file_fuzzer_get_read_size(
        const uint8_t *data,
        size_t size )
{
	if( size == 0 )
	{
		return( 1 );
	}
	return( 1 + ( size % FILE_FUZZER_MAX_NAME_SIZE ) );
}

/* Retrieves a seek offset from the input
 */
off64_t file_fuzzer_get_seek_offset(
         const uint8_t *data,
         size_t size )
{
	off64_t seek_offset = 0;
	int number_of_bytes = 0;
	int index           = 0;

	if( size > 4 )
	{
		number_of_bytes = 4;
	}
	else
	{
		number_of_bytes = (int) size;
	}
	for( index = 0;
	     index < number_of_bytes;
	     index++ )
	{
		seek_offset = ( seek_offset << 8 ) | (off64_t) data[ size - 1 - index ];
	}
	return( seek_offset );
}

/* Fuzzes a section
 */
void file_fuzzer_fuzz_section(
      libexe_section_t *section,
      const uint8_t *data,
      size_t size,
      char *name )
{
	uint16_t utf16_name[ 16 ]               = { 0 };

	libbfio_handle_t *section_file_io_handle = NULL;
	off64_t offset                           = 0;
	off64_t seek_offset                      = 0;
	off64_t start_offset                     = 0;
	size64_t size_64bit                      = 0;
	size_t name_size                         = 0;
	size_t read_size                         = 0;
	uint32_t virtual_address                 = 0;
	int result                               = 0;

	name_size = FILE_FUZZER_MAX_NAME_SIZE;

	if( libexe_section_get_name_size(
	     section,
	     &name_size,
	     NULL ) == 1 )
	{
		if( name_size > FILE_FUZZER_MAX_NAME_SIZE )
		{
			name_size = FILE_FUZZER_MAX_NAME_SIZE;
		}
		libexe_section_get_name(
		 section,
		 name,
		 name_size,
		 NULL );
	}
	name_size = FILE_FUZZER_MAX_NAME_SIZE;

	if( libexe_section_get_utf8_name_size(
	     section,
	     &name_size,
	     NULL ) == 1 )
	{
		if( name_size > FILE_FUZZER_MAX_NAME_SIZE )
		{
			name_size = FILE_FUZZER_MAX_NAME_SIZE;
		}
		libexe_section_get_utf8_name(
		 section,
		 (uint8_t *) name,
		 name_size,
		 NULL );
	}
	libexe_section_get_utf16_name_size(
	 section,
	 &name_size,
	 NULL );

	libexe_section_get_utf16_name(
	 section,
	 utf16_name,
	 16,
	 NULL );

	libexe_section_get_size(
	 section,
	 &size_64bit,
	 NULL );

	libexe_section_get_start_offset(
	 section,
	 &start_offset,
	 NULL );

	libexe_section_get_virtual_address(
	 section,
	 &virtual_address,
	 NULL );

	read_size = file_fuzzer_get_read_size(
	             data,
	             size );

	libexe_section_read_buffer(
	 section,
	 (uint8_t *) name,
	 read_size,
	 NULL );

	seek_offset = file_fuzzer_get_seek_offset(
	               data,
	               size );

	libexe_section_seek_offset(
	 section,
	 seek_offset,
	 size > 2 ? (int) ( data[ 1 ] % 3 ) : 0,
	 NULL );

	libexe_section_get_offset(
	 section,
	 &offset,
	 NULL );

	libexe_section_read_buffer_at_offset(
	 section,
	 (uint8_t *) name,
	 read_size,
	 seek_offset,
	 NULL );

	result = libexe_section_get_data_file_io_handle(
	          section,
	          &section_file_io_handle,
	          NULL );
       
	if( ( result == 1 )
	 && ( section_file_io_handle != NULL ) )
	{
		libbfio_handle_open(
		 section_file_io_handle,
		 LIBBFIO_OPEN_READ,
		 NULL );

		libbfio_handle_exists(
		 section_file_io_handle,
		 NULL );

		libbfio_handle_is_open(
		 section_file_io_handle,
		 NULL );

		libbfio_handle_get_size(
		 section_file_io_handle,
		 &size_64bit,
		 NULL );

		libbfio_handle_read_buffer(
		 section_file_io_handle,
		 (uint8_t *) name,
		 read_size,
		 NULL );

		libbfio_handle_seek_offset(
		 section_file_io_handle,
		 seek_offset,
		 0,
		 NULL );

		libbfio_handle_read_buffer_at_offset(
		 section_file_io_handle,
		 (uint8_t *) name,
		 read_size,
		 seek_offset,
		 NULL );

		libbfio_handle_close(
		 section_file_io_handle,
		 NULL );

		libbfio_handle_free(
		 &section_file_io_handle,
		 NULL );
	}
	libexe_section_free(
	 &section,
	 NULL );
}

/* Fuzzes the sections of a file
 */
static void file_fuzzer_fuzz_sections(
        libexe_file_t *file,
        const uint8_t *data,
        size_t size,
        char *name )
{
	char candidate_name[ 9 ]        = { 0 };
	libexe_section_t *section       = NULL;
	libexe_section_t *section_by_name = NULL;
	int number_of_sections          = 0;
	int section_index               = 0;
	size_t candidate_name_length    = 0;
	size_t name_size                = 0;

	for( candidate_name_length = 0;
	     candidate_name_length < 8;
	     candidate_name_length++ )
	{
		candidate_name[ candidate_name_length ] = (char) ( size > 0 ? data[ ( (size_t) candidate_name_length * size ) / 8 ] : 0 );
	}
	candidate_name[ 8 ] = 0;

	libexe_file_get_section_by_name(
	 file,
	 candidate_name,
	 8,
	 &section_by_name,
	 NULL );

	if( section_by_name != NULL )
	{
		libexe_section_free(
		 &section_by_name,
		 NULL );
	}
	if( libexe_file_get_number_of_sections(
	     file,
	     &number_of_sections,
	     NULL ) != 1 )
	{
		return;
	}
	if( number_of_sections <= 0 )
	{
		return;
	}
	section = NULL;

	if( libexe_file_get_section_by_index(
	     file,
	     0,
	     &section,
	     NULL ) == 1 )
	{
		if( section != NULL )
		{
			name_size = FILE_FUZZER_MAX_NAME_SIZE;

			if( libexe_section_get_name_size(
			     section,
			     &name_size,
			     NULL ) == 1 )
			{
				if( name_size > 1 )
				{
					if( libexe_section_get_name(
					     section,
					     name,
					     FILE_FUZZER_MAX_NAME_SIZE,
					     NULL ) == 1 )
					{
						section_by_name = NULL;

						libexe_file_get_section_by_name(
						 file,
						 name,
						 ( size_t ) ( name_size - 1 ),
						 &section_by_name,
						 NULL );

						if( section_by_name != NULL )
						{
							libexe_section_free(
							 &section_by_name,
							 NULL );
						}
					}
				}
			}
			libexe_section_free(
			 &section,
			 NULL );
		}
	}
	for( section_index = 0;
	     section_index < number_of_sections
	  && section_index < FILE_FUZZER_MAXIMUM_NUMBER_OF_SECTIONS;
	     section_index++ )
	{
		section = NULL;

		if( libexe_file_get_section_by_index(
		     file,
		     section_index,
		     &section,
		     NULL ) != 1 )
		{
			continue;
		}
		if( section == NULL )
		{
			continue;
		}
		file_fuzzer_fuzz_section(
		 section,
		 data,
		 size,
		 name );
	}
}

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	char name[ FILE_FUZZER_MAX_NAME_SIZE ]     = { 0 };

	libbfio_handle_t *signature_file_io_handle = NULL;
	libbfio_handle_t *file_io_handle           = NULL;
	libexe_file_t *file                        = NULL;
	int access_flags_read                      = 0;
	int ascii_codepage                         = 0;
	int codepage                               = 0;
	int codepage_index                         = 0;

	access_flags_read = libexe_get_access_flags_read();

	libexe_set_codepage(
	 0,
	 NULL );

	libexe_get_codepage(
	 &codepage,
	 NULL );

	if( libbfio_memory_range_initialize(
	     &signature_file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     signature_file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_signature;
	}
	libexe_check_file_signature_file_io_handle(
	 signature_file_io_handle,
	 NULL );

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		goto on_error_signature;
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libexe_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libexe_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBEXE_OPEN_READ,
	     NULL ) == 1 )
	{
		libexe_file_get_ascii_codepage(
		 file,
		 &ascii_codepage,
		 NULL );

		codepage_index = size > 0 ? ( int ) ( data[ 0 ] % 15 ) : 0;

		libexe_file_set_ascii_codepage(
		 file,
		 supported_ascii_codepages[ codepage_index ],
		 NULL );

		file_fuzzer_fuzz_sections(
		 file,
		 data,
		 size,
		 name );

		libexe_file_signal_abort(
		 file,
		 NULL );
	}
	libexe_file_close(
	 file,
	 NULL );

on_error_libbfio:
	libexe_file_free(
	 &file,
	 NULL );

on_error_signature:
	libbfio_handle_free(
	 &signature_file_io_handle,
	 NULL );

	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
