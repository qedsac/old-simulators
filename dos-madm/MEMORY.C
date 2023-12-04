/*
 * memory.c -- functions to emulate Manchester Prototype's memory operations
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "display.h"
#include "proto.h"

/*
 * load_negative -- load the complement of the number in line "s"
 *					into the accumulator
 */
void
load_negative(s)
ADDR s;
{
	Accumulator[A_LINE] = -Store[s];
	display_line(A_TUBE, A_LINE);
}

/*
 * store_accumulator -- store the number in the accumulator into line "s"
 */
void
store_accumulator(s)
ADDR s;
{
	Store[s] = Accumulator[A_LINE];
	display_line(S_TUBE, s);
}
