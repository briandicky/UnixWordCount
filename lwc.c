/*
 *  Author: Wen Chih Lo
 *  Date: 2016.9.14
 *  Purpose: Implement my own light-weight wc utility, called lwc.c, in C.
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __DEBUG__
#define debug_print(x) printf("%s = %d\n", #x, (x)); 
#else
#define debug_print(x)
#endif

typedef unsigned long count_t;

struct stats {
    count_t lines;
    count_t words;
    count_t chars;
    char filename[256];
};

static void usage() {
    fprintf(stderr, "Try 'wc --help' for more information.\n");
    exit(1);
}

int calc(int charcount) {
    int n = 0;

    while( charcount != 0 ) {
        charcount /= 10;
        n++;
    }

    return n;
}


int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    count_t charcount = 0, wordcount = 0, linecount = 0;
    int charflag = 0, wordflag = 0, lineflag = 0;
    char input[4096], filename[256];
    int i, j;
    /*c: for calculating char, sum: for command options*/
    int c, sum, ndigit, inword;
    struct stats total; /*For multiple files*/

    /*Parse cmd line options and set the flags which is used to judge options that user typed.*/
    while( (c = getopt( argc, argv, "lwc?" )) != EOF ) {
        switch(c) {
            case 'l': /*Dex(4) = Bin(100)*/
                lineflag = 4;
                break;
                
            case 'w': /*Dex(2) = Bin(010)*/
                wordflag = 2;
                break;

            case 'c': /*Dex(1) = Bin(001)*/
                charflag = 1;
                break;

            case '?':
            default:
                usage();
        }
    }

    /*Flags' content*/
    debug_print(lineflag);
    debug_print(wordflag);
    debug_print(charflag);
    /*End*/


    /*Sum all flags*/
    sum = 0;
    sum = lineflag+wordflag+charflag;
    debug_print(sum);

    /*Initialize the total structure*/
    memset(&total, 0, sizeof(struct stats));

    /*Open file*/
    for( i = 1 ; i < argc ; i++ ) {
        if( !strncmp( argv[i], "-", 1 ) == 0 ) {
            fp = fopen(argv[i], "r");
            strcpy(filename, argv[i]);
        }
        else 
            continue;

        inword = 0;

        if(fp) {
            /*Try to count the details in file(fp).*/
            while( fgets(input, sizeof(input), fp) != NULL ) {
                /*Increase line counter*/
                linecount++;

                for(j = 0 ; j < strlen(input) ; j++) {
                    /*Increase word counter*/
                    if( !inword && !( input[j] == 32 || input[j] == 10 || input[j] == 9 || input[j] == 13 ) ) {
                        inword = 1;
                        wordcount++;
                    }
                
                    if( input[j] == 32 || input[j] == 10 || input[j] == 9 || input[j] == 13 ) // ASCII: space = 32, newline = 10, tab = 9. carriage return = 13. 
                        inword = 0;
                            
                    /*Increase char counter*/
                    charcount++;
                }
            }

            total.lines += linecount;
            total.words += wordcount;
            total.chars += charcount;

            /*Calculate the total digits, which we need, according to charcount*/
            ndigit = calc(total.chars);
            debug_print(ndigit);

            /*According to command options, print the information*/
            if( sum == 7 || sum == 0 ) /*l+w+c = 4+2+1 = 7*/
                printf("%*lu %*lu %*lu %s\n", ndigit, linecount, ndigit, wordcount, ndigit, charcount, filename);
            else if( sum == 6 ) /*l+w = 4+2 = 6 */
                printf("%*lu %*lu %s\n", ndigit, linecount, ndigit, wordcount, filename);
            else if( sum == 5 ) /*l+c = 4+1 = 5*/
                printf("%*lu %*lu %s\n", ndigit, linecount, ndigit, charcount, filename);
            else if( sum == 3 ) /*w+c = 2+1 = 3*/
                printf("%*lu %*lu %s\n", ndigit, wordcount, ndigit, charcount, filename);
            else if( sum == 4 ) /*l = 4*/
                printf("%lu %s\n", linecount, filename);
            else if( sum == 2 ) /*w = 2*/
                printf("%lu %s\n", wordcount, filename);
            else if( sum == 1 ) /*c = 1*/
                printf("%lu %s\n", charcount, filename);
            else
                fprintf(stderr, "Wrong options.");

            charcount = wordcount = linecount = 0;
            fclose(fp);
        }
        else {
            /*Error messages*/
            printf("%s: No such file or directory\n", filename);
        }
    } 

    return 0;
}
