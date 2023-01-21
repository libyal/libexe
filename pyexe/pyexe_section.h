/*
 * Python object wrapper of libexe_section_t
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

#if !defined( _PYEXE_SECTION_H )
#define _PYEXE_SECTION_H

#include <common.h>
#include <types.h>

#include "pyexe_libexe.h"
#include "pyexe_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyexe_section pyexe_section_t;

struct pyexe_section
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libexe section
	 */
	libexe_section_t *section;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyexe_section_object_methods[];
extern PyTypeObject pyexe_section_type_object;

PyObject *pyexe_section_new(
           PyTypeObject *type_object,
           libexe_section_t *section,
           PyObject *parent_object );

int pyexe_section_init(
     pyexe_section_t *pyexe_section );

void pyexe_section_free(
      pyexe_section_t *pyexe_section );

PyObject *pyexe_section_read_buffer(
           pyexe_section_t *pyexe_section,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_section_read_buffer_at_offset(
           pyexe_section_t *pyexe_section,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_section_seek_offset(
           pyexe_section_t *pyexe_section,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyexe_section_get_offset(
           pyexe_section_t *pyexe_section,
           PyObject *arguments );

PyObject *pyexe_section_get_size(
           pyexe_section_t *pyexe_section,
           PyObject *arguments );

PyObject *pyexe_section_get_start_offset(
           pyexe_section_t *pyexe_section,
           PyObject *arguments );

PyObject *pyexe_section_get_virtual_address(
           pyexe_section_t *pyexe_section,
           PyObject *arguments );

PyObject *pyexe_section_get_name(
           pyexe_section_t *pyexe_section,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYEXE_SECTION_H ) */

