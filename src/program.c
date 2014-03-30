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
#include <string.h>

#include "program.h"
 #include "logging.h"

void runProgram (char *buffer) {
 	
	char *separator = " \n";
	char *token, *saveptr;
	token = strtok_r (buffer, separator, &saveptr);
	
	while (token != NULL) {
	
		logging (TRACE_DEBUG, "\"%s\" a new token", token);
		token = strtok_r (NULL, separator, &saveptr);
	
	}

}