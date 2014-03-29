#include <string.h>

#include "utils.h"

void removeCarriageReturn (char *buffer) {
	buffer [strlen (buffer) - 1] = '\0';
}