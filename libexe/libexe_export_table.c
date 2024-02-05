/*
 * Export table functions
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

#include "libexe_export_table.h"
#include "libexe_libcerror.h"
#include "libexe_libcnotify.h"
#include "libexe_libfcache.h"
#include "libexe_libfdata.h"

/* Creates an export table
 * Make sure the value export_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_export_table_initialize(
     libexe_export_table_t **export_table,
     libcerror_error_t **error )
{
	static char *function = "libexe_export_table_initialize";

	if( export_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export table.",
		 function );

		return( -1 );
	}
	if( *export_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid export table value already set.",
		 function );

		return( -1 );
	}
	*export_table = memory_allocate_structure(
	                 libexe_export_table_t );

	if( *export_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create export table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *export_table,
	     0,
	     sizeof( libexe_export_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear export table.",
		 function );

		memory_free(
		 *export_table );

		*export_table = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *export_table != NULL )
	{
		memory_free(
		 *export_table );

		*export_table = NULL;
	}
	return( -1 );
}

/* Frees an export table
 * Returns 1 if successful or -1 on error
 */
int libexe_export_table_free(
     libexe_export_table_t **export_table,
     libcerror_error_t **error )
{
	static char *function = "libexe_export_table_free";

	if( export_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export table.",
		 function );

		return( -1 );
	}
	if( *export_table != NULL )
	{
		memory_free(
		 *export_table );

		*export_table = NULL;
	}
	return( 1 );
}

/* Reads the export table
 * Returns 1 if successful or -1 on error
 */
int libexe_export_table_read(
     libexe_export_table_t *export_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     uint32_t size,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libexe_export_table_read";
	size_t read_count     = 0;

	if( export_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid export table.",
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
		 "%s: unable to create export table.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading export table at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read export table data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: export table:\n",
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

