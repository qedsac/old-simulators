/*
 * graphics.h -- System dependent definitions needed for graphics display
 *				 in Prototype Manchester Mark I simulator.
 *
 *				 [IBM/PC CGA version]
 *
 *				 NOTE:  Display routines in the simulator assume that
 *				 (0, 0) and (X_MAX, Y_MAX) are the lower-left and upper-
 *				 right corners of the graphics screen.
 *
 * LW	06/17/89
 */

#define	H_DOTS		  320		/* horizontal resolution of screen */
#define	V_DOTS		  200		/* vertical resolution of screen */

#define DOTS_PER_BYTE	4		/* # of pixels in each screen byte */

#define	BLOB_WIDTH		2		/* horz size of blob in dots */
#define	BLOB_HEIGHT		1		/* vert size of blob in dots */

#define	H_SPACE			2		/* horz dots between blobs */
#define	V_SPACE			2		/* vert dots between blobs */

#define	XH_SPACE		0		/* extra horz dots for grouping blobs */
#define	XV_SPACE		0		/* extra vert dots for grouping blobs */

/*
 * width of a display line includes one blob for every bit (and space between),
 * along with extra space between every 4 blobs and another chunk of
 * extra space between every 16 blobs (currently there is no extra space).
 */
#define	LINE_WIDTH		(BLOB_WIDTH * LINE_BITS					\
							+ H_SPACE * (LINE_BITS - 1)			\
							+ XH_SPACE * (LINE_BITS/4 - 1)		\
							+ XH_SPACE * 2)

#define CHAR_WIDTH		8		/* width of displayed char in pixels */
#define CHAR_HEIGHT		8		/* height of displayed char in pixels */

#define NUM_ROWS		(V_DOTS / CHAR_HEIGHT)
#define NUM_COLS		(H_DOTS / CHAR_WIDTH)

/* "function" to display a string at given coordinates */
#define show_label(x, y, label)			\
				(scr_curs(NUM_ROWS-1-((y)/CHAR_HEIGHT), (x)/CHAR_WIDTH),	\
				 scr_puts(label))
