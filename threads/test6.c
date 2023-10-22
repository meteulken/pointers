#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *thread_function(void *arg) {
    printf("Thread started\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;

    // Thread özelliklerini başlat
    pthread_attr_init(&attr);

    // Thread'ı detached olarak oluştur
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Thread'ı oluştur
    pthread_create(&thread, &attr, thread_function, NULL);

    // Thread özelliklerini temizle
    pthread_attr_destroy(&attr);
    //usleep(10);
    // Ana program devam ederken bekleme
    printf("Main thread continues\n");

    // Ana programın bitişini bekle
    pthread_join(thread, NULL);

    return 0;
}
