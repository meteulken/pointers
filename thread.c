#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int balance = 0;
pthread_mutex_t mutex;

void* deposit(void *amount) {

	pthread_mutex_lock(&mutex);

    	int account_balance = balance;
    
    	account_balance += *((int *) amount);
    
    	usleep(25000);
    
    	balance = account_balance;
  	pthread_mutex_unlock(&mutex);
    	return NULL;
}

int main() {

    	printf("Before: %d\n", balance);
  	pthread_mutex_init(&mutex, NULL);
    	pthread_t thread1;
    	pthread_t thread2;

    	int deposit1 = 300;
    	int deposit2 = 200;

    	pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
    	pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

    	pthread_join(thread1, NULL);
    	pthread_join(thread2, NULL);
 	pthread_mutex_destroy(&mutex);

    	printf("After: %d\n", balance);

    	return 0;
}
