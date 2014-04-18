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
#include <sys/types.h>
#include <sys/wait.h>


#include "lineparser.h"
#include "logging.h"
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
 */
 void addToHistory (char *str) {

 	history [number_input_history] = strdup (str);
 	number_input_history++;

 }

/** 
 * Execute the cd command by using the chdir function
 * if a HOME environnement variable exists ~ (tilde) to
 * home directory is managed
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

int notImplementedCommand (char *token) {

	if (strcmp (token, "alias") == 0) {
		return 1;
	} else if (strcmp (token, "bind") == 0) {
		return 1;
	} else if (strcmp (token, "builtin") == 0) {
		return 1;
	} else if (strcmp (token, "caller") == 0) { 
		return 1;
	} else if (strcmp (token, "command") == 0) { 
		return 1;
	} else if (strcmp (token, "declare") == 0) { 
		return 1;
	} else if (strcmp (token, "echo") == 0) { 
		return 1;
	} else if (strcmp (token, "enable") == 0) { 
		return 1;
	} else if (strcmp (token, "help") == 0) { 
		return 1;
	} else {
		return 0;
	}

}

void parseLine (char *buffer) {

	addToHistory (buffer);

	char *separator = " ";
	char *token, *saveptr;
	token = strtok_r (buffer, separator, &saveptr);

	/* TODO CLEAN */
	if (token == NULL) {
		/* Empty  to avoid segmentation fault when nothing is entered */
	} else if (strcmp (token, "cd") == 0) {

		token = strtok_r (NULL, separator, &saveptr);
		cdCommand (token);

	} else if (strcmp (token, "history") == 0) {

		historyCommand ();

	} else if (strcmp (token, "clear") == 0) {

		clearCommand ();

	} else if (strcmp (token, "exit") == 0) {

		exitCommand ();

	} else if (notImplementedCommand (token) == 1) {

		printf ("%s : not implemented\n", token);

	} else { /* MODIFYYYYYY */

		parseShellCommandLine (token, saveptr, separator);
		
	}
}

void parseShellCommandLine (char *token, char *saveptr, char *separator) {
			// line -> command -> redirection

		Line userLine;
		userLine.nbr_command = 0;

		/** 
		 * EXEMPLE
		 * ls -l | grep text > fichier.txt
		 * ls 
		 * 
		 */
		 while (token != NULL) {

			if (strcmp (token, "|") == 0 || userLine.nbr_command == 0) { /* if pipe */

		 		if (strcmp (token, "|") == 0) { /* If it's a pipe we take the next arg as the command name */
		 			token = strtok_r (NULL, separator, &saveptr);
		 		}

				/* Fill the struct with the first args -> the command name */
			 	Command cmd;
			 	cmd.nbr_args = 0;
			 	cmd.command_name = token;

			 	cmd.args [cmd.nbr_args++] = token;
				/* Store the command in the line */
		 		userLine.cmd_array [userLine.nbr_command++] = cmd;

			} else {

				/* If != NULL you must free redir */
		 		Redirection *redir = parseRedirection (token, separator, &saveptr);

				*(userLine.cmd_array [userLine.nbr_command-1].redir) = redir; // first element of the array of redir

				if (redir != NULL) {
					printf ("type : %s path : %s\n", (*userLine.cmd_array [userLine.nbr_command-1].redir)->redirection_type, (*userLine.cmd_array[userLine.nbr_command-1].redir)->path);
				} else { /* No redirection flag we store the command flag */
					userLine.cmd_array [userLine.nbr_command-1].args [userLine.cmd_array[userLine.nbr_command-1].nbr_args++] = token;
				}

			}

			//puts (token);
			token = strtok_r (NULL, separator, &saveptr);

		}

		if (executeUserLine (userLine) == -1) {
			fprintf (stderr, "%s\n", "error when executing the user line");
			exit (EXIT_FAILURE);
		}
}

int executeUserLine (Line line) {
	int   pp [2];
	pid_t pid;
	int   fd_in = 0;
	int cur_cmd_nbr = 0;

  	while (cur_cmd_nbr < line.nbr_command) {
      	if (pipe (pp) == -1) {
       		perror ("pipe failed");
       		return -1;
     	}

      	switch (pid = fork()) {
      		case -1 : perror ("fork failed");
      			return -1;
      			break;
			case 0 : /* child */
				dup2 (fd_in, 0);
				if (cur_cmd_nbr+1 != line.nbr_command) /* If the current command is not the last we duplicate the stdin in the pipe1 */
					dup2 (pp [1], 1);
			  	close (pp [0]);
			  	execvp (line.cmd_array [cur_cmd_nbr].command_name, line.cmd_array [cur_cmd_nbr].args);
			  	printf ("%s : command not found\n", line.cmd_array [cur_cmd_nbr].command_name);
				break;
			default : /* father */
				wait (NULL);
				close (pp [1]);
				fd_in = pp [0]; 
				cur_cmd_nbr++;
		}
    }
}