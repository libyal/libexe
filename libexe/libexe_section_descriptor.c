/*
 * Section decriptor functions
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
	if( *section_descriptor == NULL )
	{
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

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( *section_descriptor != NULL )
	{
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
     libexe_section_descriptor_t *section_descriptor,
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

		return( 1 );
	}
	memory_free(
	 section_descriptor );

	return( result );
}

/* Clones the section descriptor
 * Returns 1 if successful or -1 on error
 */
int libexe_section_descriptor_clone(
     libexe_section_descriptor_t **destination_section_descriptor,
     libexe_section_descriptor_t *source_section_descriptor,
     liberror_error_t **error )
{
	static char *function = "libexe_section_descriptor_clone";

	if( destination_section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination section descriptor.",
		 function );

		return( -1 );
	}
	if( *destination_section_descriptor != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination section descriptor value already set.",
		 function );

		return( -1 );
	}
	if( source_section_descriptor == NULL )
	{
		*destination_section_descriptor = NULL;

		return( 1 );
	}
	*destination_section_descriptor = memory_allocate_structure(
			                   libexe_section_descriptor_t );

	if( *destination_section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination section descriptor.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     *destination_section_descriptor,
	     source_section_descriptor,
	     sizeof( libexe_section_descriptor_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy source to destination section descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *destination_section_descriptor != NULL )
	{
		memory_free(
		 *destination_section_descriptor );

		*destination_section_descriptor = NULL;
	}
	return( -1 );
}

/* Reads a section descriptor
 * Returns 1 if successful or -1 on error
 */
int libexe_section_descriptor_read(
     libexe_section_descriptor_t *section_descriptor,
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     liberror_error_t **error )
{
}

