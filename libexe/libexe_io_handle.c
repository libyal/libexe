/*
 * Input/Output (IO) handle functions
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>

#include "libexe_codepage.h"
#include "libexe_coff_header.h"
#include "libexe_coff_optional_header.h"
#include "libexe_data_directory_descriptor.h"
#include "libexe_debug.h"
#include "libexe_definitions.h"
#include "libexe_io_handle.h"
#include "libexe_le_header.h"
#include "libexe_libbfio.h"
#include "libexe_libcerror.h"
#include "libexe_libcdata.h"
#include "libexe_libcnotify.h"
#include "libexe_libfdatetime.h"
#include "libexe_mz_header.h"
#include "libexe_ne_header.h"
#include "libexe_section_descriptor.h"
#include "libexe_unused.h"

#include "exe_file_header.h"
#include "exe_mz_header.h"
#include "exe_pe_header.h"
#include "exe_section_table.h"

const char *exe_pe_signature = "PE\x0\x0";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_initialize(
     libexe_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libexe_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libexe_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libexe_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		memory_free(
		 *io_handle );

		*io_handle = NULL;

		return( -1 );
	}
	( *io_handle )->executable_type = LIBEXE_EXECUTABLE_TYPE_MZ;
	( *io_handle )->ascii_codepage  = LIBEXE_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_free(
     libexe_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libexe_io_handle_free";
	int result            = 1;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		if( libexe_io_handle_clear(
		     *io_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to clear IO handle.",
			 function );

			result = -1;
		}
		if( ( *io_handle )->coff_header != NULL )
		{
			if( libexe_coff_header_free(
			     &( ( *io_handle )->coff_header ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free COFF header.",
				 function );

				result = -1;
			}
		}
		if( ( *io_handle )->coff_optional_header != NULL )
		{
			if( libexe_coff_optional_header_free(
			     &( ( *io_handle )->coff_optional_header ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free COFF optional header.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( result );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_clear(
     libexe_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libexe_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
/* TODO refactor
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libexe_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
*/
	if( io_handle->coff_header != NULL )
	{
		if( libexe_coff_header_free(
		     &( io_handle->coff_header ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free COFF header.",
			 function );

			return( -1 );
		}
	}
	if( io_handle->coff_optional_header != NULL )
	{
		if( libexe_coff_optional_header_free(
		     &( io_handle->coff_optional_header ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free COFF optional header.",
			 function );

			return( -1 );
		}
	}
	io_handle->executable_type = LIBEXE_EXECUTABLE_TYPE_MZ;
	io_handle->ascii_codepage  = LIBEXE_CODEPAGE_WINDOWS_1252;

	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_read_file_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint16_t *number_of_sections,
     libcerror_error_t **error )
{
	libexe_mz_header_t *mz_header   = NULL;
	static char *function           = "libexe_io_handle_read_file_header";

	if( libexe_mz_header_initialize(
	     &mz_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create MZ header.",
		 function );

		goto on_error;
	}
	if( libexe_mz_header_read_file_io_handle(
	     mz_header,
	     file_io_handle,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read MZ header.",
		 function );

		goto on_error;
	}
/* TODO check if value is sane */
	if( mz_header->extended_header_offset != 0 )
	{
/* TODO print data between current offset and extended_header_offset */

		if( libexe_io_handle_read_extended_header(
		     io_handle,
		     file_io_handle,
		     mz_header->extended_header_offset,
		     number_of_sections,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read extended header.",
			 function );

			goto on_error;
		}
	}
	if( libexe_mz_header_free(
	     &mz_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free MZ header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( mz_header != NULL )
	{
		libexe_mz_header_free(
		 &mz_header,
		 NULL );
	}
	return( -1 );
}

/* Reads the extended header
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_read_extended_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t extended_header_offset,
     uint16_t *number_of_sections,
     libcerror_error_t **error )
{
	uint8_t extended_header_data[ 2 ];

	static char *function = "libexe_io_handle_read_extended_header";
	ssize_t read_count    = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading extended header at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 extended_header_offset,
		 extended_header_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              extended_header_data,
	              2,
	              (off64_t) extended_header_offset,
	              error );

	if( read_count != 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read first 2 bytes of extended header data at offset: %" PRIu32 " (0x%08" PRIx32 ").",
		 function,
		 extended_header_offset,
		 extended_header_offset );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: extended header data:\n",
		 function );
		libcnotify_print_data(
		 extended_header_data,
		 2,
		 0 );
	}
#endif
/* TODO pass extended header, so it is read once */
	if( ( extended_header_data[ 0 ] == (uint8_t) 'L' )
	 && ( extended_header_data[ 1 ] == (uint8_t) 'E' ) )
	{
		if( libexe_io_handle_read_le_header(
		     io_handle,
		     file_io_handle,
		     extended_header_offset,
		     number_of_sections,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read LE header.",
			 function );

			return( -1 );
		}
	}
	else if( ( extended_header_data[ 0 ] == (uint8_t) 'N' )
	      && ( extended_header_data[ 1 ] == (uint8_t) 'E' ) )
	{
		if( libexe_io_handle_read_ne_header(
		     io_handle,
		     file_io_handle,
		     extended_header_offset,
		     number_of_sections,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read NE header.",
			 function );

			return( -1 );
		}
	}
	else if( ( extended_header_data[ 0 ] == (uint8_t) 'P' )
	      && ( extended_header_data[ 1 ] == (uint8_t) 'E' ) )
	{
		if( libexe_io_handle_read_pe_header(
		     io_handle,
		     file_io_handle,
		     extended_header_offset,
		     number_of_sections,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read PE/COFF header.",
			 function );

			return( -1 );
		}
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported extended header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the LE header
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_read_le_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t le_header_offset,
     uint16_t *number_of_sections,
     libcerror_error_t **error )
{
	libexe_le_header_t *le_header = NULL;
	static char *function         = "libexe_io_handle_read_le_header";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( number_of_sections == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sections.",
		 function );

		return( -1 );
	}
	if( libexe_le_header_initialize(
	     &le_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create LE header.",
		 function );

		goto on_error;
	}
	if( libexe_le_header_read_file_io_handle(
	     le_header,
	     file_io_handle,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read LE header.",
		 function );

		goto on_error;
	}
	io_handle->executable_type = LIBEXE_EXECUTABLE_TYPE_LE;

	*number_of_sections = 0;

	if( libexe_le_header_free(
	     &le_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free LE header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( le_header != NULL )
	{
		libexe_le_header_free(
		 &le_header,
		 NULL );
	}
	return( -1 );
}

/* Reads the NE header
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_read_ne_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t ne_header_offset,
     uint16_t *number_of_sections,
     libcerror_error_t **error )
{
	libexe_ne_header_t *ne_header = NULL;
	static char *function         = "libexe_io_handle_read_ne_header";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( number_of_sections == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sections.",
		 function );

		return( -1 );
	}
	if( libexe_ne_header_initialize(
	     &ne_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create NE header.",
		 function );

		goto on_error;
	}
	if( libexe_ne_header_read_file_io_handle(
	     ne_header,
	     file_io_handle,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read NE header.",
		 function );

		goto on_error;
	}
	io_handle->executable_type = LIBEXE_EXECUTABLE_TYPE_NE;

	*number_of_sections = 0;

	if( libexe_ne_header_free(
	     &ne_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free NE header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( ne_header != NULL )
	{
		libexe_ne_header_free(
		 &ne_header,
		 NULL );
	}
	return( -1 );
}

/* Reads the PE/COFF header
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_read_pe_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t pe_header_offset,
     uint16_t *number_of_sections,
     libcerror_error_t **error )
{
	exe_pe_header_t pe_header;

	static char *function = "libexe_io_handle_read_pe_header";
	ssize_t read_count    = 0;
	off64_t file_offset   = 0;

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( number_of_sections == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sections.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading PE header at offset: %" PRIu32 " (0x%08" PRIx32 ")\n",
		 function,
		 pe_header_offset,
		 pe_header_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              (uint8_t *) &pe_header,
	              sizeof( exe_pe_header_t ),
	              (off64_t) pe_header_offset,
	              error );

	if( read_count != (ssize_t) sizeof( exe_pe_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read PE header data at offset: %" PRIu32 " (0x%08" PRIx32 ").",
		 function,
		 pe_header_offset,
		 pe_header_offset );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: PE header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &pe_header,
		 sizeof( exe_pe_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     pe_header.signature,
	     exe_pe_signature,
	     4 ) != 0 )
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
		 "%s: signature\t\t\t\t: %c%c\\x%" PRIx8 "\\x%" PRIx8 "\n",
		 function,
		 pe_header.signature[ 0 ],
		 pe_header.signature[ 1 ],
		 pe_header.signature[ 2 ],
		 pe_header.signature[ 3 ] );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( libexe_coff_header_initialize(
	     &( io_handle->coff_header ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create COFF header.",
		 function );

		goto on_error;
	}
	file_offset = pe_header_offset + sizeof( exe_pe_header_t );

	if( libexe_coff_header_read_file_io_handle(
	     io_handle->coff_header,
	     file_io_handle,
	     file_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read COFF header.",
		 function );

		goto on_error;
	}
	file_offset += sizeof( exe_coff_header_t );

	*number_of_sections = io_handle->coff_header->number_of_sections;

	if( io_handle->coff_header->optional_header_size > 0 )
	{
		if( libexe_coff_optional_header_initialize(
		     &( io_handle->coff_optional_header ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create COFF optional header.",
			 function );

			goto on_error;
		}
		if( libexe_coff_optional_header_read_file_io_handle(
		     io_handle->coff_optional_header,
		     file_io_handle,
		     file_offset,
		     io_handle->coff_header->optional_header_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read COFF optional header.",
			 function );

			goto on_error;
		}
	}
	io_handle->executable_type = LIBEXE_EXECUTABLE_TYPE_PE_COFF;

	return( 1 );

on_error:
	if( io_handle->coff_optional_header != NULL )
	{
		libexe_coff_optional_header_free(
		 &( io_handle->coff_optional_header ),
		 NULL );
	}
	if( io_handle->coff_header != NULL )
	{
		libexe_coff_header_free(
		 &( io_handle->coff_header ),
		 NULL );
	}
	return( -1 );
}

/* Reads the section table
 * Returns 1 if successful or -1 on error
 */
int libexe_io_handle_read_section_table(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint16_t number_of_sections,
     libcdata_array_t *sections_array,
     libcerror_error_t **error )
{
	libexe_section_descriptor_t *section_descriptor = NULL;
	uint8_t *section_table                          = NULL;
	uint8_t *section_table_data                     = NULL;
	static char *function                           = "libexe_io_handle_read_section_table";
	size_t section_table_size                       = 0;
	ssize_t read_count                              = 0;
	uint32_t section_data_offset                    = 0;
	uint32_t section_data_size                      = 0;
	uint16_t section_index                          = 0;
	int entry_index                                 = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                            = 0;
	uint16_t value_16bit                            = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	section_table_size = sizeof( exe_section_table_entry_t )
	                   * number_of_sections;

	if( ( section_table_size == 0 )
	 || ( section_table_size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid section table size value out of bounds.",
		 function );

		return( -1 );
	}
	section_table = (uint8_t *) memory_allocate(
	                             sizeof( uint8_t ) * section_table_size );

	if( section_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create section table.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              section_table,
	              section_table_size,
	              error );

	if( read_count != (ssize_t) section_table_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read section table.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: section table data:\n",
		 function );
		libcnotify_print_data(
		 section_table,
		 section_table_size,
		 0 );
	}
#endif
	section_table_data = section_table;

	while( section_table_size >= sizeof( exe_section_table_entry_t ) )
	{
		if( libexe_section_descriptor_initialize(
		     &section_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create section descriptor.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     section_descriptor->name,
		     ( (exe_section_table_entry_t *) section_table_data )->name,
		     8 ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy name.",
			 function );

			goto on_error;
		}
		section_descriptor->name[ 8 ] = 0;

		section_descriptor->name_size = narrow_string_length(
		                                 section_descriptor->name );

		if( section_descriptor->name_size > 0 )
		{
			section_descriptor->name_size += 1;
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_section_table_entry_t *) section_table_data )->virtual_address,
		 section_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_section_table_entry_t *) section_table_data )->data_size,
		 section_data_size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_section_table_entry_t *) section_table_data )->data_offset,
		 section_data_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " name\t\t\t\t: %s\n",
			 function,
			 section_index,
			 section_descriptor->name );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_section_table_entry_t *) section_table_data )->virtual_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " virtual size\t\t\t: %" PRIu32 "\n",
			 function,
			 section_index,
			 value_32bit );

			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " virtual address\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 section_index,
			 section_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " data size\t\t\t: %" PRIu32 "\n",
			 function,
			 section_index,
			 section_data_size );

			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " data offset\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 section_index,
			 section_data_offset );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_section_table_entry_t *) section_table_data )->relocations_offset,
			 value_32bit );
			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " relocations offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 section_index,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_section_table_entry_t *) section_table_data )->line_numbers_offset,
			 value_32bit );
			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " line numbers offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 section_index,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_section_table_entry_t *) section_table_data )->relocations_offset,
			 value_16bit );
			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " number of relocations\t\t: %" PRIu16 "\n",
			 function,
			 section_index,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_section_table_entry_t *) section_table_data )->line_numbers_offset,
			 value_16bit );
			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " number of line numbers\t\t: %" PRIu16 "\n",
			 function,
			 section_index,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_section_table_entry_t *) section_table_data )->section_characteristic_flags,
			 value_32bit );
			libcnotify_printf(
			 "%s: entry: %02" PRIu16 " section characteristic flags\t: 0x%08" PRIx32 "\n",
			 function,
			 section_index,
			 value_32bit );
			libexe_debug_print_section_characteristic_flags(
			 value_32bit );
			libcnotify_printf(
			 "\n" );
		}
#endif
		section_table_data += sizeof( exe_section_table_entry_t );
		section_table_size -= sizeof( exe_section_table_entry_t );

		if( libexe_section_descriptor_set_data_range(
		     section_descriptor,
		     (off64_t) section_data_offset,
		     (size64_t) section_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set data range in section descriptor.",
			 function );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     sections_array,
		     &entry_index,
		     (intptr_t *) section_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append section descriptor to sections array.",
			 function );

			goto on_error;
		}
		section_descriptor = NULL;

		section_index++;
	}
	memory_free(
	 section_table );

	return( 1 );

on_error:
	if( section_descriptor != NULL )
	{
		libexe_section_descriptor_free(
		 &section_descriptor,
		 NULL );
	}
	if( section_table != NULL )
	{
		memory_free(
		 section_table );
	}
	return( -1 );
}

/* Reads the segment data into the buffer
 * Callback function for the section stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t libexe_io_handle_read_segment_data(
         intptr_t *data_handle LIBEXE_ATTRIBUTE_UNUSED,
         libbfio_handle_t *file_io_handle,
         int segment_index LIBEXE_ATTRIBUTE_UNUSED,
         int segment_file_index LIBEXE_ATTRIBUTE_UNUSED,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags LIBEXE_ATTRIBUTE_UNUSED,
         uint8_t read_flags LIBEXE_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	static char *function = "libexe_io_handle_read_segment_data";
	ssize_t read_count    = 0;

	LIBEXE_UNREFERENCED_PARAMETER( data_handle )
	LIBEXE_UNREFERENCED_PARAMETER( segment_index )
	LIBEXE_UNREFERENCED_PARAMETER( segment_file_index )
	LIBEXE_UNREFERENCED_PARAMETER( segment_flags )
	LIBEXE_UNREFERENCED_PARAMETER( read_flags )

	read_count = libbfio_handle_read_buffer(
		      file_io_handle,
		      segment_data,
		      segment_data_size,
		      error );

	if( read_count != (ssize_t) segment_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment data.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain segment offset
 * Callback function for the section stream
 * Returns the offset or -1 on error
 */
off64_t libexe_io_handle_seek_segment_offset(
         intptr_t *data_handle LIBEXE_ATTRIBUTE_UNUSED,
         libbfio_handle_t *file_io_handle,
         int segment_index LIBEXE_ATTRIBUTE_UNUSED,
         int segment_file_index LIBEXE_ATTRIBUTE_UNUSED,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "libexe_io_handle_seek_segment_offset";

	LIBEXE_UNREFERENCED_PARAMETER( data_handle )
	LIBEXE_UNREFERENCED_PARAMETER( segment_index )
	LIBEXE_UNREFERENCED_PARAMETER( segment_file_index )

	segment_offset = libbfio_handle_seek_offset(
	                  file_io_handle,
	                  segment_offset,
	                  SEEK_SET,
	                  error );

	if( segment_offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to seek segment offset.",
		 function );

		return( -1 );
	}
	return( segment_offset );
}

