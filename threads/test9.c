#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#define PHI_NUM  5
#define PHI_TIME 2000

typedef struct s_philo
{
    int eat_count;
    int id;
    uint16_t last_time;
    uint64_t phi_time;
    pthread_t thread;
    pthread_t thread2;
    pthread_mutex_t forks;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    struct s_philo *philos;
    int stop;
}t_philo;

int sandvich = 1;
uint64_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

uint64_t	time_from_start(t_philo *philo)
{
	return (current_time() - philo->phi_time);
}

void print(char *str,t_philo *philo,uint64_t time)
{

	time = time_from_start(philo);
    printf("%d - %d philo is %s\n",time,philo->id,str);
}

void *die(void *_philo)
{
    t_philo *philo = (t_philo*)_philo;
    while(!philo->stop)
    {   
        pthread_mutex_lock(&philo->left_fork);
        if ((current_time() - philo->phi_time) > PHI_TIME)
        {
            //printf("2->%lu\n",(current_time() - philo->phi_time));
            philo->stop = 1;
            //print("dead",philo,NULL);
           
        }
        pthread_mutex_unlock(&philo->left_fork);
        philo->phi_time = current_time();
        usleep(10);
        break;
    }
}

void *routine(void *_philo)
{
    t_philo *philo = (t_philo*)_philo;
    int i = 1;
    if(philo->id % 2 == 0)
        usleep(20000);
    int a = 0;
    int eat = philo->eat_count;
    uint64_t	time;
    uint64_t    asd;
	time = current_time();
    while(!philo->stop)
    {
        
        pthread_mutex_lock(&philo->right_fork);
        philo->phi_time = current_time();
        asd = time - philo->phi_time;
        //printf("1->%lu\n",philo->phi_time);
        print("eating",philo,asd);
        usleep(100000);
        print("sleep",philo,asd);
        usleep(800000);
        print("think",philo,asd);
        usleep(300000);
        //eat = philo->id;
        //pthread_mutex_lock(&philo->left_fork);
        
        //die(philo);
        //pthread_mutex_unlock(&philo->left_fork);
        //printf("1->%lu\n",philo->phi_time);

        while(!philo->stop)
        {   
            pthread_mutex_lock(&philo->left_fork);
            if ((current_time() - philo->phi_time) > PHI_TIME)
            {
                //printf("2->%lu\n",(current_time() - philo->phi_time));
                philo->stop = 1;
                print("dead",philo,1);
           
            }
            pthread_mutex_unlock(&philo->left_fork);
            philo->phi_time = current_time();
           
            break;
        }

        philo->eat_count++;
        eat++;

        i++;
        //printf("2->%lu\n",philo->phi_time);
        pthread_mutex_unlock(&philo->right_fork);
        
    }
    return NULL;
}

int main()
{
    t_philo *phi;
    phi = malloc(sizeof(t_philo) * PHI_NUM);
    phi->philos = malloc(sizeof(t_philo) * PHI_NUM);
    int i = 0;
    printf("->%lu\n",current_time());
    pthread_t thread1;
    while(i < 5)
    {
        pthread_mutex_init(&phi[i].forks,NULL);
        i++;
    }
    i = 0;
    while(i < 5)
    {
        //phi->philos[i].phi_time = current_time();
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
        //pthread_create(&phi->philos[i].thread2,NULL,die,(void*)&phi->philos[i]);
        i++;
    }

    i = 0;
    //printf("->%lu",current_time());
    while(i < 5)
    {
        pthread_join(phi->philos[i].thread,NULL);
        i++;
    }
}
