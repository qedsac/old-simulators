/*
 * exec_ord.c -- execute the EDSAC order in the order tank
 *
 * LW	03/30/89
 */
#include "edsac.h"
#include "proto.h"

/*
 * jump table -- one C function for each EDSAC function code
 */
typedef void (*EXEC_FUNC)(ADDR, int);

static EXEC_FUNC Optab[] = {
	error,				/* P */
	error,				/* Q */
	error,				/* W */
	pos_branch,			/* E */
	rshift,				/* R */
	transfer,			/* T */
	roundoff,			/* Y */
	u_transfer,			/* U */
	input,				/* I */
	output,				/* O */
	error,				/* J */
	error,				/* Pi */
	subtract,			/* S */
	halt,				/* Z */
	error,				/* K */
	error,				/* Erase */
	error,				/* blank */
	print_check,		/* F */
	error,				/* Theta */
	error,				/* D */
	error,				/* Phi */
	load_multiplier,	/* H */
	mult_sub,			/* N */
	error,				/* M */
	error,				/* Delta */
	lshift,				/* L */
	no_operation,		/* X */
	neg_branch,			/* G */
	add,				/* A */
	error,				/* B */
	collate,			/* C */
	mult_add			/* V */
};

void
exec_order()
{
	/* call the appropriate function to perform the operation */
	Optab[Order_tank.o_func](Order_tank.o_addr, Order_tank.o_long);
}
