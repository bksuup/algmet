/**
 *  Programeksempel nr 27 - S�king - sekvensielt og bin�rt i (u)sortert array.
 *
 *   Eksemplet viser s�king i en:
 *        - USORTERT array, vha. sekvensielt s�k
 *        - SORTERT array, vha. bin�rt s�k
 *
 *   Orden ( O(...)):
 *        - SEKVENSIELT s�k i USORTERT array:
 *             - N+1 sammenligninger (alltid) ved ikke-funn
 *             - N/2 sammenligninger (i gjennomsnitt) ved funn
 *        - BIN�RT s�k i SORTERT array:
 *             - Ikke mer enn  lgN + 1  sammenligninger for s�k
 *               som B�DE gir funn og ikke-funn
 *
 *        - For en SORTERT LISTE, M� man lete sekvensielt.
 *          Da hadde ordenen (gjennomsnittlig) blitt
 *          N/2  sammenligninger, b�de ved funn og ikke-funn
 *          (for man slutter � lete der den ER/BURDE HA V�RT).
 *
 *   @file     EKS_27_Soking.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <iomanip>           //  setw
#include <cstdlib>           //  (s)rand
using namespace std;


const int N = 20;            ///<  Antall elementer i arrayen det s�kes i.


void display(const int arr[], const int n);
int  sokBinert(const int arr[], const int verdi, const int n);
int  sokSekvensielt(const int arr[], const int verdi, const int n);


/**
 *  Hovedprogrammet:
 */
int main() {
    int array[N+1];                //  Array som skal sorteres.
                                   //  Bruker indeksene 1 til N,
                                   //   da 0 (null) betyr: "Intet funn".

    srand(0);                      //  Brukes ifm. tilfeldighet/randomisering.

    for (int i = 1;  i <= N;  i++) //  Array med tilfeldige tall 1-100:
        array[i] = (rand() % 100) + 1;

    cout << "\n\nArrayen m/indekser:\n";
    display(array, N);

    cout << "\n54 har indeks nr." << sokSekvensielt(array, 54, N) << '\n';
    cout << "\n56 har indeks nr." << sokSekvensielt(array, 56, N) << '\n';
    cout << "\n39 har indeks nr." << sokSekvensielt(array, 39, N) << '\n';
    cout << "\n17 har indeks nr." << sokSekvensielt(array, 17, N) << '\n';
    cout << "\n 4 har indeks nr." << sokSekvensielt(array,  4, N) << '\n';


// ***************************************************************************

    for (int i = 1; i <= N; i++)  //  Omgj�r til en sortert array med partall.
        array[i] = i*2;

    cout << "\n\n\nSORTERT arrayen m/partall:\n";
    display(array, N);

    cout << "\n24 har indeks nr." << sokBinert(array, 24, N) << '\n';
    cout << "\n 8 har indeks nr." << sokBinert(array,  8, N) << '\n';
    cout << "\n 7 har indeks nr." << sokBinert(array,  7, N) << '\n';
    cout << "\n98 har indeks nr." << sokBinert(array, 98, N) << '\n';

    cout << "\n\n";
    return 0;
}


/**
 *  Skriver ut hele en arrays innhold.
 *
 *  @param   arr      -  Arrayen som f�r hele innholdet skrevet ut
 *  @param   n        -  Antall elementer i 'arr'
 */
void display(const int arr[], const int n) {
    cout << ' ';
    for (int i = 1;  i <= n;  i++)                  //  Skriver indeksene:
        cout << setw(3) << i << ':';   cout << '\n';
    for (int i = 1;  i <= n;  i++)                  //  Skriver array-innhold:
        cout << setw(4) << arr[i];     cout << '\n';
}


/**
 *  S�ker BIN�RT i en SORTERT array.
 *
 *  @param    arr    - Sortert array som det skal s�kes i
 *  @param    verdi  - Verdien det skal letes etter indeksen for i 'arr'
 *  @param    n      - Antall elementer i 'arr'
 *  @return   Indeksen i 'arr' der 'verdi' ble funnet (0-null om ikke funnet)
 */
int sokBinert(const int arr[], const int verdi, const int n) {
    int venstre = 1,                       //  Initierer venstre og h�yre
        hoyre = n,                         //    yttergrenser for s�keomr�det.
        midten;                            //  MIDTEN av dette s�keomr�det.

    while (venstre <= hoyre) {       //  Fortsatt noe � s�ke i, og IKKE funn:
        midten = (venstre + hoyre) / 2;    //  Regner ut/finner midtpunktet.
                                                     //  Er dette den s�kte?
        if (verdi == arr[midten])  return midten;    //  Returnerer indeks.
                                     //  Befinner seg i venstre/h�yre halvdel?
        if (verdi < arr[midten])  hoyre = midten - 1;  //  Oppdaterer aktuell
        else venstre = midten + 1;                     //    yttergrense.
    }
    return 0;                        //  Ikke funnet:  returnerer 0 (null).
}


/**
 *  S�ker SEKVENSIELT i en USORTERT array.
 *
 *  @param    arr    - Usortert array som det skal s�kes i
 *  @param    verdi  - Verdien det skal letes etter indeksen for i 'arr'
 *  @param    n      - Antall elementer i 'arr'
 *  @return   Indeksen i 'arr' der 'verdi' ble funnet (0-null om ikke funnet)
 */
int sokSekvensielt(const int arr[], const int verdi, const int n) {
    int indeks = n + 1;                       //  Initierer til ETTER arrayen!
                                              //  S� lenge innenfor arrayen og
                                              //    IKKE funnet, leter videre:
    while (indeks > 0  &&  verdi != arr[--indeks])  ;   //  NB:  TOM INNMAT !!
    return (indeks);                          //  Returnerer indeksen eller 0.
}
