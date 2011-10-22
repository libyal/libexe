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
#include "libexe_libfdata.h"
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
		if( libfdata_cache_initialize(
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
		}
		if( libfdata_cache_free(
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

/* Reads data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libexe_section_read_buffer(
         libexe_section_t *section,
         void *buffer,
         size_t buffer_size,
         liberror_error_t **error )
{
	libexe_sector_data_t *sector_data         = NULL;
	libexe_internal_section_t *internal_section = NULL;
	static char *function                     = "libexe_section_read_buffer";
	size_t buffer_offset                      = 0;
	size_t read_size                          = 0;
	size_t sector_data_offset                 = 0;
	ssize_t total_read_count                  = 0;

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

	if( internal_section->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid section - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_section->sectors_vector == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal file - missing sectors vector.",
		 function );

		return( -1 );
	}
	if( internal_section->sectors_cache == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal file - missing sectors cache.",
		 function );

		return( -1 );
	}
	if( internal_section->io_handle->current_offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid internal section - invalid IO handle - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( (size64_t) internal_section->io_handle->current_offset >= internal_section->io_handle->section_size )
	{
		return( 0 );
	}
	if( (size64_t) ( internal_section->io_handle->current_offset + buffer_size ) >= internal_section->io_handle->section_size )
	{
		buffer_size = (size_t) ( internal_section->io_handle->section_size - internal_section->io_handle->current_offset );
	}
	sector_data_offset = (size_t) ( internal_section->io_handle->current_offset % internal_section->io_handle->bytes_per_sector );

	while( buffer_size > 0 )
	{
		if( libfdata_vector_get_element_value_at_offset(
		     internal_section->sectors_vector,
		     internal_section->file_io_handle,
		     internal_section->sectors_cache,
		     internal_section->io_handle->current_offset,
		     (intptr_t **) &sector_data,
		     0,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve sector data at offset: %" PRIi64 ".",
			 function,
			 internal_section->io_handle->current_offset );

			return( -1 );
		}
		if( sector_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing sector data at offset: %" PRIi64 ".",
			 function,
			 internal_section->io_handle->current_offset );

			return( -1 );
		}
		read_size = sector_data->data_size - sector_data_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
		if( read_size == 0 )
		{
			break;
		}
		if( memory_copy(
		     &( ( (uint8_t *) buffer )[ buffer_offset ] ),
		     &( ( sector_data->data )[ sector_data_offset ] ),
		     read_size ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy sector data to buffer.",
			 function );

			return( -1 );
		}
		buffer_offset     += read_size;
		buffer_size       -= read_size;
		total_read_count  += (ssize_t) read_size;
		sector_data_offset = 0;

		internal_section->io_handle->current_offset += (off64_t) read_size;

		if( (size64_t) internal_section->io_handle->current_offset >= internal_section->io_handle->section_size )
		{
			break;
		}
		if( internal_section->io_handle->abort != 0 )
		{
			break;
		}
	}
	return( total_read_count );
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

#ifdef TODO

/* Writes (media) data at the current offset
 * Returns the number of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
ssize_t libexe_section_write_buffer(
         libexe_section_t *section,
         void *buffer,
         size_t buffer_size,
         liberror_error_t **error )
{
	return( -1 );
}

/* Writes (media) data at a specific offset,
 * Returns the number of input bytes written, 0 when no longer bytes can be written or -1 on error
 */
ssize_t libexe_section_write_random(
         libexe_section_t *section,
         const void *buffer,
         size_t buffer_size,
         off64_t offset,
         liberror_error_t **error )
{
	static char *function = "libexe_section_write_random";
	ssize_t write_count   = 0;

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
	write_count = libexe_section_write_buffer(
	               section,
	               buffer,
	               buffer_size,
	               error );

	if( write_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write buffer.",
		 function );

		return( -1 );
	}
	return( write_count );
}

#endif

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
	static char *function                     = "libexe_section_seek_offset";

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

	if( internal_section->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid section - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{	
		offset += internal_section->io_handle->current_offset;
	}
	else if( whence == SEEK_END )
	{	
		offset += (off64_t) internal_section->io_handle->section_size;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: seeking media data offset: %" PRIi64 ".\n",
		 function,
		 offset );
	}
#endif
	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	internal_section->io_handle->current_offset = offset;

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
	static char *function                     = "libexe_section_get_size";

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

	if( internal_section->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid section - missing IO handle.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = internal_section->io_handle->section_size;

	return( 1 );
}

