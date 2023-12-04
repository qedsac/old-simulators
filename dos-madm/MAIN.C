/*
 * main.c -- Manchester Prototype main program
 *
 * LW	05/30/89
 */
#include "madm.h"
#include "proto.h"

main(argc, argv)
int argc;
char *argv[];
{
	process_options(argc, argv);
	initialize();

	while (edit())
		execute();

	clean_up();
}
