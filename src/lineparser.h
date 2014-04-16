#ifndef LINEPARSER_H
#define LINEPARSER_H

#define REDIR_OUT_TOFILE 1
#define REDIR_OUT_TOFILE_ADD 2
#define REDIR_ERR_TOFILE 3
#define REDIR_ERR_TOFILE_ADD 4
#define REDIR_IN 5

void historyCommand ();
void addToHistory (char *str);
void cdCommand (char *command);
void exitCommand ();
void parseLine (char *buffer);

#endif /* LINEPARSER_H */