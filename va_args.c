#include <stdio.h>
#include <stdarg.h>

void yazdir(int param, ...) {
    va_list ap;
    char *str;
    
    va_start(ap, param);
    
    while((str = va_arg(ap,char *)) != NULL)
        printf("%s ", str);
    
    va_end(ap);
}

int main(void) {
    yazdir(1, "hello", "merhaba", NULL);

    return 0;
}
