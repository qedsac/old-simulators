/*
 * madm.c -- Global variables for Mark I Prototype simulator
 *
 * LW	06/17/89
 */
#include "madm.h"

/*
 * Stuff in Williams Tubes
 */
LINE  Accumulator[ACCUM_SIZE];				/* arithmetic register */
LINE  Control[CONTROL_SIZE];				/* program counter */
LINE  Store[STORE_SIZE];					/* main memory */
INSTRUCTION Staticisor;						/* current instruction */

/*
 * control information
 */
STATUS MADM_status = STOPPED;				/* is machine running or not? */
