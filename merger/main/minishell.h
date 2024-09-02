/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:58:51 by krazikho          #+#    #+#             */
/*   Updated: 2024/08/29 14:53:40 by krazikho         ###   ########.fr       */
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
t_env *execute_command(char *command, t_env *envir, int *exit_status);
t_env *execute_builtin(t_env *envir, char **args, int *last_exit_status);
void modify_args(char **args, t_env *envir);

#endif
