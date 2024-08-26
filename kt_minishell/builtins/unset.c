/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:09:50 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/21 21:39:09 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset_env(t_env **env, char *variable)
{
    t_env *tmp;
    t_env *to_remove;

    if (!env || !variable)
        return;
    tmp = *env;
    if (tmp != NULL && ft_strcmp(tmp->variable, variable) == true)
    {
        *env = tmp->next;
		free_env_node(tmp);
        return;
    }
    while (tmp != NULL && tmp->next != NULL)
    {
        if (num_strncmp(tmp->next->variable, variable) == 0)
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

	i = 1;
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