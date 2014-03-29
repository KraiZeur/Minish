/* ************************************************************ */
/**
 * name   : file.c
 * author : RITALY Thomas
 * date   : 2014-03-26
 *
 * description : This file is Only for .. .
 */
/* ************************************************************ */

 void runProgram(char *buffer) {
 	
	char *separator = " ";
	char *token, *saveptr;
	token = strtok (buffer, separator, &saveptr);
	
	while (token != NULL) {
	
		token = strtok_r (NULL, separator, &saveptr);
	
	}

 }