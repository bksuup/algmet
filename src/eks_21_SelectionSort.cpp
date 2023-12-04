/**
 *   Programeksempel nr 21 - Selection sort (Utplukkssortering).
 *
 *   Algoritme/virkemåte:
 *          Finner det minste elementet i resten av arrayen f.o.m nr.'i',
 *          og legger det inn på plass nr.'i'.  Lar 'i' øke mot 'N'.
 *
 *   Orden ( O(...)):
 *          Bruker omtrent  (N*N)/2  (N i annen halve) sammenligninger 
 *          og  N  ombyttinger.
 *
 *   NB:  - Er LINEÆR når verdiene som sammenlignes er små, og evt. 
 *          tilhørende data er store/mye. Dvs. da gjelder det å holde
 *          antall ombyttinger nede på et minimum, siden MYE tilhørende
 *          data må byttes om/flyttes.
 *        - Er IKKE STABIL. "Stabil" vil si at rekkefølgen på LIKE elementer
 *          har samme innbyrdes rekkefølge også etter sortering.
 *              Følgende eksempel viser dette:    SMS'AS"
 *              Den første S vil bytte plass med den minste (dvs A). Dermed er
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

    cout << "\n\nArrayen FØR sortering:\n\t";
    display(array, N);             //  Skriver array FØR sortering.


    selectionSort(array, N);       //  SELECTION SORTERER !!!


    cout << "\n\nArrayen ETTER SELECTION sortering:\n\t";
    display(array, N);             //  Skriver array ETTER sortering.

    cout << "\n\n";
    return 0;
}


/**
 *  Bytter om to referanseoverførte variables innhold.
 *
 *  @param   tall1  -  Verdien som skal byttes med 'tall2' (referanseoverført)
 *  @param   tall2  -  Verdien som skal byttes med 'tall1' (referanseoverført)
 */
void bytt(int & tall1, int & tall2) {
    int temp = tall1;           //  Midlertidig (temporary) unnalagring.
    tall1 = tall2;
    tall2 = temp;
}


/**
 *  Skriver ut HELE arrayen 'arr' sitt innhold.
 *
 *  @param   arr  -  Arrayen som får hele sitt innhold skrevet ut
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
    int i, j,                      //  Løkkevariable
        minIndeks;                 //  Indeks for den MINSTE verdien
                                   //    i det intervallet det letes.
    for (i = 0;  i < n-1;  i++) {  //  Går til NEST siste element:
        minIndeks = i;             //  Initierer til FØRSTE av de gjenværende.
        for (j = i+1;  j < n;  j++)    //  Finner minste ETTER nr.'i':
            if (arr[j] < arr[minIndeks])  minIndeks = j;
        bytt(arr[minIndeks], arr[i]);  //  Flytter ned til plass nr.'i'.
    }
}