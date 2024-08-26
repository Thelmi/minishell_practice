#include "minishell_practice.h"

int main(int ac, char **av, char **ev)
{
	t_env *envir;
	envir = storing_env(ev);
	int fd = open("hola.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
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
	export_no_arg(envir);
}