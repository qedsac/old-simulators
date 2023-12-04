/*
 * cursor.c -- functions to manipulate the cursor used in
 *			   editing programs for the Prototype Manchester Machine
 *
 * LW	06/18/89
 */
#include "madm.h"
#include "graphics.h"
#include "display.h"
#include "proto.h"

typedef struct {
	ADDR c_line;		/* current line in store */
    unsigned c_bit;		/* current bit in line */
	unsigned c_x,		/* x position of cursor on screen */
			 c_y;		/* y position of cursor on screen */
} CURSOR;

static CURSOR Cursor = {
	0, 0,
	S_X - 1,
	S_Y - 1
};

/*
 * show_cursor -- display the cursor at its current screen position
 */
void
show_cursor()
{
	draw_box(1, Cursor.c_x, Cursor.c_y,
				Cursor.c_x+BLOB_WIDTH+1,
				Cursor.c_y+BLOB_HEIGHT+1);
}

/*
 * erase_cursor -- remove the cursor from its current screen position
 */
void
erase_cursor()
{
	draw_box(0, Cursor.c_x, Cursor.c_y,
				Cursor.c_x+BLOB_WIDTH+1,
				Cursor.c_y+BLOB_HEIGHT+1);
}

/*
 * place_cursor -- place the cursor at a given bit ("bit")
 *				   on a given line ("line") and display it
 *				   at its new position
 */
void place_cursor(line, bit)
ADDR line;
unsigned bit;
{
	erase_cursor();

	Cursor.c_line = line % STORE_SIZE;
	Cursor.c_bit  = bit  % LINE_BITS;

	Cursor.c_x = S_X - 1
					+ Cursor.c_bit * (BLOB_WIDTH + H_SPACE)
					+ (Cursor.c_bit/4) * XH_SPACE
					+ (Cursor.c_bit/16) * (2 * XH_SPACE);
	Cursor.c_y = S_Y - 1
					- Cursor.c_line * (BLOB_HEIGHT + V_SPACE)
					- (Cursor.c_line/4) * XV_SPACE;

	show_cursor();
}

/*
 * move_cursor -- move the cursor a given distance from the current line
 *				  ("d_line") and a given distance from the current bit
 *				  ("d_bit")
 */
void
move_cursor(d_line, d_bit)
int d_line, d_bit;
{
	place_cursor(Cursor.c_line + d_line, Cursor.c_bit  + d_bit);
}

/*
 * toggle_current_bit -- toggle the bit at the cursor's current location
 */
void
toggle_current_bit()
{
	toggle_bit(Cursor.c_line, Cursor.c_bit);
}

/*
 * display_current_bit -- display the bit at the cursor's current location
 */
void
display_current_bit()
{
	display_bit(S_TUBE, Cursor.c_line, Cursor.c_bit);
}
