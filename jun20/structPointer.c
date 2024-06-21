#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int a;
    int b;
} Sample;

int main(int argc, char const *argv[]){
    Sample* test = (Sample*)malloc(sizeof(Sample));
    test->a = 100;
    test->b = 200;
    (*test).b = 400;

    printf("%d\n%d\n", test->a, test->b);

    return 0;
}