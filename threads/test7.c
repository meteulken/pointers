#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5
#define NUM_EATINGS 5

pthread_mutex_t print_t;

typedef struct s_philo {
    int id;
    int count;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int eat_count;
    int last_eat;
    
} t_philo;

t_philo aphilo[NUM_PHILOSOPHERS];
t_philo philosophers[NUM_PHILOSOPHERS];
pthread_t philosopher_threads[NUM_PHILOSOPHERS];
pthread_mutex_t forks[NUM_PHILOSOPHERS];

void print(char *str, int id) {
    pthread_mutex_lock(&print_t);
    printf("Philosopher %d is %s\n", id, str);
    pthread_mutex_unlock(&print_t);
    return;
}

void *eat(t_philo *philo)
{
    print("eating", philo->id);
    usleep(10000);

    return NULL;
}

void *think(t_philo *philo)
{
    print("thinking", philo->id);
    usleep(10000);

    return NULL;
}
void *philosopher(t_philo *philo)
{
    int j = 0;
    int i = 0; 

    // İlk olarak, sol çatalı kilitle
    pthread_mutex_lock(philo->left_fork);

    // Verilere güvenli bir şekilde eriş
    aphilo[j].count = i;
     

    
    aphilo[j + 1].count = i + 1;

    // Sağ çatalı kilitle
   
  pthread_mutex_unlock(philo->left_fork);
    // Verilere güvenli bir şekilde eriş

    // İkinci çatalı kilidi aç
    

    // İlk çatalı kilidi aç
 

    // Data race oluşturan bölge sonu
    usleep(1000000);
    i++;

    return NULL;
}


void *routine(void *_tphilo) {
    t_philo *philo = (void*)_tphilo;
    int id = philo->id;
    int eat_count = philo->eat_count;

    if (id % 2 == 0)
        usleep(10000);

    while (1) {
        if (eat_count == 0)
            break;

        // Data race oluşturan bölge başlangıcı
        //pthread_mutex_lock(philo->left_fork);
        //pthread_mutex_lock(philo->right_fork);

        eat(philo);
        think(philo);
        usleep(10000);
            pthread_mutex_lock(philo->right_fork);
        philosopher(philo);
        pthread_mutex_unlock(philo->right_fork);
        eat_count--;
        //pthread_mutex_unlock(philo->left_fork);
        //
        // Data race oluşturan bölge sonu
    }
    return NULL;
}

int main() {

    t_philo *philo = (void*)malloc(sizeof(t_philo));

    int i = 0;
    while (i < NUM_PHILOSOPHERS) {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&print_t, NULL);
    i = 0;

    while (i < NUM_PHILOSOPHERS) {
        philosophers[i].id = i;
        philosophers[i].eat_count = NUM_EATINGS;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % NUM_PHILOSOPHERS];
        pthread_create(&philosopher_threads[i], NULL, routine, &philosophers[i]);
        i++;
    }

    i = 0;

    while (i < NUM_PHILOSOPHERS) {
        pthread_join(philosopher_threads[i], NULL);
        i++;
    }
    return 0;
}
