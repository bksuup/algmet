/**
 *   Programeksempel nr 26 - Heapsort.
 *
 *   Algoritme/virkem�te:
 *        I arrayen som skal sorteres, startes det halveis uti, og det g�s
 *        baklengs til dens start. For hvert element utf�res 'downHeap'.
 *        S� n�r man har kommet til det f�rste elementet, oppfyller HELE den
 *        originale arrayen heap-betingelsen.
 *        Deretter bytter man om det aller f�rste og det til enhver tid siste
 *        elementet, utf�rer 'downHeap' for hver gang, og teller stadig ned
 *        antall elementer i arrayen som er igjen � sortere.
 *        Se koden for 'heapSort' ALLER nederst p� denne filen.
 *
 *   Orden ( O(...)):
 *        Bruker F�RRE (selv i "worst case"!) enn  2N lg N  sammenligninger
 *        for � sortere N elementer.
 *        (Siden hver heap-operasjon er av orden  2 lg N, og n� er det N
 *        elementer som skal sorteres, s� blir dette "selvsagt" ordenen.)
 *        Dette er bare LITT saktere enn Quicksort, som er av orden:  2N ln N
 *
 *   NB:  - Bottom-up heap-KONSTRUKSJON er tidsline�r.
 *        - Ifm. bottom-up heapsortering er bruken av sentinel key i element
 *          nr.0 uinteressant. Dette fordi det bare brukes 'downHeap',
 *          og denne bruker IKKE sentinel key (men det gj�r 'remove' og
 *          'replace'). Derfor settes det IKKE opp en sentinel key i
 *          'gHeap' i 'main'. Dessuten M� det f�rste elementet ligge i nr.1,
 *          og ikke nr.0 (som da synes ledig), fordi selve koden i 'heap'
 *          forutsetter at det f�rste elementet ligger i nr.1.
 *        - Stabil?  NEI - da like elementer havner ulikt omkring i heapen
 *        - All koden i denne filen viser hvordan vi BOTTOM-UP heapsorter.
 *          Det finnes dog en annen metode, som kalles TOP-DOWN heapsortering.
 *          Denne g�r ut p� � bruke heapen mer aktivt. ALT som skal sorteres
 *          legges inn ('insert') - hele tiden tilfredstillende heap-betingelsen.
 *          (Vi bruker dermed dobbelt s� mye memory enn det som skal sorteres.)
 *          Deretter hentes ALT ut igjen ('remove'), og den originale arrayen
 *          fylles opp bakfra og fremover. Koden kunne da v�rt noe s�nt som:
 *
 *                void heapSort(unsigned char arr[], const int n)  {
 *                     int i;
 *                     Heap <unsigned char> heap(n+1);
 *                     for (i = 1;  i <= n;  i++)  heap.insert(arr[i]);
 *                     for (i = n;  i >= 1;  i--)  arr[i] = heap.remove();
 *                }
 *
 *   @file     EKS_26_Heapsort.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <cstdlib>           //  (s)rand
#include "eks_25_Heap.h"     //  Klassen Heap (bruker KUN 'downHeap(...)')
using namespace std;


const int N = 20;            ///<  Antall elementer i array som skal sorteres.


template <typename T>        //  'template' funksjon !!!
void bytt(T & verdi1, T & verdi2);

void display(const unsigned char arr[], const int n);
void heapSort(unsigned char arr[], int n);


Heap <unsigned char> gHeap;  ///<  Array som fylles og sorteres.
//                   gHeap(0); //  Kunne godt ha v�rt null elementer i heapen,
                               //    da den brukes IKKE, bare dens 'downHeap'!

/**
 *  Hovedprogrammet:
 */
int main() {
    unsigned char array[N+1];      //  Array som skal sorteres.
                                   //  Bruker indeksene 1 til N.

    srand(0);                      //  Brukes ifm. tilfeldighet/randomisering.

    for (int i = 1;  i <= N;  i++)  //  Array med tilfeldige bokstaver a-z:
        array[i] = static_cast <unsigned char> ('a' + (rand() % 26));

    cout << "\n\nArrayen F�R sortering:\n";
    display(array, N);


    heapSort(array, N);            //  HEAPSORT SORTERER !!!

                                   //  Skriver array ETTER sortering:
    cout << "\n\nArrayen ETTER HEAPSORT sortering:\n";
    display(array, N);

    cout << "\n\n";
    return 0;
}


/**
 *  Bytter om to referanseoverf�rte variables innhold.
 *
 *  @param   verdi1  -  Verdien som skal byttes med 'verdi2' (ref.overf�rt)
 *  @param   verdi2  -  Verdien som skal byttes med 'verdi1' (ref.overf�rt)
 */
template <typename T>                    //  TEMPLATE FUNKSJON !!!
void bytt(T & tegn1, T & tegn2) {
    T temp = tegn1;           //  Midlertidig (temporary) unnalagring.
    tegn1 = tegn2;
    tegn2 = temp;
}


/**
 *  Skriver ut hele en arrays innhold.
 *
 *  @param   arr      -  Arrayen som f�r hele innholdet skrevet ut
 *  @param   n        -  Antall elementer i 'arr'
 */
void display(const unsigned char arr[], const int n) {
    char tegn;
    cout << '\t';
    for (int i = 1;  i <= n;  i++)
        cout << arr[i];
    cin >> tegn;                        //  Venter p� ETT tegn og '\n'.
}


/**
 *  Sorterer en unsigned char-array STIGENDE med (Bottom-Up) HEAPSORT.
 *
 *  @param   arr      -  Arrayen som skal sorteres
 *  @param   n        -  Antall elementer initielt i 'arr'
 *  @see     Heap.downHeap(...)
 *  @see     bytt(...)
 */
void heapSort(unsigned char arr[], int n)  {
    for (int keyNr = n/2;  keyNr >= 1;  keyNr--) //  Arrayen heap-ordnes: !!!
        gHeap.downHeap(arr, n, keyNr);
//                                       display(arr, N);  cout << "\n\n";

    while (n > 1) {                              //  Fortsatt igjen � sortere:
        bytt <unsigned char> (arr[1], arr[n]);   //  Flytter 1. der 'n' er !!!
        gHeap.downHeap(arr, --n, 1);             //  Heap-ordner igjen!
//                                       display(arr, N);
    }
}
