/*
 * error.c -- error handling routines for EDSAC emulator
 *
 * LW	01/03/90
 */
#include <stdio.h>
#include "edsac.h"
#include "proto.h"

#define odd(n)	((n) & 1)

static const char Codes[] = "PQWERTYUIOJ#SZK*.FhD!HNM&LXGABCV";

/*
 * error -- print an error message and halt the machine
 */
void
error(n, lflag)
ADDR n;
int lflag;
{

	fprintf(stderr, "Execution Error\n"
					"Order = %c %u %c\n\n",
					Codes[Order_tank.o_func],
					Order_tank.o_addr,
					(Order_tank.o_long ? 'D' : 'F'));
	halt(n, lflag);
}

/*
 * check_addr -- check address "n" for validity and return it 
 *				 (adjusted, if necessary).  If the address is
 *				 odd and refers to a long number ("lflag"), it
 *				 is forced to be even.  If the address does not
 *				 physically exist, it is "wrapped-around".
 */
int
check_addr(n, lflag)
ADDR n;
int lflag;
{

	if (lflag && odd(n))		/* "long" location not even */
		n &= ~1;

	return(n % STORE_SIZE);

}
