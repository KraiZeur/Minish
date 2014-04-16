#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "utils.h"
#include "lineparser.h"
#include "command.h"

void testRemoveCarriageReturn (void) {

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	char *buffer = malloc (sizeof (5));
	strcpy (buffer, "test\n");

	removeCarriageReturn (buffer);

	assert((strcmp(buffer, "test")) == 0);

	free (buffer);

	gettimeofday(&stop, NULL);
	printf ("removeCarriageReturn success : %lu ms\n", stop.tv_usec - start.tv_usec);

}

void testGetRedirectionType (void) {

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	assert (getRedirectionType (">") == REDIR_OUT_TOFILE);
	assert (getRedirectionType ("1>") == REDIR_OUT_TOFILE);
	assert (getRedirectionType (">>") == REDIR_OUT_TOFILE_ADD);
	assert (getRedirectionType ("2>") == REDIR_ERR_TOFILE);
	assert (getRedirectionType ("2>>") == REDIR_ERR_TOFILE_ADD);

	gettimeofday(&stop, NULL);
	printf ("getRedirectionType success : %lu ms\n", stop.tv_usec - start.tv_usec);

}

void testWriteToFile () {

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	int result = writeToFile ("test.txt", "My file append unit test\n", 2);

	assert (result == 0);

	gettimeofday (&stop, NULL);
	printf ("testWriteToFile success : %lu ms\n", stop.tv_usec - start.tv_usec);
}

void testCmd () {

	struct timeval stop, start;
	gettimeofday (&start, NULL);

	Command cmd;
	cmd.command_name = "ls";
	cmd.args [0] = strdup ("ls");
	cmd.args [1] = strdup ("-l");
	cmd.nbr_args = 1;

	assert (strcmp (*(cmd.args), "ls") == 0);

	gettimeofday (&stop, NULL);
	printf ("testCmd success : %lu ms\n", stop.tv_usec - start.tv_usec);
}

void testlineToCommand (void) {

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	Command cmd;

	cmd = lineToCommand ("ls -l");

	printf ("%d\n", cmd.nbr_args);

	assert (strcmp (*(cmd.args), "ls") == 0);

	gettimeofday(&stop, NULL);
	printf ("testCmd success : %lu ms\n", stop.tv_usec - start.tv_usec);

}

void testGetWorkingDirectory (void) {

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	char *cwd = getWorkingDirectory ();

	gettimeofday(&stop, NULL);
	printf ("testGetWorkingDirectory : %s : %lu ms\n", cwd,stop.tv_usec - start.tv_usec);
}

int main (int argc, char *argv []) {

	puts ("Starting Unit Testing");
	struct timeval stop, start;
	gettimeofday(&start, NULL);

	testRemoveCarriageReturn ();
	testWriteToFile ();
	testGetRedirectionType ();
	testGetWorkingDirectory ();
	testCmd ();
	//testlineToCommand ();

	gettimeofday(&stop, NULL);
	printf ("Unitary test success : %lu ms\n", stop.tv_usec - start.tv_usec);
	
	return 0;
}