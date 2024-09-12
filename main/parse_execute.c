
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

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void runcmd(struct cmd *cmd, char **ev, t_env **envir, t_export **exp, int *last_exit_status) {
	int p[2];
	struct execcmd *ecmd;
	struct pipecmd *pcmd;
	struct redircmd *rcmd;
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);
	int pipe_fd;

	if (cmd == NULL)
		return ;
	if (cmd->type == EXEC) 
	{
		ecmd = (struct execcmd*)cmd;
		if (ecmd->argv[0] == NULL)
		{
			*last_exit_status = 1;
			return ; 
		}
	if (is_builtin(ecmd->argv[0])==true)
	{
		execute_builtin(envir , ecmd->argv, last_exit_status, exp);
		return ;
	}
	if (fork() == 0)
	{
		remove_quotes(cmd);
        // printf("%s|\n", ecmd->argv[0]);
		if (execve(ecmd->argv[0], ecmd->argv, ev) == -1)
			execve(find_path(ecmd->argv[0], ev), ecmd->argv, ev); //you should free properly, make sure strjoin is not leaking
		perror("execve failed");
		// printf("bro\n");
		exit(127);
	}
	else 
	{
	// exit between 0 - 255
		wait(NULL);
		return ;
	}
	} 
	else if (cmd->type == REDIR) 
	{
		rcmd = (struct redircmd*)cmd;
    // printf("%s\n", rcmd->file);
		int fd = open(rcmd->file, rcmd->mode, 0644);
		if (fd < 0) {
			perror("open failed");
			*last_exit_status = 1;
			return ;
		}
		if (dup2(fd, rcmd->fd) < 0) {
			perror("dup2 failed");
			close(fd);
			*last_exit_status = 1;
			return ;
		}
		close(fd);
		runcmd(rcmd->cmd, ev, envir, exp, last_exit_status);
		dup2(saved_stdout, 1);
		dup2(saved_stdin, 0);
		return;
	} 
	else if (cmd->type == PIPE) 
	{
		pcmd = (struct pipecmd*)cmd;
		if (pipe(p) < 0)
			panic("pipe failed");
		ecmd = (struct execcmd*)pcmd->left;
		if (ecmd->argv[0] == NULL)
		{
			printf("bash: syntax error near unexpected token `|\n");
			return ;
		}
		if (fork1() == 0) 
		{
			close(p[0]);
			if (dup2(p[1], STDOUT_FILENO) < 0)
				panic("dup2 failed");
			close(p[1]);
			runcmd(pcmd->left, ev, envir, exp, last_exit_status);
			exit(0);
		}
		wait(NULL); 
		if (fork1() == 0) 
		{
			close(p[1]);
			if (dup2(p[0], STDIN_FILENO) < 0)
				panic("dup2 failed");
			close(p[0]);
			if (pcmd->right->type != PIPE)
			{
				ecmd = (struct execcmd*)pcmd->right;
				if (ecmd->argv[0] == NULL)
				{
				char *read = NULL;
				// char *tmp;
				// char **tmp2;
				// int i = 0;

				pipe_fd = dup(0);
				dup2(saved_stdin, 0);
				while (!read)
				{
					write (1, "> ", 2);
					read = get_next_line(0);
					if (read && read[0] != '\n')
					{
					// tmp = read;
					// read = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
					// tmp2 = ft_split(read, ' '); //free properly
					// while (tmp2[i])
					// {
					// 	if (tmp2[i][0] == '\"' && tmp2[i][ft_strlen(tmp2[i]) - 1] == '\"')
					// 	{
					// 	tmp2[i] = ft_substr(tmp2[i], 1, ft_strlen(tmp2[i]) - 2);
					// 	}
					// 	if (tmp2[i][0] == '\'' && tmp2[i][ft_strlen(tmp2[i]) - 1] == '\'')
					// 	{
					// 	tmp2[i] = ft_substr(tmp2[i], 1, ft_strlen(tmp2[i]) - 2);
					// 	}
					// 	ecmd->argv[i] = tmp2[i];
					// 	i++;
					// }
					// free (tmp);
					// free(read);
					dup2(pipe_fd, 0);
					break ;
					}
					free (read);
					read = NULL;
				}
        runcmd(parsecmd(read, last_exit_status), ev, envir, exp, last_exit_status);
			  exit(0);
				}
			}
      // print_tree(pcmd->right);
			runcmd(pcmd->right, ev, envir, exp, last_exit_status);
			exit(0);
		}
		close(p[0]);
		close(p[1]);
		wait(NULL);
	} // exit between 0 - 255
	return ;
}

// Parsing 
int gettoken(char **ps, char *es, char **q, char **eq) // add herdoc
{
    char *s;
    int ret;
	char whitespace[6];
	char symbols[4];

	strcpy(whitespace, " \t\r\n\v");
	strcpy(symbols, "<|>"); 
    s = *ps;
    while (s < es && strchr(whitespace, *s))
        s++;
    if (q)
        *q = s;
    ret = *s;

    if (*s == 0) 
    {
        return ret;
    } 
     else if (*s == '|')
    {
        s++;
    }
    else if (*s == '<') 
    {
        s++;
        if (*s == '<') 
        {
            ret = 'h';
            s++;
        } 
	}
    else if (*s == '>') {
        s++;
        if (*s == '>') {
            ret = '+';
            s++;
        }
    } 
    else {
        ret = 'a';
        while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
            s++;
    }
    if (eq)
        *eq = s;
    while (s < es && strchr(whitespace, *s))
        s++;
    *ps = s;
    return ret;
}

int peek(char **ps, char *es, char *toks)
{
  char *s;

  char whitespace[6];
  strcpy(whitespace, " \t\r\n\v");
  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return (*s && strchr(toks, *s));
}

struct cmd* parseredirs(struct cmd *cmd, char **ps, char *es, struct heredoc **heredoc, int *last_exit_status) // add herdoc, and struct
{
  int tok;
  char *q, *eq;

  while(peek(ps, es, "<>"))
  {
    tok = gettoken(ps, es, 0, 0);
    if(gettoken(ps, es, &q, &eq) != 'a')
    {
		write(2, "bash: syntax error near unexpected token\n", 41);
		*last_exit_status = 2; // Indicating a syntax error (like bash)
		return NULL;
    }

    if(tok == '<') {
      cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
    } else if(tok == '>') {
      cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
    } else if(tok == '+') {  // >>
      cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND, 1);
    } else if(tok == 'h') {  // <<
        // printf("HELLOOO\n");
        redircmd_h(q, eq, heredoc);
      // cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND, 1);
    }
  }
  return cmd;
}

struct cmd* parseexec(char **ps, char *es, struct heredoc **heredoc, int *last_exit_status)
{
  char *q, *eq;
  int tok, argc;
  struct execcmd *cmd;
  struct cmd *ret;
  
  ret = execcmd();
  if (!ret) {
        perror("Error creating exec command");
        *last_exit_status = 1;
        return NULL;
    }
  cmd = (struct execcmd*)ret;

  argc = 0;
  ret = parseredirs(ret, ps, es, heredoc, last_exit_status); 
  while(!peek(ps, es, "|")){
    if((tok=gettoken(ps, es, &q, &eq)) == 0)
      break;
    if (tok != 'a')
    {
		*last_exit_status = 2;
        write(2, "bash: syntax error near unexpected token\n", 41);
        return NULL;
    }
    cmd->argv[argc] = q;
    cmd->eargv[argc] = eq;
    argc++;
    //if(argc >= MAXARGS)  // do we really need this
    //  panic("too many args");
    ret = parseredirs(ret, ps, es, heredoc, last_exit_status);
  }
  cmd->argv[argc] = 0;
  cmd->eargv[argc] = 0;
  return ret;
}

struct cmd* parsepipe(char **ps, char *es, struct heredoc **heredoc, int *last_exit_status)
{
  struct cmd *cmd;

  cmd = parseexec(ps, es, heredoc, last_exit_status);
  if(peek(ps, es, "|")){
    gettoken(ps, es, 0, 0);
    cmd = pipecmd(cmd, parsepipe(ps, es, heredoc, last_exit_status));
  }
  return cmd;
}

struct cmd* nulterminate(struct cmd *cmd)
{
  int i;
  // struct backcmd *bcmd;
  struct execcmd *ecmd;
  // struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if (cmd == 0)
    return 0;
  if (cmd->type == EXEC) {
    ecmd = (struct execcmd*)cmd;
    i = 0;
    while (ecmd->argv[i]) {
      *ecmd->eargv[i] = 0;
      i++;
    }
  }
  else if (cmd->type == REDIR) {
    rcmd = (struct redircmd*)cmd;
    nulterminate(rcmd->cmd);
    *rcmd->efile = 0;
    // printf("%s\n", rcmd->file);
    // int fd = open(rcmd->file, rcmd->mode, 0644);
    // write(fd,"9", 1);
    // close(fd);
  }
  else if (cmd->type == PIPE)
  {
    pcmd = (struct pipecmd*)cmd;
    nulterminate(pcmd->left);
    nulterminate(pcmd->right);
  }
  return cmd;
}

struct cmd* remove_quotes(struct cmd *cmd)
{
  int i;
  // struct backcmd *bcmd;
  struct execcmd *ecmd;
  // struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;
  char *tmp;

  if (cmd == 0)
    return 0;
  if (cmd->type == EXEC) {
    ecmd = (struct execcmd*)cmd;
    i = 0;
    while (ecmd->argv[i]) {
      if (ecmd->argv[i][0] == '\"' && ecmd->argv[i][ft_strlen(ecmd->argv[i]) - 1] == '\"')
      {
		tmp = ecmd->argv[i];
		ecmd->argv[i] = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
		// free(tmp);
      }
      if (ecmd->argv[i][0] == '\'' && ecmd->argv[i][ft_strlen(ecmd->argv[i]) - 1] == '\'')
      {
		tmp = ecmd->argv[i];
		ecmd->argv[i] = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
		// free(tmp);
      }
      i++;
    }
  }
  else if (cmd->type == REDIR) {
    rcmd = (struct redircmd*)cmd;
    remove_quotes(rcmd->cmd);
  }
  else if (cmd->type == PIPE) {
    pcmd = (struct pipecmd*)cmd;
    remove_quotes(pcmd->left);
    remove_quotes(pcmd->right);
  }
  return cmd;
}

struct cmd* parsecmd(char *s, int *last_exit_status)
{
    char *es;
    struct cmd *cmd;
    struct heredoc *heredoc;
    struct heredoc *tmp;
    char *read = NULL;
    char *tmp2 = NULL;
    int i;

    heredoc = NULL;
    es = s + strlen(s);
    cmd = parsepipe(&s, es, &heredoc, last_exit_status);
    peek(&s, es, "");

    if (s != es) {
        write(2, "minishell: syntax error: unexpected token ", 42);
		write(2, s, strlen(s));
    	*last_exit_status = 2;
		return NULL;
    }

    nulterminate(cmd);
    // print_tree(cmd);
    //remove_quotes(cmd);

    tmp = heredoc;

    while (tmp) {
        i = 0;
        while (tmp->argv[i] && tmp->argv[i] != ' ')
		{
            i++;
        }
        tmp2 = ft_substr(tmp->argv, 0, i);
		 if (tmp2 == NULL) 
		 {
            perror("Error allocating memory for heredoc delimiter");
            *last_exit_status = 1; // General error
            return NULL;
         }
        while ((read = readline("> ")) != NULL) {
            if (num_strncmp(read, tmp2) == 0) {
                free(read); // Free the input string
                break;
            }
            free(read);
        }
        if (read == NULL) 
		{
			free(tmp2);
			break;
		}
        free(tmp2);
        tmp = tmp->next;
    }

    return cmd;
}


// constructers
struct cmd* pipecmd(struct cmd *left, struct cmd *right)
{
  struct pipecmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  // if (left)
  //   cmd->left_available = 1;
  // else
  //   cmd->left_available = 0;
  // if (right)
  //   cmd->right_available = 1;
  // else
  //   cmd->right_available = 0;
  cmd->type = PIPE;
  cmd->left = left;
  cmd->right = right;
  return (struct cmd*)cmd;
}

struct cmd* redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
{
  struct redircmd *cmd;
  struct cmd *tmp;
  struct redircmd *tmp2;

  // printf("%s\n", file);
  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = REDIR;
  tmp = subcmd;
  if (subcmd && subcmd->type == REDIR)
  {
    tmp2 = (struct redircmd *)subcmd;
    while (tmp->type == REDIR)
    {
      tmp2 = (struct redircmd *)tmp;
      tmp = ((struct redircmd *)tmp)->cmd;
    }
    tmp2->cmd = (struct cmd*)cmd;
  }
  cmd->cmd = tmp;
  cmd->file = file;
  cmd->efile = efile;
  cmd->mode = mode;
  cmd->fd = fd;
  if (subcmd && subcmd->type == REDIR)
  {
    return (subcmd);
  }
  return (struct cmd*)cmd;
}

void redircmd_h(char *argv, char *eargv, struct heredoc **heredoc)
{
  struct heredoc *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = HEREDOC;
  cmd->argv = argv;
  cmd->eargv = eargv;
  cmd->next = NULL;

// printf("%s|\n", argv);
  if (*heredoc == NULL)
  {
    // create a node, new head
    *heredoc = cmd;
  }
  else
  {
    // add to the linked list
    struct heredoc *tmp = *heredoc;
    while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
  }
}

struct cmd* execcmd(void)
{
  struct execcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = EXEC;
  return (struct cmd*)cmd;
}
