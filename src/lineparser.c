/* ************************************************************ */
/**
 * name   : lineparser.c
 * author : RITALY Thomas
 * date   : 2014-03-26
 *
 * description : This file is Only for .. .
 */
/* ************************************************************ */

#include <string.h>

#include "lineparser.h"
#include "logging.h"

void parserLine (char *buffer) {

	char *separator = " \n";
	char *token, *saveptr;
	token = strtok_r (buffer, separator, &saveptr);

	while (token != NULL) {

		logging (TRACE_DEBUG, "\"%s\" a new token", token);
		token = strtok_r (NULL, separator, &saveptr);

	}

}