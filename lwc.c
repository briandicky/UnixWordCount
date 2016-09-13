#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    char *token = "";

    printf("%d\n", argc);
    
    while(token != NULL) {
        printf("%s\n", *token);
        *token = &argv[i];
        i++;
    }

    return 0;
}
