#include <string.h>

#include "utils.h"

void removeCarriageReturn (char *buffer) {
	
	if (buffer [strlen (buffer) - 1] == '\n') {
		buffer [strlen (buffer) - 1] = '\0';
	}
	
}