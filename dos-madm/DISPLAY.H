/*
 * display.h -- System independent definitions needed for graphics
 *				display in the Prototype Manchester Mark I simulator.
 *
 *				NOTE:  Display routines in the simulator assume that
 *				(0, 0) and (X_MAX, Y_MAX) are the lower-left and upper-
 *				right corners of the graphics screen.
 *
 * LW	06/18/89
 */

/*
 * definitions for setting up "monitor tubes" on the screen
 */
typedef struct {
	unsigned mt_x, mt_y;	/* display coords of 1st bit in 1st line in tube */
	LINE *mt_val;			/* pointer to values being displayed */
} MONITOR_TUBE;

#define NUM_MONITORS	3		/* there are 3 monitor tubes, 1 each for: */

#define A_TUBE			0		/* the accumulator, */
#define C_TUBE			1		/* the control, */
#define S_TUBE			2		/* and the store */

/* x-y coords for the 1st bits in the various tubes */
/* Accumulator & Control Tubes are evenly spaced in the top half */
/* of the display; the Store Tube is centered in the bottom half */
#define A_X		((H_DOTS - 2*LINE_WIDTH)/3		\
					- ((H_DOTS - 2*LINE_WIDTH)/3) % DOTS_PER_BYTE)
#define A_Y		(3 * V_DOTS / 4)
#define C_X		((H_DOTS - A_X - LINE_WIDTH)	\
					- (H_DOTS - A_X - LINE_WIDTH) % DOTS_PER_BYTE)
#define C_Y		(A_Y + 2)
#define S_X		((H_DOTS - LINE_WIDTH)/2		\
					- ((H_DOTS - LINE_WIDTH)/2) % DOTS_PER_BYTE)
#define S_Y		(V_DOTS / 2)

extern MONITOR_TUBE monitors[];
