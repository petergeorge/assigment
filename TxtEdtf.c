#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txtedtf.h"
extern sFlagsTyp opt ;
/*
#define MAXROW  500
#define MAX_MAT_COL 15
*/
static int FindFirst (char Mat [MAX_MAT_ROW][MAX_MAT_COL], char to[]);
static int FindLast (char Mat [MAX_MAT_ROW][MAX_MAT_COL], char to[]);
static int FindFirst_In ( char Mat [MAX_MAT_ROW][MAX_MAT_COL], char from[]);
static int FindLast_In (char Mat [MAX_MAT_ROW][MAX_MAT_COL], char from[]);

void FileToMat (FILE *fp, char TxtMat [MAX_MAT_ROW][MAX_MAT_COL])
{
    int  j = 0, k = 0;
    char c;
    while ((c = (char)fgetc(fp)) != EOF)
    {
        if ( (c != ' ') && (c != '\n') )
        {
            TxtMat[j][k] = c ;
            k++;
        }
        else if (c == ' ')
        {
            TxtMat[j][k] = '\0' ;
            j++;
            TxtMat[j][0] = ' ' ;
            TxtMat[j][1] = '\0' ;
            j++;
            k = 0;
        }
        else
        {
            TxtMat[j][k] = '\0' ;
            j++;
            TxtMat[j][0] = '\n' ;
            TxtMat[j][1] = '\0' ;
            j++;
            k = 0;
        }
    }

}


void SetToZero ( char Mat [MAX_MAT_ROW][MAX_MAT_COL])
{
    int i, j;
    for (i = 0 ; i < MAX_MAT_ROW ; i++)
    {
        for (j = 0 ; j < MAX_MAT_COL ; j++)
        {
            Mat [i][j] = 0;
        }
    }
}


int ReplaceFirst ( char Mat [MAX_MAT_ROW][MAX_MAT_COL],char from[], char to[])
{

    int j = 0 ;
    if (opt.insense == 0) j = FindFirst(Mat, from) ;

    else j = FindFirst_In(Mat, from) ;

    if (j != -1) strcpy(Mat[j], to) ;

    return j ;

}

int ReplaceLast (char Mat [MAX_MAT_ROW][MAX_MAT_COL],char from[], char to[])
{
    int j = 0 ;

    if (opt.insense == 0)
        j = FindLast(Mat, from) ;
    else
        j = FindLast_In(Mat, from) ;

    if (j != -1) strcpy(Mat[j], to) ;

    return j ;
}


int ReplaceAll (char Mat [MAX_MAT_ROW][MAX_MAT_COL],char from[], char to[])
{
    int i = 0 ;
    int ret = -1 ;
    char searchTemp [STR_SIZE] ;
    char fromTemp [STR_SIZE] ;
    strcpy(fromTemp, from) ;
    strupr(fromTemp) ;
    for (i = 0 ; i < MAX_MAT_ROW ; i++)
    {
        if (opt.insense == 1)
        {
            strcpy (searchTemp,Mat[i]) ;
            strupr(searchTemp) ;

            if (!(strcmp(searchTemp,fromTemp)))
            {
                strcpy (Mat[i], to) ;
                ret = 1 ;
            }
        }
        else
        {
            if (!(strcmp(Mat[i],from)))
            {
                strcpy (Mat[i], to) ;
                ret = 1 ;
            }
        }
    }
    return ret ;
}


void backUp (char Mat[][MAX_MAT_COL], char fName [])
{
    FILE *newFile;
    char tempArr [STR_SIZE] ;
    char c = 1;
    int i = 0 ;

    for ( i = 0, c = fName[i]  ; c != '.' ; i++, c = fName[i] )
    {
        tempArr[i] = fName[i] ;

    }
    tempArr[i]   = '_' ;
    tempArr[i+1] = 'B';
    tempArr[i+2] = 'a';
    tempArr[i+3] = 'c';
    tempArr[i+4] = 'k';
    tempArr[i+5] = 'u';
    tempArr[i+6] = 'p';
    tempArr[i+7] = '.';
    tempArr[i+8] = 't';
    tempArr[i+9] = 'x';
    tempArr[i+10] = 't';
    tempArr[i+11] = '\0';

    newFile = fopen (tempArr, "w" );

    if (newFile == NULL)
    {
        printf("backup File : %s can not be created\n", tempArr) ;
        exit(EXIT_FAILURE);
    }

    matToFile(newFile , Mat) ;
//fprintf(newFile , "%c" , EOF) ;

    fclose(newFile) ;

}

/*returns index of first found string or -1 if not found*/
static int FindFirst (char Mat [MAX_MAT_ROW][MAX_MAT_COL], char to[])
{
    int i;
    for (i = 0 ; i < MAX_MAT_ROW ; i++)
    {
        if ( !(strcmp(Mat[i], to)) ) return i ;
    }

    return -1 ;
}

/*Return index of last occurence or -1 if not found*/
static int FindLast (char Mat [MAX_MAT_ROW][MAX_MAT_COL], char to[])
{
    int ret = -1 ;
    int i;
    for (i = 0 ; i < MAX_MAT_ROW ; i++)
    {
        if ( !(strcmp(Mat[i], to)) ) ret = i ;
    }
    return ret ;
}


static int FindFirst_In ( char Mat [MAX_MAT_ROW][MAX_MAT_COL], char from[])
{
    int i;
    char fromTemp [STR_SIZE] ;
    char searchTemp [STR_SIZE] ;

    strcpy (fromTemp, from) ;
    strupr(fromTemp) ;

    for (i = 0 ; i < MAX_MAT_ROW ; i++)
    {
        strcpy(searchTemp, Mat[i]) ;
        strupr (searchTemp) ;
        if ( !(strcmp(searchTemp, fromTemp)) ) return i ;
    }

    return -1 ;
}

static int FindLast_In (char Mat [MAX_MAT_ROW][MAX_MAT_COL], char from[])
{
    int i;
    int ret = -1 ;
    char fromTemp [STR_SIZE] ;
    char searchTemp [STR_SIZE] ;

    strcpy (fromTemp, from) ;
    strupr(fromTemp) ;

    for (i = 0 ; i < MAX_MAT_ROW ; i++)
    {
        strcpy(searchTemp, Mat[i]) ;
        strupr (searchTemp) ;
        if ( !(strcmp(searchTemp, fromTemp)) ) ret = i ;
    }

    return ret ;
}

void matToFile(FILE * fp, char Mat[MAX_MAT_ROW][MAX_MAT_COL])
{
    int i = 0 ;

    while (i < MAX_MAT_ROW)
    {
        fprintf(fp, "%s", Mat [i]) ;
        i++;
    }
}
