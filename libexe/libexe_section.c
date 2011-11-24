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
#include "libexe_libfcache.h"
#include "libexe_libfdata.h"
#include "libexe_section.h"
#include "libexe_section_io_handle.h"

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
	if( *section != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid section value already set.",
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
	if( libfcache_cache_initialize(
	     &( internal_section->data_cache ),
	     LIBEXE_MAXIMUM_CACHE_ENTRIES_SECTION_DATA,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data cache.",
		 function );

		goto on_error;
	}
	internal_section->io_handle          = io_handle;
	internal_section->section_descriptor = section_descriptor;
	internal_section->flags              = flags;

	*section = (libexe_section_t *) internal_section;

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
	int result                                  = 1;

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

				result = -1;
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

				result = -1;
			}
		}
		if( libfcache_cache_free(
		     &( internal_section->data_cache ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data cache.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_section );
	}
	return( result );
}

/* Retrieves the size of the ASCII formatted name
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
	if( name_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name size.",
		 function );

		return( -1 );
	}
	*name_size = internal_section->section_descriptor->name_size;

	return( 1 );
}

/* Retrieves the ASCII formatted name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libexe_section_get_name(
     libexe_section_t *section,
     char *name,
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
	if( name_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( name_size < internal_section->section_descriptor->name_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid name value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     name,
	     internal_section->section_descriptor->name,
	     internal_section->section_descriptor->name_size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libexe_section_read_buffer(
         libexe_section_t *section,
         void *buffer,
         size_t buffer_size,
         liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_read_buffer";
	ssize_t read_count                          = 0;

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
		 "%s: invalid section - missing section descriptor.",
		 function );

		return( -1 );
	}
	read_count = libfdata_block_read_buffer(
	              internal_section->section_descriptor->data_block,
	              internal_section->file_io_handle,
	              internal_section->data_cache,
	              buffer,
	              buffer_size,
	              error );

	if( read_count == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer from section data block.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libexe_section_read_random(
         libexe_section_t *section,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         liberror_error_t **error )
{
	static char *function = "libexe_section_read_random";
	ssize_t read_count    = 0;

	if( libexe_section_seek_offset(
	     section,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	read_count = libexe_section_read_buffer(
	              section,
	              buffer,
	              buffer_size,
	              error );

	if( read_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libexe_section_seek_offset(
         libexe_section_t *section,
         off64_t offset,
         int whence,
         liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_seek_offset";

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
		 "%s: invalid section - missing section descriptor.",
		 function );

		return( -1 );
	}
	offset = libfdata_block_seek_offset(
	          internal_section->section_descriptor->data_block,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek in section data block.",
		 function );

		return( -1 );
	}
	return( offset );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int libexe_section_get_size(
     libexe_section_t *section,
     size64_t *size,
     liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_get_size";

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
		 "%s: invalid section - missing section descriptor.",
		 function );

		return( -1 );
	}
	if( libfdata_block_get_size(
	     internal_section->section_descriptor->data_block,
	     size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve section data block size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the virtual address
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libexe_section_get_virtual_address(
     libexe_section_t *section,
     uint32_t *virtual_address,
     liberror_error_t **error )
{
	libexe_internal_section_t *internal_section = NULL;
	static char *function                       = "libexe_section_get_virtual_address";

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
	if( virtual_address == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid virtual address.",
		 function );

		return( -1 );
	}
	*virtual_address = internal_section->section_descriptor->virtual_address;

	return( 1 );
}

/* Retrieves the section data file IO handle
 * Returns 1 if successful -1 on error
 */
int libexe_section_get_data_file_io_handle(
     libexe_section_t *section,
     libbfio_handle_t **file_io_handle,
     liberror_error_t **error )
{
	libexe_section_io_handle_t *io_handle = NULL;
	static char *function                 = "libexe_section_get_data_file_io_handle";

	if( libexe_section_io_handle_initialize(
	     &io_handle,
	     section,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create section file IO handle.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_initialize(
	     file_io_handle,
	     (intptr_t *) io_handle,
	     (int (*)(intptr_t *, liberror_error_t **)) libexe_section_io_handle_free,
	     (int (*)(intptr_t **, intptr_t *, liberror_error_t **)) libexe_section_io_handle_clone,
	     (int (*)(intptr_t *, int flags, liberror_error_t **)) libexe_section_io_handle_open,
	     (int (*)(intptr_t *, liberror_error_t **)) libexe_section_io_handle_close,
	     (ssize_t (*)(intptr_t *, uint8_t *, size_t, liberror_error_t **)) libexe_section_io_handle_read,
	     (ssize_t (*)(intptr_t *, const uint8_t *, size_t, liberror_error_t **)) libexe_section_io_handle_write,
	     (off64_t (*)(intptr_t *, off64_t, int, liberror_error_t **)) libexe_section_io_handle_seek_offset,
	     (int (*)(intptr_t *, liberror_error_t **)) libexe_section_io_handle_exists,
	     (int (*)(intptr_t *, liberror_error_t **)) libexe_section_io_handle_is_open,
	     (int (*)(intptr_t *, size64_t *, liberror_error_t **)) libexe_section_io_handle_get_size,
	     LIBBFIO_FLAG_IO_HANDLE_MANAGED | LIBBFIO_FLAG_IO_HANDLE_CLONE_BY_FUNCTION,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( io_handle != NULL )
	{
		libexe_section_io_handle_free(
		 io_handle,
		 NULL );
	}
	return( -1 );
}

