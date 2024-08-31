#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

# define EXEC 1
# define BUILTIN 2
# define REDIR 3
# define PIPE 4

#define MAXARGS 10

typedef struct cmd  // Base command structure
{
  int type; // Type of command (EXEC, BUILTIN, REDIR, PIPE)
} cmd;

typedef struct execcmd  // Execution command structure
{
  int type; // Type should be EXEC
  char *argv[MAXARGS]; // Argument vector (command, flags, args)
  char *eargv[MAXARGS]; // End pointers for each argument
} execcmd;

typedef struct redircmd  // Redirection command structure
{
  int type; // Type should be REDIR
  struct cmd *cmd; // Command to be executed before redirection
  char *file; // File to which output/input is redirected
  char *efile; // End pointer for the file name
  int mode; // File open mode (O_WRONLY | O_CREAT)
  int fd; // File descriptor for redirection (0 = stdin, 1 = stdout)
} redircmd;

typedef struct pipecmd  // Pipe command structure
{
  int type; // Type should be PIPE
  struct cmd *left; // Command on the left side of the pipe
  struct cmd *right; // Command on the right side of the pipe
} pipecmd;

// Main
void runcmd(struct cmd *cmd); // Run a command
int getcmd(char *buf, int nbuf); // Get a command from input
int fork1(); // Fork a process
void panic(char *s); // Print an error message and exit

// Parsing
struct cmd* parsecmd(char *s); // Parse a command string
struct cmd* parsepipe(char **ps, char *es); // Parse pipe commands
struct cmd* parseexec(char **ps, char *es); // Parse execution commands
struct cmd* parseredirs(struct cmd *cmd, char **ps, char *es); // Parse redirections
int gettoken(char **ps, char *es, char **q, char **eq); // Tokenize input
struct cmd* pipecmd(struct cmd *left, struct cmd *right); // Create a pipe command

// Tree
struct cmd* execcmd(void); // Create an execution command
struct cmd* redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd); // Create a redirection command

#endif // MINISHELL_H

