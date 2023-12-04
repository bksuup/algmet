/**
 *   Programeksempel nr 21 - Selection sort (Utplukkssortering).
 *
 *   Algoritme/virkem�te:
 *          Finner det minste elementet i resten av arrayen f.o.m nr.'i',
 *          og legger det inn p� plass nr.'i'.  Lar 'i' �ke mot 'N'.
 *
 *   Orden ( O(...)):
 *          Bruker omtrent  (N*N)/2  (N i annen halve) sammenligninger 
 *          og  N  ombyttinger.
 *
 *   NB:  - Er LINE�R n�r verdiene som sammenlignes er sm�, og evt. 
 *          tilh�rende data er store/mye. Dvs. da gjelder det � holde
 *          antall ombyttinger nede p� et minimum, siden MYE tilh�rende
 *          data m� byttes om/flyttes.
 *        - Er IKKE STABIL. "Stabil" vil si at rekkef�lgen p� LIKE elementer
 *          har samme innbyrdes rekkef�lge ogs� etter sortering.
 *              F�lgende eksempel viser dette:    SMS'AS"
 *              Den f�rste S vil bytte plass med den minste (dvs A). Dermed er
 *              den faktisk ferdig sortert, mens S har havnet mellom S' og S".
 *
 *   @file     EKS_21_SelectionSort.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <cstdlib>           //  (s)rand
using namespace std;


const int N = 20;            ///<  Antall elementer i array som skal sorteres.


void bytt(int & tall1, int & tall2);
void display(const int arr[], const int n);
void selectionSort(int arr[], const int n);


/**
 *  Hovedprogrammet:
 */
int main() {
    int array[N];                  //  Array som skal sorteres.

    srand(0);                      //  Brukes ifm. tilfeldighet/randomisering.

    for (int i = 0;  i < N;  i++)  //  Fyller array med tilfeldige tall 1-100:
        array[i] = (rand() % 100) + 1;

    cout << "\n\nArrayen F�R sortering:\n\t";
    display(array, N);             //  Skriver array F�R sortering.


    selectionSort(array, N);       //  SELECTION SORTERER !!!


    cout << "\n\nArrayen ETTER SELECTION sortering:\n\t";
    display(array, N);             //  Skriver array ETTER sortering.

    cout << "\n\n";
    return 0;
}


/**
 *  Bytter om to referanseoverf�rte variables innhold.
 *
 *  @param   tall1  -  Verdien som skal byttes med 'tall2' (referanseoverf�rt)
 *  @param   tall2  -  Verdien som skal byttes med 'tall1' (referanseoverf�rt)
 */
void bytt(int & tall1, int & tall2) {
    int temp = tall1;           //  Midlertidig (temporary) unnalagring.
    tall1 = tall2;
    tall2 = temp;
}


/**
 *  Skriver ut HELE arrayen 'arr' sitt innhold.
 *
 *  @param   arr  -  Arrayen som f�r hele sitt innhold skrevet ut
 *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
 */
void display(const int arr[], const int n) {
    for (int i = 0;  i < n;  i++)
        cout << ' ' << arr[i];
    cout << '\n';
}


/**
 *  Sorterer en input-array STIGENDE med SELECTION SORTERING.
 *
 *  @param   arr  -  Arrayen som skal sorteres
 *  @param   n    -  Antall elementer i arrayen 'arr'
 *  @see     bytt(...)
 */
void selectionSort(int arr[], const int n) {
    int i, j,                      //  L�kkevariable
        minIndeks;                 //  Indeks for den MINSTE verdien
                                   //    i det intervallet det letes.
    for (i = 0;  i < n-1;  i++) {  //  G�r til NEST siste element:
        minIndeks = i;             //  Initierer til F�RSTE av de gjenv�rende.
        for (j = i+1;  j < n;  j++)    //  Finner minste ETTER nr.'i':
            if (arr[j] < arr[minIndeks])  minIndeks = j;
        bytt(arr[minIndeks], arr[i]);  //  Flytter ned til plass nr.'i'.
    }
}