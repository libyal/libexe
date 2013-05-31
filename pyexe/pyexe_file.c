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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyexe.h"
#include "pyexe_file_object_io_handle.h"
#include "pyexe_libbfio.h"
#include "pyexe_libcerror.h"
#include "pyexe_libclocale.h"
#include "pyexe_libcstring.h"
#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_store.h"
#include "pyexe_stores.h"
#include "pyexe_unused.h"
#include "pyexe_volume.h"

#if !defined( LIBEXE_HAVE_BFIO )
LIBEXE_EXTERN \
int libexe_volume_open_file_io_handle(
     libexe_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libexe_error_t **error );
#endif

PyMethodDef pyexe_volume_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyexe_volume_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the volume to abort the current activity." },

	/* Functions to access the volume */

	{ "open",
	  (PyCFunction) pyexe_volume_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a volume." },

	{ "open_file_object",
	  (PyCFunction) pyexe_volume_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a volume using a file-like object." },

	{ "close",
	  (PyCFunction) pyexe_volume_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a volume." },

	/* Functions to access the stores */

	{ "get_number_of_stores",
	  (PyCFunction) pyexe_volume_get_number_of_stores,
	  METH_NOARGS,
	  "get_number_of_stores() -> Integer\n"
	  "\n"
	  "Retrieves the number of stores." },

	{ "get_store",
	  (PyCFunction) pyexe_volume_get_store,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_store(store_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific store." },

	{ "get_stores",
	  (PyCFunction) pyexe_volume_get_stores,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_stores() -> Object\n"
	  "\n"
	  "Retrieves a sequence object of the stores." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyexe_volume_object_get_set_definitions[] = {

	{ "number_of_stores",
	  (getter) pyexe_volume_get_number_of_stores,
	  (setter) 0,
	  "The number of stores.",
	  NULL },

	{ "stores",
	  (getter) pyexe_volume_get_stores,
	  (setter) 0,
	  "The stores.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyexe_volume_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pyexe.volume",
	/* tp_basicsize */
	sizeof( pyexe_volume_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyexe_volume_free,
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
	0,
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
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyexe volume object (wraps libexe_volume_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyexe_volume_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyexe_volume_object_get_set_definitions,
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
	(initproc) pyexe_volume_init,
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

/* Creates a new volume object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_new(
           void )
{
	pyexe_volume_t *pyexe_volume = NULL;
	static char *function                = "pyexe_volume_new";

	pyexe_volume = PyObject_New(
	                    struct pyexe_volume,
	                    &pyexe_volume_type_object );

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	if( pyexe_volume_init(
	     pyexe_volume ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pyexe_volume );

on_error:
	if( pyexe_volume != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_volume );
	}
	return( NULL );
}

/* Creates a new volume object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_new_open(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyexe_volume = NULL;

	PYEXE_UNREFERENCED_PARAMETER( self )

	pyexe_volume = pyexe_volume_new();

	pyexe_volume_open(
	 (pyexe_volume_t *) pyexe_volume,
	 arguments,
	 keywords );

	return( pyexe_volume );
}

/* Creates a new volume object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_new_open_file_object(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pyexe_volume = NULL;

	PYEXE_UNREFERENCED_PARAMETER( self )

	pyexe_volume = pyexe_volume_new();

	pyexe_volume_open_file_object(
	 (pyexe_volume_t *) pyexe_volume,
	 arguments,
	 keywords );

	return( pyexe_volume );
}

/* Intializes a volume object
 * Returns 0 if successful or -1 on error
 */
int pyexe_volume_init(
     pyexe_volume_t *pyexe_volume )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	static char *function    = "pyexe_volume_init";
	libcerror_error_t *error = NULL;

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	/* Make sure libexe volume is set to NULL
	 */
	pyexe_volume->volume = NULL;

	if( libexe_volume_initialize(
	     &( pyexe_volume->volume ),
	     &error ) != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a volume object
 */
void pyexe_volume_free(
      pyexe_volume_t *pyexe_volume )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_volume_free";
	int result               = 0;

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return;
	}
	if( pyexe_volume->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume - missing ob_type.",
		 function );

		return;
	}
	if( pyexe_volume->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyexe_volume->volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume - missing libexe volume.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_free(
	          &( pyexe_volume->volume ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free libexe volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free libexe volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );
	}
	pyexe_volume->ob_type->tp_free(
	 (PyObject*) pyexe_volume );
}

/* Signals the volume to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_signal_abort(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_volume_signal_abort";
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_signal_abort(
	          pyexe_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to signal abort.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to signal abort.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_open(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	char *filename              = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "filename", "mode", NULL };
	static char *function       = "pyexe_volume_open";
	int result                  = 0;

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s|s",
	     keyword_list,
	     &filename,
	     &mode ) == 0 )
        {
                return( NULL );
        }
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_open(
	          pyexe_volume->volume,
                  filename,
                  LIBEXE_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a volume using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_open_file_object(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	PyObject *file_object            = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	char *mode                       = NULL;
	static char *keyword_list[]      = { "file_object", "mode", NULL };
	static char *function            = "pyexe_volume_open_file_object";
	int result                       = 0;

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
        {
                return( NULL );
        }
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	if( pyexe_file_object_initialize(
	     &file_io_handle,
	     file_object,
	     &error ) != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file IO handle.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file IO handle.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_open_file_io_handle(
	          pyexe_volume->volume,
                  file_io_handle,
                  LIBEXE_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Closes a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_close(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_volume_close";
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_close(
	          pyexe_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to close volume.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to close volume.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the number of stores
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_get_number_of_stores(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_volume_get_number_of_stores";
	int number_of_stores     = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_get_number_of_stores(
	          pyexe_volume->volume,
	          &number_of_stores,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyInt_FromLong(
	         (long) number_of_stores ) );
}

/* Retrieves a specific store by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_get_store_by_index(
           pyexe_volume_t *pyexe_volume,
           int store_index )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error  = NULL;
	libexe_store_t *store = NULL;
	PyObject *store_object    = NULL;
	static char *function     = "pyexe_volume_get_store_by_index";
	int result                = 0;

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_get_store(
	          pyexe_volume->volume,
	          store_index,
	          &store,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve store: %d.",
			 function,
			 store_index );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve store: %d.\n%s",
			 function,
			 store_index,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	store_object = pyexe_store_new(
	                store,
	                pyexe_volume );

	if( store_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create store object.",
		 function );

		goto on_error;
	}
	return( store_object );

on_error:
	if( store != NULL )
	{
		libexe_store_free(
		 &store,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific store
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_get_store(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *store_object      = NULL;
	static char *keyword_list[] = { "store_index", NULL };
	int store_index             = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &store_index ) == 0 )
        {
		return( NULL );
        }
	store_object = pyexe_volume_get_store_by_index(
	                pyexe_volume,
	                store_index );

	return( store_object );
}

/* Retrieves a stores sequence and iterator object for the stores
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_volume_get_stores(
           pyexe_volume_t *pyexe_volume,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	PyObject *stores_object  = NULL;
	static char *function    = "pyexe_volume_get_stores";
	int number_of_stores     = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_volume == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_volume_get_number_of_stores(
	          pyexe_volume->volume,
	          &number_of_stores,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of stores.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	stores_object = pyexe_stores_new(
	                 pyexe_volume,
	                 &pyexe_volume_get_store_by_index,
	                 number_of_stores );

	if( stores_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create stores object.",
		 function );

		return( NULL );
	}
	return( stores_object );
}

