/*
 * COFF header functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libexe_coff_header.h"
#include "libexe_debug.h"
#include "libexe_libcerror.h"
#include "libexe_libcnotify.h"
#include "libexe_libfdatetime.h"

#include "exe_file_header.h"

/* Creates a COFF header
 * Make sure the value coff_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_header_initialize(
     libexe_coff_header_t **coff_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_coff_header_initialize";

	if( coff_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid COFF header.",
		 function );

		return( -1 );
	}
	if( *coff_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid COFF header value already set.",
		 function );

		return( -1 );
	}
	*coff_header = memory_allocate_structure(
	                libexe_coff_header_t );

	if( *coff_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create COFF header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *coff_header,
	     0,
	     sizeof( libexe_coff_header_t ) ) == NULL )
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
	if( *coff_header != NULL )
	{
		memory_free(
		 *coff_header );

		*coff_header = NULL;
	}
	return( -1 );
}

/* Frees a COFF header
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_header_free(
     libexe_coff_header_t **coff_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_coff_header_free";

	if( coff_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid COFF header.",
		 function );

		return( -1 );
	}
	if( *coff_header != NULL )
	{
		memory_free(
		 *coff_header );

		*coff_header = NULL;
	}
	return( 1 );
}

/* Reads the COFF header
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_header_read_data(
     libexe_coff_header_t *coff_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libexe_coff_header_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( coff_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid COFF header.",
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
	if( data_size < sizeof( exe_coff_header_t ) )
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
		 "%s: COFF header:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( exe_coff_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (exe_coff_header_t *) data )->number_of_sections,
	 coff_header->number_of_sections );

	byte_stream_copy_to_uint32_little_endian(
	 ( (exe_coff_header_t *) data )->creation_time,
	 coff_header->creation_time );

	byte_stream_copy_to_uint16_little_endian(
	 ( (exe_coff_header_t *) data )->optional_header_size,
	 coff_header->optional_header_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_coff_header_t *) data )->target_architecture_type,
		 value_16bit );
		libcnotify_printf(
		 "%s: target architecture type\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of sections\t\t\t: %" PRIu16 "\n",
		 function,
		 coff_header->number_of_sections );

		if( libexe_debug_print_posix_time_value(
		     function,
		     "creation time\t\t\t\t",
		     ( (exe_coff_header_t *) data )->creation_time,
		     4,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_POSIX_TIME_VALUE_TYPE_SECONDS_32BIT_SIGNED,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print POSIX time value.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_header_t *) data )->symbol_table_offset,
		 value_32bit );
		libcnotify_printf(
		 "%s: symbol table offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_header_t *) data )->number_of_symbols,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of symbols\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: optional header size\t\t\t: %" PRIu16 "\n",
		 function,
		 coff_header->optional_header_size );

		byte_stream_copy_to_uint16_little_endian(
		 ( (exe_coff_header_t *) data )->characteristic_flags,
		 value_16bit );
		libcnotify_printf(
		 "%s: characteristic flags\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );
		libexe_debug_print_file_characteristic_flags(
		 value_16bit );
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads the COFF header from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_header_read_file_io_handle(
     libexe_coff_header_t *coff_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t data[ sizeof( exe_coff_header_t ) ];

	static char *function = "libexe_coff_header_read_file_io_handle";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading COFF header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              sizeof( exe_coff_header_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( exe_coff_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read COFF header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libexe_coff_header_read_data(
	     coff_header,
	     data,
	     sizeof( exe_coff_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read COFF header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	return( 1 );
}

