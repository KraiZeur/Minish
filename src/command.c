/* ************************************************************ */
/**
* name   : command.c
* author : RITALY Thomas
* date   : 2014-03-29
*
* description : This file is Only for .. .
*/
/* ************************************************************ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"

/** 
 * Parse a line and create the Command associated 
 */
Command lineToCommand (char *line) {

	Command cmd;

	char *separator = " ";
	char *token, *saveptr;

	token = strtok_r (line, separator, &saveptr);

	int argc = 0;

	while (token != NULL) {

		strcpy (cmd.args [argc], token);
		
		token = strtok_r (NULL, separator, &saveptr);
	
	}

	cmd.nbr_args = argc;

	return cmd;

}

/** 
 * Execute the clear command 
 */
void clearCommand () {

	system ("clear");

}