#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    int* iPtr;
    int myInt = 10;
    iPtr = &myInt;
    float* fPtr;

    cout << iPtr << endl;

    for(int i = 0; i < 100; i++){
        iPtr++; // when add 1, the address will be added by 4
        fPtr = (float*)iPtr;
        cout << i << " - " << iPtr << " :: " << *iPtr << endl;
        cout << "float: " << fPtr << " :: " << *fPtr << endl;
    }

    return 0;
}