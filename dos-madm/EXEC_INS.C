/*
 * exec_ins.c -- execute the Present Instruction
 *
 * LW	06/17/89
 */
#include "madm.h"
#include "proto.h"

/*
 * jump table -- one C function for each function code
 */
typedef void (*EXEC_FUNC)(ADDR);

static EXEC_FUNC Optab[] = {

	/* function */		/* Operation */

	jump,				/*   s, C	 */
	rjump,				/* c + s, C  */
	load_negative,		/*	-s, A	 */
	store_accumulator,	/*	 a, S	 */
	subtract,			/* a - s, A  */
	subtract,		/* undocumented a - s, A */
	test,				/*	 Test	 */
	stop				/*	 Stop	 */
};

void
exec_instruction()
{
	/* call the appropriate function to perform the operation */
	Optab[Staticisor.i_func](Staticisor.i_addr);
}
