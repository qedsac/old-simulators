/*
 * execute.c -- fetch and execute instructions for the Manchester Prototype
 *
 * LW	06/16/89
 */
#include "madm.h"
#include "proto.h"
#include "keyboard.h"

void
execute()
{
	do {
		fetch_instruction();
		exec_instruction();
	} while (MADM_status == RUNNING && !cmd_ready());
}
