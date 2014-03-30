/* ************************************************************ */
/**
 * name   : minish.c
 * author : RITALY Thomas
 * date   : 2014-03-26
 *
 * description : Main file of the program
 */
/* ************************************************************ */

#include <stdio.h>

#include "program.h"
#include "logging.h"
#include "utils.h"

#define BUFFER_SIZE 512

/** 
 * Main function of the program call the runProgram function to
 * start the program 
 */
int main (int argc, char  *argv []) {

	puts ("Welcome to minish");
	initLoggingFile ("log.txt");
	logging (TRACE_INFO, "Starting the program");

	char buffer [BUFFER_SIZE];

	while (fgets (buffer , BUFFER_SIZE , stdin) != NULL) {

		removeCarriageReturn (buffer);
		logging (TRACE_DEBUG, "\"%s\" is read from stdin", buffer);
		runProgram (buffer);

	}

	logging (TRACE_INFO, "Closing the program");
	closeLoggingFile ();

	return 0;
}