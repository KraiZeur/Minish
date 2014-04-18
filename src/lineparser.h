#ifndef LINEPARSER_H
#define LINEPARSER_H

#include "command.h"

#define REDIR_OUT_TOFILE 1
#define REDIR_OUT_TOFILE_ADD 2
#define REDIR_ERR_TOFILE 3
#define REDIR_ERR_TOFILE_ADD 4
#define REDIR_IN 5

void historyCommand ();
void addToHistory (char *str);
void cdCommand (char *command);
void exitCommand ();
int notImplementedCommand (char *token);
void parseLine (char *buffer);
void parseShellCommandLine (char *token, char *saveptr, char *separator);
int executeUserLine (Line line);

#endif /* LINEPARSER_H */