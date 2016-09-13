#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int i = 0;
    char *token = "";

    printf("%d\n", argc);
    
    while(token != NULL) {
        printf("%s\n", token);
        i++;
    }

    return 0;
}
