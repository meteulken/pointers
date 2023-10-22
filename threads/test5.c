#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *lock_thread(void *arg)
{
    int i = 0;

    while(i < 5)
    {
        pthread_mutex_lock(&mutex);
        printf("mutex lock\n");
        i++;
    }
    pthread_mutex_unlock(&mutex);
    printf("mutex unlock\n");
}

int main()
{
    pthread_t thread;
    pthread_mutexattr_t atr;

    pthread_mutexattr_init(&atr);
    

    pthread_mutexattr_settype(&atr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex,&atr);

    pthread_create(&thread,NULL,lock_thread,NULL);

    pthread_join(thread,NULL);
}