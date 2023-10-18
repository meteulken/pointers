
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;

pthread_t thread1;
pthread_t thread2;
pthread_t thread3;

typedef struct s_args
{
    int arg_id;
    char *arg_name;
    int arg_acc;
} t_args;

typedef struct s_bank
{
    int _id;
    char *_name;
    int _account;
} t_bank;

int balance = 500;

typedef struct s_human
{
    int _i;
    int id;
    char *name;
    int age;
    int account;
    t_args arg[10];
    t_bank bank[10];
} t_human;


void add_money(t_human *_human,int i)
{
    static int j = 0;
    while(j <= i / 2)
    {
        _human->bank[j]._account += (balance);
        j++;
        balance += _human->bank[j]._account;
    }
}

t_human *add_user(t_human *_human,char* name,int money,int i)
{
    static int j = 0;
    while(j <= i / 2)
    {
        _human->bank[j]._id = i ;
        _human->bank[j]._name = name;
        _human->bank[j]._account = money; 
        j++;
    }
    return _human;
}

void view_info(t_human *_human)
{
    int i = _human->_i;
    int j = 0;
     while(j < i / 2)
    {
        printf("id: %d | Name: %s | Money: %d\n",_human->bank[j]._id,_human->bank[j]._name,_human->bank[j]._account);
        j++;
    }
}


int main(int argc,char *argv[])
{
    t_human *_human;
    _human = malloc(sizeof(t_human));
    if(!_human)
        return -1;
    t_args *_args;
    _args = malloc(sizeof(t_args));
    
    int i = 0;

    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);
    pthread_mutex_init(&mutex3,NULL);


    pthread_create(&thread1,NULL,(void*)view_info,_human);
    pthread_create(&thread1,NULL,(void*)view_info,_human);
    pthread_create(&thread1,NULL,(void*)view_info,_human);


    while(++i < argc - 1)
    {
        _human = add_user(_human,argv[i],atoi(argv[i + 1]),i);
        i++;
    }
    _human->_i = i;
    view_info(_human);
    printf("__________\n");
    add_money(_human,i);
    view_info(_human);

    printf("->%d",balance);
}
