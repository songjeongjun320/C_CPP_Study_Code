#include <iostream>

using namespace std;

int main(int argc, char** argv){
    int iList[100] = {0};

    for(int i = 0; i < 100; i++){
        cout << i << ": " << iList[i] << endl;
    }
    return 0;
}