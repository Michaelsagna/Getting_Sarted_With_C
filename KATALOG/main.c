/*Programm zur Verwaltung eines Buchkatalogs.*
 *Es enthält eine Menue für die Interaktion mit dem User*
 *In dem Menue kann der User
 *                          1. den Gesamtbestand anzeigen lassen
 *                          2. neues Element zum bestehenden Bestand hinzufügen.
 *                          3. Bestand alphabetisch nach Namen sortieren.
 *                          4. Das Programm beenden durch die ESC-Taste
 *Mögliche Erweiterungen: Bestand dauerhaft speichern, so dass der Inhalt aktulisiert wird bei jede Änderung.   */
#include "book_katalog.h"


void main()
{   
    
    int choice;
    while((choice=menue())!=ESC)
    {
        flush();
        switch (choice)
        {
            case SHOW:  show();
                        break;
            case ADD:   if(add()) kat_len++;
                        break;
            case SORT:  sort();
                        break;
            default:    printf("\nUngültige Eingabe!\nMögliche Eingaben : - 1 - 2 - 3 - ESC - \n");    
                        break;
        }
        WEITER;
        flush();
    }
     
}
