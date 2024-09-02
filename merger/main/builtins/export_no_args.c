/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrhelmy <mrhelmy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:10:11 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/21 18:57:06 by mrhelmy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int listsize(t_env *env)
{
	int count;
	t_env *tmp;
	
	count = 0;
	tmp = env;
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void sort_array(t_env **env_arr, int count)
{
    int i;
    int j;
    t_env *tmp;

    i = 0;
    j = 0;
    while (i < count - 1)
    {
        j = i + 1;
        while (j < count)
        {
            if (num_strncmp(env_arr[i]->variable, env_arr[j]->variable) > 0)
            {
                tmp = env_arr[i];
                env_arr[i] = env_arr[j];
                env_arr[j] = tmp;
            }
            j++;
        } 
        i++;
    }
}

void printing_export(t_env **env_arr, int env_count)
{
	int i;

	i = 0;
	while (i < env_count)
	{
		printf("declare -x %s", env_arr[i]->variable);
        if (env_arr[i]->value)
            printf("=\"%s\"", env_arr[i]->value);
        else
            printf("=\"\"");
        printf("\n");
        i++;
	}
}
void export_no_arg(t_env *env)
{
	t_env *tmp;
	t_env **env_arr;
	int env_count;
	int i;
	
	env_count = listsize(env);
	if (env_count == 0)
        return;
	env_arr = malloc(sizeof(t_env *) * env_count);
    if (!env_arr)
        return;
    i = 0;
    tmp = env;
    while(i < env_count)
    {
        env_arr[i] = tmp;
        tmp = tmp->next;
        i++;
    }
    sort_array(env_arr, env_count);
    i = 0;
    printing_export(env_arr, env_count);
    free(env_arr);
}
