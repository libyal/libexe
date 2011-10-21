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

#if !defined( _LIBEXE_INTERNAL_SECTION_H )
#define _LIBEXE_INTERNAL_SECTION_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libexe_extern.h"
#include "libexe_io_handle.h"
#include "libexe_libbfio.h"
#include "libexe_libfdata.h"
#include "libexe_section_descriptor.h"
#include "libexe_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

#define LIBEXE_SECTION_FLAGS_DEFAULT			LIBEXE_SECTION_FLAG_NON_MANAGED_FILE_IO_HANDLE

enum LIBEXE_SECTION_FLAGS
{
	LIBEXE_SECTION_FLAG_NON_MANAGED_FILE_IO_HANDLE	= 0x00,
	LIBEXE_SECTION_FLAG_MANAGED_FILE_IO_HANDLE	= 0x01,
};

typedef struct libexe_internal_section libexe_internal_section_t;

struct libexe_internal_section
{
	/* The IO handle
	 */
	libexe_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The section descriptor
	 */
	libexe_section_descriptor_t *section_descriptor;

	/* The data cache
	 */
	libfdata_cache_t *data_cache;

	/* The flags
	 */
	uint8_t flags;
};

int libexe_section_initialize(
     libexe_section_t **section,
     libexe_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libexe_section_descriptor_t *section_descriptor,
     uint8_t flags,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_section_free(
     libexe_section_t **section,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_section_get_name_size(
     libexe_section_t *section,
     size_t *name_size,
     liberror_error_t **error );

LIBEXE_EXTERN \
int libexe_section_get_name(
     libexe_section_t *section,
     uint8_t *name,
     size_t name_size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

