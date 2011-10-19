/*
 * File functions
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

#if !defined( _LIBEXE_INTERNAL_FILE_H )
#define _LIBEXE_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libexe_array_type.h"
#include "libexe_extern.h"
#include "libexe_io_handle.h"
#include "libexe_libbfio.h"
#include "libexe_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libexe_internal_file libexe_internal_file_t;

struct libexe_internal_file
{
	/* The items array
	 */
	libexe_array_t *items_array;

	/* The IO handle
	 */
	libexe_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;
};

LIBEXE_EXTERN \
int libexe_file_initialize(
     libexe_file_t **file,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_free(
     libexe_file_t **file,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_signal_abort(
     libexe_file_t *file,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_open(
     libexe_file_t *file,
     const char *filename,
     int access_flags,
     liberror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBEXE_EXTERN \
int libexe_file_open_wide(
     libexe_file_t *file,
     const wchar_t *filename,
     int access_flags,
     liberror_error_t **error );
#endif

LIBEXE_EXTERN \
int libexe_file_open_file_io_handle(
     libexe_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_close(
     libexe_file_t *file,
     liberror_error_t **error );

int libexe_file_open_read(
     libexe_internal_file_t *internal_file,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_get_ascii_codepage(
     libexe_file_t *file,
     int *ascii_codepage,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_set_ascii_codepage(
     libexe_file_t *file,
     int ascii_codepage,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_get_version(
     libexe_file_t *file,
     uint32_t *major_version,
     uint32_t *minor_version,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_get_number_of_items(
     libexe_file_t *file,
     int *number_of_items,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_file_get_item(
     libexe_file_t *file,
     int item_index,
     libexe_item_t **item,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif
