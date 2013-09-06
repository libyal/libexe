/*
 * Python object definition of the libexe section
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
#include "pyexe_datetime.h"
#include "pyexe_file.h"
#include "pyexe_libcerror.h"
#include "pyexe_libcstring.h"
#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_section.h"
#include "pyexe_unused.h"

PyMethodDef pyexe_section_object_methods[] = {

	/* Functions to access the section data */

	{ "read_buffer",
	  (PyCFunction) pyexe_section_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer(size) -> String\n"
	  "\n"
	  "Reads a buffer of section data." },

	{ "read_random",
	  (PyCFunction) pyexe_section_read_random,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_random(size, offset) -> String\n"
	  "\n"
	  "Reads a buffer of secton data at a specific offset." },

	{ "seek_offset",
	  (PyCFunction) pyexe_section_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek_offset(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the section data." },

	{ "get_offset",
	  (PyCFunction) pyexe_section_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Long\n"
	  "\n"
	  "Retrieves the current offset within the section data." },

	/* Some Pythonesque aliases */

	{ "read",
	  (PyCFunction) pyexe_section_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read(size) -> String\n"
	  "\n"
	  "Reads a buffer of section data." },

	{ "seek",
	  (PyCFunction) pyexe_section_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the section data." },

	{ "tell",
	  (PyCFunction) pyexe_section_get_offset,
	  METH_NOARGS,
	  "tell() -> Long\n"
	  "\n"
	  "Retrieves the current offset within the section data." },

	/* Functions to access the section values */

	{ "get_size",
	  (PyCFunction) pyexe_section_get_size,
	  METH_NOARGS,
	  "get_size() -> Long\n"
	  "\n"
	  "Retrieves the size of the section data." },

	{ "get_start_offset",
	  (PyCFunction) pyexe_section_get_start_offset,
	  METH_NOARGS,
	  "get_start_offset() -> Long\n"
	  "\n"
	  "Retrieves the start offset." },

	{ "get_virtual_address",
	  (PyCFunction) pyexe_section_get_virtual_address,
	  METH_NOARGS,
	  "get_virtual_address() -> Long\n"
	  "\n"
	  "Retrieves the virtual address." },

	{ "get_name",
	  (PyCFunction) pyexe_section_get_name,
	  METH_NOARGS,
	  "get_name() -> Unicode string or None\n"
	  "\n"
	  "Returns the name." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyexe_section_object_get_set_definitions[] = {

	{ "size",
	  (getter) pyexe_section_get_size,
	  (setter) 0,
	  "The size.",
	  NULL },

	{ "start_offset",
	  (getter) pyexe_section_get_start_offset,
	  (setter) 0,
	  "The start offset.",
	  NULL },

	{ "virtual_address",
	  (getter) pyexe_section_get_virtual_address,
	  (setter) 0,
	  "The virtual address.",
	  NULL },

	{ "name",
	  (getter) pyexe_section_get_name,
	  (setter) 0,
	  "The name.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyexe_section_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pyexe.section",
	/* tp_basicsize */
	sizeof( pyexe_section_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyexe_section_free,
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
	"pyexe section object (wraps libexe_section_t)",
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
	pyexe_section_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyexe_section_object_get_set_definitions,
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
	(initproc) pyexe_section_init,
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

/* Creates a new section object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_new(
           libexe_section_t *section,
           pyexe_file_t *file_object )
{
	pyexe_section_t *pyexe_section = NULL;
	static char *function          = "pyexe_section_new";

	if( section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section.",
		 function );

		return( NULL );
	}
	pyexe_section = PyObject_New(
	                 struct pyexe_section,
	                 &pyexe_section_type_object );

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize section.",
		 function );

		goto on_error;
	}
	if( pyexe_section_init(
	     pyexe_section ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize section.",
		 function );

		goto on_error;
	}
	pyexe_section->section     = section;
	pyexe_section->file_object = file_object;

	Py_IncRef(
	 (PyObject *) pyexe_section->file_object );

	return( (PyObject *) pyexe_section );

on_error:
	if( pyexe_section != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_section );
	}
	return( NULL );
}

/* Intializes an section object
 * Returns 0 if successful or -1 on error
 */
int pyexe_section_init(
     pyexe_section_t *pyexe_section )
{
	static char *function = "pyexe_section_init";

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section.",
		 function );

		return( -1 );
	}
	/* Make sure libexe section is set to NULL
	 */
	pyexe_section->section = NULL;

	return( 0 );
}

/* Frees an section object
 */
void pyexe_section_free(
      pyexe_section_t *pyexe_section )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_section_free";

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section.",
		 function );

		return;
	}
	if( pyexe_section->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section - missing ob_type.",
		 function );

		return;
	}
	if( pyexe_section->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyexe_section->section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section - missing libexe section.",
		 function );

		return;
	}
	if( libexe_section_free(
	     &( pyexe_section->section ),
	     &error ) != 1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYEXE_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to free libexe section.",
			 function );
		}
		else
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to free libexe section.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );
	}
	if( pyexe_section->file_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_section->file_object );
	}
	pyexe_section->ob_type->tp_free(
	 (PyObject*) pyexe_section );
}

/* Reads (section) data at the current offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_read_buffer(
           pyexe_section_t *pyexe_section,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	PyObject *result_data       = NULL;
	static char *function       = "pyexe_section_read_buffer";
	static char *keyword_list[] = { "size", NULL };
	ssize_t read_count          = 0;
	int read_size               = -1;

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyexe section.",
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

	read_count = libexe_section_read_buffer(
	              pyexe_section->section,
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

/* Reads (section) data at a specific offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_read_random(
           pyexe_section_t *pyexe_section,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	PyObject *result_data       = NULL;
	static char *function       = "pyexe_section_read_random";
	static char *keyword_list[] = { "size", "offset", NULL };
	off64_t read_offset         = 0;
	ssize_t read_count          = 0;
	int read_size               = 0;

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyexe section.",
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

	read_count = libexe_section_read_random(
	              pyexe_section->section,
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

/* Seeks a certain offset in the (section) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_seek_offset(
           pyexe_section_t *pyexe_section,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error    = NULL;
	static char *function       = "pyexe_section_seek_offset";
	static char *keyword_list[] = { "offset", "whence", NULL };
	off64_t offset              = 0;
	int whence                  = 0;

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid pyexe section.",
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

	offset = libexe_section_seek_offset(
	          pyexe_section->section,
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

/* Retrieves the current offset in the (section) data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_get_offset(
           pyexe_section_t *pyexe_section,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_section_get_offset";
	off64_t current_offset   = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_section_get_offset(
	          pyexe_section->section,
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
PyObject *pyexe_section_get_size(
           pyexe_section_t *pyexe_section,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_section_get_size";
	size64_t size            = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_section_get_size(
	          pyexe_section->section,
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

/* Retrieves the start offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_get_start_offset(
           pyexe_section_t *pyexe_section,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_section_get_start_offset";
	off64_t start_offset     = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_section_get_start_offset(
	          pyexe_section->section,
	          &start_offset,
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
			 "%s: unable to retrieve start offset.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve start offset.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if defined( HAVE_LONG_LONG )
	if( start_offset > (off64_t) LLONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: start offset value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLongLong(
	         (long long) start_offset ) );
#else
	if( start_offset > (off64_t) LONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: start offset value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLong(
	         (long) start_offset ) );
#endif
}

/* Retrieves the virtual address
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_get_virtual_address(
           pyexe_section_t *pyexe_section,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	static char *function    = "pyexe_section_get_virtual_address";
	uint32_t virtual_address = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_section_get_virtual_address(
	          pyexe_section->section,
	          &virtual_address,
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
			 "%s: unable to retrieve virtual address.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve virtual address.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if defined( HAVE_LONG_LONG )
	if( (uint64_t) virtual_address > (uint64_t) LLONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: FAT date time value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLongLong(
	         (long long) virtual_address ) );
#else
	if( (uint64_t) virtual_address > (uint64_t) LONG_MAX )
	{
		PyErr_Format(
		 PyExc_OverflowError,
		 "%s: FAT date time value exceeds maximum.",
		 function );

		return( NULL );
	}
	return( PyLong_FromLong(
	         (long) virtual_address ) );
#endif
}

/* Retrieves the name
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_section_get_name(
           pyexe_section_t *pyexe_section,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	char error_string[ PYEXE_ERROR_STRING_SIZE ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pyexe_section_get_name";
	const char *errors       = NULL;
	char *name               = NULL;
	size_t name_size         = 0;
	int result               = 0;

	PYEXE_UNREFERENCED_PARAMETER( arguments )

	if( pyexe_section == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid section.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_section_get_utf8_name_size(
	          pyexe_section->section,
	          &name_size,
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
			 "%s: unable to retrieve UTF-8 name size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 name size.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the name is present
	 */
	else if( ( result == 0 )
	      || ( name_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	name = (char *) PyMem_Malloc(
	                 sizeof( char ) * name_size );

	if( name == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 name.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_section_get_utf8_name(
	          pyexe_section->section,
	          (uint8_t *) name,
	          name_size,
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
			 "%s: unable to retrieve UTF-8 name.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 name.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the name is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 name );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 name,
	                 (Py_ssize_t) name_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 name into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 name );

	return( string_object );

on_error:
	if( name != NULL )
	{
		PyMem_Free(
		 name );
	}
	return( NULL );
}

