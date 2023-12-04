/*
 * memory.c -- functions to emulate EDSAC's memory operations
 *
 * LW	04/28/89
 */
#include "edsac.h"
#include "proto.h"

/*
 * u_transfer -- transfer the contents of the accumulator to
 *				 storage location "n" and do not clear the accumulator
 *
 *				 Be careful not to disturb the sandwich bit in a
 *				 short word.
 */
void
u_transfer(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);

	if (lflag)
		Store[n++] = Accumulator[1];

	Store[n] = (Store[n] & SANDWICH_BIT) + Accumulator[0];
}

/*
 * transfer -- transfer the contents of the accumulator to
 *			   storage location "n" and clear the accumulator
 */
void
transfer(n, lflag)
ADDR n;
int lflag;
{
	int i;

	u_transfer(n, lflag);

	for (i = 0; i < ACCUM_SIZE; i++)
		Accumulator[i] = 0;

}

/*
 * load_multiplier -- copy the number in storage location "n" into
 *					  the multiplier register
 *
 *					  Ignore the sandwich bit in short words.
 */
void
load_multiplier(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);

	if (lflag)
		Multiplier[1] = Store[n++];
	else
		Multiplier[1] = 0;

	Multiplier[0] = Store[n] & ~SANDWICH_BIT;
}
