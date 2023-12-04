/**
 *   Programeksempel nr 22 - Insertion sort (Innstikkssortering).
 *
 *   Algoritme/virkemåte:
 *        Henter stadig et nytt element utover i arrayen, og smetter det inn
 *        der skal ligge blant de allerede sorterte tidligere i arrayen.
 *        Når man finner et nytt aller minste element, så vil while-løkka
 *        kunne gå utforbi arrayens nedre grense (nr.0). Derfor inneholder
 *        element nr.0 en verdi som er mindre enn ALT annet i hele arrayen.
 *        Denne kalles "SENTINEL KEY" (STOPPVERDI).
 *
 *   Orden ( O(...)):
 *        Bruker omtrent  (N*N)/4  (N i annen kvarte) sammenligninger 
 *        og  (N*N)/8  ombyttinger i GJENNOMSNITT. 
 *        I VERSTE FALL (når allerede baklengs sortert): DOBBELT så mye
 *
 *   NB:  - Er nærmest LINEÆR for så godt som ferdig sorterte arrayer.
 *          For da vil while-løkka går null/få ganger for hvert element.
 *          Da overgår den ALLE andre metoder (også Quicksort og Heapsort).
 *        - Er også rask når ALLE elementene er helt ferdig sortert, og legger
 *          til noen SVÆRT FÅ ALLER bakerst, som da skal sorteres/flyttes inn.
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

    cout << "\n\nArrayen FØR sortering:\n\t";
    display(array, N+1);           //  Skriver array FØR sortering.


    insertionSort(array, N+1);     //  INSERTION SORTERER !!!


    cout << "\n\nArrayen ETTER INSERTION sortering:\n\t";
    display(array, N+1);           //  Skriver array ETTER sortering.

    cout << "\n\n";
    return 0;
}



/**
 *  Skriver ut HELE arrayen 'arr' sitt innhold.
 *
 *  @param   arr  -  Arrayen som får hele sitt innhold skrevet ut
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
    int i, j,                      //  Løkkevariable.
        verdi;                     //  Verdien/elementet som evt.
                                   //    skal flyttes ned/stikkes inn.
    for (i = 2;  i < n;  i++) {    //  Går fra nr.2 og ut arrayen:
        verdi = arr[i];            //  Den som evt. skal flyttes ned.
        j = i;                     //  Initierer til aktuelt element.
        while (arr[j-1] > verdi) { //  Så lenge tidligere er større:
            arr[j] = arr[j-1];     //  Flytter de opp ETT hakk/indeks.
            j--;                   //  Minsker 'j', til støter på
        }                          //    SENTINEL key!
        arr[j] = verdi;            //  Smetter inn der 'j' stanset.
    }
}