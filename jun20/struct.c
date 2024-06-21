#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i;
    float f;
    double d;
} testStruct;

int main(int argc, char const *argv[]){
    struct {
        int a;
        float b;
        char c;
    } test1;

    test1.a = 10;
    test1.b = 3.14;
    test1.c = 'a';

    testStruct test2;
    test2.i = 100;
    test2.f = 1.2;
    test2.d = 1.234236243623562;

    return 0;
}