#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Bu örnekte kullanılacak olan adlandırılmış semafor adı
#define SEMAPHORE_NAME "/my_semaphore33"

void useSemaphoreFunctions() {
    sem_t *mySemaphore;
	int sem_value;
    // Semafor oluşturma
	
    mySemaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, 1);
	if (sem_getvalue(mySemaphore, &sem_value) == -1) {
    	perror("sem_getvalue");
    	exit(EXIT_FAILURE);
		}
	else
		printf("Semafor Değeri: %d\n", sem_value);
    if (mySemaphore == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("Semafor oluşturuldu.\n");
	int a = 0;
	int b = 0;
    // Semaforı kullanma
    if (a = sem_wait(mySemaphore) == -1) {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
	if (sem_getvalue(mySemaphore, &sem_value) == -1) {
    	perror("sem_getvalue");
    	exit(EXIT_FAILURE);
		}
	else
		printf("Semafor Değeri: %d\n", sem_value);

	printf("%did\n",a);
    printf("Semafor kullanılıyor...\n");

    sleep(22); // Semaforun kullanım süresini simüle etmek için bekleyin

    // Semaforı geri bırakma
    if (b=sem_post(mySemaphore) == -1) {
        perror("sem_post");
        exit(EXIT_FAILURE);
    }
	if (sem_getvalue(mySemaphore, &sem_value) == -1) {
    	perror("sem_getvalue");
    	exit(EXIT_FAILURE);
		}
	else
		printf("Semafor Değeri: %d\n", sem_value);
	printf("%did\n",b);
    printf("Semafor geri bırakıldı.\n");

    // Semaforı kapatma
    if (sem_close(mySemaphore) == -1) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }

    printf("Semafor kapatıldı.\n");

    // Semaforu silme (opsiyonel)
    if (sem_unlink(SEMAPHORE_NAME) == -1) {
        perror("sem_unlink");
        exit(EXIT_FAILURE);
    }

    printf("Semafor silindi.\n");
}

int main() {
    useSemaphoreFunctions();
    return 0;
}
