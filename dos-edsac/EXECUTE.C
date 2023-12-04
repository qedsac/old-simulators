/*
 * execute.c -- fetch and execute EDSAC orders
 *
 * LW	04/21/89
 */
#include "edsac.h"
#include "proto.h"

void
execute()
{
	for (EDSAC_status = RUNNING; EDSAC_status != STOPPED; ) {
		fetch_order();
		exec_order();
	}
}
