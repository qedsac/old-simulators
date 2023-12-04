/*
 * inout.c -- functions to emulate EDSAC's input/output operations
 *
 * LW	01/03/90
 */
#include <stdio.h>
#include "edsac.h"
#include "inout.h"
#include "proto.h"

/*
 * input -- Read the next row of holes on the input tape and place
 *			the resulting integer, multiplied by 2**(-16), in
 *			storage location "n".  Be careful not to disturb the
 *			sandwich bit in short words.  Note that the hi-order
 *			bit on the "tape" is reversed.
 */
void
input(n, lflag)
ADDR n;
int lflag;
{
	int c;

	n = check_addr(n, lflag);

	if (lflag)
		Store[n++] = 0;

	if ((c = getc(Tape_reader)) == EOF)
		error(n, lflag);

	Store[n] = (Store[n] & SANDWICH_BIT) + (c & MAX_CHAR ^ CHAR_HI_BIT);
}

/* character set up on teleprinter */
static int Set_up_char = 0x10;	/* harmless character at first */

/*
 * output -- print the character now set up on the teleprinter and
 *			 set up on the teleprinter the character represented
 *			 by the most significant bits in storage location "n"
 */
void
output(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);
	putc(Set_up_char, Teleprinter);

	Set_up_char = (Store[n+lflag] >> (HIWORD_BITS - CHAR_BITS)) & MAX_CHAR;
}

/*
 * print_check -- place the bits which represent the character
 *				  now set up on the teleprinter in the five most
 *				  significant places in storage location "n",
 *				  clearing the remainder of the location.
 *				  Be careful not to disturb the sandwich bit in
 *				  a short word.
 */
void
print_check(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);

	if (lflag)
		Store[n++] = 0;

	Store[n] = (Store[n] & SANDWICH_BIT)
				+ ((WORD) Set_up_char << (HIWORD_BITS - CHAR_BITS));
}
