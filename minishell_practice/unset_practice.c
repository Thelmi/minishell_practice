#include "minishell_practice.h"

void free_env_node(t_env *node)
{
    if (node)
    {
        free(node->variable);
        free(node->value);
        free(node);
    }
}

void unset_env(t_env **env, char *variable)
{
    t_env *tmp;
    t_env *to_remove;

    if (!env || !variable)
        return;
    tmp = *env;
    if (tmp != NULL && t_strcmp(tmp->variable, variable) == 0)
    {
        *env = tmp->next;
		free_env_node(tmp);
        return;
    }
    while (tmp != NULL && tmp->next != NULL)
    {
        if (t_strcmp(tmp->next->variable, variable) == 0)
        {
            to_remove = tmp->next;
            tmp->next = tmp->next->next;
			free_env_node(to_remove);
            return;
        }
        tmp = tmp->next;
    }
}

void unset(t_env **env, int ac, char **av)
{
    int i;
	char *variable;

	i = 2;
    while (i < ac)
    {
		variable= av[i];
        if (variable == NULL || *variable == '\0')
            printf("Invalid argument: %s\n", av[i]);
        else
            unset_env(env, variable);
        i++;
    }
}
