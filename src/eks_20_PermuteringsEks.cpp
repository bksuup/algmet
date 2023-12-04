/**
 *  Programeksempel nr 20 - Tallplassering (etter visse regler) i et rutenett.
 *
 *  For programmets funksjonalitet se:  PermuteringsEks.pdf
 *
 *  Eksemplet er S� GODT SOM HELT IDENTISK til EKS_19_Permutering.cpp,
 *  bortsett fra at:
 *     - funksjonen 'rettSum(...)' er ny
 *     - innholdet i 'permuter' er litt utvidet (med if-setninger)
 *     - 'display' er litt omskrevet
 *
 *  (Dette var oppg.nr.5 p� eksamen 15/12-1994 i LO164A-Algoritmiske metoder)
 *
 *  (Andre tidligere eksamensoppgaver som ogs� bruker permutering:
 *  H06-nr.4,  H07-nr.4, H11-nr.4,  H15-nr.4,  H16-nr.4,  S96-nr.5,  S10-nr.4)
 *
 *  @file     EKS_20_PermuteringsEks.CPP
 *  @author   Frode Haug, NTNU
 */


#include <iostream>                 //  cout
#include <iomanip>                  //  setw
using namespace std;


const int N = 16;                   ///<  Arrayens lengde.

int gAntallLosninger;               ///<  Antall l�sninger funnet (hittil).
                                    //    Det er 7040 l�sninger (speilinger
                                    //      og rotasjoner inkludert).
                                    //    Det er 416 l�sninger n�r '1' st�r
                                    //      fast i �vre venstre hj�rne.
void bytt(int & tall1, int & tall2);
void display(const int arr[], const int n);
void permuter(int arr[], const int i, const int n);
bool rettSum(int arr[], int n);
void roterVenstre(int arr[], const int i, const int n);


/**
 *  Hovedprogrammet:
 */
int main() {
    int array[N];                    //  Array som skal permuteres.

    for (int i = 0; i < N; i++)      //  Fyller array med: 1, 2, 3, ..., N
        array[i] = i + 1;

    permuter(array, 0, N);           //  Lager (og skriver) permutasjoner av
                                     //    ALLE arrayelementene.
    cout << '\n';
    display(array, N);       //  Skriver array etter at ferdig
                             //    (for � vise at origisnal er gjenopprettet).

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
    cout << "\nL�sning nr." << ++gAntallLosninger << ":";
    for (int i = 0; i < N; i++) {
        if (i % 4 == 0)  cout << '\n';
        cout << setw(5) << arr[i];
    }
    cout << '\n';
}


/**
 *  Genererer rekursivt ALLE mulige permutasjoner av innholdet i 'arr'.
 *
 *  @param   arr  -  Arrayen som skal permuteres
 *  @param   i    -  Indeksen som ALLE ETTERF�LGENDE verdier skal flyttes til
 *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
 *  @see     bytt(...)
 *  @see     display()
 *  @see     rettSum(...)
 *  @see     roterVenstre(...)
 */
void permuter(int arr[], const int i, const int n) {
    if (i == n-1  &&  rettSum(arr, i))  //  N�dd en ny LOVLIG permutasjon:
        display(arr, n);                //  Skriver ut arrayens innhold.
    else {                              //  Skal permutere:
                                        //  Ikke p� slutten av en linje,
                                        //    eller siste linjesum = 34 !!!
        if ((i+1) % 4 != 0  ||  rettSum(arr, i))
           permuter(arr, i+1, n);       //  Beholder n�v�rende nr.'i'.
                                        //  Permuterer resten.
        for (int t = i+1;  t < n;  t++) {
            bytt(arr[i], arr[t]);       //  Bytter nr.'i' etter tur med
                                        //    ALLE de andre etterf�lgende.
                                        //  Ikke p� slutten av en linje,
                                        //    eller siste linjesum = 34 !!!
            if ((i+1) % 4 != 0 || rettSum(arr, i))
               permuter(arr, i + 1, n); //  For hver av ombyttene: permuterer
        }                               //     resten av de etterf�lgende.
        roterVenstre(arr, i, n);        //  Gjenoppretter opprinnelig array!!!
    }
}


/**
 *  Sjekker om 'arr' tilfredstiller kravene beskrevet i PermuteringsEks_pdf.
 *
 *  @param    arr  -  Arrayen som skal sjekkes for 34-summer
 *  @param    n    -  Indeksen det skal sjekkes BAKOVER i fra
 *  @return   Om ALLE de 10 linje-/kolonne-/diagonal-summene er 34 eller ei
 */
bool rettSum(int arr[], int n) {
    if (arr[n-3] + arr[n-2] + arr[n-1] + arr[n] != 34) // Siste LINJESUM = 34?
       return false;
    if (n == N-1) {                             //  Permutert HELT ut arrayen:
        for (int i = 0; i < 4; i++)               //  ALLE kolonnesummer = 34?
            if (arr[0 + i] + arr[4 + i] + arr[8 + i] + arr[12 + i] != 34)
               return false;
        if (arr[0] + arr[5] + arr[10] + arr[15] != 34) //  DIAGONALsum = 34?
           return false;
        if (arr[3] + arr[6] + arr[9] + arr[12] != 34)  //  BIDIAGONALsum = 34?
           return false;
    }
    return true;
}


/**
 *  Venstreroterer en array innhold.
 *
 *  @param   arr  -  Arrayen som f�r (deler av) sitt innhold venstrerotert
 *  @param   i    -  Laveste indeks som skal venstreroteres
 *  @param   n    -  'n-1' er h�yeste indeks som venstreroteres
 */
void roterVenstre(int arr[], const int i, const int n) {
    int venstreVerdi = arr[i];            //  Tar vare p� f�rste.
    for (int k = i + 1; k < n; k++)       //  Roterer (flytter alle ned
        arr[k - 1] = arr[k];                //     ETT hakk/indeks).
    arr[n - 1] = venstreVerdi;              //  Legger f�rste inn bakerst.
}
