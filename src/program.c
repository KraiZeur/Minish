/* ************************************************************ */
/**
 * name   : program.c
 * author : RITALY Thomas
 * date   : 2014-03-29
 *
 * description : Contains the main function to run the program
 */
/* ************************************************************ */

#include <stdio.h>
#include <stdlib.h>

#include "program.h"
#include "logging.h"
 #include "utils.h"
#include "lineparser.h"

#define BUFFER_SIZE 512

void runProgram () {
 	
	char buffer [BUFFER_SIZE];

	/* Read from stdin the user's commands */
	while (fgets (buffer , BUFFER_SIZE , stdin) != NULL) {

		removeCarriageReturn (buffer);
		logging (TRACE_DEBUG, "\"%s\" is read from stdin", buffer);

		parserLine (buffer);

	}

}