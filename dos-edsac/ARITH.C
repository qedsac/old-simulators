/*
 * arith.c -- functions to emulate EDSAC's arithmetic operations
 *			  Note that operations on short words need to avoid
 *			  using the sandwich bit
 *
 * LW	05/20/90
 * LW	05/11/90	fixed bug in roundoff
 */
#include "edsac.h"
#include "orders.h"
#include "proto.h"

/*
 * add -- add the number in storage location "n" into the
 *		  accumulator
 */
void
add(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);

	if (lflag) {
		Accumulator[1] += Store[n++];

		if (Accumulator[1] > MAX_LOWORD) {
			++Accumulator[0];
			Accumulator[1] &= MAX_LOWORD;
		}
	}

	Accumulator[0] += Store[n] & ~SANDWICH_BIT;
	Accumulator[0] &= MAX_HIWORD;
}

/*
 * subtract -- subtract the number in storage location "n"
 *			   from the accumulator
 */
void
subtract(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);

	if (lflag) {
		Accumulator[1] -= Store[n++];

		if (Accumulator[1] < 0) {
			--Accumulator[0];
			Accumulator[1] &= MAX_LOWORD;
		}
	}

	Accumulator[0] -= Store[n] & ~SANDWICH_BIT;
	Accumulator[0] &= MAX_HIWORD;
}

/*
 * mult_add -- multiply the number in storage location "n" by
 *			   the number in the multiplier register and add
 *			   the product into the accumulator
 */
void
mult_add(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);
	do_mult(n, lflag);
	add_into_acc();
}

/*
 * mult_sub -- multiply the number in storage location "n" by
 *			   the number in the multiplier register and subtract
 *			   the product from the accumulator
 */
void
mult_sub(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);
	do_mult(n, lflag);
	sub_from_acc();
}

/*
 * collate -- AND the number in storage location "n" with the
 *			  contents of the multiplier register and add
 *			  the result into the accumulator
 */
void
collate(n, lflag)
ADDR n;
int lflag;
{
	n = check_addr(n, lflag);

	if (lflag) {
		Accumulator[1] += Store[n++] & Multiplier[1];

		if (Accumulator[1] > MAX_LOWORD) {
			++Accumulator[0];
			Accumulator[1] &= MAX_LOWORD;
		}
	}

	Accumulator[0] += Store[n] & ~SANDWICH_BIT & Multiplier[0];
	Accumulator[0] &= MAX_HIWORD;
}

/*
 * rshift --  shift the number in the accumulator to the right
 */
void
rshift(n, lflag)
ADDR n;
int lflag;
{
	/* calculate proper control word & shift */
	if (n == 0 && !lflag)
		shift_right(R_CODE << (ADDR_BITS + FLAG_BITS));
	else
		shift_right((CONTROL_WORD)(n << 1) + lflag);
}

/*
 * lshift --  shift the number in the accumulator to the left
 */
void
lshift(n, lflag)
ADDR n;
int lflag;
{
	/* calculate proper control word & shift */
	if (n == 0 && !lflag)
		shift_left(L_CODE << (ADDR_BITS + FLAG_BITS));
	else
		shift_left((CONTROL_WORD)(n << 1) + lflag);
}

/*
 * roundoff -- round-off the number in the accumulator to 34 bits
 *			   (i.e., add 2**(-35) to the accumulator)
 */
void
roundoff(n, lflag)
ADDR n;
int lflag;
{
	Accumulator[2] += SANDWICH_BIT;

	if (Accumulator[2] > MAX_LOWORD) {
		Accumulator[2] &= MAX_LOWORD;

		if (++Accumulator[1] > MAX_LOWORD) {
			Accumulator[1] &= MAX_LOWORD;
			++Accumulator[0];
			Accumulator[0] &= MAX_HIWORD;
		}
	}
}
