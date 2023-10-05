#include <stdio.h>
#include <stdlib.h>

typedef struct t_list {
  int data;
  struct t_list *next;
} t_list;

int main() {
  t_list *lst = malloc(sizeof(t_list));
  t_list **lst_ptr = &lst;

  lst->data = 10;

  lst->next = malloc(sizeof(t_list));

  lst->next->data = 20;

    printf("lst_ptr: %p\n", (void *)&lst_ptr); // lst_ptr işaretçisinin adresini yazdırın
    printf("alst: %p\n", (void *)lst); // lst işaretçisinin değerini yazdırın
  printf("*lst_ptr: %p\n", (void *)*lst_ptr); // lst_ptr'nin işaret ettiği değeri yazdırın
  printf("lst->data: %p\n", (void *)&lst->data); // lst->data'nın adresini yazdırın
  printf("lst->next->data: %p\n", (void *)&lst->next->data);
  printf("\n------\n");

   
    printf("*lst_ptr: %p\n", (void *)*lst_ptr);   // lst_ptr'nin işaret ettiği adresi yazdırın
    printf("**lst_ptr: %p\n", (void **)*lst_ptr); // lst_ptr'nin işaret ettiği adresin bir sonraki işaret ettiği adresi yazdırın
     printf("lst_ptr: %p\n", (void *)lst_ptr);     // lst_ptr işaretçisinin adresini yazdırın
 printf("\n------\n");
 
    printf("lst_ptr + 1: %p\n", (void *)(lst_ptr + 1));
    printf("lst + 1: %p\n", (void *)(lst + 1));
    
  printf("\n------\n");
  printf("blst: %p\n", &lst);
   printf("*lst_ptr: %p\n", &(*lst_ptr));
  printf("lst_ptr: %p\n", &lst_ptr);
 
  printf("lst->data: %p\n", &lst->data);
  printf("lst->next->data: %p\n", &lst->next->data);

    printf("\n------\n");
    printf("lst_ptr: %p\n", &lst_ptr + 1);
    printf("lst_ptr: %p\n", &lst + 1);
     printf("*lst_ptr: %p\n", (lst_ptr + 1));
    printf("*lst_ptr: %p\n", (*lst_ptr + 1));
    printf("*lst_ptr: %p\n", &(*lst->next));
   
    printf("*lst_ptr: %p\n", (lst->next));

  return 0;
}
