/*
 * Section functions
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
#include <memory.h>
#include <types.h>

#include <liberror.h>

#include "libexe_definitions.h"
#include "libexe_io_handle.h"
#include "libexe_libbfio.h"
#include "libexe_section.h"

/* Initializes the section and its values
 * Returns 1 if successful or -1 on error
 */
int libexe_section_initialize(
     libexe_section_t **section,
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libexe_section_descriptor_t *section_descriptor,
     uint8_t flags,
     liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_initialize";

	if( section == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section.",
		 function );

		return( -1 );
	}
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
	if( ( flags & ~( LIBEXE_SECTION_FLAG_MANAGED_FILE_IO_HANDLE ) ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02" PRIx8 ".",
		 function,
		 flags );

		return( -1 );
	}
	if( *section == NULL )
	{
		internal_section = memory_allocate_structure(
		                    libexe_internal_section_t );

		if( internal_section == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create internal section.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     internal_section,
		     0,
		     sizeof( libexe_internal_section_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear internal section.",
			 function );

			memory_free(
			 internal_section );

			return( -1 );
		}
		if( ( flags & LIBEXE_SECTION_FLAG_MANAGED_FILE_IO_HANDLE ) == 0 )
		{
			internal_section->file_io_handle = file_io_handle;
		}
		else
		{
			if( libbfio_handle_clone(
			     &( internal_section->file_io_handle ),
			     file_io_handle,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy file IO handle.",
				 function );

				goto on_error;
			}
			if( libbfio_handle_set_open_on_demand(
			     internal_section->file_io_handle,
			     1,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to set open on demand in file IO handle.",
				 function );

				goto on_error;
			}
		}
		internal_section->io_handle          = io_handle;
		internal_section->section_descriptor = section_descriptor;
		internal_section->flags              = flags;

		*section = (libexe_section_t *) internal_section;
	}
	return( 1 );

on_error:
	if( internal_section != NULL )
	{
		if( ( flags & LIBEXE_SECTION_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_section->file_io_handle != NULL )
			{
				libbfio_handle_free(
				 &( internal_section->file_io_handle ),
				 NULL );
			}
		}
		memory_free(
		 internal_section );
	}
	return( -1 );
}

/* Frees an section
 * Returns 1 if successful or -1 on error
 */
int libexe_section_free(
     libexe_section_t **section,
     liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_free";

	if( section == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section.",
		 function );

		return( -1 );
	}
	if( *section != NULL )
	{
		internal_section = (libexe_internal_section_t *) *section;
		*section         = NULL;

		/* The io_handle and section_descriptor references are freed elsewhere
		 */
		if( ( internal_section->flags & LIBEXE_SECTION_FLAG_MANAGED_FILE_IO_HANDLE ) != 0 )
		{
			if( internal_section->file_io_handle != NULL )
			{
				if( libbfio_handle_close(
				     internal_section->file_io_handle,
				     error ) != 0 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_CLOSE_FAILED,
					 "%s: unable to close file IO handle.",
					 function );

					return( -1 );
				}
				if( libbfio_handle_free(
				     &( internal_section->file_io_handle ),
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free file IO handle.",
					 function );

					return( -1 );
				}
			}
		}
		memory_free(
		 internal_section );
	}
	return( 1 );
}

/* Retrieves the size of the name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libexe_section_get_name_size(
     libexe_section_t *section,
     size_t *name_size,
     liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_get_name_size";

	if( section == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section.",
		 function );

		return( -1 );
	}
	internal_section = (libexe_internal_section_t *) section;

	if( internal_section->section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal section - missing section descriptor.",
		 function );

		return( -1 );
	}
/* TODO */
	return( 1 );
}

/* Retrieves the name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libexe_section_get_name(
     libexe_section_t *section,
     uint8_t *name,
     size_t name_size,
     liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_get_name";

	if( section == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid section.",
		 function );

		return( -1 );
	}
	internal_section = (libexe_internal_section_t *) section;

	if( internal_section->section_descriptor == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal section - missing section descriptor.",
		 function );

		return( -1 );
	}
/* TODO */
	return( 1 );
}

