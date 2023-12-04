/*
 * keyboard.h -- System dependent definitions needed for 
 *				 use of the keyboard in "editing" programs
 *				 for Prototype Manchester Mark I simulator.
 *
 *				 [IBM/PC Aztec C version]
 *
 * LW	06/16/89
 */
#define START_CMD	'\r'		/* CR to start pgm at instruction 1 */
#define SSTEP_CMD	's'			/* 's' to single-step program */
#define CLEAR_CMD	'c'			/* 'c' to clear store (KSC key) */
#define CLR_AC_CMD	'k'			/* 'k' to clear A & C (KCC key) */
#define TOGGLE_CMD	' '			/* space bar to toggle the current bit */
#define QUIT_CMD	'\033'		/* ESC to leave simulator */

#define UP_CMD		'\310'		/* Up arrow key on IBM/PC */
#define DOWN_CMD	'\320'		/* Down arrow key on IBM/PC */
#define RIGHT_CMD	'\315'		/* Right arrow key on IBM/PC */
#define LEFT_CMD	'\313'		/* Left arrow key on IBM/PC */

/* 
 * use Aztec C keyboard functions for echo-free input & polling
 */
#define next_cmd()	scr_getc()			/* get character/cmd from keyboard */
#define cmd_ready() (scr_poll() != -1)	/* has a key been pressed? */
