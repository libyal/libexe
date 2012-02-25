/*
 * Section decriptor functions
 *
 * Copyright (c) 2011-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <libcstring.h>
#include <liberror.h>
#include <libnotify.h>

#include "libexe_io_handle.h"
#include "libexe_libbfio.h"
#include "libexe_section_descriptor.h"

#include "exe_section_table.h"

/* Initialize the section descriptor
 * Returns 1 if successful or -1 on error
 */
int libexe_section_descriptor_initialize(
     libexe_section_descriptor_t **section_descriptor,
     liberror_error_t **error )
{
	static char *function = "libexe_section_descriptor_initialize";

	if( section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section descriptor.",
		 function );

		return( -1 );
	}
	if( *section_descriptor != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid section descriptor value already set.",
		 function );

		return( -1 );
	}
	*section_descriptor = memory_allocate_structure(
	                       libexe_section_descriptor_t );

	if( *section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create section descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *section_descriptor,
	     0,
	     sizeof( libexe_section_descriptor_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear section descriptor.",
		 function );

		memory_free(
		 *section_descriptor );

		*section_descriptor = NULL;

		return( -1 );
	}
	if( libfdata_block_initialize(
	     &( ( *section_descriptor )->data_block ),
	     NULL,
	     NULL,
	     NULL,
	     &libfdata_block_read_segment_data,
	     0,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data block.",
		 function );

		goto on_error;
	}
	if( libfdata_block_resize_segments(
	     ( *section_descriptor )->data_block,
	     1,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_RESIZE_FAILED,
		 "%s: unable to resize number of segments of data block.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *section_descriptor != NULL )
	{
		if( ( *section_descriptor )->data_block != NULL )
		{
			libfdata_block_free(
			 &( ( *section_descriptor )->data_block ),
			 NULL );
		}
		memory_free(
		 *section_descriptor );

		*section_descriptor = NULL;
	}
	return( -1 );
}

/* Frees the section descriptor including elements
 * Returns 1 if successful or -1 on error
 */
int libexe_section_descriptor_free(
     libexe_section_descriptor_t **section_descriptor,
     liberror_error_t **error )
{
	static char *function = "libexe_section_descriptor_free";
	int result            = 1;

	if( section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section descriptor.",
		 function );

		return( -1 );
	}
	if( *section_descriptor != NULL )
	{
		if( libfdata_block_free(
		     &( ( *section_descriptor )->data_block ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data block.",
			 function );

			result = -1;
		}
		memory_free(
		 *section_descriptor );

		*section_descriptor = NULL;
	}
	return( result );
}

/* Sets the data range
 * Returns 1 if successful or -1 on error
 */
int libexe_section_descriptor_set_data_range(
     libexe_section_descriptor_t *section_descriptor,
     off64_t data_offset,
     size64_t data_size,
     liberror_error_t **error )
{
	static char *function = "libexe_section_descriptor_set_data_range";

	if( section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section descriptor.",
		 function );

		return( -1 );
	}
	if( libfdata_block_set_segment_by_index(
	     section_descriptor->data_block,
	     0,
	     data_offset,
	     data_size,
	     0,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set segment in data block.",
		 function );

		return( -1 );
	}
	return( 1 );
}

