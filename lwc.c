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
    int null;
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
    struct stats wcfile[100];
    int k = 0;
    int invalid_detector = 0;


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
                for(j = 0 ; j < strlen(input) ; j++) {
                    /*Increase word counter*/
                    if( !inword && !( input[j] == 32 || input[j] == 10 || input[j] == 9 || input[j] == 13 ) ) {
                        inword = 1;
                        wordcount++;
                    }
                
                    if( input[j] == 32 || input[j] == 10 || input[j] == 9 || input[j] == 13 ) // ASCII: space = 32, newline = 10, tab = 9. carriage return = 13. 
                        inword = 0;
                            
                    /*Increase line counter*/
                    if( input[j] == 10 )
                        linecount++;

                    /*Increase char counter*/
                    charcount++;
                }
            }

            /*Record all the output messages*/
            wcfile[k].lines = linecount;
            wcfile[k].words = wordcount;
            wcfile[k].chars = charcount;
            wcfile[k].null = 0;
            strcpy(wcfile[k].filename, filename);
            k++;
            debug_print(k);

            /*Sum up all lines/words/chars*/
            total.lines += linecount;
            total.words += wordcount;
            total.chars += charcount;

            charcount = wordcount = linecount = 0;
            fclose(fp);
        }
        else {
            /*Null file pointer*/
            wcfile[k].null = 1;
            strcpy(wcfile[k].filename, filename);
            k++;
            debug_print(k);
        }
    } 

    /*Calculate the total digits, which we need, according to charcount*/
    if( k > 1) {
        ndigit = calc(total.chars);
        debug_print(ndigit);
    }
    else {
        ndigit = calc(wcfile[0].chars);
        debug_print(ndigit);
    }

    /*Print the output*/
    for( i = 0 ; i < k ; i++) {
        if( wcfile[i].null ) {
            /*Error messages*/
            fprintf(stderr, "wc: %s: No such file or directory\n", filename);
            invalid_detector = 1;
            continue;
        }
                                                                                                                                          
        /*According to command options, print the information*/
        if( sum == 7 || sum == 0 ) /*l+w+c = 4+2+1 = 7*/
            printf("%*lu %*lu %*lu %s\n", ndigit, wcfile[i].lines, ndigit, wcfile[i].words, ndigit, wcfile[i].chars, wcfile[i].filename);
        else if( sum == 6 ) /*l+w = 4+2 = 6 */
            printf("%*lu %*lu %s\n", ndigit, wcfile[i].lines, ndigit, wcfile[i].words, wcfile[i].filename);
        else if( sum == 5 ) /*l+c = 4+1 = 5*/
            printf("%*lu %*lu %s\n", ndigit, wcfile[i].lines, ndigit, wcfile[i].chars, wcfile[i].filename);
        else if( sum == 3 ) /*w+c = 2+1 = 3*/
            printf("%*lu %*lu %s\n", ndigit, wcfile[i].words, ndigit, wcfile[i].chars, wcfile[i].filename);
        else if( sum == 4 ) /*l = 4*/ {
            if( k > 1)
                printf("%*lu %s\n", ndigit, wcfile[i].lines, wcfile[i].filename);
            else
                printf("%lu %s\n", wcfile[i].lines, wcfile[i].filename);
        }
        else if( sum == 2 ) /*w = 2*/ {
            if( k > 1 )
                printf("%*lu %s\n", ndigit, wcfile[i].words, wcfile[i].filename);
            else
                printf("%lu %s\n", wcfile[i].words, wcfile[i].filename);
        }
        else if( sum == 1 ) /*c = 1*/ {
            if( k > 1 )
                printf("%*lu %s\n", ndigit, wcfile[i].chars, wcfile[i].filename);
            else
                printf("%lu %s\n", wcfile[i].chars, wcfile[i].filename);
        }
        else
            fprintf(stderr, "Wrong options.");
    }


    if( k > 1 ) {
        if( sum == 7 || sum == 0 ) /*l+w+c = 4+2+1 = 7*/                                                            
            printf("%*lu %*lu %*lu %s\n", ndigit, total.lines, ndigit, total.words, ndigit, total.chars, "total");
        else if( sum == 6 ) /*l+w = 4+2 = 6 */
            printf("%*lu %*lu %s\n", ndigit, total.lines, ndigit, total.words, "total");
        else if( sum == 5 ) /*l+c = 4+1 = 5*/
            printf("%*lu %*lu %s\n", ndigit, total.lines, ndigit, total.chars, "total");
        else if( sum == 3 ) /*w+c = 2+1 = 3*/
            printf("%*lu %*lu %s\n", ndigit, total.words, ndigit, total.chars, "total");
        else if( sum == 4 ) /*l = 4*/
            printf("%*lu %s\n", ndigit, total.lines, "total");
        else if( sum == 2 ) /*w = 2*/
            printf("%*lu %s\n", ndigit, total.words, "total");
        else if( sum == 1 ) /*c = 1*/
            printf("%*lu %s\n", ndigit, total.chars, "total");
        else
            fprintf(stderr, "Wrong options.");
    }
    
    return invalid_detector;  
}
