#include <iostream>

using namespace std;

int main(){
    int n;
    int sum = 0;
    cin >> n;
    for (int i = 0; i < n ; i++){
        sum += i;
        printf("%d %d\n", i, sum);
    }
    printf("Final summation up to %d is %d\n", n-1, sum); // Clarify the final summation up to n-1
    cout << "The end" << endl;
    return 0;
}