#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "lineparser.h"
#include "command.h"

void testRemoveCarriageReturn (void) {

	char *buffer = malloc (sizeof (5));
	strcpy (buffer, "test\n");

	removeCarriageReturn (buffer);

	assert((strcmp(buffer, "test")) == 0);

	puts ("removeCarriageReturn success");

}

void testGetRedirectionType (void) {

	assert (getRedirectionType (">") == REDIR_OUT_TOFILE);
	assert (getRedirectionType ("1>") == REDIR_OUT_TOFILE);
	assert (getRedirectionType (">>") == REDIR_OUT_TOFILE_ADD);
	assert (getRedirectionType ("2>") == REDIR_ERR_TOFILE);
	assert (getRedirectionType ("2>>") == REDIR_ERR_TOFILE_ADD);

	puts ("getRedirectionType success");

}

void testCmd () {

	Command cmd;
	cmd.command_name = "ls";
	cmd.args [0] = "ls";
	cmd.args [1] = "-l";
	cmd.nbr_args = 1;

	assert (strcmp (*(cmd.args), "ls") == 0);
}

void testlineToCommand (void) {

	Command cmd;

	cmd = lineToCommand ("ls -l");

	printf ("%d\n", cmd.nbr_args);

	assert (strcmp (*(cmd.args), "ls") == 0);

}

void testGetWorkingDirectory (void) {
	puts (getWorkingDirectory ());
}

int main (int argc, char *argv []) {

	puts ("Starting Unit Testing");

	testRemoveCarriageReturn ();
	testGetRedirectionType ();
	testGetWorkingDirectory ();
	testCmd ();
	testlineToCommand ();
	
	return 0;
}