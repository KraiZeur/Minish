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

#define BUFFER_SIZE 512

static char *history [BUFFER_SIZE];
static int number_input_history = 0;

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

/** 
 * 1 -> overwrite the file
 * 2 -> append to the file
 */
/* writeToFile (redir.path, "te222222 APPEND\n", 2); */
int writeToFile (char *path, char *message, int redirtype) {

	int desc, flags = 0;

	int current_out = dup (1);

	/* Check the redirType and associate the differents flags for the open function */
	switch (redirtype) {
		case 1 : flags = O_WRONLY | O_CREAT;
			break;
		case 2 : flags = O_APPEND | O_WRONLY | O_CREAT;
			break;
		default: flags = O_WRONLY | O_CREAT;
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

	dup2 (desc, STDOUT_FILENO);

	write (desc, message, strlen (message));

	/* Then we reset the stdout and close the file descriptor */
	if (dup2 (current_out, 1) < 0) {
        fprintf (stderr, "couldn't reset output\n");
        return 1;
    }

	if (close (desc) == -1) {
		perror ("close error");
		return -1;
	}

	return 0;

}


/** 
 * Return NULL if no redir 
 */
Redirection *parseRedirection (char *token, char *separator, char **saveptr) {

	Redirection *redir = NULL;

	switch (getRedirectionType (token)) {

		case REDIR_OUT_TOFILE : redir = malloc (sizeof (Redirection));

			redir->redirection_type = ">";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
				free (redir);
				return NULL;
			} else {
				redir->path = strdup (token);
				printf ("> Path : %s\n", redir->path);
			}

			break;
		case REDIR_OUT_TOFILE_ADD : redir = malloc (sizeof (Redirection));

			redir->redirection_type = ">>";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
				free (redir);
				return NULL;
			} else {
				redir->path = strdup (token);
				printf (">> Path : %s\n", redir->path);
			}

			break;
		case REDIR_ERR_TOFILE : redir = malloc (sizeof (Redirection));

			redir->redirection_type = "2>";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
				free (redir);
				return NULL;
			} else {
				redir->path = strdup (token);
				printf ("2> Path : %s\n", redir->path);
			}

			break;
		case REDIR_ERR_TOFILE_ADD : redir = malloc (sizeof (Redirection));

			redir->redirection_type = "2>>";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
				free (redir);
				return NULL;
			} else {
				redir->path = strdup (token);
				printf ("2>> Path : %s\n", redir->path);
			}

			break;
		case REDIR_IN : redir = malloc (sizeof (Redirection));

			redir->redirection_type = ">";
			token = strtok_r (NULL, separator, saveptr);

			if (token == NULL) {
				puts ("minish: syntax error near unexpected token `newline'");
				free (redir);
				return NULL;
			} else {
				redir->path = strdup (token);
				printf ("2>> Path : %s\n", redir->path);
			}

			break;
		default: /* Do nothing */
			break;

	}

	return redir;

}


/** 
 * Display the history to the stdout 
 */
void historyCommand () {

	int i = 0;

	for (i = 0; i < number_input_history; i++) {
		printf (" %d %s\n", i, history [i]);
	}

}

/** 
 * Add an element to the history 
 * Every elements of the history need to be free 
 */
void addToHistory (char *str) {

	/* TODO desalocate HISTORY */
	history [number_input_history] = malloc (sizeof (strlen (str)));
	strcpy (history [number_input_history], str);
	number_input_history++;

}

/** 
 * Execute the cd command by using the chdir function
 * if a HOME environnement variable exists ~ (tilde) for
 * home directory is allowed 
 */
void cdCommand (char *command) {

	if (command == NULL) { /* No paramter so home directory */

		char homeDir [125];

		/* Check that the variable HOME exists */
		if ( getenv ("HOME") != NULL) {
			strcpy (homeDir, getenv ("HOME"));

			if (chdir (homeDir) == -1) 
				fprintf (stderr, "minish: cd: %s: %s\n", homeDir, strerror (errno));
		}

	} else if (command [0] == '~') { /* Manage the home directory */

		char homeDir [125];
		char buffer [512];

		/* Check that the variable HOME exists */
		if ( getenv ("HOME") != NULL) {
			strcpy (homeDir, getenv ("HOME"));

			/* Remove the ~ by getting the next char */
			command = command+1;

			/* Add the home path to the user's input path */
			sprintf (buffer, "%s%s", homeDir, command);

			if (chdir (buffer) == -1) 
				fprintf (stderr, "minish: cd: %s: %s\n", buffer, strerror (errno));
		}

	} else { /* We move from the user input */

		if (chdir (command) == -1)
			fprintf (stderr, "minish: cd: %s: %s\n", command, strerror (errno));
	}
	
}

void exitCommand () {
	exit (EXIT_SUCCESS);
}

void parseLine (char *buffer) {

	/* SEGFAULT ON EMPTY STRING */

	addToHistory (buffer);

	char *separator = " ";
	char *token, *saveptr;
	token = strtok_r (buffer, separator, &saveptr);

	/* TODO CLEAN */
	if (token == NULL) {
		/* Empty  to avoid segmentation fault when nothing is entered */
	} else if (strncmp (token, "cd", 2) == 0) {

		token = strtok_r (NULL, separator, &saveptr);
		cdCommand (token);

	} else if (strcmp (token, "history") == 0) {

		historyCommand ();

	} else if (strcmp (token, "clear") == 0) {

		clearCommand ();

	} else if (strcmp (token, "exit") == 0) {

		exitCommand ();

	} else { /* MODIFYYYYYY */

		// line -> command -> redirection

		Line userLine;
		userLine.nbr_pipes = 0;


		int args_number = 0;
		/* Fill the struct with the first args -> the command name */
		Command cmd;
		cmd.command_name = token;
		cmd.args [args_number] = token;

		/** 
		 * EXEMPLE
		 * ls -l | grep text > fichier.txt
		 * ls 
		 * 
		 */

		while (token != NULL) {

			/* If != NULL you must free redir */
			Redirection *redir = parseRedirection (token, separator, &saveptr);

			*(cmd.redir) = redir; // first element of the array of redir

			if (redir != NULL) {
				printf ("type : %s path : %s\n", (*cmd.redir)->redirection_type, (*cmd.redir)->path);
			}

			token = strtok_r (NULL, separator, &saveptr);

		}

		// each time a pipe is found create a new cmd
		*(userLine.cmd_array) = cmd; // first array element takes the first cmd

	}

}