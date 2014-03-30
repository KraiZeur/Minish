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

/** 
 * Main function of the program call the runProgram function to
 * start the program 
 */
int main (int argc, char  *argv []) {

	puts ("Welcome to minish");
	initLoggingFile ("log.txt");
	logging (TRACE_INFO, "Starting the program");

	/* Run the program loop until Ctrl+D signal */
	runProgram ();

	logging (TRACE_INFO, "Closing the program");
	closeLoggingFile ();

	return 0;
}