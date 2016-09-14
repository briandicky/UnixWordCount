/*
 *  Author: Wen Chih Lo
 *  Date: 2016.9.14
 *  Purpose: Implement my own light-weight wc utility, called lwc.c, in C.
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 666

#ifdef DEBUG
#define debug_print(x) printf("%s = %d\n", #x, (x)) 
#else
#define debug_print do{}while(0)
#endif

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    int charcount = 0, wordcount = 0, linecount = 0;
    int charflag = 0, wordflag = 0, lineflag = 0;
    char input[512];
    int i, inword = 0;


    /*Set the flags which is used to judge options that user typed.*/
    for( i = 0 ; i < argc ; i++ ) {
        if( strcmp(argv[i], "-l") == 0 ) {
            lineflag = 1;
        }
        else if( strcmp(argv[i], "-w") == 0 ) {
            wordflag = 1;
        }
        else if( strcmp(argv[i], "-c") == 0 ) {
            charflag = 1;
        }
        else if( strcmp(argv[i], "-lw") == 0 || strcmp(argv[i], "-wl") == 0 ) {
            lineflag = 1;
            wordflag = 1;
        }
        else if( strcmp(argv[i], "-lc") == 0 || strcmp(argv[i], "-cl") == 0 ) {
            lineflag = 1;
            charflag = 1;
        }
        else if( strcmp(argv[i], "-wc") == 0 || strcmp(argv[i], "-cw") == 0 ) {
            wordflag = 1;
            charflag = 1;
        }
        else if( strcmp(argv[i], "-lwc") == 0 || strcmp(argv[i], "-lcw") == 0 || strcmp(argv[i], "-wlc") == 0 || strcmp(argv[i], "-wcl") == 0 || strcmp(argv[i], "-clw") == 0 || strcmp(argv[i], "-cwl") == 0 ) {
            lineflag = 1; 
            wordflag = 1; 
            charflag = 1;
        }
    }

    /*Flags' content*/
    debug_print(lineflag);
    debug_print(wordflag);
    debug_print(charflag);
    /*End*/
    
    /*Open file*/
    fp = fopen(argv[2], "r");

    if(fp) {
        /*Try to count the details in file(fp).*/
        while( fgets(input, sizeof(input), fp) != NULL ) {
            /*Increase line counter*/
            linecount++;

            for(i = 0 ; i < strlen(input) ; i++) {
                /*Increase word counter*/
                if( !inword ) {
                    inword = 1;
                    wordcount++;
                }
                
                if( input[i] == 32 || input[i] == 10 ) // ASCII: space = 32, newline = 10
                    inword = 0;
                
                /*Increase char counter*/
                charcount++;
            }
        }
        printf(" %d %d %d %s\n", linecount, wordcount, charcount, argv[2]);
    }
    else {
        /*Error messages*/
        printf("ERROR: File not found.\n");
    }

    fclose(fp);

    return 0;
}
