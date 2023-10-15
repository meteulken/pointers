#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
    int data;
    struct s_list *next;

} t_list;

void list_print(t_list *ptr)
{
    if(!ptr)
        return ;

    while(ptr)
    {
        printf("->%d\n",ptr->data);
        ptr = ptr->next;
    }
}

void list_append(t_list **ptr, t_list **src)
{
    if(!ptr | !src)
        return;

    t_list *tmp;
    t_list *asd;

    tmp = *src;
    *src = tmp->next;
    
    while((*ptr)->next)
        (*ptr) = (*ptr)->next;

    (*ptr)->next = tmp;

    tmp->next = NULL;

    *src = tmp->next;
}

void list_add_back(t_list *ptr, t_list *content)
{
    if(!ptr || !content)
        return ;

    while(ptr->next)
    {
        ptr = ptr->next;
    }
    ptr->next = content;
}

void list_add_front(t_list **ptr, t_list *content)
{
    if(!ptr || !content)
        return ;

    t_list *tmp;

    tmp = *ptr;

    content->next = tmp;

    *ptr = content;
}

t_list	*lst_last(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_list *lst_new(int data)
{
    t_list *ptr;

    ptr = (t_list*)malloc(sizeof(t_list));

    if(!ptr)
        return NULL;

    ptr->data = data;
    ptr->next = NULL;

    return ptr;
}

int main()
{
    t_list *ptr = lst_new(10);
    t_list *ptr2 = lst_new(20);
    t_list *ptr3 = lst_new(5);
    t_list *ptr4 = lst_new(40);

    t_list *ptr7 = lst_new(55);
    t_list *ptr6 = lst_new(65);

    list_add_back(ptr,ptr2);
    list_add_front(&ptr,ptr3);
    list_add_back(ptr,ptr4);
    list_print(ptr);
    printf("\n");
    t_list *ptr5 = lst_last(ptr);
    list_print(ptr5);

    printf("-----------\n");
    list_print(ptr7);
    list_append(&ptr7,&ptr6);
    printf("-----------\n");
    list_print(ptr7);
}
