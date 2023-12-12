#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int ft_exec(char **argv, char **env, int i, int pipeIndex) {
    int pid;
    int status;
    int pipefd[2];
    int j = 0;
    int x = 0;

    while(argv[j])
    {
        if(strcmp(argv[j], "|") == 0) 
        {
            pipeIndex++;
            break;
        }
        j++;
    }
    /*
    while(argv[x])
    {
        if(strcmp(argv[x], ";") == 0) 
        {
            pipeIndex = 0;
            break;
        }
        x++;
    }*/
    if (pipeIndex > 0) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return 0;
        }
    }

    pid = fork();

    if (pid == 0) 
    {
        argv[i] = 0;
        if (pipeIndex > 0) 
        {
            dup2(pipefd[1], STDOUT_FILENO); // stdout'u pipe'a yönlendir
            close(pipefd[1]); // yazma ucunu kapat
        }
        execve(*argv, argv, env);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    waitpid(pid, &status, 0);

    if (pipeIndex > 0) {
        dup2(pipefd[0], STDIN_FILENO); // stdin'i pipe'dan oku
        close(pipefd[0]); // okuma ucunu kapat
    }

    return 1;
}

char *write_error(char *str) 
{
    int i = 0;
    while (str[i])
    {
        write(2, &str[i], 1);
        i++;
    }   
    return 0;
}

int cd_func(char **argv,int i)
{
    if(chdir(argv[i + 1]) == -1)
    {
       write_error("cd: ");
       write_error(argv[i + 1]);
       write_error(": No such file or directory\n");
    }
    exit(EXIT_FAILURE);

}

int main(int argc, char **argv, char **env) {
    int i = 0;
    int pipeIndex = 0;

    while (argv[i] && argv[++i]) {
        argv += i;
        i = 0;
        if(strncmp(argv[i], "cd", 2) == 0)
        {
            cd_func(argv,i);
        }
        while (argv[i] && strcmp(argv[i], "|") != 0 && strcmp(argv[i], ";") != 0) {
            i++;
        }
        if (i)
            ft_exec(argv, env, i, pipeIndex);
    }

    return 0;
}
