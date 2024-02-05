/*
 * MZ header of an executable (EXE) file
 *
 * Copyright (C) 2011-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _EXE_MZ_HEADER_H )
#define _EXE_MZ_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define EXE_MZ_SIGNATURE	(uint8_t *) "MZ"

typedef struct exe_mz_header exe_mz_header_t;

struct exe_mz_header
{
	/* Signature
	 * Consists of 2 bytes
	 */
	uint8_t signature[ 2 ];

	/* Size of the last page
	 * Consists of 2 bytes
	 */
	uint8_t last_page_size[ 2 ];

	/* Number of pages
	 * Consists of 2 bytes
	 */
	uint8_t number_of_pages[ 2 ];

	/* Number of relocation entries
	 * Consists of 2 bytes
	 */
	uint8_t number_of_relocation_entries[ 2 ];

	/* Number of header paragraphs
	 * Consists of 2 bytes
	 */
	uint8_t number_of_header_paragraphs[ 2 ];

	/* Minimum number of allocated paragraphs
	 * Consists of 2 bytes
	 */
	uint8_t minimum_allocated_paragraphs[ 2 ];

	/* Maximum number of allocated paragraphs
	 * Consists of 2 bytes
	 */
	uint8_t maximum_allocated_paragraphs[ 2 ];

	/* Initial stack segment
	 * Consists of 2 bytes
	 */
	uint8_t initial_stack_segment[ 2 ];

	/* Initial stack pointer
	 * Consists of 2 bytes
	 */
	uint8_t initial_stack_pointer[ 2 ];

	/* Checksum
	 * Consists of 2 bytes
	 */
	uint8_t checksum[ 2 ];

	/* Entry point
	 * Consists of 4 bytes
	 */
	uint8_t entry_point[ 4 ];

	/* Relocation table offset
	 * Consists of 2 bytes
	 */
	uint8_t relocation_table_offset[ 2 ];

	/* Overlay number
	 * Consists of 2 bytes
	 */
	uint8_t overlay_number[ 2 ];

	/* Unknown1
	 * Consists of 32 bytes
	 */
	uint8_t unknown1[ 32 ];

	/* Extended header offset
	 * Consists of 4 bytes
	 */
	uint8_t extended_header_offset[ 4 ];

	/* Unknown2
	 * Consists of 112 bytes
	 */
	uint8_t unknown2[ 112 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _EXE_MZ_HEADER_H ) */

