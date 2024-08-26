#include "minishell_practice.h"

int main(int ac, char **av, char **ev)
{
	t_env *envir;
	int fd;

	envir = storing_env(ev);
	fd = open("hola.txt", O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error duplicating file descriptor");
		close(fd);
		return 2;
	}
	close(fd);
	env(envir);
}
