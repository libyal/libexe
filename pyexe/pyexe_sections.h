/*
 * Python object definition of the stores sequence and iterator
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

#if !defined( _PYEXE_STORES_H )
#define _PYEXE_STORES_H

#include <common.h>
#include <types.h>

#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_volume.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyexe_stores pyexe_stores_t;

struct pyexe_stores
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The pyexe volume object
	 */
	pyexe_volume_t *volume_object;

	/* The get store by index callback function
	 */
	PyObject* (*get_store_by_index)(
	             pyexe_volume_t *volume_object,
	             int store_index );

	/* The (current) store index
	 */
	int store_index;

	/* The number of stores
	 */
	int number_of_stores;
};

extern PyTypeObject pyexe_stores_type_object;

PyObject *pyexe_stores_new(
           pyexe_volume_t *volume_object,
           PyObject* (*get_store_by_index)(
                        pyexe_volume_t *volume_object,
                        int store_index ),
           int number_of_stores );

int pyexe_stores_init(
     pyexe_stores_t *pyexe_stores );

void pyexe_stores_free(
      pyexe_stores_t *pyexe_stores );

Py_ssize_t pyexe_stores_len(
            pyexe_stores_t *pyexe_stores );

PyObject *pyexe_stores_getitem(
           pyexe_stores_t *pyexe_stores,
           Py_ssize_t item_index );

PyObject *pyexe_stores_iter(
           pyexe_stores_t *pyexe_stores );

PyObject *pyexe_stores_iternext(
           pyexe_stores_t *pyexe_stores );

#if defined( __cplusplus )
}
#endif

#endif

