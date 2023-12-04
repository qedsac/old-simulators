/*
 * edsac.h -- definitions relating to EDSAC's operating characteristics
 *
 * LW	01/03/90
 */

typedef enum {STOPPED, RUNNING} STATUS;

extern STATUS EDSAC_status;

/*
 * EDSAC word size is 17 bits
 * (18 bits when "sandwich bit" used in a double-word variable)
 */
typedef long WORD;

#define HIWORD_BITS		17							/* # of bits/word */
#define MAX_HIWORD		(~(~0L << HIWORD_BITS))		/* mask for usable bits */

#define SIGN_BIT		(1L << (HIWORD_BITS-1))		/* most sig. bit */
#define SANDWICH_BIT	(SIGN_BIT << 1)				/* bit between words */

#define LOWORD_BITS		(HIWORD_BITS+1)				/* reg size + sandwich */
#define MAX_LOWORD		(MAX_HIWORD | SANDWICH_BIT)	/* mask w/ sandwich bit */

/*
 * Structure of an EDSAC order (instruction)
 */
typedef unsigned int ADDR;		/* EDSAC storage location */

typedef struct {
	int  o_func;		/* function code */
	ADDR o_addr;		/* store location referred to */
	int  o_long;		/* 1 if long (35-bit) location, 0 if short (17-bit) */
} ORDER;

#define FUNC_BITS			5						/* 5 bits */
#define MAX_FUNC			(~(~0 << FUNC_BITS))	/* function mask */

#define ADDR_BITS			11						/* 11 bits */
#define MAX_ADDR			(~(~0 << ADDR_BITS))	/* address mask */

#define FLAG_BITS			1						/* 1 bit  */
#define MAX_FLAG			(~(~0 << FLAG_BITS))	/* flag mask */

typedef unsigned int CONTROL_WORD;	/* control word for shift orders */
									/* must hold at least 15 bits */
/*
 * EDSAC ultrasonic tanks (registers & main memory)
 */
#define STORE_SIZE	1024
#define ACCUM_SIZE	4
#define MULT_SIZE	2

extern WORD  Accumulator[], Multiplier[], Store[];
extern ADDR  Sequence_control_tank;
extern ORDER Order_tank;
