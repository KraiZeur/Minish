#ifndef COMMAND_H
#define COMMAND_H

#define MAX_ARGS 50
#define MAX_CMD 50
#define MAX_REDIR 50

typedef struct {
	char *redirection_type;
	char *path;
} Redirection;

typedef struct {
	char *command_name;
	char *args [MAX_ARGS];
	int nbr_args;
	Redirection *redir [MAX_REDIR]; /* NULL When no redirection */
} Command;

typedef struct {
	Command cmd_array [MAX_CMD];
	int nbr_pipes;
} Line;

Command lineToCommand (char *line);
void clearCommand ();

#endif /* COMMAND_H */