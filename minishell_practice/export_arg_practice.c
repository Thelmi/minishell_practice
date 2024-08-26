#include "minishell_practice.h"

void update_env(t_env **env, char *variable, char *value)
{
	t_env *tmp;
	t_env *new_node;
	
	tmp = *env;
	
	while(tmp != NULL)
	{
		if (t_strcmp(tmp->variable, variable) == 0)
        {
            free(tmp->value);
            tmp->value = value;
            free(variable);
            return;
        }
		tmp = tmp->next;
	}
	new_node = create_env_Nodes(variable, value);
    if (new_node != NULL)
    {
        new_node->next = *env;
        *env = new_node;
    }
    else 
        printf("Erorr");
}

void export_with_args(t_env **env, int ac, char **av)
{
	int i = 1;
	char *variable;
    char *value;
    
    while(i < ac)
    {
        variable = substr_before_char(av[i], '=');
        value = substr_after_char(av[i], '=');
   
        if (variable == NULL || *variable == '\0')
        {
            printf("invalid");
            free(variable);
            free(value);
        }
        else 
           	update_env(env, variable, value);
        i++;
    }
}
