/*
 * Input/Output (IO) handle functions
 *
 * Copyright (c) 2011, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "libexe_array_type.h"
#include "libexe_codepage.h"
#include "libexe_definitions.h"
#include "libexe_io_handle.h"
#include "libexe_libbfio.h"
#include "libexe_unused.h"

#include "exe_file_header.h"

const char *exe_mz_file_signature = "MZ";

/* Initialize an IO handle
 * Make sure the value io_handle is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_initialize(
     libexe_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libexe_io_handle_initialize";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle == NULL )
	{
		*io_handle = memory_allocate_structure(
		              libexe_io_handle_t );

		if( *io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create IO handle.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     *io_handle,
		     0,
		     sizeof( libexe_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			goto on_error;
		}
		( *io_handle )->ascii_codepage = LIBEXE_CODEPAGE_WINDOWS_1252;
	}
	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees a IO handle
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_free(
     libexe_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "libexe_io_handle_free";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_read_file_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     liberror_error_t **error )
{
	exe_mz_file_header_t mz_file_header;

	static char *function = "libexe_io_handle_read_file_header";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              (uint8_t *) &mz_file_header,
	              sizeof( exe_mz_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( exe_mz_file_header_t ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: file header:\n",
		 function );
		libnotify_print_data(
		 (uint8_t *) &mz_file_header,
		 sizeof( exe_mz_file_header_t ) );
	}
#endif
	if( memory_compare(
	     mz_file_header.signature,
	     exe_mz_file_signature,
	     2 ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: signature\t\t\t\t: %c%c\n",
		 function,
		 mz_file_header.signature[ 0 ],
		 mz_file_header.signature[ 1 ] );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.last_page_size,
		 value_16bit );
		libnotify_printf(
		 "%s: last page size\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.number_of_pages,
		 value_16bit );
		libnotify_printf(
		 "%s: number of pages\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.number_of_relocation_entries,
		 value_16bit );
		libnotify_printf(
		 "%s: number of relocation entries\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.number_of_header_paragraphs,
		 value_16bit );
		libnotify_printf(
		 "%s: number of header paragraphs\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.minimum_allocated_paragraphs,
		 value_16bit );
		libnotify_printf(
		 "%s: minimum allocated paragraphs\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.maximum_allocated_paragraphs,
		 value_16bit );
		libnotify_printf(
		 "%s: maximum allocated paragraphs\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.initial_stack_segment,
		 value_16bit );
		libnotify_printf(
		 "%s: initial stack segment\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.initial_stack_pointer,
		 value_16bit );
		libnotify_printf(
		 "%s: initial stack pointer\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.checksum,
		 value_16bit );
		libnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint32_little_endian(
		 mz_file_header.entry_point,
		 value_32bit );
		libnotify_printf(
		 "%s: entry point\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.relocation_table_offset,
		 value_16bit );
		libnotify_printf(
		 "%s: relocation table offset\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 mz_file_header.overlay_number,
		 value_16bit );
		libnotify_printf(
		 "%s: overlay number\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

