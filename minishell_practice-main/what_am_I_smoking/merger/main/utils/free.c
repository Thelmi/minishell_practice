/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krazikho <krazikho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:17:37 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/23 12:58:55 by krazikho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// our freeing functions
#include "../minishell.h"

void free_env(t_env *env)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp != NULL)
	{
		tmp = env->next;
		free(env->variable);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void free_env_node(t_env *node)
{
    if (node)
    {
        free(node->variable);
        free(node->value);
        free(node);
    }
}