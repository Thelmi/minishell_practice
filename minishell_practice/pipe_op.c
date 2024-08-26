#include "minishell_practice.h"

int main(int ac, char **av, char **ev)
{
	t_env *envir = storing_env(ev);
	int pipe_fd[2];
	
	char *argv[] = {"grep" , "PWD", NULL};
	if (pipe(pipe_fd) == -1)
	{
		printf("pipe what? ur trousser?\n");
		return 1;
	}
	int id = fork();
	if (id == -1)
	{
		printf("NO spaghetti\n");
		return 2;
	}
	if (id != 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
		    printf("dupi dupi output\n");
		    return 5;
		}
		close(pipe_fd[1]);
		env(envir);	
	}
	else
	{
		wait(NULL);
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		 {
		    printf("dupi dupi intput\n");
		    return 4;
		 }
		execve("/usr/bin/grep", argv , ev);
		close(pipe_fd[0]);
	}
}