
#include "minishell_practice.h"

// int main(int ac, char **av, char **ev)
// {
//     int pipe_fd[2];
//     char *argv[] = {"grep", "PWD", NULL};

//     if (pipe(pipe_fd) == -1)
//     {
//         perror("pipe:");
//         return 1;
//     }
//     int pid = fork();
//     if (pid == -1)
//     {
//         perror("fork:");
//         return 1;
//     }

//     if (pid != 0) 
//     {
//         close(pipe_fd[0]);
//         int fd = open("hola.txt", O_RDONLY); 
//         if (fd == -1)
//         {
//             perror("open:");
//             return 2;
//         }

//         char buffer[1024];
//         int bytes_read;

//         while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
//         {
//             if (write(pipe_fd[1], buffer, bytes_read) == -1)
//             {
//                 perror("write to pipe:");
//                 return 3;
//             }
//         }

//         close(fd);
//         close(pipe_fd[1]);  
//         wait(NULL); 
//     }
//     else 
//     {
//         close(pipe_fd[1]); 

//         if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
//         {
//             perror("dup2 for input:");
//             return 4;
//         }
//         close(pipe_fd[0]);

//         execve("/usr/bin/grep", argv, ev);
//         perror("execve:"); 
//         return 5;
//     }

//     return 0;
// }
#include "minishell_practice.h"

int main(int ac, char **av, char **ev)
{
    int fd = open("hola.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open:");
        return 1;
    }

    int pid = fork();
    if (pid == -1)
    {
        perror("fork:");
        return 1;
    }

    if (pid != 0)
    {
        close(fd);
        wait(NULL); 
    }
    else
    {
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 for input:");
            return 2;
        }
        close(fd);
        char *argv[] = {"grep", "PWD", NULL};
        execve("/usr/bin/grep", argv, ev);
        perror("execve:");
        return 3;
    }

    return 0;
}
