#pragma once
#include <stdint.h>

/*
 * Format: height, width, spacing, first_char, last_char, <bitmap>
 * Bit 0 = top row, bit 7 = bottom row — one byte per column, left to right
 * Covers '0' (48) to ':' (58)
 *
 * Visual layout per digit (5x7 active, row 7 = padding):
 *
 *  '0'        '1'        '2'        '3'        '4'
 *  _ X X X _  _ _ X _ _  _ X X X X  _ X X X X  X _ _ _ X
 *  X _ _ _ X  _ X X _ _  _ _ _ _ X  _ _ _ _ X  X _ _ _ X
 *  X _ _ _ X  _ _ X _ _  _ _ _ _ X  _ _ _ _ X  X _ _ _ X
 *  X _ _ _ X  _ _ X _ _  _ X X X _  _ X X X X  X X X X X
 *  X _ _ _ X  _ _ X _ _  X _ _ _ _  _ _ _ _ X  _ _ _ _ X
 *  X _ _ _ X  _ _ X _ _  X _ _ _ _  _ _ _ _ X  _ _ _ _ X
 *  _ X X X _  _ X X X _  X X X X X  _ X X X X  _ _ _ _ X
 *
 *  '5'        '6'        '7'        '8'        '9'
 *  X X X X X  _ X X X _  X X X X X  _ X X X _  _ X X X X
 *  X _ _ _ _  X _ _ _ _  _ _ _ _ X  X _ _ _ X  X _ _ _ X
 *  X _ _ _ _  X _ _ _ _  _ _ _ _ X  X _ _ _ X  X _ _ _ X
 *  X X X X _  X X X X _  _ _ _ _ X  _ X X X _  _ X X X X
 *  _ _ _ _ X  X _ _ _ X  _ _ _ _ X  X _ _ _ X  _ _ _ _ X
 *  _ _ _ _ X  X _ _ _ X  _ _ _ _ X  X _ _ _ X  _ _ _ _ X
 *  _ X X X X  _ X X X _  _ _ _ _ X  _ X X X _  _ X X X X
 *
 *  ':'
 *  _ _ _ _ _
 *  _ X X _ _
 *  _ X X _ _
 *  _ _ _ _ _
 *  _ X X _ _
 *  _ X X _ _
 *  _ _ _ _ _
 */

static const uint8_t font_modern[] =
{
    8, 5, 1, 48, 58,
    0x3E, 0x41, 0x41, 0x41, 0x3E,  /* 0 */
    0x00, 0x42, 0x7F, 0x40, 0x00,  /* 1 */
    0x70, 0x49, 0x49, 0x49, 0x47,  /* 2 */
    0x00, 0x49, 0x49, 0x49, 0x7F,  /* 3 */
    0x0F, 0x08, 0x08, 0x08, 0x7F,  /* 4 */
    0x0F, 0x49, 0x49, 0x49, 0x71,  /* 5 */
    0x3E, 0x49, 0x49, 0x49, 0x30,  /* 6 */
    0x01, 0x01, 0x01, 0x01, 0x7F,  /* 7 */
    0x36, 0x49, 0x49, 0x49, 0x36,  /* 8 */
    0x06, 0x49, 0x49, 0x49, 0x7F,  /* 9 */
    0x00, 0x36, 0x36, 0x00, 0x00,  /* : */
};
