/*
 * NE header of an executable (EXE) file
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

#if !defined( _EXE_NE_HEADER_H )
#define _EXE_NE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define EXE_NE_SIGNATURE	(uint8_t *) "NE"

typedef struct exe_ne_header exe_ne_header_t;

struct exe_ne_header
{
	/* Signature
	 * Consists of 2 bytes
	 * "NE"
	 */
	uint8_t signature[ 2 ];

/* TODO */
	/* Todo
	 * Consists of 62 bytes
	 */
	uint8_t todo[ 62 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _EXE_NE_HEADER_H ) */

