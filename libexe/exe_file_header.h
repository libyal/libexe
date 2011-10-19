/*
 * The file header definition of a MZ, PE/COFF executable (EXE)
 *
 * Copyright (c) 2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _EXE_FILE_HEADER_H )
#define _EXE_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct exe_mz_file_header exe_mz_file_header_t;

struct exe_mz_file_header
{
	/* Signature
	 * Consists of 4 bytes
	 * "MZ"
	 */
	uint8_t signature[ 2 ];

	/* The size of the last page
	 * Consists of 2 bytes
	 */
	uint8_t last_page_size[ 2 ];

	/* The number of pages
	 * Consists of 2 bytes
	 */
	uint8_t number_of_pages[ 2 ];

	/* The number of relocation entries
	 * Consists of 2 bytes
	 */
	uint8_t number_of_relocation_entries[ 2 ];

	/* The number of header paragraphs
	 * Consists of 2 bytes
	 */
	uint8_t number_of_header_paragraphs[ 2 ];

	/* The minimum number of allocated paragraphs
	 * Consists of 2 bytes
	 */
	uint8_t minimum_allocated_paragraphs[ 2 ];

	/* The maximum number of allocated paragraphs
	 * Consists of 2 bytes
	 */
	uint8_t maximum_allocated_paragraphs[ 2 ];

	/* The initial stack segment
	 * Consists of 2 bytes
	 */
	uint8_t initial_stack_segment[ 2 ];

	/* The initial stack pointer
	 * Consists of 2 bytes
	 */
	uint8_t initial_stack_pointer[ 2 ];

	/* The checksum
	 * Consists of 2 bytes
	 */
	uint8_t checksum[ 2 ];

	/* The entry point
	 * Consists of 4 bytes
	 */
	uint8_t entry_point[ 4 ];

	/* The relocation table offset
	 * Consists of 2 bytes
	 */
	uint8_t relocation_table_offset[ 2 ];

	/* The overlay number
	 * Consists of 2 bytes
	 */
	uint8_t overlay_number[ 2 ];
};

#if defined( __cplusplus )
}
#endif

#endif

