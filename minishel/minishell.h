#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef struct s_env
{
    char *front;
    char *back;
    struct s_env *next;

} t_env;

typedef struct s_list
{
    char **env;
    char *path;

} t_list;

void command_echo(char *command);
void command_cd(char* command);
void command_pwd();

char **copy_matrix(char **env);
char *str_trim(char *str);
int command(char *str);
char *trim_cmd(char *str);
void trim_path(t_list *list);
void go_to_exevce(t_list *list,char *cmd);
void try_path(char *path, char *commund);

char *trim_path_second(char *path);


#endif