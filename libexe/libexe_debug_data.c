/*
 * Debug data functions
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
#include <memory.h>
#include <types.h>

#include "libexe_debug_data.h"
#include "libexe_libcerror.h"
#include "libexe_libcnotify.h"
#include "libexe_libfcache.h"
#include "libexe_libfdata.h"

/* Creates a debug data
 * Make sure the value debug_data is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_debug_data_initialize(
     libexe_debug_data_t **debug_data,
     libcerror_error_t **error )
{
	static char *function = "libexe_debug_data_initialize";

	if( debug_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug data.",
		 function );

		return( -1 );
	}
	if( *debug_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid debug data value already set.",
		 function );

		return( -1 );
	}
	*debug_data = memory_allocate_structure(
	               libexe_debug_data_t );

	if( *debug_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create debug data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *debug_data,
	     0,
	     sizeof( libexe_debug_data_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear debug data.",
		 function );

		memory_free(
		 *debug_data );

		*debug_data = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *debug_data != NULL )
	{
		memory_free(
		 *debug_data );

		*debug_data = NULL;
	}
	return( -1 );
}

/* Frees a debug data
 * Returns 1 if successful or -1 on error
 */
int libexe_debug_data_free(
     libexe_debug_data_t **debug_data,
     libcerror_error_t **error )
{
	static char *function = "libexe_debug_data_free";

	if( debug_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug data.",
		 function );

		return( -1 );
	}
	if( *debug_data != NULL )
	{
		memory_free(
		 *debug_data );

		*debug_data = NULL;
	}
	return( 1 );
}

/* Reads the debug data
 * Returns 1 if successful or -1 on error
 */
int libexe_debug_data_read(
     libexe_debug_data_t *debug_data,
     libbfio_handle_t *file_io_handle,
     uint32_t file_offset,
     uint32_t size,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libexe_debug_data_read";
	size_t read_count     = 0;

	if( debug_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid debug data.",
		 function );

		return( -1 );
	}
	if( ( size == 0 )
	 || ( size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid size value out of bounds.",
		 function );

		return( -1 );
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create debug data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading debug data at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              size,
	              (off64_t) file_offset,
	              error );

	if( read_count != (ssize_t) size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read debug data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: debug data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 (size_t) size,
		 0 );
	}
#endif
	/* TODO extract values */

	memory_free(
	 data );

	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

