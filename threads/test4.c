#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *lock_thread(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        printf("Mutex kilitlendi\n");
    }
    pthread_mutex_unlock(&mutex);
    printf("Mutex serbest bırakıldı\n");
    return NULL;
}

int main() {
    pthread_t thread;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread, NULL, lock_thread, NULL);
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
