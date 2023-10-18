/*Programm zur Verwaltung eines Buchkatalogs.*
 *Es enthält eine Menue für die Interaktion mit dem User*
 *In dem Menue kann der User
 *                          1. den Gesamtbestand anzeigen lassen
 *                          2. neues Element zum bestehenden Bestand hinzufügen.
 *                          3. Bestand alphabetisch nach Namen sortieren.
 *                          4. Das Programm beenden durch die ESC-Taste
 *Mögliche Erweiterungen: Bestand dauerhaft speichern, so dass der Inhalt aktulisiert wird bei jede Änderung.   
 *Diese Erweiterung wurde nun umgesetzt und erfolgreich getestet*/
#include "book_katalog.h"
BUCH katalog[KAT_SIZE]={};
int kat_len=0;

void main()
{   
    kat_len=initKatalogData();
    int choice;
    while((choice=menue())!=ESC)
    {
        flushInputBuffer();
        switch (choice)
        {
            case SHOW:  showKatalogEntries();
                        break;
            case ADD:   if(addBook()) kat_len++;
                        break;
            case SORT:  sortKatalog();
                        break;
            default:    printf("\nUngültige Eingabe!\nMögliche Eingaben : - 1 - 2 - 3 - ESC - \n");    
                        break;
        }
        WEITER;
        flushInputBuffer();
    }
    updateKatalogData();
     
}
