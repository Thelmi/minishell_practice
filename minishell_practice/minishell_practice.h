#ifndef MINISHELL
#define MINISHELL

#include <stdlib.h>
#include <stdio.h>

typedef struct env
{
	char *variable;
	char *value;
	struct env *next;
}               t_env;

// Functions used in env

t_env   *storing_env(char **ev);
t_env   *create_env_Nodes(char *variable_content, char *value_content);
void     env(t_env *env);

// export no args
void    printing_export(t_env **env_arr, int env_count);
void    export_no_arg(t_env *env);

// export with args
void update_env(t_env **env, char *variable, char *value);
void export_with_args(t_env **envir, int ac, char **av);

// We might use them, globally
int     t_strcmp(char *s1, char* s2);
void    printlist(t_env *list);
char    *substr_before_char(char *str , char c);
char    *substr_after_char(char *str , char c);
int     listsize(t_env *env);
void    sort_array(t_env **env_arr, int count);
#endif
