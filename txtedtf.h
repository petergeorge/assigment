#ifndef TXTEDTF_H_INCLUDED
#define TXTEDTF_H_INCLUDED

#define STR_SIZE 100
#define MAX_MAT_ROW 10000
#define MAX_MAT_COL STR_SIZE

typedef struct{
    unsigned char backup    : 1 ;
    unsigned char first     : 1 ;
    unsigned char last      : 1 ;
    unsigned char insense   : 1 ;
    unsigned char from      : 1 ;
    unsigned char all       : 1 ;

}sFlagsTyp ;



void FileToMat (FILE *fp, char TxtMat [MAX_MAT_ROW][MAX_MAT_COL]) ;
void SetToZero ( char Mat [MAX_MAT_ROW][MAX_MAT_COL]) ;
int ReplaceFirst ( char Mat [MAX_MAT_ROW][MAX_MAT_COL],char from[], char to[]) ;
int ReplaceLast (char Mat [MAX_MAT_ROW][MAX_MAT_COL],char from[], char to[]);
int ReplaceAll (char Mat [MAX_MAT_ROW][MAX_MAT_COL],char from[], char to[]) ;
void backUp (char Mat[][MAX_MAT_COL], char fName []) ;
void matToFile(FILE * fp , char Mat[MAX_MAT_ROW][MAX_MAT_COL]);


#endif // TXTEDTF_H_INCLUDED
