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

#if !defined( _LIBEXE_COFF_OPTIONAL_HEADER_H )
#define _LIBEXE_COFF_OPTIONAL_HEADER_H

#include <common.h>
#include <types.h>

#include "libexe_data_directory_descriptor.h"
#include "libexe_definitions.h"
#include "libexe_libbfio.h"
#include "libexe_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libexe_coff_optional_header libexe_coff_optional_header_t;

struct libexe_coff_optional_header
{
	/* The data directories
	 */
        libexe_data_directory_descriptor_t data_directories[ LIBEXE_NUMBER_OF_DATA_DIRECTORIES ];
};

int libexe_coff_optional_header_initialize(
     libexe_coff_optional_header_t **coff_optional_header,
     libcerror_error_t **error );

int libexe_coff_optional_header_free(
     libexe_coff_optional_header_t **coff_optional_header,
     libcerror_error_t **error );

int libexe_coff_optional_header_read_data(
     libexe_coff_optional_header_t *coff_optional_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libexe_coff_optional_header_read_file_io_handle(
     libexe_coff_optional_header_t *coff_optional_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     uint16_t optional_header_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBEXE_COFF_OPTIONAL_HEADER_H ) */

