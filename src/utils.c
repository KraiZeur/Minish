#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

void removeCarriageReturn (char *buffer) {

	if (buffer [strlen (buffer) - 1] == '\n') {
		buffer [strlen (buffer) - 1] = '\0';
	}
	
}

/** 
 * Get the current working directory as a string
 * /!\ You must free the variable 
 */
char *getWorkingDirectory () {

	char *cwd = malloc (1024);
	getcwd (cwd, 1024);

	return cwd;

}
