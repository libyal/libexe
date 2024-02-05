/*
 * COFF optional header functions
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

#include "libexe_coff_optional_header.h"
#include "libexe_data_directory_descriptor.h"
#include "libexe_debug.h"
#include "libexe_definitions.h"
#include "libexe_libcerror.h"
#include "libexe_libcnotify.h"

#include "exe_file_header.h"

/* Creates a COFF optional header
 * Make sure the value coff_optional_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_optional_header_initialize(
     libexe_coff_optional_header_t **coff_optional_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_coff_optional_header_initialize";

	if( coff_optional_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid COFF optional header.",
		 function );

		return( -1 );
	}
	if( *coff_optional_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid COFF optional header value already set.",
		 function );

		return( -1 );
	}
	*coff_optional_header = memory_allocate_structure(
	                         libexe_coff_optional_header_t );

	if( *coff_optional_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create COFF optional header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *coff_optional_header,
	     0,
	     sizeof( libexe_coff_optional_header_t ) ) == NULL )
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
	if( *coff_optional_header != NULL )
	{
		memory_free(
		 *coff_optional_header );

		*coff_optional_header = NULL;
	}
	return( -1 );
}

/* Frees a COFF optional header
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_optional_header_free(
     libexe_coff_optional_header_t **coff_optional_header,
     libcerror_error_t **error )
{
	static char *function = "libexe_coff_optional_header_free";

	if( coff_optional_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid COFF optional header.",
		 function );

		return( -1 );
	}
	if( *coff_optional_header != NULL )
	{
		memory_free(
		 *coff_optional_header );

		*coff_optional_header = NULL;
	}
	return( 1 );
}

/* Reads the COFF optional header
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_optional_header_read_data(
     libexe_coff_optional_header_t *coff_optional_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libexe_data_directory_descriptor_t *data_directory_descriptor = NULL;
	static char *function                                         = "libexe_coff_optional_header_read_data";
	size_t data_offset                                            = 0;
	uint32_t number_of_data_directories_entries                   = 0;
	uint16_t signature                                            = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                                          = 0;
	uint32_t value_32bit                                          = 0;
	uint16_t value_16bit                                          = 0;
#endif

	if( coff_optional_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid COFF optional header.",
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
	if( ( data_size < sizeof( exe_coff_optional_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: COFF optional header:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (exe_coff_optional_header_t *) data )->signature,
	 signature );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 signature );

		libcnotify_printf(
		 "%s: major linker version\t\t: %" PRIu8 "\n",
		 function,
		 ( (exe_coff_optional_header_t *) data )->major_linker_version );

		libcnotify_printf(
		 "%s: minor linker version\t\t: %" PRIu8 "\n",
		 function,
		 ( (exe_coff_optional_header_t *) data )->minor_linker_version );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_t *) data )->text_section_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: text section size\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_t *) data )->initialized_data_section_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: initialized data section size\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_t *) data )->uninitialized_data_section_size,
		 value_32bit );
		libcnotify_printf(
		 "%s: uninitialized data section size\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_t *) data )->entry_point_offset,
		 value_32bit );
		libcnotify_printf(
		 "%s: entry point offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_t *) data )->code_base_offset,
		 value_32bit );
		libcnotify_printf(
		 "%s: code base offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( signature == LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURE_PE32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_t *) data )->data_base_offset,
			 value_32bit );
			libcnotify_printf(
			 "%s: data base offset\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( signature != LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURE_PE32 )
	 && ( signature != LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURE_PE32_PLUS ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	data_offset = sizeof( exe_coff_optional_header_t );

	if( signature == LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURE_PE32 )
	{
		if( sizeof( exe_coff_optional_header_pe32_t ) > ( data_size - data_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid data size value too small.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->number_of_data_directories_entries,
		 number_of_data_directories_entries );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->image_base_offset,
			 value_32bit );
			libcnotify_printf(
			 "%s: image base offset\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->section_alignment_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: section alignment size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->file_alignment_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: file alignment size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->major_operating_system_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: major operating system version\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->minor_operating_system_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: minor operating system version\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->major_image_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: major image version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->minor_image_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: minor image version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->major_subsystem_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: major subsystem version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->minor_subsystem_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: minor subsystem version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->image_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: image size\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->headers_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: headers size\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->checksum,
			 value_32bit );
			libcnotify_printf(
			 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->subsystem,
			 value_16bit );
			libcnotify_printf(
			 "%s: subsystem\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->dll_characteristic_flags,
			 value_16bit );
			libcnotify_printf(
			 "%s: DLL characteristic flags\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );
			libexe_debug_print_dll_characteristic_flags(
			 value_16bit );
			libcnotify_printf(
			 "\n" );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->stack_reservation_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: stack reservation size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->stack_commit_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: stack commit size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->heap_reservation_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: heap reservation size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->heap_commit_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: heap commit size\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_t *) &( data[ data_offset ] ) )->unknown2,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown2\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: number of data directory entries\t: %" PRIu32 "\n",
			 function,
			 number_of_data_directories_entries );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		data_offset += sizeof( exe_coff_optional_header_pe32_t );
	}
	else if( signature == LIBEXE_COFF_OPTIONAL_HEADER_SIGNATURE_PE32 )
	{
		if( sizeof( exe_coff_optional_header_pe32_plus_t ) > ( data_size - data_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid data size value too small.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->number_of_data_directories_entries,
		 number_of_data_directories_entries );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->image_base_offset,
			 value_64bit );
			libcnotify_printf(
			 "%s: image base offset\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->section_alignment_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: section alignment size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->file_alignment_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: file alignment size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->major_operating_system_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: major operating system version\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->minor_operating_system_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: minor operating system version\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->major_image_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: major image version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->minor_image_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: minor image version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->major_subsystem_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: major subsystem version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->minor_subsystem_version,
			 value_16bit );
			libcnotify_printf(
			 "%s: minor subsystem version\t\t: %" PRIu16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->image_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: image size\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->headers_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: headers size\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->checksum,
			 value_32bit );
			libcnotify_printf(
			 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->subsystem,
			 value_16bit );
			libcnotify_printf(
			 "%s: subsystem\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->dll_characteristic_flags,
			 value_16bit );
			libcnotify_printf(
			 "%s: DLL characteristic flags\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );
			libexe_debug_print_dll_characteristic_flags(
			 value_16bit );
			libcnotify_printf(
			 "\n" );

			byte_stream_copy_to_uint64_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->stack_reservation_size,
			 value_64bit );
			libcnotify_printf(
			 "%s: stack reservation size\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->stack_commit_size,
			 value_64bit );
			libcnotify_printf(
			 "%s: stack commit size\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->heap_reservation_size,
			 value_64bit );
			libcnotify_printf(
			 "%s: heap reservation size\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->heap_commit_size,
			 value_64bit );
			libcnotify_printf(
			 "%s: heap commit size\t\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_pe32_plus_t *) &( data[ data_offset ] ) )->unknown2,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: number of data directory entries\t: %" PRIu32 "\n",
			 function,
			 number_of_data_directories_entries );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		data_offset += sizeof( exe_coff_optional_header_pe32_plus_t );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	if( number_of_data_directories_entries > 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported number of data directory entries: %" PRIu32 ".",
		 function,
		 number_of_data_directories_entries );

		return( -1 );
	}
	if( ( (size_t) number_of_data_directories_entries * 8 ) > ( data_size - data_offset ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_EXPORT_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->export_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->export_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: export table RVA\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: export table size\t\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_IMPORT_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->import_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->import_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: import table RVA\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: import table size\t\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_RESOURCE_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->resource_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->resource_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: resource table RVA\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: resource table size\t\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_EXCEPTION_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->exception_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->exception_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: exception table RVA\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: exception table size\t\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_CERTIFICATE_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->certificate_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->certificate_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: certificate table RVA\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: certificate table size\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_BASE_RELOCATION_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->base_relocation_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->base_relocation_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: base relocation table RVA\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: base relocation table size\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_DEBUG_DATA ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->debug_data_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->debug_data_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: debug data RVA\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: debug data size\t\t\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->architecture_specific_data_rva,
			 value_32bit );
			libcnotify_printf(
			 "%s: architecture-specific data RVA\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->architecture_specific_data_size,
			 value_32bit );
			libcnotify_printf(
			 "%s: architecture-specific data size\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->global_pointer_register,
			 value_32bit );
			libcnotify_printf(
			 "%s: global pointer register\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->unknown3,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_THREAD_LOCAL_STORAGE_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->thread_local_storage_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->thread_local_storage_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: thread local storage table RVA\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: thread local storage table size\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_LOAD_CONFIGURATION_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->load_configuration_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->load_configuration_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: load configuration table RVA\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: load configuration table size\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_BOUND_IMPORT_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->bound_import_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->bound_import_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: bound import table RVA\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: bound import table size\t\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_IMPORT_ADDRESS_TABLE ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->import_address_table_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->import_address_table_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: import address table RVA\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: import address table size\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_DELAY_IMPORT_DESCRIPTOR ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->delay_import_descriptor_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->delay_import_descriptor_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: delay import descriptor RVA\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: delay import descriptor size\t: %" PRIu32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
		data_directory_descriptor = &( coff_optional_header->data_directories[ LIBEXE_DATA_DIRECTORY_COM_PLUS_RUNTIME_HEADER ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->com_plus_runtime_header_rva,
		 data_directory_descriptor->virtual_address );

		byte_stream_copy_to_uint32_little_endian(
		 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->com_plus_runtime_header_size,
		 data_directory_descriptor->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: COM+ runtime header RVA\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->virtual_address );

			libcnotify_printf(
			 "%s: COM+ runtime header size\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_directory_descriptor->size );
		}
#endif
		number_of_data_directories_entries--;
	}
	if( number_of_data_directories_entries > 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (exe_coff_optional_header_data_directories_t *) &( data[ data_offset ] ) )->unknown4,
			 value_64bit );
			libcnotify_printf(
			 "%s: unknown4\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			libcnotify_printf(
			 "\n" );
		}
#endif
		number_of_data_directories_entries--;
	}
	return( 1 );
}

/* Reads the COFF optional header from a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libexe_coff_optional_header_read_file_io_handle(
     libexe_coff_optional_header_t *coff_optional_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     uint16_t optional_header_size,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libexe_coff_optional_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( optional_header_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid optional header size value out of bounds.",
		 function );

		return( -1 );
	}
	if( optional_header_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid optional header size value out of bounds.",
		 function );

		return( -1 );
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * optional_header_size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create COFF optional header data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading COFF optional header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              (size_t) optional_header_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) optional_header_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read COFF optional header data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libexe_coff_optional_header_read_data(
	     coff_optional_header,
	     data,
	     (size_t) optional_header_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read COFF optional header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
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

