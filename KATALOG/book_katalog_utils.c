#include"book_katalog.h"
                                                                        /*Globale Daten*/
extern BUCH katalog[];                                                  /*Deklaration der Programmglobalen Daten*/
extern int kat_len;                                                     /*Erst dadurch wird die Sichtbarkkeit dieser Daten in anderen Modulen des Programms ermöglicht */
static char *auswahl[]={"            1 = Katalogeinträge anzeigen.\n\n",
                    "            2 = Katalogeinträge hinzufügen.\n\n",
                    "            3 = Katalogeinträge sortieren.\n\n",
                    "            ESC = Programm beenden.\n\n",
                    "Ihre Wahl: \n>"};

/*********************************************************************************************/
/*HauptFunktionalitäten*/
int menue(void)
{
    
    CLS;
    HEADER;
    LOCATE(6,1);
    for(int i=0;i<5;i++)
    {
        printf("%s",auswahl[i]);
    }
    return getchar();
}
/*********************************************************************************************/
void showKatalogEntries()
{
    printf("Suchbegriff eingeben \n>");
    
    char name[30]; int count;
    int eingabe=readUserInput(name,29,ESC,'\r');
    if(eingabe==ESC)
        return;
        
    strtoup(name);
    count=search_byAuthor(katalog,kat_len,name);
    if(count==0)
        printf("\n\nEs wurde kein passender Eintrag gefunden. \n");
    
    else
        printf("Es wurden %d Einträge gefunden\n",count);
    

}

int addBook()
{
    int is_added=0;
    static char entry_msg[]="ISBN\t\t\t\t--->\n\nAUTHOR\t\t\t\t--->\n\nTITEL\t\t\t\t--->\n\nERSCHEINUNGSJAHR\t\t--->\n\nVERLAG\t\t\t\t--->\n\n";
    char buffer[50];
    BUCH *kat_ptr;
    kat_ptr=katalog+kat_len;
    CLS;
    HEADER;
    LOCATE(4,1);
    printf("%s",auswahl[1]);

    LOCATE(6,1);

    printf("%s",entry_msg);

    LOCATE(6,40);
    if(readUserInput(buffer,49,ESC,'\r')==ESC)
        return is_added;
    kat_ptr->isbn=atol(buffer);

    LOCATE(8,40);
    if(readUserInput(buffer,49,ESC,'\r')==ESC)
        return is_added;
    strtoup(buffer);
    strcpy(kat_ptr->author,buffer);

    LOCATE(10,40);
    if(readUserInput(buffer,49,ESC,'\r')==ESC)
        return is_added;
    strcpy(kat_ptr->titel,buffer);

    LOCATE(12,40);
    if(readUserInput(buffer,49,ESC,'\r')==ESC)
        return is_added;
    kat_ptr->erscheinungsjahr=atoi(buffer);

    LOCATE(14,40);
    if(readUserInput(buffer,49,ESC,'\r')==ESC)
        return is_added;
    strcpy(kat_ptr->verlag,buffer);
    is_added=1;
    return is_added;
}

void sortKatalog()
{
    qsort(katalog,kat_len,sizeof(BUCH),string_compare);
    printf(" \n\nSortiervorgang erfolgreich abgeschlossen!\n\n");
}

/*********************************************************************************************/
/*HilfsFunktionalitäten*/
static int string_compare(const void *b1,const void *b2)
{
    const BUCH *_b1=b1,*_b2=b2;
    return strncmp(_b1->author,_b2->author,strlen(_b1->author));
}

static int readUserInput(char *buffer,int max,...)
{
    int c, breakc;
    int nc=0;
    va_list argp;                   /*Vereinbarung eines Zeigers auf die optionalen Argumente*/

    do
    {
        *buffer='\0';
        c=getchar();                          /* Einlesen eines Zeichen. Bei Sonderzeichen erweiterter code nutzen*/
        if(c==0)
            c+=256; 

        va_start(argp,max);                     /*Zeiger initialisieren*/
        do
        {                                       /*Zeichen mit Abbruchliste vergleichen*/
            if(c==(breakc=va_arg(argp,int)))    /*Zeiger zum einlesen verwenden*/
                return breakc;
        } while (breakc!='\r');                                                      
        va_end(argp);                           /*zeiger zurücksetzen*/
        if(c=='\b'&& nc>0)
        {
            --nc, --buffer;
            putchar(c);putchar(' ');putchar(c);
        }
        else if(c>=32 && c<=255 && nc < max)
        {
            ++nc,*buffer++=c;
        }
        else if(nc==max)
        {
            putchar('\a');
        }
    }while(c!='\n');

}

static int search_byAuthor(BUCH *kat,int len,char *pattern)
{
    int len_id, anzahl=0;
    len_id=strlen(pattern);
    for(;len>0;--len)
    {
        if(strncmp(kat->author,pattern,len_id)==0)
        {
            SEPARATOR;
            printf("BuchNummer: %-40lu\n",(kat)->isbn);
            printf("Author: %-40s\n",(kat)->author);
            printf("Titel: %-40s\n",(kat)->titel);
            printf("Erschienen im Jahr: %-4i\n",(kat)->erscheinungsjahr);
            printf("Verlag: %-40s\n",(kat)->verlag);
            ++anzahl;
        }
        kat++;

    }
    SEPARATOR;
    return anzahl;
    
}

static void strtoup(char *str)
{
    char *sp=str;

    while(*sp!='\0' && (*sp==' ' || *sp=='\t'))
        sp++;

    while((*str=toupper(*sp))!='\0')
    {
         ++sp; ++str;
    }
    
}

void flushInputBuffer()
{
    int c;
    while((c=getchar())!='\n' && c!=EOF)
    {
        ;
    }
}

/*********************************************************************************************/
/*Ergänzende Funktionalitäten*/
void updateKatalogData()
{
    FILE *fp;
    if((fp=fopen("./katalogInitData","w"))!=NULL)
    {
        fwrite(katalog,sizeof(BUCH),kat_len,fp);
        fclose(fp);
    }
   
}

int initKatalogData()
{
    FILE *fp;
    int filesize=0,len=0,len_final=0;
    if((fp=fopen("./katalogInitData","r"))!=NULL)
    {
        fseek(fp,0L,SEEK_END);
        filesize=ftell(fp);
        len=filesize/sizeof(BUCH);
        rewind(fp);
        len_final=fread(katalog,sizeof(BUCH),len,fp);
        fclose(fp);
    }

    else
    {

        if(addBook())
            len_final++;
    }
    return len_final;

    
    
}


