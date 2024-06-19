#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    ifstream infile;
    infile.open("lorem.txt");

    char line[255];

    do{
        infile.getline(line, 255);
        cout << "READ: " << line << endl;
    }while(!infile.eof());

    return 0;
}