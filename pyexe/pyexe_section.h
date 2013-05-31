/*
 * Python object definition of the libexe store
 *
 * Copyright (c) 2011-2013, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYEXE_STORE_H )
#define _PYEXE_STORE_H

#include <common.h>
#include <types.h>

#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_volume.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyexe_store pyexe_store_t;

struct pyexe_store
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libexe store
	 */
	libexe_store_t *store;

	/* The pyexe volume object
	 */
	pyexe_volume_t *volume_object;
};

extern PyMethodDef pyexe_store_object_methods[];
extern PyTypeObject pyexe_store_type_object;

PyObject *pyexe_store_new(
           libexe_store_t *store,
           pyexe_volume_t *volume_object );

int pyexe_store_init(
     pyexe_store_t *pyexe_store );

void pyexe_store_free(
      pyexe_store_t *pyexe_store );

PyObject *pyexe_store_read_buffer(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_store_read_random(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_store_seek_offset(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_store_get_offset(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_size(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_volume_size(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_identifier(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_creation_time(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_creation_time_as_integer(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_copy_identifier(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_copy_set_identifier(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_number_of_blocks(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

PyObject *pyexe_store_get_block_by_index(
           pyexe_store_t *pyexe_store,
           int block_index );

PyObject *pyexe_store_get_block(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_store_get_blocks(
           pyexe_store_t *pyexe_store,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif

