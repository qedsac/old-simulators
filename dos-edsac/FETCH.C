/*
 * fetch.c -- fetch the next order from the store into
 *			  the order tank, separating the order into
 *			  its components and pointing the sequence
 *			  control at the next order to be executed.
 *
 * LW	03/30/89
 */
#include "edsac.h"
#include "proto.h"

void
fetch_order()
{
	WORD curr_order;

	curr_order = Store[Sequence_control_tank++];

	Order_tank.o_long = curr_order & MAX_FLAG;
	curr_order >>= FLAG_BITS;
	Order_tank.o_addr = curr_order & MAX_ADDR;
	curr_order >>= ADDR_BITS;
	Order_tank.o_func = curr_order & MAX_FUNC;
}
