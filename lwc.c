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
    //FILE *fp;
    //int charcount = 0, wordcount = 0, linecount = 0;
    int charflag = 0, wordflag = 0, lineflag = 0;
    //char input[512];
    int i;


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
        else {
            lineflag = 1;
            wordflag = 1;
            charflag = 1;
        }
        
    }
    
    debug_print(lineflag);
    debug_print(wordflag);
    debug_print(charflag);

    return 0;
}
