
#include "minishell_practice.h"

// char *substr_after_char(char *str , char c)
// {
// 	int i;
// 	int len;
	
// 	i = 0;
// 	len = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == c)
// 			break;
// 		i++;
// 	}
// 	if (str && !str[i + 1])
// 		return (NULL);
// 	len = i;
// 	while(str[len])
// 		len++;
// 	char *new_str = malloc(sizeof(char) * (len - i));
// 	if (!new_str)
// 		return (NULL);
// 	len = 0;
// 	i++;
// 	while(str[i])
// 		new_str[len++] = str[i++];
// 	new_str[len] = '\0';
// 	return (new_str);
// }

// char *substr_before_char(char *str , char c)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == c)
// 			break;
// 		i++;
// 	}
// 	char *new_str = malloc(sizeof(char) * i);
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == c)
// 			break;
// 		new_str[i] = str[i];
// 		i++;
// 	}
// 	new_str[i] = '\0';
// 	return (new_str);
// }

// t_env *create_env_Nodes(char *variable_content, char *value_content)
// {
// 	t_env *list;

// 	list = malloc(sizeof(list));
// 	if (!list)
// 		return (NULL);
// 	list->variable = variable_content;
// 	list->value = value_content;
// 	list->next = NULL;
// 	return (list);
// }

// void printlist(t_env *list)
// {
// 	t_env  *tmp;
// 	tmp = list;
// 	while(tmp != NULL)
// 	{
// 		printf("%s\n", tmp->variable);
// 		tmp = tmp->next;
// 	}
// 	tmp = list;
// 	printf("*************************************************************************************************\n");
// 	while(tmp != NULL)
// 	{
// 		printf("%s\n", tmp->value);
// 		tmp = tmp->next;
// 	}
// }

// int t_strcmp(char *s1, char* s2)
// {
// 	int i = 0;
// 	while(s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return(s1[i] - s2[i]);
// }

// t_env *storing_env(char **ev)
// {
// 	t_env *env;
// 	t_env *tmp;
// 	t_env *newnode;
// 	int i;

// 	env = create_env_Nodes(substr_before_char(ev[0], '='), substr_after_char(ev[0], '='));
// 	newnode = NULL;
// 	tmp = env;
// 	i = 1;
	
// 	while(ev[i])
// 	{
// 		newnode = create_env_Nodes(substr_before_char(ev[i], '='), substr_after_char(ev[i], '='));
// 		tmp ->next = newnode;
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	// printlist(env);
// 	return (env);
// }

// void env(t_env *env)
// {
// 	t_env  *tmp;
// 	tmp = env;
// 	while(tmp != NULL)
// 	{
// 		printf("%s", tmp->variable);
// 		printf("=");
// 		printf("%s\n", tmp->value);
// 		tmp = tmp->next;
// 	}
// }

// int main(int ac, char **av, char **ev)
// {
// 	t_env *envir;
// 	if (ac == 1)
// 		exit(1);
// 	envir = storing_env(ev);
// 	if (t_strcmp(av[1] , "env") == 0)
// 		env(envir);
// 	else
// 		printf("bruh learn how to type first");
// }

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

char *substr_after_char(char *str , char c)
{
	int i;
	int len;
	
	if (!str)
        return (NULL);
	i = 0;
	len = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (NULL);
	i++;
	while(str[i + len])
		len++;
	char *new_str = malloc(sizeof(char) * (len) + 1);
	if (!new_str)
		return (NULL);
	len = 0;
	while(str[i])
		new_str[len++] = str[i++];
	new_str[len] = '\0';
	return (new_str);
}

char *substr_before_char(char *str , char c)
{
	int i;

	if (!str)
        return (NULL);
	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			break;
		i++;
	}
	char *new_str = malloc(sizeof(char) * i);
	if (!new_str)
		return (NULL);
	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			break;
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

t_env *create_env_Nodes(char *variable_content, char *value_content)
{
	t_env *list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->variable = variable_content;
	list->value = value_content;
	list->next = NULL;
	return (list);
}

void printlist(t_env *list)
{
	t_env  *tmp;
	tmp = list;
	while(tmp != NULL)
	{
		printf("%s\n", tmp->variable);
		tmp = tmp->next;
	}
	tmp = list;
	printf("*************************************************************************************************\n");
	while(tmp != NULL)
	{
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

int t_strcmp(char *s1, char* s2)
{
	int i = 0;
	while(s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return(s1[i] - s2[i]);
}

t_env *storing_env(char **ev)
{
	t_env *env;
	t_env *tmp;
	t_env *newnode;
	int i;

	if (!ev || !ev[0])
        return NULL;
	env = create_env_Nodes(substr_before_char(ev[0], '='), substr_after_char(ev[0], '='));
	if (!env)
        return (NULL);
	newnode = NULL;
	tmp = env;
	i = 1;
	
	while(ev[i])
	{
		newnode = create_env_Nodes(substr_before_char(ev[i], '='), substr_after_char(ev[i], '='));
		if (!newnode)
			return (free_env(env), NULL);
		tmp ->next = newnode;
		tmp = tmp->next;
		i++;
	}
	// printlist(env);
	return (env);
}

void env(t_env *env)
{
	t_env  *tmp;
	if (!env)
    {
        printf("Environment is empty or not initialized.\n");
        return;
    }
	tmp = env;
	while(tmp != NULL)
	{
		printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **ev)
{
	t_env *envir;
	if (ac == 1)
		exit(1);
	envir = storing_env(ev);
	
	if (t_strcmp(av[1] , "env") == 0)
		env(envir);
	else if(t_strcmp(av[1] , "export") == 0 && ac == 2)
		export_no_arg(envir);
	else if (t_strcmp(av[1] , "export") == 0 && ac > 2)
	{
		export_with_args(&envir, ac, av);
		env(envir);
	}
	else
		printf("bruh learn how to type first\n");
}