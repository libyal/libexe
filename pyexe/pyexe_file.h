/*
 * Python object definition of the libexe volume
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

#if !defined( _PYEXE_FILE_H )
#define _PYEXE_FILE_H

#include <common.h>
#include <types.h>

#include "pyexe_libexe.h"
#include "pyexe_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyexe_volume pyexe_volume_t;

struct pyexe_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libexe volume
	 */
	libexe_volume_t *volume;
};

extern PyMethodDef pyexe_volume_object_methods[];
extern PyTypeObject pyexe_volume_type_object;

PyObject *pyexe_volume_new(
           void );

PyObject *pyexe_volume_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_volume_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pyexe_volume_init(
     pyexe_volume_t *pyexe_volume );

void pyexe_volume_free(
      pyexe_volume_t *pyexe_volume );

PyObject *pyexe_volume_signal_abort(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments );

PyObject *pyexe_volume_open(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_volume_open_file_object(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_volume_close(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments );

PyObject *pyexe_volume_get_number_of_stores(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments );

PyObject *pyexe_volume_get_store_by_index(
           pyexe_volume_t *pyexe_volume,
           int store_index );

PyObject *pyexe_volume_get_store(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_volume_get_stores(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif

