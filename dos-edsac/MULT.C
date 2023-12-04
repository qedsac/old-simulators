/*
 * mult.c -- auxiliary functions necessary to multiply two
 *			 35-bit numbers.  The EDSAC arithmetical unit assumes
 *			 that all numbers are within the range -1 <= x < 1.
 *			 In other words, the decimal point is assumed to be
 *			 just to the right of the leftmost bit.
 *
 * LW	05/21/89
 */
#include <string.h>
#include "edsac.h"
#include "proto.h"

typedef unsigned int FACTOR[4];				/* 4 9-bit numbers */

static FACTOR Factors[2];			/* multiplier & multiplicand */
static unsigned long Result[8];
static int Negative_result;

#define	LO9MASK		0x1ff			/* masks used for creating factors */
#define HI9MASK		(LO9MASK << 9)

#define FSIGN_BIT	0x80			/* msw of 35-bit factor is only 8 bits */
#define LO8MASK		0xff

#define sign_set(f)	((f)[0] & FSIGN_BIT)

/*
 * complement -- form the two's complement of a given factor ("f")
 */
static
void
complement(f)
FACTOR f;
{
	int i;

	for (i = 0; i < 4; i++)
		f[i] = ~f[i] & LO9MASK;

	for (i = 3; i >= 0 && ++f[i] > LO9MASK; i--)
		f[i] &= LO9MASK;

	f[0] &= LO8MASK;
}

/*
 * set_up_mult -- set everything up to multiply a number (possibly long)
 *				  from the store ("num") by the value in the multiplier
 *				  register:  Clear the result ("Result") and
 *				  create two 35-bit factors made up of 1 8-bit and 3 9-bit
 *				  chunks ("Factors") from the two values to be multiplied.
 *				  Force the factors to be non-negative, but remember
 *				  what sign the result will be ("Negative_result").
 *
 *				  Ignore the sandwich bit in short words from the store.
 */
static
void
set_up_mult(num, lflag)
WORD num[];			/* may be single- or double-word from store */
int lflag;
{
	int i;

	Negative_result = 0;
	memset(Result, 0, sizeof(Result));
	memset(Factors, 0, sizeof(Factors));

	if (lflag) {
		Factors[1][3] = num[0] & LO9MASK;
		Factors[1][2] = (num[0] & HI9MASK) >> 9;
	}

	Factors[0][3] = Multiplier[1] & LO9MASK;
	Factors[0][2] = (Multiplier[1] & HI9MASK) >> 9;

	Factors[0][1] = Multiplier[0] & LO9MASK;
	Factors[0][0] = (Multiplier[0] & HI9MASK) >> 9;
	Factors[1][1] = num[lflag] & LO9MASK;
	Factors[1][0] = (num[lflag] & ~SANDWICH_BIT & HI9MASK) >> 9;

	for (i = 0; i < 2; i++) {
		if (sign_set(Factors[i])) {
			Negative_result = !Negative_result;
			complement(Factors[i]);
		}
	}

}

/*
 * perform_mult -- multiply 2 35-bit factors ("Factors") and put the
 *				   result in "Result".
 */
static
void
perform_mult()
{
	int i, j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			Result[i+j+1] += (unsigned long) Factors[0][i] * Factors[1][j];

	for (i = 7; i > 0; i--) {
		Result[i-1] += (Result[i] & ~LO9MASK) >> 9;
		Result[i] &= LO9MASK;
	}
}

/*
 * do_mult -- multiply the number in storage location "n" by
 *			  the value in the multiplier register,
 *			  placing the result in "Result"
 */
void
do_mult(n, lflag)
ADDR n;
int lflag;
{
	set_up_mult(&Store[n], lflag);
	perform_mult();
}

/*
 * add_into_acc -- add the result of the multiplication ("Result")
 *				   into the accumulator.  
 */
void
add_into_acc()
{
	int i;

	if (Negative_result) {
		Negative_result = 0;
		sub_from_acc();
	} else {
		/* the result needs to be shifted 2 bits to the left to preserve */
		/* the position of the decimal point */
		for (i = ACCUM_SIZE-1; i > 0; i--) {
			Accumulator[i] += (Result[2*i+1] | (Result[2*i] << 9)) << 2;

			if (Accumulator[i] > MAX_LOWORD) {
				Accumulator[i-1] += Accumulator[i] >> LOWORD_BITS;
				Accumulator[i] &= MAX_LOWORD;
			}
		}

		Accumulator[0] += (Result[1] | (Result[0] << 9)) << 2;
		Accumulator[0] &= MAX_HIWORD;
	}
}

/*
 * sub_from_acc -- subtract the result of the multiplication ("Result")
 *				   from the accumulator.  
 */
void
sub_from_acc()
{
	int i;

	if (Negative_result) {
		Negative_result = 0;
		add_into_acc();
	} else {
		for (i = ACCUM_SIZE-1; i > 0; i--) {
			/* the result needs to be shifted 2 bits to the left to preserve */
			/* the position of the decimal point */
			Accumulator[i] -= (Result[2*i+1] | (Result[2*i] << 9)) << 2;

			if (Accumulator[i] < 0) {
				Accumulator[i-1] += Accumulator[i] >> LOWORD_BITS;
					/* note:  the above stmt relies on a signed right shift */
					/*        this is not portable */
				Accumulator[i] &= MAX_LOWORD;
			}
		}

		Accumulator[0] -= (Result[1] | (Result[0] << 9)) << 2;
		Accumulator[0] &= MAX_HIWORD;
	}
}
