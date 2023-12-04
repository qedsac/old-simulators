/*
 * graphics.c -- system dependent graphics routines for Prototype
 *				 Manchester Mark I simulator.
 *
 *				 [IBM/PC Aztec C 4.10 Version]
 *
 *				 NOTE:  Display routines in the simulator assume that
 *				 (0, 0) and (X_MAX, Y_MAX) are the lower-left and upper-
 *				 right corners of the graphics screen.  If system-supplied
 *				 functions assume otherwise, the adjustments should be
 *				 made here.
 *
 * LW	06/18/89
 */

#include "madm.h"
#include "graphics.h"
#include "display.h"
#include "proto.h"

#define odd(n)	((n) & 1)

/*
 * set_up_graphics -- put the display into graphics mode (if necessary)
 *					  and set up the display screen.
 */
void
set_up_graphics()
{
	static const char main_title[] = "Manchester Mark I Prototype";
	static const char sub_title[]  = "(1948)";

	mode('m');		/* IBM/PC 320x200 color graphics mode */

	show_label((H_DOTS - sizeof(main_title)*CHAR_WIDTH)/2,
				V_DOTS - 1, main_title);
	show_label((H_DOTS - sizeof(sub_title)*CHAR_WIDTH)/2,
				V_DOTS - 1 - CHAR_WIDTH, sub_title);

	/* note that C & A labels are aligned horizontally */
	show_label(A_X - CHAR_WIDTH,  C_Y + CHAR_HEIGHT, "A:");
	show_label(C_X - CHAR_WIDTH,  C_Y + CHAR_HEIGHT, "C:");
	show_label(S_X - CHAR_WIDTH,  S_Y + CHAR_HEIGHT, "S:");
}

/*
 * clear_graphics -- clear the graphics display
 */
void
clear_graphics()
{
	mode('l');		/* IBM/PC 80x25 color text mode */
}

/*
 * blob -- display a blob of light at coordinates (x, y) on the screen.
 *		   A "dash" blob will be displayed for a non-zero "value", a
 *		   "dot" for zero (this simulates the "look" of the Williams
 *		   Tube memory for the Prototype Mark I).
 */
void
blob(value, x, y)
int value;
unsigned x, y;
{
	if (value != 0) 
		color('w');			/* white dashes */
	else
		color(0);			/* black background */

	point(x+1, y);

	if (value == 0)
		color('r');			/* dots are red (to look dimmer) */

	point(x, y);
}

static unsigned char Scan_lines[(LINE_WIDTH+DOTS_PER_BYTE-1)/DOTS_PER_BYTE];

/*
 * set_up_line -- set up the scan line(s) needed to display a given
 *				  "value" on the screen.
 *
 *				  NOTE:  The current algorithm for this routine works
 *				  only if S_X, BLOB_WIDTH+H_SPACE, and XHSPACE
 *				  are divisible by DOTS_PER_BYTE;
 */
void
set_up_line(value)
LINE value;
{
	register unsigned i, byte;

	byte = 0;

	for (i = 0; i < LINE_BITS; i++) {

		if (i % 16 == 0)
			byte += 3 * XH_SPACE / DOTS_PER_BYTE;
		else if (i % 4 == 0)
			byte += XH_SPACE / DOTS_PER_BYTE;

		Scan_lines[byte] = (value & 0x1) ? 0xf0 : 0x80;
		value >>= 1;

		byte += (BLOB_WIDTH + H_SPACE) / DOTS_PER_BYTE;
	}

}

/*
 * show_line -- display the value last set up by "set_up_line" at 
 *				location (x, y) on the screen.
 */
void
show_line(x, y)
unsigned x, y;
{
	extern unsigned _dsval;		/* segment for static data */
	register unsigned offset;	/* offset into video buffer */

	offset =  ((V_DOTS - 1 - y) & ~0x1) * ((H_DOTS / DOTS_PER_BYTE) / 2)
				+ (x / DOTS_PER_BYTE);

	if (!odd(y))
		offset += 0x2000;

	/* assume small data model & CGA card */
	movblock(Scan_lines, _dsval, offset, 0xb800,
			sizeof(Scan_lines));
}

/*
 * draw_box -- draw a box whose lower left hand corner is (lo_x, lo_y)
 *			   and whose upper right hand corner is (hi_x, hi_y).
 *			   The remaining parameter ("visible") determines if the box
 *			   is to be visible or not.
 */
void
draw_box(visible, lo_x, lo_y, hi_x, hi_y)
int visible;
unsigned lo_x, lo_y, hi_x, hi_y;
{
	if (visible)
		color('w');	/* foreground color */
	else
		color(0);	/* background color */

	line(lo_x, lo_y, hi_x, lo_y);
	lineto(hi_x, hi_y);
	lineto(lo_x, hi_y);
	lineto(lo_x, lo_y);
}
