/**
 *   Programeksempel nr 22 - Insertion sort (Innstikkssortering).
 *
 *   Algoritme/virkem�te:
 *        Henter stadig et nytt element utover i arrayen, og smetter det inn
 *        der skal ligge blant de allerede sorterte tidligere i arrayen.
 *        N�r man finner et nytt aller minste element, s� vil while-l�kka
 *        kunne g� utforbi arrayens nedre grense (nr.0). Derfor inneholder
 *        element nr.0 en verdi som er mindre enn ALT annet i hele arrayen.
 *        Denne kalles "SENTINEL KEY" (STOPPVERDI).
 *
 *   Orden ( O(...)):
 *        Bruker omtrent  (N*N)/4  (N i annen kvarte) sammenligninger 
 *        og  (N*N)/8  ombyttinger i GJENNOMSNITT. 
 *        I VERSTE FALL (n�r allerede baklengs sortert): DOBBELT s� mye
 *
 *   NB:  - Er n�rmest LINE�R for s� godt som ferdig sorterte arrayer.
 *          For da vil while-l�kka g�r null/f� ganger for hvert element.
 *          Da overg�r den ALLE andre metoder (ogs� Quicksort og Heapsort).
 *        - Er ogs� rask n�r ALLE elementene er helt ferdig sortert, og legger
 *          til noen SV�RT F� ALLER bakerst, som da skal sorteres/flyttes inn.
 *        - Stabil?   Se oppgave nr.10.
 *
 *   @file     EKS_22_InsertionSort.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <cstdlib>           //  (s)rand
using namespace std;


const int N = 20;            ///<  Antall elementer i array som skal sorteres.


void display(const int arr[], const int n);
void insertionSort(int arr[], const int n);


/**
 *  Hovedprogrammet:
 */
int main() {
    int array[N+1];                //  Array som skal sorteres.
                                   //  Bruker indeksene 1-N
                                   //    da det ligger SENTINEL KEY
                                   //    (STOPPVERDI) i element nr.0 !!!

    srand(0);                      //  Brukes ifm. tilfeldighet/randomisering.

    array[0] = -1;                 //  Legger inn SENTINEL KEY !!!

    for (int i = 1;  i <= N;  i++) //  Fyller array med tilfeldige tall 1-100:
        array[i] = (rand() % 100) + 1;

    cout << "\n\nArrayen F�R sortering:\n\t";
    display(array, N+1);           //  Skriver array F�R sortering.


    insertionSort(array, N+1);     //  INSERTION SORTERER !!!


    cout << "\n\nArrayen ETTER INSERTION sortering:\n\t";
    display(array, N+1);           //  Skriver array ETTER sortering.

    cout << "\n\n";
    return 0;
}



/**
 *  Skriver ut HELE arrayen 'arr' sitt innhold.
 *
 *  @param   arr  -  Arrayen som f�r hele sitt innhold skrevet ut
 *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
 */
void display(const int arr[], const int n) {
    for (int i = 1;  i < n;  i++)
        cout << ' ' << arr[i];
    cout << '\n';
}


/**
 *  Sorterer en input-array STIGENDE med INSERTION SORTERING.
 *
 *  @param   arr  -  Arrayen som skal sorteres
 *  @param   n    -  Antall elementer i arrayen 'arr'
 */
void insertionSort(int arr[], const int n) {
    int i, j,                      //  L�kkevariable.
        verdi;                     //  Verdien/elementet som evt.
                                   //    skal flyttes ned/stikkes inn.
    for (i = 2;  i < n;  i++) {    //  G�r fra nr.2 og ut arrayen:
        verdi = arr[i];            //  Den som evt. skal flyttes ned.
        j = i;                     //  Initierer til aktuelt element.
        while (arr[j-1] > verdi) { //  S� lenge tidligere er st�rre:
            arr[j] = arr[j-1];     //  Flytter de opp ETT hakk/indeks.
            j--;                   //  Minsker 'j', til st�ter p�
        }                          //    SENTINEL key!
        arr[j] = verdi;            //  Smetter inn der 'j' stanset.
    }
}