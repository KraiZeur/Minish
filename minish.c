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

#include "commandParser.c"

/** 
 * Main function of the program call the runProgram function to
 * start the program 
 */
int main (int argc, char  *argv[]) {

	puts ("Welcome to minish");

	char buffer[254];

	while (fgets (buffer , 254 , stdin) != NULL) {

		runProgram (buffer);

	}

	return 0;
}