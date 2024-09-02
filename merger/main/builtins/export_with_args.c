/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:10:03 by mrhelmy           #+#    #+#             */
/*   Updated: 2024/08/27 09:32:06 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int num_strncmp(char *s1, char* s2)
{
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

int is_valid_identifier(const char *str)
{
    int i;

	i = 0;
    if (!str || str[i] == '\0')
        return 0;

    if (!(isalpha(str[i]) || str[i] == '_')) // libft function
        return 0;
    i++;
    while (str[i] != '\0')
    {
        if (!(isalnum(str[i]) || str[i] == '_')) // libft function
            return 0;
        i++;
    }

    return 1;
}

void update_env(t_env **env, char *variable, char *value)
{
    t_env *tmp;
    t_env *new_node;

    tmp = *env;
    while (tmp != NULL)
    {
        if (num_strncmp(tmp->variable, variable) == 0)
        {
            free(tmp->value);
            tmp->value = value;
            free(variable);
            return;
        }
        tmp = tmp->next;
    }
    new_node = create_env_nodes(variable, value);
    if (new_node != NULL)
    {
        new_node->next = *env;
        *env = new_node;
    }
    else
    {
        printf("Error: Memory allocation failed for new environment variable.\n");
        free(variable);
        free(value);
    }
}

void export_with_args(t_env **env, int ac, char **av)
{
    int i = 1;
    char *variable;
    char *value;

    while (i < ac)
    {
        if (strchr(av[i], '=') == NULL) // libft function
        {
            printf("export: `%s': not a valid identifier\n", av[i]);
            i++;
            continue;
        }

        variable = substr_before_char(av[i], '=');
        value = substr_after_char(av[i], '=');

        if (variable == NULL || !*variable || !is_valid_identifier(variable))
        {
            printf("export: `%s': not a valid identifier\n", av[i]);
            free(variable);
            free(value);
        }
        else
        {
            update_env(env, variable, value);
        }
        i++;
    }
}
