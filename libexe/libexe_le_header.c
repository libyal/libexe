/*
 * LE header functions
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

#include "libexe_le_header.h"
#include "libexe_libcerror.h"
#include "libexe_libcnotify.h"

#include "exe_le_header.h"

/* Creates a LE header
 * Make sure the value le_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_le_header_initialize(
     libexe_le_header_t **le_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_le_header_initialize";

	if( le_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid LE header.",
		 function );

		return( -1 );
	}
	if( *le_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid LE header value already set.",
		 function );

		return( -1 );
	}
	*le_header = memory_allocate_structure(
	              libexe_le_header_t );

	if( *le_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create LE header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *le_header,
	     0,
	     sizeof( libexe_le_header_t ) ) == NULL )
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
	if( *le_header != NULL )
	{
		memory_free(
		 *le_header );

		*le_header = NULL;
	}
	return( -1 );
}

/* Frees a LE header
 * Returns 1 if successful or -1 on error
 */
int libexe_le_header_free(
     libexe_le_header_t **le_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_le_header_free";

	if( le_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid LE header.",
		 function );

		return( -1 );
	}
	if( *le_header != NULL )
	{
		memory_free(
		 *le_header );

		*le_header = NULL;
	}
	return( 1 );
}

/* Reads the LE header
 * Returns 1 if successful or -1 on error
 */
int libexe_le_header_read_data(
     libexe_le_header_t *le_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libexe_le_header_read_data";

	if( le_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid LE header.",
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
	if( data_size < sizeof( exe_le_header_t ) )
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
		 "%s: LE header:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( exe_le_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     ( (exe_le_header_t *) data )->signature,
	     EXE_LE_SIGNATURE,
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c\n",
		 function,
		 ( (exe_le_header_t *) data )->signature[ 0 ],
		 ( (exe_le_header_t *) data )->signature[ 1 ] );
/* TODO */

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads the LE header from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libexe_le_header_read_file_io_handle(
     libexe_le_header_t *le_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t data[ sizeof( exe_le_header_t ) ];

	static char *function = "libexe_le_header_read_file_io_handle";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading LE header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              sizeof( exe_le_header_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( exe_le_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read LE header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libexe_le_header_read_data(
	     le_header,
	     data,
	     sizeof( exe_le_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read LE header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	return( 1 );
}

