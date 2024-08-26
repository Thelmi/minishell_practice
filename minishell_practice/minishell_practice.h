#ifndef MINISHELL
#define MINISHELL


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>

#define BUFFER_SIZE 1

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
void    update_env(t_env **env, char *variable, char *value);
void    export_with_args(t_env **envir, int ac, char **av);

// unset
void    unset(t_env **env, int ac, char **av);
void    unset_env(t_env **env, char *variable);
void    free_env_node(t_env *node);

// We might use them, globally
int     t_strcmp(char *s1, char* s2);
void    printlist(t_env *list);
char    *substr_before_char(char *str , char c);
char    *substr_after_char(char *str , char c);
int     listsize(t_env *env);
void    sort_array(t_env **env_arr, int count);

static void	  get_and_update(char *buffer, char **str);
char	      *get_next_line(int fd);
void	     *ft_memmove(void *dst, const void *src, size_t len);
char	     *ft_strchr(const char *s, int c);
size_t	     ft_strlen(char *str, int c);
char	    *ft_strjoin(char *s1, char *s2);
char        *get_next_line(int fd);
int		    free_str(char **str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int     wordcount(char *str, char sep);
char	**free_arr(char **arr);
char	**getwords(char **arr, char *s, char c, int word);
char	**ft_split(char const *s, char c);
#endif