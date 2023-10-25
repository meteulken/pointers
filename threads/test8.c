#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define PHI_NUM  5

typedef struct s_philo
{
    int eat_count;
    int id;
    pthread_t thread;
    pthread_mutex_t forks;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    struct s_philo *philos;
    int stop;
}t_philo;

int sandvich = 1;

void print(char *str,int id)
{
    
}

void *routine(void *_philo)
{
    t_philo *philo = (t_philo*)_philo;
    int i = 0;
    if(philo->id % 2 == 0)
        usleep(20000);
    int a = 0;
    int eat = philo->eat_count;
    while(!philo->stop)
    {
        
        printf("%d philo is right fork\n",philo->id);
        if(eat == 10)
            philo->stop = 1;
        else
            philo->stop = 0;
        printf("%d philo is eating\n",philo->id);
        usleep(100000);
        printf("%d philo is sleeping\n",philo->id);
        usleep(100000);
        printf("%d philo is thinking\n",philo->id);
        usleep(100000);
        //eat = philo->id;
        
        eat++;
        pthread_mutex_lock(&philo->right_fork);
        sandvich++;
        pthread_mutex_unlock(&philo->right_fork);
        //pthread_mutex_lock(&philo[i].left_fork);
        //a += sandvich;
        //pthread_mutex_unlock(&philo[i].left_fork);
        printf("->%d\n",eat);

        i++;
    }
    return NULL;
}

int main()
{
    t_philo *phi;
    phi = malloc(sizeof(t_philo) * PHI_NUM);
    phi->philos = malloc(sizeof(t_philo) * PHI_NUM);
    int i = 0;
    while(i < 5)
    {
        pthread_mutex_init(&phi[i].forks,NULL);
        i++;
    }
    i = 0;
    while(i < 5)
    {
        phi->philos[i].stop = 0;
        phi->philos[i].left_fork = phi[i].forks;
        phi->philos[i].right_fork = phi[(i + 1) % PHI_NUM].forks;
        i++;
    }
    i = 0;
    while(i < 5)
    {
        phi->philos[i].id = i + 1;
        phi->philos[i].eat_count = 0;
        i++;
    }
    i = 0;
    while(i < 5)
    {
        pthread_create(&phi->philos[i].thread,NULL,routine,(void*)&phi->philos[i]);
        i++;
    }
    i = 0;
    while(i < 5)
    {
        pthread_join(phi->philos[i].thread,NULL);
        i++;
    }
}
