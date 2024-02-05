/*
 * MZ header functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libexe_libcerror.h"
#include "libexe_libcnotify.h"
#include "libexe_mz_header.h"

#include "exe_mz_header.h"

/* Creates a MZ header
 * Make sure the value mz_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_mz_header_initialize(
     libexe_mz_header_t **mz_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_mz_header_initialize";

	if( mz_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MZ header.",
		 function );

		return( -1 );
	}
	if( *mz_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid MZ header value already set.",
		 function );

		return( -1 );
	}
	*mz_header = memory_allocate_structure(
	              libexe_mz_header_t );

	if( *mz_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create MZ header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *mz_header,
	     0,
	     sizeof( libexe_mz_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *mz_header != NULL )
	{
		memory_free(
		 *mz_header );

		*mz_header = NULL;
	}
	return( -1 );
}

/* Frees a MZ header
 * Returns 1 if successful or -1 on error
 */
int libexe_mz_header_free(
     libexe_mz_header_t **mz_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_mz_header_free";

	if( mz_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MZ header.",
		 function );

		return( -1 );
	}
	if( *mz_header != NULL )
	{
		memory_free(
		 *mz_header );

		*mz_header = NULL;
	}
	return( 1 );
}

/* Reads the MZ header
 * Returns 1 if successful or -1 on error
 */
int libexe_mz_header_read_data(
     libexe_mz_header_t *mz_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function                 = "libexe_mz_header_read_data";
	uint16_t number_of_relocation_entries = 0;
	uint16_t relocation_table_offset      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                  = 0;
	uint16_t value_16bit                  = 0;
#endif

	if( mz_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid MZ header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < sizeof( exe_mz_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: MZ header:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( exe_mz_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     ( (exe_mz_header_t *) data )->signature,
	     EXE_MZ_SIGNATURE,
	     2 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 ( (exe_mz_header_t *) data )->number_of_relocation_entries,
	 number_of_relocation_entries );

	byte_stream_copy_to_uint16_little_endian(
	 ( (exe_mz_header_t *) data )->relocation_table_offset,
	 relocation_table_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t\t: %c%c\n",
		 function,
		 ( (exe_mz_header_t *) data )->signature[ 0 ],
		 ( (exe_mz_header_t *) data )->signature[ 1 ] );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->last_page_size,
		 value_16bit );
		libcnotify_printf(
		 "%s: last page size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->number_of_pages,
		 value_16bit );
		libcnotify_printf(
		 "%s: number of pages\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of relocation entries\t\t: %" PRIu16 "\n",
		 function,
		 number_of_relocation_entries );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->number_of_header_paragraphs,
		 value_16bit );
		libcnotify_printf(
		 "%s: number of header paragraphs\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->minimum_allocated_paragraphs,
		 value_16bit );
		libcnotify_printf(
		 "%s: minimum allocated paragraphs\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->maximum_allocated_paragraphs,
		 value_16bit );
		libcnotify_printf(
		 "%s: maximum allocated paragraphs\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->initial_stack_segment,
		 value_16bit );
		libcnotify_printf(
		 "%s: initial stack segment\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->initial_stack_pointer,
		 value_16bit );
		libcnotify_printf(
		 "%s: initial stack pointer\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->checksum,
		 value_16bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_mz_header_t *) data )->entry_point,
		 value_32bit );
		libcnotify_printf(
		 "%s: entry point\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: relocation table offset\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 relocation_table_offset );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_mz_header_t *) data )->overlay_number,
		 value_16bit );
		libcnotify_printf(
		 "%s: overlay number\t\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( relocation_table_offset >= 0x40 )
	{
/* TODO read data */
		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_mz_header_t *) data )->extended_header_offset,
		 mz_header->extended_header_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unknown1:\n",
			 function );
			libcnotify_print_data(
			 ( (exe_mz_header_t *) data )->unknown1,
			 32,
			 0 );

			libcnotify_printf(
			 "%s: extended header offset\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 mz_header->extended_header_offset );

			libcnotify_printf(
			 "%s: unknown2:\n",
			 function );
			libcnotify_print_data(
			 ( (exe_mz_header_t *) data )->unknown2,
			 112,
			 0 );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
/* TODO print data between realloc and current offset */
	if( number_of_relocation_entries > 0 )
	{
/* TODO print relation table entries */
	}
	return( 1 );
}

/* Reads the MZ header from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libexe_mz_header_read_file_io_handle(
     libexe_mz_header_t *mz_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t data[ sizeof( exe_mz_header_t ) ];

	static char *function = "libexe_mz_header_read_file_io_handle";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading MZ header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              sizeof( exe_mz_header_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( exe_mz_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read MZ header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libexe_mz_header_read_data(
	     mz_header,
	     data,
	     sizeof( exe_mz_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read MZ header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	return( 1 );
}

