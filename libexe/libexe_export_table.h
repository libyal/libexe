/*
 * Export table functions
 *
 * Copyright (C) 2011-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBEXE_EXPORT_TABLE_H )
#define _LIBEXE_EXPORT_TABLE_H

#include <common.h>
#include <types.h>

#include "libexe_libbfio.h"
#include "libexe_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libexe_export_table libexe_export_table_t;

struct libexe_export_table
{
	/* Dummy
	 */
	int dummy;
};

int libexe_export_table_initialize(
     libexe_export_table_t **export_table,
     libcerror_error_t **error );

int libexe_export_table_free(
     libexe_export_table_t **export_table,
     libcerror_error_t **error );

int libexe_export_table_read(
     libexe_export_table_t *export_table,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     uint32_t size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBEXE_EXPORT_TABLE_H ) */

