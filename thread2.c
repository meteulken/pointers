#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int balance = 0;

pthread_mutex_t mutex;



void *hesap(void *ammount)
{
    int *donusum = 0;
    pthread_mutex_lock(&mutex);
    int local_balance = balance;

    donusum = (int *)ammount; 

    local_balance += *donusum;
    usleep(25000);
    balance = local_balance;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    printf("Baslangic: %d\n",balance);
    printf("Son dddd: %lu\n",sizeof(mutex));
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread;
    pthread_t thread2;

    int account1 = 300;
    int account2 = 500;

    pthread_create(&thread2,NULL,hesap,(void *)&account1);
    pthread_create(&thread,NULL,hesap,(void *)&account2);

    pthread_join(thread,NULL);
    pthread_join(thread2,NULL);

    pthread_mutex_destroy(&mutex);
    printf("Son Durum: %d",balance);
    return (0);
}
