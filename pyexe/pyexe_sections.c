/*
 * Python object definition of the sequence and iterator object of sections
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
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

#include "pyexe_libcerror.h"
#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_section.h"
#include "pyexe_sections.h"

PySequenceMethods pyexe_sections_sequence_methods = {
	/* sq_length */
	(lenfunc) pyexe_sections_len,
	/* sq_concat */
	0,
	/* sq_repeat */
	0,
	/* sq_item */
	(ssizeargfunc) pyexe_sections_getitem,
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

PyTypeObject pyexe_sections_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyexe._sections",
	/* tp_basicsize */
	sizeof( pyexe_sections_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyexe_sections_free,
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
	&pyexe_sections_sequence_methods,
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
	"pyexe internal sequence and iterator object of sections",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	(getiterfunc) pyexe_sections_iter,
	/* tp_iternext */
	(iternextfunc) pyexe_sections_iternext,
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
	(initproc) pyexe_sections_init,
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

/* Creates a new sections object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_sections_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items )
{
	pyexe_sections_t *sections_object = NULL;
	static char *function             = "pyexe_sections_new";

	if( parent_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid parent object.",
		 function );

		return( NULL );
	}
	if( get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid get item by index function.",
		 function );

		return( NULL );
	}
	/* Make sure the sections values are initialized
	 */
	sections_object = PyObject_New(
	                   struct pyexe_sections,
	                   &pyexe_sections_type_object );

	if( sections_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create sections object.",
		 function );

		goto on_error;
	}
	if( pyexe_sections_init(
	     sections_object ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize sections object.",
		 function );

		goto on_error;
	}
	sections_object->parent_object     = parent_object;
	sections_object->get_item_by_index = get_item_by_index;
	sections_object->number_of_items   = number_of_items;

	Py_IncRef(
	 (PyObject *) sections_object->parent_object );

	return( (PyObject *) sections_object );

on_error:
	if( sections_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) sections_object );
	}
	return( NULL );
}

/* Intializes a sections object
 * Returns 0 if successful or -1 on error
 */
int pyexe_sections_init(
     pyexe_sections_t *sections_object )
{
	static char *function = "pyexe_sections_init";

	if( sections_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object.",
		 function );

		return( -1 );
	}
	/* Make sure the sections values are initialized
	 */
	sections_object->parent_object     = NULL;
	sections_object->get_item_by_index = NULL;
	sections_object->current_index     = 0;
	sections_object->number_of_items   = 0;

	return( 0 );
}

/* Frees a sections object
 */
void pyexe_sections_free(
      pyexe_sections_t *sections_object )
{
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyexe_sections_free";

	if( sections_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           sections_object );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( sections_object->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) sections_object->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) sections_object );
}

/* The sections len() function
 */
Py_ssize_t pyexe_sections_len(
            pyexe_sections_t *sections_object )
{
	static char *function = "pyexe_sections_len";

	if( sections_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object.",
		 function );

		return( -1 );
	}
	return( (Py_ssize_t) sections_object->number_of_items );
}

/* The sections getitem() function
 */
PyObject *pyexe_sections_getitem(
           pyexe_sections_t *sections_object,
           Py_ssize_t item_index )
{
	PyObject *section_object = NULL;
	static char *function    = "pyexe_sections_getitem";

	if( sections_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object.",
		 function );

		return( NULL );
	}
	if( sections_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( sections_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( ( item_index < 0 )
	 || ( item_index >= (Py_ssize_t) sections_object->number_of_items ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid invalid item index value out of bounds.",
		 function );

		return( NULL );
	}
	section_object = sections_object->get_item_by_index(
	                  sections_object->parent_object,
	                  (int) item_index );

	return( section_object );
}

/* The sections iter() function
 */
PyObject *pyexe_sections_iter(
           pyexe_sections_t *sections_object )
{
	static char *function = "pyexe_sections_iter";

	if( sections_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object.",
		 function );

		return( NULL );
	}
	Py_IncRef(
	 (PyObject *) sections_object );

	return( (PyObject *) sections_object );
}

/* The sections iternext() function
 */
PyObject *pyexe_sections_iternext(
           pyexe_sections_t *sections_object )
{
	PyObject *section_object = NULL;
	static char *function    = "pyexe_sections_iternext";

	if( sections_object == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object.",
		 function );

		return( NULL );
	}
	if( sections_object->get_item_by_index == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object - missing get item by index function.",
		 function );

		return( NULL );
	}
	if( sections_object->current_index < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object - invalid current index.",
		 function );

		return( NULL );
	}
	if( sections_object->number_of_items < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid sections object - invalid number of items.",
		 function );

		return( NULL );
	}
	if( sections_object->current_index >= sections_object->number_of_items )
	{
		PyErr_SetNone(
		 PyExc_StopIteration );

		return( NULL );
	}
	section_object = sections_object->get_item_by_index(
	                  sections_object->parent_object,
	                  sections_object->current_index );

	if( section_object != NULL )
	{
		sections_object->current_index++;
	}
	return( section_object );
}

