/* ************************************************************ */
/**
* name   : lineparser.c
* author : RITALY Thomas
* date   : 2014-03-26
*
* description : This file is Only for .. .
*/
/* ************************************************************ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "lineparser.h"
#include "logging.h"
#include "command.h"
#include "utils.h"

int getRedirectionType (char *redirection) {

	if (strcmp (redirection, ">") == 0 || strcmp (redirection, "1>") == 0) {
		return REDIR_OUT_TOFILE;
	} else if (strcmp (redirection, ">>") == 0) {
		return REDIR_OUT_TOFILE_ADD;
	} else if (strcmp (redirection, "2>") == 0) {
		return REDIR_ERR_TOFILE;
	} else if (strcmp (redirection, "2>>") == 0) {
		return REDIR_ERR_TOFILE_ADD;
	} else if (strcmp (redirection, "<") == 0) {
		return REDIR_IN;
	} else {
		return 0;
	}

	return 0;

}

/* writeToFile (redir.path, "te222222 APPEND\n", 2); */
int writeToFile (char *path, char *message, int redirtype) {

	int desc, flags;

	switch (redirtype) {
		case 1 : flags = O_WRONLY | O_CREAT;
			break;
		case 2 : flags = O_APPEND | O_WRONLY | O_CREAT;
			break;
		default: 
			break;
	}

	if ((desc = open (path, flags)) == -1) {
		if (errno == EACCES){
			fprintf (stderr, "minish: %s : Permission denied\n", path);
		} else {
			perror ("minish: error opening the file");
		}
		return -1;
	}


	dup2 (desc, 1);

	write (desc, message, strlen (message));

	if (close (desc) == -1) {
		perror ("close error");
		return -1;
	}

	return 0;

}

Redirection *parseRedirection (char *token, char *separator, char **saveptr) {

	Redirection *redir = NULL;

	switch (getRedirectionType (token)) {

		case REDIR_OUT_TOFILE : redir = malloc (sizeof (Redirection));

			redir->redirection_type = ">";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
			} else {
				redir->path = token;
				printf ("> Path : %s\n", redir->path);
			}

			break;
		case REDIR_OUT_TOFILE_ADD : redir = malloc (sizeof (Redirection));

			redir->redirection_type = ">>";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
			} else {
				redir->path = token;
				printf (">> Path : %s\n", redir->path);
			}

			break;
		case REDIR_ERR_TOFILE : redir = malloc (sizeof (Redirection));

			redir->redirection_type = "2>";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
			} else {
				redir->path = token;
				printf ("2> Path : %s\n", redir->path);
			}

			break;
		case REDIR_ERR_TOFILE_ADD : redir = malloc (sizeof (Redirection));

			redir->redirection_type = "2>>";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
			} else {
				redir->path = token;
				printf ("2>> Path : %s\n", redir->path);
			}

			break;
		case REDIR_IN : redir = malloc (sizeof (Redirection));

			redir->redirection_type = ">";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				perror ("error");
				puts ("minish: syntax error near unexpected token `newline'");
			} else {
				redir->path = token;
				printf ("2>> Path : %s\n", redir->path);
			}

			break;
		default: /* Do nothing */
			break;

	}

	return redir;

}

void cdCommand (char *command) {

	/* Manage the ~ when user wants to go to the home directory */
	if (command[0] == '~') {

		char homeDir[125];
		char buffer[512];

		/* Check that the variable HOME exists */
		if ( getenv ("HOME") != NULL) {
			strcpy (homeDir, getenv ("HOME"));

			/* Remove the ~ */
			command = command+1;

			/* Add the home path to the user's input path */
			sprintf (buffer, "%s%s", homeDir, command);

			if (chdir (buffer) == -1) 
				fprintf(stderr, "minish: cd: %s: %s\n", buffer, strerror(errno));
		}

	} else { /* We move from the user input */

		if (chdir (command) == -1)
			fprintf(stderr, "minish: cd: %s: %s\n", command, strerror(errno));
	}
	
}

void parserLine (char *buffer) {

	char *separator = " ";
	char *token, *saveptr;
	token = strtok_r (buffer, separator, &saveptr);

	if (strcmp (token, "cd") == 0) {

		token = strtok_r (NULL, separator, &saveptr);
		cdCommand (token);

	} else { /* MODIFYYYYYY */

		int args_number = 0;
		Command cmd;
		cmd.command_name = token;
		cmd.args[args_number] = token;

		while (token != NULL) {

			/* If != NULL you must free redir */
			Redirection *redir = parseRedirection (token, separator, &saveptr);

			*(cmd.redir) = redir;

			if (redir != NULL) {
				printf ("%s\n", *(cmd.redir)->path);
			}

			token = strtok_r (NULL, separator, &saveptr);

		}

	}

}