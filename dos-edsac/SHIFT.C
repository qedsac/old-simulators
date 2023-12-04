/*
 * shift.c -- auxiliary functions necessary to shift the
 *			  number in the accumulator.  On the EDSAC, it seems,
 *			  a right shift will preserve the sign bit, but a
 *			  left shift will not.
 *
 *			  NOTE:  All shifting on the EDSAC is done via
 *			  a "control word" rather than a count of the
 *			  number of bits to be shifted.
 *
 *			  A control word is set up so that the position of
 *			  the rightmost 1 indicates the number of bits to be
 *			  shifted.  For example, a control word of 0x01 would
 *			  imply a 1-bit shift, 0x20 a 6-bit shift, and 0x5000
 *			  a 13-bit shift.
 *
 * LW	04/07/89
 */
#include "edsac.h"
#include "proto.h"

#define lobitclear(n)	(((n) & 0x01) == 0)

static int Nbits;		/* number of bits to be shifted */
static WORD Mask;		/* for extracting bits shifted from one word */
						/* in the accumulator to the next one */
static WORD Sign_bit;	/* original sign of accumulator */

/*
 * set_up_shift -- translate EDSAC shift control word ("control") into
 *				   a count of the number of bits to shift ("Nbits")
 *				   and a mask to extract that number of bits from a
 *				   word ("Mask").
 *				   The shifts will be arithmetic, rather than logical
 *				   so remember the accumulator's sign.
 */
static
void
set_up_shift(control)
CONTROL_WORD control;
{
	Nbits = 1;
	Mask = ~(WORD)0x01;		/* a WORD of all ones */

	Sign_bit = Accumulator[0] & SIGN_BIT;

	for (; lobitclear(control); control >>= 1) {
		++Nbits;
		Mask <<= 1;
	}

	Mask = ~Mask;
}

/*
 * shift_right -- shift the accumulator to the right by the number
 *				  of bits indicated by the control word ("control")
 */
void
shift_right(control)
CONTROL_WORD control;
{
	int i;

	set_up_shift(control);

	for (i = ACCUM_SIZE-1; i > 0; i--) {
		Accumulator[i] >>= Nbits;
		Accumulator[i] |= (Accumulator[i-1] & Mask) << (LOWORD_BITS - Nbits);
	}

	Accumulator[0] >>= Nbits;

	if (Sign_bit != 0)			/* adjust for negative number */
		Accumulator[0] |= Mask << (HIWORD_BITS - Nbits);
}

/*
 * shift_left -- shift the accumulator to the left by the number
 *				 of bits indicated by the control word ("control")
 */
void
shift_left(control)
CONTROL_WORD control;
{
	int i;

	set_up_shift(control);

	Mask <<= LOWORD_BITS - Nbits;

	for (i = 0; i < ACCUM_SIZE-1; i++) {
		Accumulator[i] <<= Nbits;
		Accumulator[i] |= (Accumulator[i+1] & Mask) >> (LOWORD_BITS - Nbits);
		Accumulator[i+1] &= ~Mask;
	}

	Accumulator[ACCUM_SIZE-1] <<= Nbits;
	Accumulator[0] &= MAX_HIWORD;
}
