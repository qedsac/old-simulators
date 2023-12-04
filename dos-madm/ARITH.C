/*
 * arith.c -- functions to emulate Manchester Prototype's
 *			  arithmetic operations
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "display.h"
#include "proto.h"

/*
 * subtract -- subtract the number in storage location "s"
 *			   from the accumulator
 */
void
subtract(s)
ADDR s;
{
	Accumulator[A_LINE] -= Store[s];
	display_line(A_TUBE, A_LINE);
}
