#include <iostream>

using namespace std;

void swap(int&, int&);
void swap(int*, int*);

int main(int argc, char** argv){
    int a = 100;
    int b = 200;

    cout << a << '\n' << b << endl;
    cout << &a << '\n' << &b << endl;

    swap(a,b);
    swap(&a,&b);

    cout << a << '\n' << b << endl;
}

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}