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
