#include "minishell.h"

void panic(char *s)
{
  printf(2, "%s\n", s);
  exit(1);
}
int fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}

int getcmd(char *buf, int nbuf)
{
  printf(2, "$ ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

struct cmd* parsecmd(char *s)
{
  char *es;
  struct cmd *cmd;

  es = s + strlen(s);
  cmd = parseline(&s, es);
  peek(&s, es, "");
  if(s != es){
    printf(2, "leftovers: %s\n", s);
    panic("syntax");
  }
  nulterminate(cmd);
  return cmd;
}

void runcmd(struct cmd *cmd)
{
  int p[2];
  
	struct execcmd *ecmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;

  if (cmd == NULL)
    exit(1);
  else if (cmd->type == EXEC) 
  {
    ecmd = (struct execcmd*)cmd;
    if (ecmd->argv[0] == NULL)
      exit(1);
    exec(ecmd->argv[0], ecmd->argv);
    printf(2, "exec %s failed\n", ecmd->argv[0]);
  } 
else if (cmd->type == REDIR)
{
    rcmd = (struct redircmd*)cmd;
    // close(rcmd->fd);
    if (open(rcmd->file, rcmd->mode) < 0) {
      printf(2, "open %s failed\n", rcmd->file);
      exit(1);
    }
    runcmd(rcmd->cmd);
}
  else if (cmd->type == PIPE) 
  {
    pcmd = (struct pipecmd*)cmd;
    if (pipe(p) < 0)
      panic("pipe");
    if (fork1() == 0) 
    {
    //   close(1);
      close(p[0]);
    //   dup(p[1]);
      dup2(p[1], STDOUT_FILENO);
    //   close(p[0]);
      close(p[1]);
      runcmd(pcmd->left);
    }
    if (fork1() == 0) 
    {
      close(p[1]);
    //   close(0);
      dup2(p[0], STDIN_FILENO);
      close(p[0]);
      runcmd(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait(NULL);
    wait(NULL);
  } 
  exit(0);
}

