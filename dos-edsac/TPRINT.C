/*
 * tprint.c -- Emulate the EDSAC teleprinter.
 *			   Input will be teleprinter codes;
 *			   output will be native character set
 *			   (some ASCII hard-coded).
 *
 *				   Usage:  tprint [filename ... ]
 *
 *			   Input comes from the files specified on
 *			   the command line.  If no files are specified
 *			   or "-" is used as a filename, the standard
 *			   input is used.
 *
 * LW	05/30/89
 */
#include <stdio.h>
#include <string.h>
#include "tprint.h"

#define	SWITCH			0x100
#define LMODE			0		/* letter printing mode */
#define FMODE			1		/* figure printing mode */

#define isswitch(c)		((c) & SWITCH)

#define CR				'\r'
#define LF				'\n'
#define BELL			'\a'

#define STERLING		'\234'	/* IBM-PC ASCII for Pounds-Sterling symbol */


int Mode = LMODE;		/* assume teleprinter starts in letter printing mode */

/* translation table for EDVAC teleprinter characters. */
const int transtab[2][32] = {
	/* letter mode */
	{
		'P', 'Q', 'W', 'E',
		'R', 'T', 'Y', 'U',
		'I', 'O', 'J', SWITCH+FMODE,
		'S', 'Z', 'K', SWITCH+LMODE,
		SWITCH+LMODE, 'F', CR,  'D',
		' ', 'H', 'N', 'M',
		LF,  'L', 'X', 'G',
		'A', 'B', 'C', 'V'
	},
	/* figure mode */
	{
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', BELL, SWITCH+FMODE,
		'"', '+', '(', SWITCH+LMODE,
		SWITCH+FMODE, '$', CR, ';',
		' ', STERLING,  ',', '.',
		LF,  ')', '/', '#',
		'-', '?', ':', '='
	}
};

main(argc, argv)
int argc;
char *argv[];
{
	int i;
	FILE *f;

	if (argc == 1) {			/* no files specified */
		print_file(stdin);
	} else {
		for (i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-") == 0)
				print_file(stdin);
			else if ((f = fopen(argv[i], "r")) != NULL)
							   /* replace ^ with "rb" when possible */
				print_file(f);
			else
				fprintf(stderr, "%s:  Can't open file\n", argv[i]);
		}
	}
}

/*
 * print_file -- print the characters for teleprinter codes in file "infile"
 */
void
print_file(infile)
FILE *infile;
{
	int c;

	while ((c = getc(infile)) != EOF)
		print_char(c);

}

/*
 * print_char -- print the character represented by the EDVAC teleprinter
 *				 code "c".  "SWITCH" characters change the teleprinter from
 *				 "letter shift" to "figure shift" and back again
 */
void
print_char(c)
int c;
{
	c = transtab[Mode][c & 0x1f];	/* translate character */

	if (isswitch(c))
		Mode = c & (~SWITCH);		/* switch printer mode */
	else
		putc(c, stdout);			/* or print it */
}
