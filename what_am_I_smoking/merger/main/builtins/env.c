/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:26:02 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/27 09:29:01 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_env *env)
{
	t_env	*tmp;

	if (!env)
	{
		printf ("Environment is empty or not initialized.\n");
		return ;
	}
	tmp = env;
	while (tmp != NULL)
	{
		printf ("%s", tmp->variable);
		printf ("=");
		printf ("%s\n", tmp->value);
		tmp = tmp->next;
	}
}
