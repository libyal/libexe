/*
 * Python bindings module for libexe (pyexe)
 *
 * Copyright (C) 2011-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyexe.h"
#include "pyexe_error.h"
#include "pyexe_file.h"
#include "pyexe_file_object_io_handle.h"
#include "pyexe_libbfio.h"
#include "pyexe_libcerror.h"
#include "pyexe_libexe.h"
#include "pyexe_python.h"
#include "pyexe_section.h"
#include "pyexe_sections.h"
#include "pyexe_unused.h"

#if !defined( LIBEXE_HAVE_BFIO )

LIBEXE_EXTERN \
int libexe_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libexe_error_t **error );

#endif /* !defined( LIBEXE_HAVE_BFIO ) */

/* The pyexe module methods
 */
PyMethodDef pyexe_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyexe_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "check_file_signature",
	  (PyCFunction) pyexe_check_file_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature(filename) -> Boolean\n"
	  "\n"
	  "Checks if a file has a executable (EXE) file signature." },

	{ "check_file_signature_file_object",
	  (PyCFunction) pyexe_check_file_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature_file_object(file_object) -> Boolean\n"
	  "\n"
	  "Checks if a file has a executable (EXE) file signature using a file-like object." },

	{ "open",
	  (PyCFunction) pyexe_open_new_file,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pyexe_open_new_file_with_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a file using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pyexe/libexe version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_get_version(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments PYEXE_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYEXE_UNREFERENCED_PARAMETER( self )
	PYEXE_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libexe_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Checks if a file has a executable (EXE) file signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_check_file_signature(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *filename_narrow = NULL;
	static char *function       = "pyexe_check_file_signature";
	static char *keyword_list[] = { "filename", NULL };
	int result                  = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	PYEXE_UNREFERENCED_PARAMETER( self )

	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|",
	     keyword_list,
	     &string_object ) == 0 )
	{
		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyexe_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = libexe_check_file_signature_wide(
		          filename_wide,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyexe_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libexe_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

		if( result == -1 )
		{
			pyexe_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyexe_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libexe_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pyexe_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Checks if a file has a executable (EXE) file signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_check_file_signature_file_object(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object            = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	static char *function            = "pyexe_check_file_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYEXE_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|",
	     keyword_list,
	     &file_object ) == 0 )
	{
		return( NULL );
	}
	if( pyexe_file_object_initialize(
	     &file_io_handle,
	     file_object,
	     &error ) != 1 )
	{
		pyexe_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libexe_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyexe_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to check file signature.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     &error ) != 1 )
	{
		pyexe_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( result != 0 )
	{
		Py_IncRef(
		 (PyObject *) Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 (PyObject *) Py_False );

	return( Py_False );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_open_new_file(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pyexe_file_t *pyexe_file = NULL;
	static char *function    = "pyexe_open_new_file";

	PYEXE_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pyexe_file = PyObject_New(
	              struct pyexe_file,
	              &pyexe_file_type_object );

	if( pyexe_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( pyexe_file_init(
	     pyexe_file ) != 0 )
	{
		goto on_error;
	}
	if( pyexe_file_open(
	     pyexe_file,
	     arguments,
	     keywords ) == NULL )
	{
		goto on_error;
	}
	return( (PyObject *) pyexe_file );

on_error:
	if( pyexe_file != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_file );
	}
	return( NULL );
}

/* Creates a new file object and opens it using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyexe_open_new_file_with_file_object(
           PyObject *self PYEXE_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pyexe_file_t *pyexe_file = NULL;
	static char *function    = "pyexe_open_new_file_with_file_object";

	PYEXE_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pyexe_file = PyObject_New(
	              struct pyexe_file,
	              &pyexe_file_type_object );

	if( pyexe_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( pyexe_file_init(
	     pyexe_file ) != 0 )
	{
		goto on_error;
	}
	if( pyexe_file_open_file_object(
	     pyexe_file,
	     arguments,
	     keywords ) == NULL )
	{
		goto on_error;
	}
	return( (PyObject *) pyexe_file );

on_error:
	if( pyexe_file != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyexe_file );
	}
	return( NULL );
}

#if PY_MAJOR_VERSION >= 3

/* The pyexe module definition
 */
PyModuleDef pyexe_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pyexe",
	/* m_doc */
	"Python libexe module (pyexe).",
	/* m_size */
	-1,
	/* m_methods */
	pyexe_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pyexe module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pyexe(
                void )
#else
PyMODINIT_FUNC initpyexe(
                void )
#endif
{
	PyObject *module           = NULL;
	PyGILState_STATE gil_state = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libexe_notify_set_stream(
	 stderr,
	 NULL );
	libexe_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pyexe_module_definition );
#else
	module = Py_InitModule3(
	          "pyexe",
	          pyexe_module_methods,
	          "Python libexe module (pyexe)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
#if PY_VERSION_HEX < 0x03070000
	PyEval_InitThreads();
#endif
	gil_state = PyGILState_Ensure();

	/* Setup the file type object
	 */
	pyexe_file_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyexe_file_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyexe_file_type_object );

	PyModule_AddObject(
	 module,
	 "file",
	 (PyObject *) &pyexe_file_type_object );

	/* Setup the section type object
	 */
	pyexe_section_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyexe_section_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyexe_section_type_object );

	PyModule_AddObject(
	 module,
	 "section",
	 (PyObject *) &pyexe_section_type_object );

	/* Setup the sections type object
	 */
	pyexe_sections_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyexe_sections_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyexe_sections_type_object );

	PyModule_AddObject(
	 module,
	 "sections",
	 (PyObject *) &pyexe_sections_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

