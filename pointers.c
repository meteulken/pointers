#include <stdio.h>

int main() 
{
    char *str[8];
    str[0] = "Merhaba";
    str[1] = "dünya";

    char *next_char_ptr = *(str + 1);

  printf("adres str'in bir sonraki değeri: %p\n", next_char_ptr);
  
   printf("adres str: %p\n", &(**str));

  // str dizisinin bir sonraki değerini buluyoruz

  char *next_char_ptr2 = &(*(*str + 1));

  // str dizisinin ikinci karakterinin adresini yazdırıyoruz

  printf("adres str'in bir sonraki değeri: %p\n", next_char_ptr2);
  printf("adres str: %p\n", &(**str)); 
  
   printf("adres str: %p\n", &(*str));
   printf("adres str: %d\n", (**str));
    
    printf("adres str: %p\n", &str);

    printf("adres str: %p\n", str);
 
   printf("adres str: %p\n", str + 1);
        printf("adres3 str: %p\n", &str + 1);
      //  printf("adres3 str: %d\n", str + 1);
     printf("*str str: %s\n", *str);
    // printf("*str + 1 str: %s\n", *str + 1);
    printf("str[0] adres: %p\n", &str[0]);
    printf("str[1] adres: %p\n", &str[1]);
    
    printf("str[0] adres: %p\n", (void *)&str[0]);
    printf("str[1] adres: %p\n", (void *)&str[1]);
    


  return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;


pthread_t thread1;
pthread_t thread2;
pthread_t thread3;

typedef struct job_list
{
    int id;
    char *name;
    int age;
    struct job_list *next;
} j_list;

typedef struct team_list
{
    int id;
    char *name;
    int age;
    struct job_list *next;
} t_list;

typedef struct human_list
{
    int data;
    j_list str[10];
    t_list company[10];
} s_list;


void add_company(s_list *head,int i,t_list *jobs)
{
    jobs->id = head->str[i].id;
    jobs->name = head->str[i].name;
    jobs->age = head->str[i].age;
    jobs->next = NULL;
    
}

void add(s_list *head, int i)
{
    if(i == 0)
    {
        head->data = i;
        head->str[i].id = 1 + i;
        head->str[i].name = "John";
        head->str[i].age = 30;
        head->str[i].next = NULL;
    }
    else if (i == 1)
    {
        head->data = i;
        head->str[i].id = 1 + i;
        head->str[i].name = "Alex";
        head->str[i].age = 25;
        head->str[i].next = NULL;
    }
    else if (i == 2)
    {
        head->data = i;
        head->str[i].id = 1 + i;
        head->str[i].name = "Mate";
        head->str[i].age = 22;
        head->str[i].next = NULL;
    }
}

void prints(t_list *head)
{
    printf("%d. User Adding...\n",head->id);
}

void print_list(t_list *head, void (*print_func)(t_list *))
{
    if(head != NULL)
    {
        printf("%d : %s : %d\n", head->id, head->name, head->age);
    }
    print_func(head);
  
}

void *start(void *arg) {
    pthread_mutex_lock(&mutex1);
    s_list *head = (s_list *)arg;

    t_list *job = (t_list*)malloc(sizeof(t_list));
    if (head == NULL) {
        perror("Memory allocation error");
        return NULL;
    }
    static int i = 0;

    add(head,i);

    add_company(head,i,job);
        //usleep(10000);
    print_list(job,prints);
    i++;
    pthread_mutex_unlock(&mutex1);

    return NULL;
}
int main()
{
    s_list *head = (s_list*)malloc(sizeof(s_list));
    if (head == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    pthread_mutex_init(&mutex1, NULL);

    pthread_create(&thread1, NULL, (void *)start, head);
    usleep(1000);
    pthread_create(&thread2, NULL, (void *)start, head);
    usleep(1000);
    pthread_create(&thread3, NULL, (void *)start, head);
    usleep(1000);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);


    free(head);
    return 0;
}
