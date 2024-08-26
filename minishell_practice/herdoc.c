#include "minishell_practice.h"

static size_t	t_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int main(int ac, char **argv)
{
	char	*read;
	char	input_strings[1000];
	char	**input_splitted;
	int		i;
	int		j;
	int		z;

	(void)ac;

	input_splitted = NULL;
	i = 0;
	j = 0;
	while (argv[i])
	{
		z = 0;
		if (argv[i + 1] && argv[i][0] == '<' && argv[i][1] == '<' && argv[i][2] == '\0')
		{
			while (argv[i + 1][z])
			{
				input_strings[j] = argv[i + 1][z];
				j++;
				z++;
			}
		}
		input_strings[j++] = ' ';
		i++;
	}
	input_strings[j++] = '\0';
	input_splitted = ft_split(input_strings, ' ');
	i = 0;
	while (read)
	{
		write(1, "> ", 2);
		read = get_next_line(0);
		read[t_strlen(read) - 1] = '\0';
		if (t_strcmp(read, input_splitted[i]) == 0)
		{
			i++;
			if (input_splitted[i] == NULL)
			{
				if (read)
					free(read);
				break ;
			}
		}
		if (read)
			free(read);
	}
	//free splited
}