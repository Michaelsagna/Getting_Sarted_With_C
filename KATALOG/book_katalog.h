/*All Header files and declaration of function prototypes are held in this file as well as *
 * all global variables and Makros*/
/*********************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<ctype.h>
/*********************************************************************************************/
#define CLS printf("\033[2J");
#define LOCATE(z,s) printf("\033[%d;%dH",z,s);
#define HEADER CLS; LOCATE(1,20); printf("*** BÜCHER-VERZEICHNIS ***");
#define WEITER printf("\n\n--- Weiter mit Enter ---\n\n");
#define SEPARATOR               printf("****************************\n")
/*********************************************************************************************/
#define CR 13
#define ESC 27
#define KAT_SIZE 200

#define SHOW '1'
#define ADD '2'
#define SORT '3'
/*********************************************************************************************/
struct book                                                     /*Struktur eines Katalogeintrags*/
{
    long int isbn;
    char author[50];
    char titel[50];
    short erscheinungsjahr;
    char verlag[20];
};
typedef struct book BUCH;
/*********************************************************************************************/
                                                                        /*Prototypen*/
extern int menue(void);
extern int add(void);
extern void show(void);
extern void sort(void);
extern int input(char *buffer,int max,...);
extern void flush();
extern int search_byAuthor(BUCH *kat,int len,char*);
extern int input(char *buffer,int max,...);
extern void strtoup(char *);
extern int string_compare(const void *b1,const void *b2);

                                                                        /*Globale Daten*/
extern BUCH katakog[];                                      
extern int kat_len;

extern char *auswahl[];

/* Ende der Headerdatei*/


/*********************************************************************************************/