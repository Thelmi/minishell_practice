#include "minishell.h"

void panic(char *s)
{
  printf("%s\n", s);
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

char *gets(char *buf, int max)
{
    int i = 0;
    int cc;
    char c;

    while (i + 1 < max) {
        cc = read(0, &c, 1);
        if (cc < 1) {
            break;
        }
        buf[i++] = c;
        if (c == '\n' || c == '\r') {
            break;
        }
    }
    buf[i] = '\0';
    return buf;
}

int getcmd(char *buf, int nbuf) 
{
  printf("$ ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

void runcmd(struct cmd *cmd)
{
    int p[2];
    struct execcmd *ecmd;
    struct pipecmd *pcmd;
    struct redircmd *rcmd; // we might add for herdoc, it depends

    if (cmd == NULL)
        exit(1);
    if (cmd->type == EXEC) 
    {
        ecmd = (struct execcmd*)cmd;
        if (ecmd->argv[0] == NULL)
            exit(1);
        exec(ecmd->argv[0], ecmd->argv);
        perror("exec failed");
        exit(1);
    } 
    else if (cmd->type == REDIR) 
    {
        rcmd = (struct redircmd*)cmd;
        int fd = open(rcmd->file, rcmd->mode);
        if (fd < 0) {
            perror("open failed");
            exit(1);
        }
        if (dup2(fd, rcmd->fd) < 0) {
            perror("dup2 failed");
            exit(1);
        }
        close(fd);
        runcmd(rcmd->cmd);
    } 
    else if (cmd->type == PIPE) 
    {
        pcmd = (struct pipecmd*)cmd;
        if (pipe(p) < 0)
            panic("pipe failed");

        if (fork1() == 0) 
        {
            close(p[0]);
            if (dup2(p[1], STDOUT_FILENO) < 0)
                panic("dup2 failed");
            close(p[1]);
            runcmd(pcmd->left);
        }
        if (fork1() == 0) 
        {
            close(p[1]);
            if (dup2(p[0], STDIN_FILENO) < 0)
                panic("dup2 failed");
            close(p[0]);
            runcmd(pcmd->right);
        }
        close(p[0]);
        close(p[1]);
        wait(NULL); // wait should be after fork
        wait(NULL);
    }
    exit(0);
}

