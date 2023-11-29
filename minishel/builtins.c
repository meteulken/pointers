#include "minishell.h"

void command_cd(char* command)
{
    if(chdir(command) == -1)
        printf("error\n");
}

void command_pwd()
{
    char *str;

    str = getcwd(NULL,0);

    printf("%s\n",str);
}

void command_echo(char *command)
{
    int i = 0;
    while(command[i])
    {
        write(1,&command[i],1);
        i++;
    }
    write(1,"\n",1);
}