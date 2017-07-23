#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"txtedtf.h"


sFlagsTyp opt = {0,0,0,0,0,0} ;

int main(int argc, char * argv[])
{
   // char * argv[] = {"replace" , "-b" , "-i" , "-f" , "--" , "E:\\test.txt"} ;
   // int argc = 6 ;
    FILE * fp ;
    char fileMatrix [MAX_MAT_ROW][MAX_MAT_COL]  ;


    char from [STR_SIZE] = {0} ;
    char to   [STR_SIZE] = {0} ;
    int i, j, fileStart , status = -1;

    for (i = 1 ; strcmp (argv[i], "--") ; i++)
    {
        if      ( !strcmp (argv[i], "-b") ) opt.backup  = 1 ;
        else if ( !strcmp (argv[i], "-f") ) opt.first   = 1 , opt.all = 1 ;
        else if ( !strcmp (argv[i], "-l") ) opt.last    = 1 , opt.all = 1 ;
        else if ( !strcmp (argv[i], "-i") ) opt.insense = 1 ;
        else if (opt.from == 0 )
        {
            strcpy (from, argv[i]) ;
            opt.from = 1 ;
        }
        else strcpy (to, argv[i]) ;
    }/*End of for*/

    i++ ; // to point to the string of the first txt file name
    fileStart = i ; // files strings start index .
    for (j = fileStart ; j < argc ; j++)
    {
        status = -1 ;
        fp = fopen(argv[j], "r") ;

        if ( fp == NULL )
        {
            printf("File : %s Can NOT be Opened\nProgram will terminate\n", argv[j]) ;
            exit(EXIT_FAILURE) ;
        }

        SetToZero(fileMatrix) ;
        FileToMat(fp, fileMatrix) ;

        if (opt.backup == 1)
        {
            backUp(fileMatrix, argv[j]) ;
        }

        fclose(fp);

        fp = fopen(argv[j], "w") ;

        if ( fp == NULL )
        {
            printf("File : %s Can NOT be Opened\nProgram will terminate\n", argv[j]) ;
            exit(EXIT_FAILURE) ;
        }


        if (opt.first == 1)
        {
           status = ReplaceFirst(fileMatrix, from, to);
        }

        if (opt.last == 1)
        {
            status = ReplaceLast(fileMatrix, from,to) ;
        }

        if (opt.all == 0)
        {
            status = ReplaceAll(fileMatrix , from , to) ;
        }

        matToFile(fp , fileMatrix) ;

        fclose(fp) ;

        if (status == -1) printf("string : %s not found in file : %s\n" , from , argv[j]) ;
        else printf("string : %s found and replaced in file : %s\n" , from , argv[j]) ;
    }

    return 0;
}
