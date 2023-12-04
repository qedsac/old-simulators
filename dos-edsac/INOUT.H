/*
 * inout.h -- definitions relating to EDSAC's I/O devices
 *			  (stdio.h must be #included before this file)
 *
 * LW	01/03/90
 */
#define CHAR_BITS		5
#define CHAR_HI_BIT		(1 << (CHAR_BITS-1))
#define MAX_CHAR		(~(~0 << CHAR_BITS))	/* max value of punched */
												/* or printed char */

extern FILE *Tape_reader;		/* punched input */
extern FILE *Teleprinter;		/* teleprinter output */
