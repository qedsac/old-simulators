/*
 * display.c -- routines to display binary values on the simulated
 *				Williams Tube "memory" for the Prototype Mark I.
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "graphics.h"
#include "display.h"
#include "proto.h"

/* initialize the monitor tubes */
MONITOR_TUBE monitors[NUM_MONITORS] = {
	{A_X, A_Y, Accumulator},
	{C_X, C_Y, Control},
	{S_X, S_Y, Store}
};

/*
 * display_bit -- display the single bit value at position "bit"
 *				  on line "line" on the given monitor tube ("tube").
 *				  Note that numbers are displayed with the least
 *				  significant bit on the left (backwards binary).
 */
void
display_bit(tube, line, bit)
int tube;
ADDR line;
unsigned bit;
{
	blob((int)(monitors[tube].mt_val[line] >> bit) & 0x1,
		 monitors[tube].mt_x + bit * (BLOB_WIDTH + H_SPACE)
							+ (bit/4) * XH_SPACE
							+ (bit/16) * (2 * XH_SPACE),
		 monitors[tube].mt_y - line * (BLOB_HEIGHT + V_SPACE)
							- (line/4) * XV_SPACE);
}

/*
 * display_line -- display the value on a given "line" of the
 *				   given monitor "tube".
 */
void
display_line(tube, line)
int tube;
ADDR line;
{
	set_up_line(monitors[tube].mt_val[line]);
	show_line(monitors[tube].mt_x,
			  monitors[tube].mt_y - line * (BLOB_HEIGHT + V_SPACE)
			  					  - (line/4) * XV_SPACE);
}
