/*
 *  Author: Wen Chih Lo
 *  Date: 2016.9.14
 *  Purpose: Implement my own light-weight wc utility, called lwc.c, in C.
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define __DEBUG__ 666

#ifdef __DEBUG__
#define debug_print(x) printf("%s = %d\n", #x, (x)); 
#else
#define debug_print(x)
#endif


typedef unsigned long count_t;

static void usage() {
    fprintf(stderr, "usage: wc [OPTIONS] FILE...\n\n");
    fprintf(stderr, "  -c      Output character count\n");
    fprintf(stderr, "  -l      Output line count\n");
    fprintf(stderr, "  -w      Output word count\n");
    exit(1);
}


int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    count_t charcount = 0, wordcount = 0, linecount = 0;
    int charflag = 0, wordflag = 0, lineflag = 0;
    char input[1024], filename[256];
    int i, inword = 0;
    int c;

    /*Set the flags which is used to judge options that user typed.*/
    while( (c = getopt( argc, argv, "lwc" )) != EOF ) {
        switch(c) {
            case 'l':
                lineflag = 1;
                break;
                
            case 'w':
                wordflag = 1;
                break;

            case 'c':
                charflag = 1;
                break;

            default:
                usage();
        }
    }

    /*Flags' content*/
    debug_print(lineflag);
    debug_print(wordflag);
    debug_print(charflag);
    /*End*/
    
    /*Open file*/
    for( i = 1 ; i < argc ; i++ ) 
        if( !strncmp( argv[i], "-", 1 ) == 0 ) {
            fp = fopen(argv[i], "r");
            strcpy(filename, argv[i]);
        }

    if(fp) {
        /*Try to count the details in file(fp).*/
        while( fgets(input, sizeof(input), fp) != NULL ) {
            /*Increase line counter*/
            linecount++;

            for(i = 0 ; i < strlen(input) ; i++) {
                /*Increase word counter*/
                if( !inword && !( input[i] == 32 || input[i] == 10 || input[i] == 9 ) ) {
                    inword = 1;
                    wordcount++;
                }
                
                if( input[i] == 32 || input[i] == 10 || input[i] == 9 ) // ASCII: space = 32, newline = 10, tab = 9. 
                    inword = 0;
                            
                /*Increase char counter*/
                charcount++;
            }
        }
        printf("%lu %lu %lu %s\n", linecount, wordcount, charcount, filename);
        fclose(fp);
    }
    else {
        /*Error messages*/
        printf("ERROR: File not found.\n");
    }

    return 0;
}
