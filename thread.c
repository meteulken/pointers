#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int balance = 0;
sem_t *semaphore;

void *hesap(void *ammount)
{
    int a = 0;
    int *donusum = (int *)ammount;
    sem_wait(semaphore);

    int local_balance = balance;

    local_balance += *donusum;
    usleep(25000);
    balance = local_balance;
    while(1)
        a = 5;
    sem_post(semaphore);

    return NULL;
}

int main()
{
    printf("Baslangic: %d\n", balance);

    // Create a named semaphore
    semaphore = sem_open("/my_semaphore", O_CREAT, 0666, 1);

    pthread_t thread;
    pthread_t thread2;

    int account1 = 300;
    int account2 = 500;

    pthread_create(&thread2, NULL, hesap, (void *)&account1);
    pthread_create(&thread, NULL, hesap, (void *)&account2);
    pthread_join(thread2, NULL);
    pthread_join(thread, NULL);

    while(1);

    // Close and unlink the named semaphore
    sem_close(semaphore);
    sem_unlink("/my_semaphore");

    printf("Son Durum: %d\n", balance);

    return 0;
}
