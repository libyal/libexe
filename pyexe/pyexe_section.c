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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyexe.h"
#include "pyexe_block.h"
#include "pyexe_blocks.h"
#include "pyexe_datetime.h"
#include "pyexe_guid.h"
#include "pyexe_libcerror.h"
#include "pyexe_libcstring.h"
#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_store.h"
#include "pyexe_unused.h"

PyMethodDef pyexe_store_object_methods[] = {

	/* Functions to access the store data */

	{ "read_buffer",
	  (PyCFunction) pyexe_store_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer(size) -> String\n"
	  "\n"
	  "Reads a buffer of store data from the file(s)." },

	{ "read_random",
	  (PyCFunction) pyexe_store_read_random,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_random(size, offset) -> String\n"
	  "\n"
	  "Reads a buffer of store data at a specific offset from the file(s)." },

	{ "seek_offset",
	  (PyCFunction) pyexe_store_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek_offset(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the store data." },

	{ "get_offset",
	  (PyCFunction) pyexe_store_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Long\n"
	  "\n"
	  "Retrieves the current offset within the store data." },

	/* Some Pythonesque aliases */

	{ "read",
	  (PyCFunction) pyexe_store_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read(size) -> String\n"
	  "\n"
	  "Reads a buffer of store data from the file(s)." },

	{ "seek",
	  (PyCFunction) pyexe_store_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the store data." },

	{ "tell",
	  (PyCFunction) pyexe_store_get_offset,
	  METH_NOARGS,
	  "tell() -> Long\n"
	  "\n"
	  "Retrieves the current offset within the store data." },

	/* Functions to access the store values */

	{ "get_size",
	  (PyCFunction) pyexe_store_get_size,
	  METH_NOARGS,
	  "get_size() -> Long\n"
	  "\n"
	  "Retrieves the size of the store data." },

	{ "get_volume_size",
	  (PyCFunction) pyexe_store_get_volume_size,
	  METH_NOARGS,
	  "get_volume_size() -> Long\n"
	  "\n"
	  "Retrieves the size of the volume as stored in the store information." },

	{ "get_identifier",
	  (PyCFunction) pyexe_store_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the identifier (GUID)." },

	{ "get_creation_time",
	  (PyCFunction) pyexe_store_get_creation_time,
	  METH_NOARGS,
	  "get_creation_time() -> Datetime\n"
	  "\n"
	  "Returns the creation date and time." },

	{ "get_creation_time_as_integer",
	  (PyCFunction) pyexe_store_get_creation_time_as_integer,
	  METH_NOARGS,
	  "pyexe_store_get_creation_time_as_integer() -> Long\n"
	  "\n"
	  "Returns the creation date and time as a 64-bit integer containing a FILETIME value." },

	{ "get_copy_identifier",
	  (PyCFunction) pyexe_store_get_copy_identifier,
	  METH_NOARGS,
	  "get_copy_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the copy identifier (GUID)." },

	{ "get_copy_set_identifier",
	  (PyCFunction) pyexe_store_get_copy_set_identifier,
	  METH_NOARGS,
	  "get_copy_set_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the copy set identifier (GUID)." },

	/* Functions to access the blocks */

	{ "get_number_of_blocks",
	  (PyCFunction) pyexe_store_get_number_of_blocks,
	  METH_NOARGS,
	  "get_number_of_blocks() -> Integer\n"
	  "\n"
	  "Retrieves the number of blocks." },

	{ "get_block",
	  (PyCFunction) pyexe_store_get_block,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_block(block_index) -> Object or None\n"
	  "\n"
	  "Retrieves a specific block." },

	{ "get_blocks",
	  (PyCFunction) pyexe_store_get_blocks,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_blocks() -> Object\n"
	  "\n"
	  "Retrieves a sequence object of the blocks." },


	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyexe_store_object_get_set_definitions[] = {

	{ "size",
	  (getter) pyexe_store_get_size,
	  (setter) 0,
	  "The size.",
	  NULL },

	{ "volume_size",
	  (getter) pyexe_store_get_volume_size,
	  (setter) 0,
	  "The volume size.",
	  NULL },

	{ "identifier",
	  (getter) pyexe_store_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "creation_time",
	  (getter) pyexe_store_get_creation_time,
	  (setter) 0,
	  "The creation date and time.",
	  NULL },

	{ "copy_identifier",
	  (getter) pyexe_store_get_copy_identifier,
	  (setter) 0,
	  "The copy identifier.",
	  NULL },

	{ "copy_set_identifier",
	  (getter) pyexe_store_get_copy_set_identifier,
	  (setter) 0,
	  "The copy set identifier.",
	  NULL },

	{ "number_of_blocks",
	  (getter) pyexe_store_get_number_of_blocks,
	  (setter) 0,
	  "The number of blocks.",
	  NULL },

	{ "blocks",
	  (getter) pyexe_store_get_blocks,
	  (setter) 0,
	  "The blocks.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyexe_store_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pyexe.store",
	/* tp_basicsize */
	sizeof( pyexe_store_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyexe_store_free,
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
	"pyexe store object (wraps libexe_store_t)",
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
	pyexe_store_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyexe_store_object_get_set_definitions,
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
	(initproc) pyexe_store_init,
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

/* Creates a new store object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_new(
           libexe_store_t *store,
           pyexe_volume_t *volume_object )
{
	pyexe_store_t *pyexe_store = NULL;
	static char *function              = "pyexe_store_new";

	if( store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	pyexe_store = PyObject_New(
	                   struct pyexe_store,
	                   &pyexe_store_type_object );

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize store.",
		 function );

		goto on_error;
	}
	if( pyexe_store_init(
	     pyexe_store ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize store.",
		 function );

		goto on_error;
	}
	pyexe_store->store         = store;
	pyexe_store->volume_object = volume_object;

	Py_IncRef(
	 (PyObject *) pyexe_store->volume_object );

	return( (PyObject *) pyexe_store );

on_error:
	if( pyexe_store != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_store );
	}
	return( NULL );
}

/* Intializes an store object
 * Returns 0 if successful or -1 on error
 */
int pyexe_store_init(
     pyexe_store_t *pyexe_store )
{
	static char *function = "pyexe_store_init";

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	/* Make sure libexe store is set to NULL
	 */
	pyexe_store->store = NULL;

	return( 0 );
}

/* Frees an store object
 */
void pyexe_store_free(
      pyexe_store_t *pyexe_store )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_store_free";

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return;
	}
	if( pyexe_store->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store - missing ob_type.",
		 function );

		return;
	}
	if( pyexe_store->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyexe_store->store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store - missing libexe store.",
		 function );

		return;
	}
	if( libexe_store_free(
	     &( pyexe_store->store ),
	     &error ) != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to free libexe store.",
			 function );
		}
		else
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to free libexe store.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );
	}
	if( pyexe_store->volume_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_store->volume_object );
	}
	pyexe_store->ob_type->tp_free(
	 (PyObject*) pyexe_store );
}

/* Reads (store) data at the current offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_read_buffer(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	PyObject *result_data       = NULL;
	static char *function       = "pyexe_store_read_buffer";
	static char *keyword_list[] = { "size", NULL };
	ssize_t read_count          = 0;
	int read_size               = -1;

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyexe store.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|i",
	     keyword_list,
	     &read_size ) == 0 )
	{
		return( NULL );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
	if( read_size > INT_MAX )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
	result_data = PyString_FromStringAndSize(
	               NULL,
	               read_size );

	Py_BEGIN_ALLOW_THREADS

	read_count = libexe_store_read_buffer(
	              pyexe_store->store,
	              PyString_AsString(
	               result_data ),
	              (size_t) read_size,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count != (ssize_t) read_size )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to read data.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to read data.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( result_data );
}

/* Reads (store) data at a specific offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_read_random(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	PyObject *result_data       = NULL;
	static char *function       = "pyexe_store_read_random";
	static char *keyword_list[] = { "size", "offset", NULL };
	off64_t read_offset         = 0;
	ssize_t read_count          = 0;
	int read_size               = 0;

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyexe store.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i|L",
	     keyword_list,
	     &read_size,
	     &read_offset ) == 0 )
	{
		return( NULL );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
	if( read_size > INT_MAX )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
	if( read_offset < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read offset value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into the memory buffer
	 */
	result_data = PyString_FromStringAndSize(
	               NULL,
	               read_size );

	Py_BEGIN_ALLOW_THREADS

	read_count = libexe_store_read_random(
	              pyexe_store->store,
	              PyString_AsString(
	               result_data ),
	              (size_t) read_size,
	              (off64_t) read_offset,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count != (ssize_t) read_size )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to read data.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to read data.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( result_data );
}

/* Seeks a certain offset in the (store) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_seek_offset(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	static char *function       = "pyexe_store_seek_offset";
	static char *keyword_list[] = { "offset", "whence", NULL };
	off64_t offset              = 0;
	int whence                  = 0;

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyexe store.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "L|i",
	     keyword_list,
	     &offset,
	     &whence ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	offset = libexe_store_seek_offset(
	          pyexe_store->store,
	          offset,
	          whence,
	          &error );

	Py_END_ALLOW_THREADS

 	if( offset == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to seek offset.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to seek offset.\n%s",
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

/* Retrieves the current offset in the (store) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_offset(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_store_get_offset";
	off64_t current_offset   = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_offset(
	          pyexe_store->store,
	          &current_offset,
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
			 "%s: unable to retrieve offset.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve offset.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if defined( HAVE_LONG_LONG )
	if( current_offset > (off64_t) LLONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: offset value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLongLong(
	         (long long) current_offset ) );
#else
	if( current_offset > (off64_t) LONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: offset value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLong(
	         (long) current_offset ) );
#endif
}

/* Retrieves the size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_size(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_store_get_size";
	size64_t size            = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_size(
	          pyexe_store->store,
	          &size,
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
			 "%s: failed to retrieve size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: failed to retrieve size.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if defined( HAVE_LONG_LONG )
	if( size > (size64_t) LLONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: size value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLongLong(
	         (long long) size ) );
#else
	if( size > (size64_t) LONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: size value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLong(
	         (long) size ) );
#endif
}

/* Retrieves the volume size as stored in the store information
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_volume_size(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_store_get_volume_size";
	size64_t volume_size     = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_volume_size(
	          pyexe_store->store,
	          &volume_size,
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
			 "%s: failed to retrieve volume size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: failed to retrieve volume size.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if defined( HAVE_LONG_LONG )
	if( volume_size > (size64_t) LLONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: size value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLongLong(
	         (long long) volume_size ) );
#else
	if( volume_size > (size64_t) LONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: size value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLong(
	         (long) volume_size ) );
#endif
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_identifier(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyexe_store_get_identifier";
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_identifier(
	          pyexe_store->store,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve identifier.",
			 function );
		}
		else
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve identifier.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	string_object = pyexe_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the creation date and time
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_creation_time(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pyexe_store_get_creation_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_creation_time(
	          pyexe_store->store,
	          &filetime,
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
			 "%s: unable to retrieve creation time.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve creation time.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pyexe_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the creation date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_creation_time_as_integer(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_store_get_creation_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_creation_time(
	          pyexe_store->store,
	          &filetime,
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
			 "%s: unable to retrieve creation time.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve creation time.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if defined( HAVE_LONG_LONG )
	if( filetime > (uint64_t) LLONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: filetime value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLongLong(
	         (long long) filetime ) );
#else
	if( filetime > (uint64_t) LONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: filetime value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLong(
	         (long) filetime ) );
#endif
}

/* Retrieves the copy identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_copy_identifier(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyexe_store_get_copy_identifier";
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_copy_identifier(
	          pyexe_store->store,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve copy identifier.",
			 function );
		}
		else
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve copy identifier.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	string_object = pyexe_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the copy set identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_copy_set_identifier(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyexe_store_get_copy_set_identifier";
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_copy_set_identifier(
	          pyexe_store->store,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve copy set identifier.",
			 function );
		}
		else
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve copy set identifier.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	string_object = pyexe_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the number of blocks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_number_of_blocks(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_store_get_number_of_blocks";
	int number_of_blocks     = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_number_of_blocks(
	          pyexe_store->store,
	          &number_of_blocks,
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
			 "%s: unable to retrieve number of blocks.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of blocks.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyInt_FromLong(
	         (long) number_of_blocks ) );
}

/* Retrieves a specific block by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_block_by_index(
           pyexe_store_t *pyexe_store,
           int block_index )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error  = NULL;
	libexe_block_t *block = NULL;
	PyObject *block_object    = NULL;
	static char *function     = "pyexe_store_get_block_by_index";
	int result                = 0;

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_block_by_index(
	          pyexe_store->store,
	          block_index,
	          &block,
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
			 "%s: unable to retrieve block: %d.",
			 function,
			 block_index );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve block: %d.\n%s",
			 function,
			 block_index,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	block_object = pyexe_block_new(
	                block,
	                pyexe_store );

	if( block_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create block object.",
		 function );

		goto on_error;
	}
	return( block_object );

on_error:
	if( block != NULL )
	{
		libexe_block_free(
		 &block,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific block
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_block(
           pyexe_store_t *pyexe_store,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *block_object      = NULL;
	static char *keyword_list[] = { "block_index", NULL };
	int block_index             = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &block_index ) == 0 )
        {
		return( NULL );
        }
	block_object = pyexe_store_get_block_by_index(
	                pyexe_store,
	                block_index );

	return( block_object );
}

/* Retrieves a blocks sequence and iterator object for the blocks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_store_get_blocks(
           pyexe_store_t *pyexe_store,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	PyObject *blocks_object  = NULL;
	static char *function    = "pyexe_store_get_blocks";
	int number_of_blocks     = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_store == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid store.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_store_get_number_of_blocks(
	          pyexe_store->store,
	          &number_of_blocks,
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
			 "%s: unable to retrieve number of blocks.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve number of blocks.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	blocks_object = pyexe_blocks_new(
	                 pyexe_store,
	                 &pyexe_store_get_block_by_index,
	                 number_of_blocks );

	if( blocks_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create blocks object.",
		 function );

		return( NULL );
	}
	return( blocks_object );
}

