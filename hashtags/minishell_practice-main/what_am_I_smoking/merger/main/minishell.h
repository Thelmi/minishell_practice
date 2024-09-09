/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:58:51 by krazikho          #+#    #+#             */
/*   Updated: 2024/09/09 21:27:47 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h> //printf
#include <unistd.h> //write and fork
#include <stdlib.h> //exit, malloc, free
#include <readline/readline.h> //readline
#include <readline/history.h> //add_history
#include <stdbool.h> //bool
#include <string.h> // remove it when we will use libft
#include <ctype.h> // remove it when we will use libft
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <limits.h>

#define BUFFER_SIZE 1
// Our environment struct
typedef struct env
{
	char *variable;
	char *value;
	struct env *next;
} t_env;

// Functions used to store the enironment in the struct

t_env   *create_env_nodes(char *variable_content, char *value_content); // warning malloc used
t_env   *storing_env(char **ev); // warning createNodes used here which uses malloc

// Builtins
void    env(t_env *env);
void 	pwd();
void 	cd(char **args, t_env **envir);
void 	echo(char **command, t_env *env);

// export without args
void    sort_array(t_env **env_arr, int count);
void    printing_export(t_env **env_arr, int env_count);
void    export_no_arg(t_env *env);

// export with args
int is_valid_identifier(const char *str);
void update_env(t_env **env, char *variable, char *value);
void export_with_args(t_env **env, int ac, char **av);

// unset_practice
void    unset_env(t_env **env, char *variable);
void    unset(t_env **env, int ac, char **av);

// We might use them, globally
char    *substr_before_char(char *str , char c); // warning malloc is used
char    *substr_after_char(char *str , char c); // warning malloc is used
bool     ft_strcmp(char *s1, char *s2);
int     listsize(t_env *env);
int     num_strncmp(char *s1, char* s2);

// Freeing functions
void    free_env(t_env *env);
char	**free_arr(char **arr);
void    free_env_node(t_env *node);

// Temperory libft functions
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int     wordcount(char *str, char sep);
char	**getwords(char **arr, char *s, char c, int word);
char	**ft_split(char const *s, char c);
char 	*getcopyenv(char *str, t_env **envir);

//cd utils
void update_env_for_cd(t_env **env, char *variable, char *value);

//echo utils
bool is_only_n(const char *str);

//execution
t_env *execute_command(char *command, t_env **envir, int *last_exit_status, char** ev);
t_env *execute_builtin(t_env **envir, char **args, int *last_exit_status);
void modify_args(char **args, t_env *envir);

bool is_builtin(char *command);

//////parse & execute

# define EXEC 1
# define BUILTIN 2
# define REDIR 3
# define PIPE 4
# define HEREDOC 5

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
} t_execcmd;

typedef struct heredoc  // Execution command structure
{
  int type; // Type should be HEREDOC
  char *argv; // Argument vector (command, flags, args)
  char *eargv; // End pointers for each argument
  void *next;
} t_heredoc;

typedef struct redircmd  // Redirection command structure
{
  int type; // Type should be REDIR
  struct cmd *cmd; // Command to be executed before redirection
  char *file; // File to which output/input is redirected
  char *efile; // End pointer for the file name
  int mode; // File open mode (O_WRONLY | O_CREAT)
  int fd; // File descriptor for redirection (0 = stdin, 1 = stdout)
} t_redircmd;

typedef struct pipecmd  // Pipe command structure
{
  int type; // Type should be PIPE
  struct cmd *left; // Command on the left side of the pipe
  struct cmd *right; // Command on the right side of the pipe
  // int left_available;
  // int right_available;
} t_pipecmd;

// Main
void runcmd(struct cmd *cmd, char **ev, t_env **envir); // Run a command
int getcmd(char *buf, int nbuf); // Get a command from input
int fork1(); // Fork a process
void panic(char *s); // Print an error message and exit

// Parsing

struct cmd* parsecmd(char *s); // Parse a command string
struct cmd* parsepipe(char **ps, char *es, struct heredoc **heredoc); // Parse pipe commands
struct cmd* parseexec(char **ps, char *es, struct heredoc **heredoc); // Parse execution commands
 // Parse redirections
struct cmd* parseredirs(struct cmd *cmd, char **ps, char *es, struct heredoc **heredoc);  // Parse redirections
int gettoken(char **ps, char *es, char **q, char **eq); // Tokenize input
struct cmd* pipecmd(struct cmd *left, struct cmd *right); // Create a pipe command
struct cmd* nulterminate(struct cmd *cmd);
// Tree
struct cmd* execcmd(void); // Create an execution command
struct cmd* redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd); // Create a redirection command
void redircmd_h(char *argv, char *eargv, struct heredoc **heredoc);



// get next line 

// char	*ft_strjoin(char *s1, char *s2);
// void	*ft_memmove(void *dst, const void *src, size_t len);

char	*get_next_line(int fd);
char	*gnl_strchr(const char *s, int c);
void	*gnl_memmove(void *dst, const void *src, size_t len);
size_t	enhanced_strlen(char *str, int c);
int     gnl_free_str(char **str); 
char	*gnl_strjoin(char *s1, char *s2);
#endif
