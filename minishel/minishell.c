#include "minishell.h"

int command(char *str)
{
    if(strcmp("pwd",str) == 0)
        return 1;
    else if (strcmp("cd",str) == 0)
        return 2;
    else if (strcmp("echo",str) == 0)
        return 3;
    else if (strcmp("exit",str) == 0)
        exit(0);
    return 0;
}

int go_to_func(char *str, int a)
{
    if(a == 1)
    {
        command_pwd();
    }
    else if (a == 2)
    {
        command_cd(str);
    }
    else if (a == 3)
    {
        command_echo(str);
    }
    return 0;
}

char **copy_matrix(char **env)
{
    int i = 0;
    char **new;
    while(env[i])
        i++;

    new = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while(env[i])
    {
        new[i] = env[i];
        i++;
    }
    new[i] = "\0";
    return new;
}

int main(int argc, char *argv[], char **env)
{
    if(argc > 1)
        printf("error arg\n");

    t_list *box = malloc(sizeof(t_list));

    int i = 0;
    char *progmpt = "myshell $ ";
    char *cmd;
    char *trim;
    char *cmd_trim;

    box->env = copy_matrix(env);
    trim_path(box);
    while(1)
    {
        cmd = readline(progmpt);
        if(cmd)
        {
            cmd_trim = trim_cmd(cmd);
            trim = str_trim(cmd);
        }
        i = command(cmd_trim);
        if(i != 0)
        {
            go_to_func(trim,i);
        }
        else
        {
            go_to_exevce(box,cmd_trim);
        }

    }
}