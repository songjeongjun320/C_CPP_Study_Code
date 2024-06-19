#include <stdio.h>
int main(int argc, char** argv){
    FILE* file;
    file = fopen("./lorem.txt", "r");
    char line[255];

    while(fgets(line, 255, file) != NULL){
        printf("Read: %s\n", line);
    }
}