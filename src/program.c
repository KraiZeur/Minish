/* ************************************************************ */
/**
 * name   : program.c
 * author : RITALY Thomas
 * date   : 2014-03-29
 *
 * description : 
 */
/* ************************************************************ */

#include <stdio.h>
#include <stdlib.h>

#include "program.h"
#include "logging.h"
#include "utils.h"
#include "lineparser.h"

#define BUFFER_SIZE 512

/** 
 * Display the line containing the username and the current directory path
 * user@user:path$ 
 */
void displayStandardLine () {
	char *cwd = getWorkingDirectory ();
	char *username = getenv ("USER");
	if (username == NULL) 
		printf ("\x1b[32mUSER:\x1b[0m%s$ ", cwd);
	else 
		printf ("\x1b[32m%s:\x1b[0m%s$ ", username, cwd);
	
	free (cwd);
	fflush (stdout);
}

/** 
 * Run the program display the standard line and take inputs
 * from user  
 */
void runProgram () {
 	
	char buffer [BUFFER_SIZE];

	displayStandardLine ();

	/* Read from stdin the user's commands */
	while (fgets (buffer , BUFFER_SIZE , stdin) != NULL) {

		removeCarriageReturn (buffer);
		logging (TRACE_DEBUG, "\"%s\" is read from stdin", buffer);

		parseLine (buffer);

		displayStandardLine ();

	}

}