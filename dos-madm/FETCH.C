/*
 * fetch.c -- fetch the next instruction from the store into
 *			  the P.I. and separate it into its components
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "display.h"
#include "proto.h"

void
fetch_instruction()
{
	Control[PI_LINE] = Store[++Control[CI_LINE] & MAX_ADDR];

	display_line(C_TUBE, CI_LINE);
	display_line(C_TUBE, PI_LINE);

	Staticisor.i_addr = Control[PI_LINE] & MAX_ADDR;
	Staticisor.i_func = (Control[PI_LINE] >> ADDR_BITS) & MAX_FUNC;
}
