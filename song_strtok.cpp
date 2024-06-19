#include <string.h>
#include <iostream>
using namespace std;

int charToInt(char);

int main(int argc, char** argv){
    char sourceString[] = "Lorem ipsum dolor sit amet consectetur adipiscing elit Integer tempor\
posuere nibh quis tempor Sed eu turpis nulla Suspendisse vestibulum blandit enim vitae\
feugiat Nulla malesuada orci ut nisi blandit congue Maecenas vulputate magna in tellus eros";
    char* token;

    printf("Splitting string...");

    token = strtok(sourceString, " ");

    while(token != NULL){
        printf("%s\n", token);
        for (size_t i = 0; i < strlen(token); i++){
            printf("Character value of %c = %d\n", token[i], charToInt(token[i]));
        }
        token = strtok(NULL, " ");
    }
    return 0;
}

int charToInt(char item){
    if ((item >= 'a') && (item <= 'z')){
        return (int)item;
    }
    else if ((item >= 'A') && (item <= 'Z')){
        return (int)item;
    }
    else{
        return -1;
    }
}