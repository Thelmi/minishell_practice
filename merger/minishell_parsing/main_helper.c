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
        cc = write(0, &c, 1);
        // write(1, &c, 1);
        // printf("%c\n", c);
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



size_t	ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size > 0)
	{
		while (src[i] && --size)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

static char	**ft_malloc_error(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_nb_words(char const *s, char c)
{
	size_t	i;
	size_t	nb_words;

	if (!s[0])
		return (0);
	i = 0;
	nb_words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_words++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_words++;
	return (nb_words);
}

static void	ft_get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == c)
			return ;
		(*next_word_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*next_word;
	size_t	next_word_len;
	size_t	i;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_nb_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < ft_nb_words(s, c))
	{
		ft_get_next_word(&next_word, &next_word_len, c);
		tab[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_word, next_word_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (tab == 0)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tab[i] = s2[j];
		j++;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (0);
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
	return (0);
}


void runcmd(struct cmd *cmd, char **ev) {
    int p[2];
    struct execcmd *ecmd;
    struct pipecmd *pcmd;
    struct redircmd *rcmd;

    if (cmd == NULL)
        exit(1);
// printf("I am a child\n");
    if (cmd->type == EXEC) 
    {
        ecmd = (struct execcmd*)cmd;
        if (ecmd->argv[0] == NULL)
            exit(1);
        
        // Replace exec with execve
        // printf("%s\n", ecmd->argv[0]);
        // if (ecmd->argv[1])
        // printf("%s\n", ecmd->argv[1]);
        // if (ecmd->argv[2])
        // printf("%s\n", ecmd->argv[2]);
        // printf("%s\n", find_path(ecmd->argv[0], ev));
        execve(find_path(ecmd->argv[0], ev), ecmd->argv, ev); //you should free properly, make sure strjoin is not leaking
        
        // If execve fails, print an error message and exit
        perror("execve failed");
        exit(1);
    } 
    else if (cmd->type == REDIR) 
    {
        rcmd = (struct redircmd*)cmd;
        int fd = open(rcmd->file, rcmd->mode, 0644); // Ensure mode is specified
        if (fd < 0) {
            perror("open failed");
            exit(1);
        }
        if (dup2(fd, rcmd->fd) < 0) {
            perror("dup2 failed");
            exit(1);
        }
        close(fd);
        runcmd(rcmd->cmd, ev);
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
            runcmd(pcmd->left, ev);
        }
        wait(NULL); 
        if (fork1() == 0) 
        {
            close(p[1]);
            if (dup2(p[0], STDIN_FILENO) < 0)
                panic("dup2 failed");
            // printf("OK\n");
            close(p[0]);
            runcmd(pcmd->right, ev);
        }
        close(p[0]);
        close(p[1]);
        // wait(NULL); // wait should be after fork
        wait(NULL);
    }
    exit(0);
}
