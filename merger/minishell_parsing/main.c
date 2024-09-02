
#include "minishell.h"

struct cmd* print_tree(struct cmd *cmd)
{
  int i;
  struct backcmd *bcmd;
  struct execcmd *ecmd;
  struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

// # define EXEC 1
// # define BUILTIN 2
// # define REDIR 3
// # define PIPE 4

  if (cmd == 0)
    return 0;
  if (cmd->type == EXEC) {
    ecmd = (struct execcmd*)cmd;
	printf("%s\n", ecmd->argv[0]);
  if (ecmd->argv[1])
    printf("argv[1] : %s\n", ecmd->argv[1]);
    // i = 0;
    // while (ecmd->argv[i]) {
    //   *ecmd->eargv[i] = 0;
    //   i++;
    // }
  }
  else if (cmd->type == REDIR) {
    rcmd = (struct redircmd*)cmd;
	printf("redirect %d\n", rcmd->type);
    print_tree(rcmd->cmd);
    // *rcmd->efile = 0;
  }
  else if (cmd->type == PIPE) {
	printf("|\n");
    pcmd = (struct pipecmd*)cmd;
    print_tree(pcmd->left);
    print_tree(pcmd->right);
  }
  return cmd;
}

int main(int ac, char **av, char **ev)
{
char cwd[1024];
// printf("%s\n", getcwd(cwd, sizeof(cwd)));
	 char *buf;// why this static
	while((buf = readline("minishell> ")) != NULL) // readline
	{
	    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
	    {
	      buf[strlen(buf)] = '\0';
	      if(chdir(buf+3) < 0)
	        printf("cannot cd %s\n", buf+3);

			// printf("%s|\n", getcwd(cwd, sizeof(cwd)));
	      continue;
	    }
		// parsecmd(buf);
		print_tree(parsecmd(buf));
	    // if (fork1() == 0)
	    //   runcmd(parsecmd(buf), ev);
	    wait(NULL);
	    free(buf);
    }
  exit(0);
}

// test it and fix it
// add herdocs to the logic
// integrated into our program (kt_minishell)
// make it work for builtins as well
// test it again