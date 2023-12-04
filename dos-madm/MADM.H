/*
 * madm.h -- definitions relating to the operating characteristics of
 *			 the prototype Manchester Mark I
 *
 * LW	06/17/89
 */

typedef enum {STOPPED, RUNNING, MANUAL} STATUS;

extern STATUS MADM_status;

/*
 * Storage line in prototype Williams tube is 32 bits long
 */
typedef long LINE;

#define LINE_BITS		32
#define MAX_LINE		(~(~0L << LINE_BITS))		/* mask for usable bits */

/*
 * Structure of an instruction in the prototype
 */
typedef unsigned int ADDR;		/* storage location */

typedef struct {
	int  i_func;		/* function code */
	ADDR i_addr;		/* store location referred to */
} INSTRUCTION;

#define FUNC_BITS			3
#define MAX_FUNC			(~(~0 << FUNC_BITS))	/* function mask */

#define ADDR_BITS			13
#define UNUSED_ADDR_BITS	8
#define MAX_ADDR			(~(~0 << (ADDR_BITS - UNUSED_ADDR_BITS)))
									/* address mask */

/*
 * Prototype registers & main memory (all in Williams Tubes)
 */
/* # of lines in the various Williams Tubes */
#define ACCUM_SIZE		 1
#define CONTROL_SIZE	 2
#define STORE_SIZE		32

/* indices of each line in the "register" tubes */
#define	A_LINE		0		/* Accumulator line */

#define CI_LINE		0		/* Control Instruction line */
#define PI_LINE		1		/* Present Instruction line */

extern LINE  Accumulator[], Control[], Store[];
extern INSTRUCTION Staticisor;
