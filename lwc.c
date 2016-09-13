/*
 *  Author: Wen Chih Lo
 *  Date: 2016.9.14
 *  Purpose: Implement my own light-weight wc utility, called lwc.c, in C.
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

int main(int argc, char *argv[])
{
    int i = 0;
    char *token = "";

    printf("%d\n", argc);

    while(token != NULL) {
        printf("%s\n", token);
        token = argv[i];
        i++;
    }

    FILE *fp;
    int charcount = 0, wordcount = 0, linecount = 0;
    bool charflag = false, wordflag = false, lineflag = false;
    char input[512];


    return 0;
}
