/*
 * init.c -- routines to initialize the prototype Manchester machine
 *
 * LW	06/17/89
 */
#include <stdio.h>
#include <ctype.h>
#include "madm.h"
#include "display.h"
#include "proto.h"

static int Demo = 0;	/* flag will be non-zero if demo is desired */

/*
 * Code for Kilburn's Highest Factor Routine
 *		(the world's first working program:
 *				21 June 1948)
 *
 * 18 July 1948 version
 *
 * This code is loaded into the store if the
 * program is run as a demo.
 */
static LINE Orig_pgm[] = {
	0,
	0x4018,		/*    -24, A  */
	0x601a,		/*      a, 26 */
	0x401a,		/*    -26, A  */
	0x601b,		/*      a, 27 */
	0x4017,		/*    -23, A  */
	0x801b,		/* a - 27, A  */
	0xc000,		/*     Test   */
	0x2014,		/* c + 20, C  */
	0x801a,		/* a - 26, A  */
	0x6019,		/*      a, 25 */
	0x4019,		/*    -25, A  */
	0xc000,		/*     Test   */
	0xe000,		/*     Stop   */
	0x401a,		/*    -26, A  */
	0x8015,		/* a - 21, A  */
	0x601b,		/*      a, 27 */
	0x401b,		/*    -27, A  */
	0x601a,		/*      a, 26 */
	0x0016,		/*     22, C  */
	-3,			/* [20] */
	1,			/* [21] */
	4,			/* [22] */
	-0x40000,	/* [23] = -(2**18) */
	0x3ffff		/* [24] = (2**18) - 1 */
};

#define NUM_INSTRUCTIONS	(sizeof(Orig_pgm) / sizeof(*Orig_pgm))

/*
 * initialize -- load the demo program into the store (if necessary)
 *				 and display the contents of the store on the
 *				 simulated Williams tube.
 */
void
initialize()
{
	ADDR line;

	if (Demo) {
		for (line = 0; line < NUM_INSTRUCTIONS; line++)
			Store[line] = Orig_pgm[line];
	}

	set_up_graphics();

	display_line(A_TUBE, A_LINE);

	for (line = 0; line < CONTROL_SIZE; line++)
		display_line(C_TUBE, line);

	for (line = 0; line < STORE_SIZE; line++)
		display_line(S_TUBE, line);

}

/*
 * clean_up -- restore the PC or terminal to its original condition
 */
void
clean_up()
{
	clear_graphics();
}

/*
 * process_options -- process any options that may have been entered
 *					  on the command line.  Currently only "-d" (load
 *					  the demo program) is supported.
 */
void
process_options(argc, argv)
int argc;
char *argv[];
{
	int i;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && tolower(argv[i][1]) == 'd')
			Demo = 1;
		else
			fprintf(stderr, "%s:  Unknown option\n", argv[i]);
	}

}
