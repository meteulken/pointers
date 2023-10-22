#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define PHILONUM 5

typedef struct s_philo
{
    int id;
    int eat_count;
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;
    pthread_t thread;
} t_philo;

t_philo philo[PHILONUM];

void print(char *str,int id)
{
    printf("%d philo is %s\n",id,str);
}

void *routine(void *_philo)
{
    t_philo *philo = (t_philo *)_philo;
    
    int eat;
    int id;
    id = philo->id;
    eat = philo->eat_count;

    if(id % 2 == 0)
        usleep(200000);

    while(1)
    { 
        if(eat == 0)
            break;
        pthread_mutex_lock(&philo->right_fork);
        print("eating",id);
        usleep(200000);
        pthread_mutex_lock(&philo->left_fork);
        print("thinking",id);
        usleep(200000);
        print("sleeping",id);
        usleep(200000);
        pthread_mutex_unlock(&philo->right_fork);
        pthread_mutex_unlock(&philo->left_fork);
        eat--;
    }

}

int main()
{
    int i = 0;
    
    while (i < PHILONUM)
    {
        pthread_mutex_init(&philo[i].left_fork, NULL);
        pthread_mutex_init(&philo[i].right_fork, NULL); 
        i++;
    }

    i = 0;

    while (i < PHILONUM)
    {
        philo[i].id = i + 1;
        philo[i].eat_count = PHILONUM;
        pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
        i++;
    }

    i = 0;
    while (i < PHILONUM)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }

    return 0;
}
