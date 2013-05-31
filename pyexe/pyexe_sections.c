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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyexe.h"
#include "pyexe_libcerror.h"
#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_store.h"
#include "pyexe_stores.h"
#include "pyexe_volume.h"

PySequenceMethods pyexe_stores_sequence_methods = {
	/* sq_length */
	(lenfunc) pyexe_stores_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyexe_stores_getitem,
	/* sq_slice */
	0,
	/* sq_ass_item */
	0,
	/* sq_ass_slice */
	0,
	/* sq_contains */
	0,
	/* sq_inplace_concat */
	0,
	/* sq_inplace_repeat */
	0
};

PyTypeObject pyexe_stores_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pyexe._stores",
	/* tp_basicsize */
	sizeof( pyexe_stores_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyexe_stores_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	&pyexe_stores_sequence_methods,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
        /* tp_flags */
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_ITER,
	/* tp_doc */
	"internal pyexe stores sequence and iterator object",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyexe_stores_iter,
	/* tp_iternext */
	(iternextfunc) pyexe_stores_iternext,
	/* tp_methods */
	0,
	/* tp_members */
	0,
	/* tp_getset */
	0,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyexe_stores_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new stores object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_stores_new(
           pyexe_volume_t *volume_object,
           PyObject* (*get_store_by_index)(
                        pyexe_volume_t *volume_object,
                        int store_index ),
           int number_of_stores )
{
	pyexe_stores_t *pyexe_stores = NULL;
	static char *function                = "pyexe_stores_new";

	if( volume_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume object.",
		 function );

		return( NULL );
	}
	if( get_store_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get store by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the stores values are initialized
	 */
	pyexe_stores = PyObject_New(
	                    struct pyexe_stores,
	                    &pyexe_stores_type_object );

	if( pyexe_stores == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stores.",
		 function );

		goto on_error;
	}
	if( pyexe_stores_init(
	     pyexe_stores ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize stores.",
		 function );

		goto on_error;
	}
	pyexe_stores->volume_object      = volume_object;
	pyexe_stores->get_store_by_index = get_store_by_index;
	pyexe_stores->number_of_stores   = number_of_stores;

	Py_IncRef(
	 (PyObject *) pyexe_stores->volume_object );

	return( (PyObject *) pyexe_stores );

on_error:
	if( pyexe_stores != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_stores );
	}
	return( NULL );
}

/* Intializes a stores object
 * Returns 0 if successful or -1 on error
 */
int pyexe_stores_init(
     pyexe_stores_t *pyexe_stores )
{
	static char *function = "pyexe_stores_init";

	if( pyexe_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( -1 );
	}
	/* Make sure the stores values are initialized
	 */
	pyexe_stores->volume_object      = NULL;
	pyexe_stores->get_store_by_index = NULL;
	pyexe_stores->store_index        = 0;
	pyexe_stores->number_of_stores   = 0;

	return( 0 );
}

/* Frees a stores object
 */
void pyexe_stores_free(
      pyexe_stores_t *pyexe_stores )
{
	static char *function = "pyexe_stores_free";

	if( pyexe_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return;
	}
	if( pyexe_stores->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - missing ob_type.",
		 function );

		return;
	}
	if( pyexe_stores->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyexe_stores->volume_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_stores->volume_object );
	}
	pyexe_stores->ob_type->tp_free(
	 (PyObject*) pyexe_stores );
}

/* The stores len() function
 */
Py_ssize_t pyexe_stores_len(
            pyexe_stores_t *pyexe_stores )
{
	static char *function = "pyexe_stores_len";

	if( pyexe_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) pyexe_stores->number_of_stores );
}

/* The stores getitem() function
 */
PyObject *pyexe_stores_getitem(
           pyexe_stores_t *pyexe_stores,
           Py_ssize_t item_index )
{
	PyObject *store_object = NULL;
	static char *function  = "pyexe_stores_getitem";

	if( pyexe_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( NULL );
	}
	if( pyexe_stores->get_store_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - missing get store by index function.",
		 function );

		return( NULL );
	}
	if( pyexe_stores->number_of_stores < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - invalid number of stores.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) pyexe_stores->number_of_stores ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	store_object = pyexe_stores->get_store_by_index(
	                pyexe_stores->volume_object,
	                (int) item_index );

	return( store_object );
}

/* The stores iter() function
 */
PyObject *pyexe_stores_iter(
           pyexe_stores_t *pyexe_stores )
{
	static char *function = "pyexe_stores_iter";

	if( pyexe_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) pyexe_stores );

	return( (PyObject *) pyexe_stores );
}

/* The stores iternext() function
 */
PyObject *pyexe_stores_iternext(
           pyexe_stores_t *pyexe_stores )
{
	PyObject *store_object = NULL;
	static char *function  = "pyexe_stores_iternext";

	if( pyexe_stores == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores.",
		 function );

		return( NULL );
	}
	if( pyexe_stores->get_store_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - missing get store by index function.",
		 function );

		return( NULL );
	}
	if( pyexe_stores->store_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - invalid store index.",
		 function );

		return( NULL );
	}
	if( pyexe_stores->number_of_stores < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid stores - invalid number of stores.",
		 function );

		return( NULL );
	}
	if( pyexe_stores->store_index >= pyexe_stores->number_of_stores )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	store_object = pyexe_stores->get_store_by_index(
	                pyexe_stores->volume_object,
	                pyexe_stores->store_index );

	if( store_object != NULL )
	{
		pyexe_stores->store_index++;
	}
	return( store_object );
}

