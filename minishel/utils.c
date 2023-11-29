#include "minishell.h"

char *trim_cmd(char *str)
{
    int i = 0;
    char *new;
    while(str[i] && str[i] != ' ')
            i++;

    new = malloc(sizeof(char) * (i + 1));
    i = 0;
    while(str[i] && str[i] != ' ')
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return new;
}

char *str_trim(char *str)
{
    int i = 0;
    int j = 0;
    int a = 0;
    char *new;
    while(str[i] && str[i] != ' ')
            i++;
    i++;
    a = i;
    while(str[i])
    {
        i++;
        j++;
    }
    i = 0;
    new = malloc(sizeof(char) * (j + 1));
    while(str[a])
    {
        new[i] = str[a];
        a++;
        i++;
    }
    new[i] = '\0';
    return new;
}

void trim_path(t_list *list)
{
    int i = 0;
    char **env_list;

    env_list = list->env;

    while(env_list[i])
    {
        if(env_list[i][0] == 'P' && env_list[i][1] == 'A')
        {
            if(env_list[i][2] == 'T' && env_list[i][3] == 'H')
                break;
        }
        i++;
    }
    list->path = env_list[i];
}

char *trim_path_second(char *path)
{
    int i = 0;
    int j = 0;
    int a = 0;
    static int x = 0;
    char *new_path;

    while(path[x] && path[x] != ':')
    {
        x++;
        a++;
    }
    printf("1->%d\n",a);
    new_path = malloc(sizeof(char) * (a + 1));

    while(path[i] && path[i] != ':')
    {
        new_path[j] = path[i];
        i++;
        j++;
    }
    //new_path[j] = '/';
    new_path[++j] = '\0';
    return (new_path);
}

void try_path(char *path, char *commund)
{
    int i = 0;
    int x = 0;
    int j = 0;
    char *cmd;

    path += 5;

    while(1)
    {
    cmd = trim_path_second(path);
    while(cmd[i])
        i++;
    cmd[i] = '/';
    while(i++ && commund[x])
    {
        cmd[i] = commund[x++];
    }
    printf("->%s\n",cmd);
    if(!access(cmd,F_OK))
    {
        printf("basarili\n");
        break;
    }
        
    }
    

}
void go_to_exevce(t_list *list,char *cmd)
{
    int i = 0;
    int pid;

    try_path(list->path,cmd);

    

}