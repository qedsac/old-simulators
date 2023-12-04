/*
 * control.c -- functions to emulate Manchester Prototype's
 *				control operations
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "display.h"
#include "proto.h"

/*
 * stop -- Stop the machine.
 */
void
stop(s)
ADDR s;
{
	MADM_status = STOPPED;
}

/*
 * unused -- unknown operation (null instruction assumed)
 */
void
unused(s)
ADDR s;
{}

/*
 * test -- skip the next instruction if the accumulator is
 *		   less than zero.
 */
void
test(s)
ADDR s;
{
	if (Accumulator[A_LINE] < 0)
		++Control[CI_LINE];
}

/*
 * jump -- replace the C.I. with the number in line "s"
 */
void
jump(s)
ADDR s;
{
	Control[CI_LINE] = Store[s];
	display_line(C_TUBE, CI_LINE);
}

/* 
 * rjump -- add the number in line "s" to the C.I.
 */
void
rjump(s)
ADDR s;
{
	Control[CI_LINE] += Store[s];
	display_line(C_TUBE, CI_LINE);
}
