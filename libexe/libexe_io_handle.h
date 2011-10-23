/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBEXE_IO_HANDLE_H )
#define _LIBEXE_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libexe_array_type.h"
#include "libexe_libbfio.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *exe_mz_signature;

typedef struct libexe_io_handle libexe_io_handle_t;

struct libexe_io_handle
{
	/* The creation time
	 */
	uint32_t creation_time;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libexe_io_handle_initialize(
     libexe_io_handle_t **io_handle,
     liberror_error_t **error );

int libexe_io_handle_free(
     libexe_io_handle_t **io_handle,
     liberror_error_t **error );

int libexe_io_handle_read_file_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint16_t *number_of_sections,
     liberror_error_t **error );

int libexe_io_handle_read_mz_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t *pe_header_offset,
     liberror_error_t **error );

int libexe_io_handle_read_pe_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint32_t pe_header_offset,
     uint16_t *number_of_sections,
     liberror_error_t **error );

int libexe_io_handle_read_coff_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint16_t *number_of_sections,
     liberror_error_t **error );

int libexe_io_handle_read_coff_optional_header(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint16_t optional_header_size,
     liberror_error_t **error );

int libexe_io_handle_read_section_table(
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     uint16_t number_of_sections,
     libexe_array_t *sections_array,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

