#include <stdio.h>

int main()
{
    char ch;
    int i = 0;
    int f, a = 10, b = 20;
    while (i < 5){
        printf("choose one of them (+ - * /) : ");
        scanf(" %c", &ch);
        printf("ch = %c\n", ch);
        switch (ch) {
            case '+': {
                f = a + b; 
                printf("f = %d\n", f); 
                break;
            }
            case '-': {
                f = a - b; 
                printf("f = %d\n", f); 
                break;
            }
            case '*': {
                f = a * b; 
                printf("f = %d\n", f); 
                break;
            }
            case '/': {
                f = a / b; 
                printf("f = %d\n", f); 
                break;
            }
            default: {
                printf("invalid operator\n"); 
                break;
            }
        }
        i++;
    }

}