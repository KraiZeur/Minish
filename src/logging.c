#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#include "logging.h"
#include "utils.h"

/* The file used to log the output messages */
static FILE* logging_file;

void initLoggingFile (const char *path) {

	if ((logging_file = fopen (path, "a")) == NULL) {
		perror ("Open the logging file failed");
	}

}

/** 
 * Takes the type of log and a formatted string for the
 * logging message. 
 */
void logging (const char *tag, const char *format, ...) {

	if (logging_file != NULL) {
		time_t now;
		char buffer [512];
		va_list args;

		time(&now);

		char *bufferTime = ctime(&now);
		removeCarriageReturn (bufferTime);

		/* Format the args */
		va_start(args, format);
	    vsnprintf(buffer, sizeof(buffer), format, args);
	    va_end(args);

		fprintf (logging_file, "%s [%s]: %s\n", bufferTime, tag, buffer);
		fflush (logging_file);
	}

}

/** 
 * Close the logging file if the user doesn't have the right
 * to open/write in the file do nothing 
 */
void closeLoggingFile () {

	if (logging_file != NULL) {
		if ((fclose (logging_file)) == EOF) {
			perror ("Close the logging file failed");
		}
	}

}