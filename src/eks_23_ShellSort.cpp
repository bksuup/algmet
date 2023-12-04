/**
 *   Programeksempel nr 23 - Shellsort.
 *
 *   Algoritme/virkemåte:
 *        Betrakter hvert h'te element som en del av en subarray.
 *        Går gjennom (ved å starte på 'h'+1) og sorterer (vha. insertion sort)
 *        ALLE slike subarrayer. Lar 'h' gå mot 1.
 *
 *   Orden ( O(...)):
 *        Gjør ALDRI mer enn N^(3/2) (dvs. N opphøyd i 3/2) sammenligninger
 *        for 'h'-verdiene: 1, 4, 13, 40, 121, 364, 1093, .....
 *        (Som er gode valg for 'h'. Knapt noen verdier som er bedre/raskere.
 *        En del matematisk analyse er gjort for ulike slike trinn-sekvenser.
 *        Så en annen vanlig beskrivelse av orden er:  N*logN*logN  )
 *
 *   NB:  - Når 'h' er lik 1 er Shellsort det samme som Insertion sort !!!
 *        - Bruk gjerne shellsort!  Dersom det da ikke er verdt å erstatte
 *          med mere sofistikerte/avanserte (slik som Quicksort m.m.). 
 *          Disse er IKKE SÅ mye raskere!
 *        - Bruker også SENTINEL KEY.
 *        - Stabil?   Se oppgave nr.10.
 *
 *   @file     EKS_23_ShellSort.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <string>            //  string
#include <cstdlib>           //  (s)rand
using namespace std;


const int N = 20;            ///<  Antall elementer i array som skal sorteres.


void display(const char arr[], const int n);
void shellSort(char arr[], const int n);
void skriv(const string & tekst, const char arr[],
           const int i, const int j, const int h, const char verdi);


/**
 *  Hovedprogrammet:
 */
int main() {
    char array[N+1];               //  Array som skal sorteres.
                                   //  Bruker indeksene 1-N
                                   //    da det ligger SENTINEL KEY
                                   //    (STOPPVERDI) i element nr.0 !!!

    srand(0);                      //  Brukes ifm. tilfeldighet/randomisering.

    array[0] = ' ';                //  Legger inn SENTINEL KEY !!!

    for (int i = 1;  i <= N;  i++) //  Array med tilfeldige bokstaver A-Z:
        array[i] =  static_cast <char> ('A' + (rand() % 26));

    cout << "\n\nArrayen FØR sortering:\n\t";
    display(array, N+1);           //  Skriver array FØR sortering.


    shellSort(array, N+1);         //  SHELLSORT SORTERER !!!


    cout << "\n\nArrayen ETTER SHELLSORT sortering:\n\t";
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
void display(const char arr[], const int n) {
    for (int i = 1;  i < n;  i++)
        cout << arr[i];
    cout << '\n';
}


/**
 *  Sorterer en char-array STIGENDE med SHELLSORT.
 *
 *  @param   arr  -  Arrayen som skal sorteres
 *  @param   n    -  Antall elementer i arrayen 'arr'
 *  @see     skriv(...)
 */
void shellSort(char arr[], const int n) {
    int  i, j, h;                   //  Løkkevariable.
    char verdi;                     //  Verdien/elementet som evt. skal
                                    //    flyttes bakover i subarrayen.
    for (h = 1;  h <= n/9;  h = (3*h)+1)  ;  //  NB: Tom for-løkke !!!
                                    //  Dvs. 'h' = 1, 4, 13, 40, 121, 364, ...
                                    //  Her: 21/9 = 2,  da blir 'h' lik 4 !!!
                                    //  Ved 36 elementer eller LITT flere:
                                    //    36/9 = 4, DA blir h lik 13.
//                                 char tegn;
    while (h > 0)  {                //  Så lenge det finnes subarrayer:

        for (i = h+1;  i < n;  i++) {   //  Går gjennom subarrayene:
            verdi = arr[i];    //  Den som evt. skal flyttes innen subarrayen.
            j  = i;            //  Initierer til aktuelt element.
//                                 skriv("Før", arr, i, j, h, verdi);
                               //  Så lenge er en i subarrayen 'h' plasser
                               //    lengre nede/tidligere og denne er større:
            while (j > h  &&  arr[j-h] > verdi) {
//                                 skriv("Inni - start", arr, i, j, h, verdi);
                arr[j] = arr[j-h]; // Flytter den opp 'h' plasser.
                j -= h;            // Indeks blir den 'h' plasser lengre nede.
//                                 skriv("Inni - slutt", arr, i, j, h, verdi);
            }
            arr[j] = verdi;        //  Smetter på plass der 'j' har stanset.
//                                 skriv("Etter", arr, i, j, h, verdi);
        }
//                             cout << "\n\nH = " << h << " er ferdig !!\n\n";
//                             cin >> tegn;
        h /= 3;               //  'h' minskes til en 1/3-del for hver looping.
    }
}


/**
 *  Skriver ut ledetekst, arrays innhold og mange hjelpevariables innhold.
 *
 *  @param   tekst  -  Ledetekst som skrives aller først
 *  @param   arr    -  Array hvis innhold eller enkeltelement skrives ut
 *  @param   i      -  Indeks som øker
 *  @param   j      -  Indeks som minsker
 *  @param   h      -  Ser på hvert h'te element bakover
 *  @param   verdi  -  Elementet/verdien som evt. skal flyttes bakover
 */
void skriv(const string & tekst, const char arr[],
           const int i, const int j, const int h, const char verdi) {
    char tegn;

    cout << '\n' << tekst << ":\t";

    if (tekst == "Etter") {
        cout << "Sammenligning utført,";
        if (j <= h) cout << "\tJ <= H\t\t";
        else        cout << "\t'" << arr[j - h] << "' <= '" << verdi << "'\t";
        display(arr, N + 1);
    }   //  Dvs. "Før",  "Inni - start"  og  "Inni - slutt":
    else {
        if (tekst == "Før") cout << '\t';
        cout << "H: " << h
             << "\tI: " << i << "\tJ: " << j
             << "\tJ-H: " << j - h;
        if (tekst == "Inni - slutt") {
            cout << "  ";
            display(arr, N + 1);
        }  else {   //  Dvs. "Før"  og  "Inni - start":
            cout << "\t\tarr[" << j - h << "]: '" << arr[j - h]
                  << "'  >  verdi: '" << verdi << "'";
            if (tekst == "Før") cout << "   ?";
            else cout << "   !!!";   //  Dvs. "Inni - start"
        }
    }
    cin >> tegn;
}
