/**
 *  Programeksempel nr 20 - Tallplassering (etter visse regler) i et rutenett.
 *
 *  For programmets funksjonalitet se:  PermuteringsEks.pdf
 *
 *  Eksemplet er SÅ GODT SOM HELT IDENTISK til EKS_19_Permutering.cpp,
 *  bortsett fra at:
 *     - funksjonen 'rettSum(...)' er ny
 *     - innholdet i 'permuter' er litt utvidet (med if-setninger)
 *     - 'display' er litt omskrevet
 *
 *  (Dette var oppg.nr.5 på eksamen 15/12-1994 i LO164A-Algoritmiske metoder)
 *
 *  (Andre tidligere eksamensoppgaver som også bruker permutering:
 *  H06-nr.4,  H07-nr.4, H11-nr.4,  H15-nr.4,  H16-nr.4,  S96-nr.5,  S10-nr.4)
 *
 *  @file     EKS_20_PermuteringsEks.CPP
 *  @author   Frode Haug, NTNU
 */


#include <iostream>                 //  cout
#include <iomanip>                  //  setw
using namespace std;


const int N = 16;                   ///<  Arrayens lengde.

int gAntallLosninger;               ///<  Antall løsninger funnet (hittil).
                                    //    Det er 7040 løsninger (speilinger
                                    //      og rotasjoner inkludert).
                                    //    Det er 416 løsninger når '1' står
                                    //      fast i øvre venstre hjørne.
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
                             //    (for å vise at origisnal er gjenopprettet).

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
    cout << "\nLøsning nr." << ++gAntallLosninger << ":";
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
 *  @param   i    -  Indeksen som ALLE ETTERFØLGENDE verdier skal flyttes til
 *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
 *  @see     bytt(...)
 *  @see     display()
 *  @see     rettSum(...)
 *  @see     roterVenstre(...)
 */
void permuter(int arr[], const int i, const int n) {
    if (i == n-1  &&  rettSum(arr, i))  //  Nådd en ny LOVLIG permutasjon:
        display(arr, n);                //  Skriver ut arrayens innhold.
    else {                              //  Skal permutere:
                                        //  Ikke på slutten av en linje,
                                        //    eller siste linjesum = 34 !!!
        if ((i+1) % 4 != 0  ||  rettSum(arr, i))
           permuter(arr, i+1, n);       //  Beholder nåværende nr.'i'.
                                        //  Permuterer resten.
        for (int t = i+1;  t < n;  t++) {
            bytt(arr[i], arr[t]);       //  Bytter nr.'i' etter tur med
                                        //    ALLE de andre etterfølgende.
                                        //  Ikke på slutten av en linje,
                                        //    eller siste linjesum = 34 !!!
            if ((i+1) % 4 != 0 || rettSum(arr, i))
               permuter(arr, i + 1, n); //  For hver av ombyttene: permuterer
        }                               //     resten av de etterfølgende.
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
 *  @param   arr  -  Arrayen som får (deler av) sitt innhold venstrerotert
 *  @param   i    -  Laveste indeks som skal venstreroteres
 *  @param   n    -  'n-1' er høyeste indeks som venstreroteres
 */
void roterVenstre(int arr[], const int i, const int n) {
    int venstreVerdi = arr[i];            //  Tar vare på første.
    for (int k = i + 1; k < n; k++)       //  Roterer (flytter alle ned
        arr[k - 1] = arr[k];                //     ETT hakk/indeks).
    arr[n - 1] = venstreVerdi;              //  Legger første inn bakerst.
}
