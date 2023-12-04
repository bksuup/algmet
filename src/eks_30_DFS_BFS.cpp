/**
 *   Programeksempel nr 30 - DFS og BFS på graf.
 *
 *   Eksemplet viser både DFS (Dybde-Først-Søk) og BFS (Bredde-Først-Søk)
 *   i en (liten) graf. Det vises hvordan dette kan gjøres både vha.
 *   nabo-matrise og nabo-liste.
 *
 *   Algoritme/virkemåte:
 *        Bruker en hjelpearray ('gBesokt') som inneholder:
 *            - USETT (= 0) om en node ennå ikke er sett/besøkt.
 *            - N (= 1 til V) når noden ble sett/besøkt som nr.N.
 *              Til denne opptellingen brukes variabelen 'gBesoktSomNr'.
 *            - SENERE (= -1) om en er innom noden (dvs. delvis sett), men
 *              den skal besøkes ordentlig senere i et Bredde-Først-Søk (BFS).
 *        DFS-algoritmen er rekursiv.
 *        BFS-algoritmen er iterativ.
 *
 *   Orden ( O(...)):
 *        - DFS på en graf representert vha. nabo-MATRISE er av orden:  V*V
 *        - DFS på en graf representert vha. nabo-LISTE er av orden:  V+E
 *
 *   NB:  - Nodenes ID/nr er konvertert til indeksintervallet 0 til ANTNODER-1
 *        - Nabomatrisen for uretted graf er ALLTID en speiling omkring
 *          hoveddiagonalen (fra øvre venstre til nedre høyre hjørne).
 *        - Dersom man kommer tilbake til en node som tidligere er
 *          sett/besøkt, så inneholder (selvsagt) grafen minst en sykel.
 *        - Antall ganger hver enkelt for-løkke i main får at
 *          (gBesokt[i] == USETT) er sann, er antall komponenter i grafen.
 *
 *
 *   Dybde-Først-Søketreet for grafen i dette eksemplet (når startende i A):
 *   =======================================================================
 *
 *                     ..... A......
 *                     :   /    :  :
 *                     :  B     :  :
 *                     :/   \   :  :
 *                     C     F  :  :
 *                            \ :  :
 *                              D  :
 *                               \ :
 *                                 E
 *
 *   - Dersom dette treet traverseres
 *     - preorder:  så fås den rekkefølgen nodene ble sett/besøkt i.
 *     - postorder: så fås den rekkefølge som nodene er ferdige med å
 *                  besøke alle sine naboer.
 *   - Prikkede linjer viser kanter/rekursive kall som IKKE blir
 *     fulgt/startet. Disse går ALLTID oppover i treet!
 *   - Treet m/prikkede linjer blir derfor ENDA en måte å tegne grafen på!
 *
 *
 *   @file     EKS_30_DFS_BFS.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <queue>             //  queue
#include <vector>            //  vector
using namespace std;


const int ANTNODER =  6;             ///<  Antall noder i grafen (V).
const int USETT    =  0;             ///<  Node er IKKE sett ennå.
const int SENERE   = -1;             ///<  Innom, men ikke ferdig sett/besøkt.

void BFS(int nr);
void DFS(const int nr);
void DFS_Liste(const int nr);
void initierNaboListe();
void nullstill();
void skriv();


int  gNaboMatrise[ANTNODER][ANTNODER]       ///<  Nabomatrise for grafen:
     = { { 0, 1, 1, 1, 1, 0 },   // A = 0
         { 1, 0, 1, 0, 0, 1 },   // B = 1          E-------A-------C
         { 1, 1, 0, 0, 0, 0 },   // C = 2          |      / \      |
         { 1, 0, 0, 0, 1, 1 },   // D = 3          D------   B------
         { 1, 0, 0, 1, 0, 0 },   // E = 4          |         |
         { 0, 1, 0, 1, 0, 0 } }; // F = 5          F----------
//         A  B  C  D  E  F


int  gBesokt[ANTNODER];                     ///<  Status for node nr.i.
int  gBesoktSomNr;                          ///<  Besøkt noden som nr.X.

queue  <int> gBesokeSenere;                 ///<  Noder å besøke senere/snart.
vector <int> gNaboListe[ANTNODER];          ///<  Nabolister for samme grafen.
                                            //    ARRAY MED VECTORER !!!

/**
 *  Hovedprogrammet:
 */
int main() {
    int i;

    cout << "\n\n DYBDE-FØRST-SØK (DFS) vha. nabo-MATRISE:\n";
    nullstill();                          //  Nullstiller hjelpevariable.

    for (i = 0; i < ANTNODER; i++)        //  Går gjennom ALLE nodene:
        if (gBesokt[i] == USETT) DFS(i);  //  Besøker første USETTE påtrufne
                                          //    i HVER KOMPONENT !!!


    cout << "\n\n BREDDE-FØRST-SØK (BFS) vha. nabo-MATRISE:\n";
    nullstill();

    for (i = 0; i < ANTNODER; i++)
        if (gBesokt[i] == USETT) BFS(i);



    cout << "\n\n DYBDE-FØRST-SØK (DFS) vha. nabo-LISTE:\n";
    nullstill();
    initierNaboListe();

    for (i = 0; i < ANTNODER; i++)
        if (gBesokt[i] == USETT) DFS_Liste(i);



    cout << "\n\n";
    return 0;
}


/**
 *  Vha. BFS og nabomatrise besøkes iterativt ALLE komponentens noder.
 *
 *  @param   nr  - Indeks (0 til ANTNODER-1) for STARTNODEN i besøket
 */
 void BFS(int nr) {
    int j;                                     //  Indeks for aktuelle naboer.
    gBesokeSenere.push(nr);                    //  Legges BAKERST i besøkskø.
    while (!gBesokeSenere.empty()) {           //  Ennå noder å besøke igjen:
        nr = gBesokeSenere.front();            //  AVLES den førstes ID/nr.
        gBesokeSenere.pop();                   //  FJERNER/TAR UT fra køen.
        gBesokt[nr] = ++gBesoktSomNr;          //  Setter besøksnummeret.
        for (j = 0;  j < ANTNODER;  j++)       //  Nodens linje i matrisen:
            if (gNaboMatrise[nr][j])           //  Er nabo med nr.j,
                if (gBesokt[j] == USETT) {     //    og denne er ubesøkt:
                    gBesokeSenere.push(j);     //  Legger nabo BAKERST i køen.
                    gBesokt[j] = SENERE;       //  Setter at delvis besøkt!!!
                }
//                                              skriv();
    }
}


/**
 *  Vha. DFS og NABOMATRISE besøkes rekursivt ALLE komponentens noder.
 *
 *  @param   nr  -  Indeks (0 til ANTNODER-1) for noden som skal besøkes
 */
 void DFS(const int nr) {
    gBesokt[nr] = ++gBesoktSomNr;               //  Setter besøksnummeret.
//                                              skriv();
    for (int j = 0;  j < ANTNODER;  j++)        //  Nodens linje i matrisen:
        if (gNaboMatrise[nr][j])                //  ER nabo med nr.j:
            if (gBesokt[j] == USETT) DFS(j);    //  Nr.j er usett:  Besøker
}


/**
 *  Vha. DFS og NABOLISTE besøkes rekursivt ALLE komponentens noder.
 *
 *  @param   nr  -  Indeks (0 til ANTNODER-1) for noden som skal besøkes
 */
 void DFS_Liste(const int nr) {
    int nabo;                                   //  Aktuell nabos ID/nr.
    gBesokt[nr] = ++gBesoktSomNr;               //  Setter besøksnummeret.
//                                              skriv();
                                                //  Går gjennom naboer:
    for (unsigned int j = 0;  j < gNaboListe[nr].size();  j++)  {
        nabo = gNaboListe[nr].at(j);            //  Henter naboen ID/nr.
                                                //  Usett nabo besøkes:
        if (gBesokt[nabo-1] == USETT) DFS_Liste(nabo-1);
    }
}


/**
 *  Initierer naboliste (med "tilfeldig" rekkefølge) for eksemplets graf.
 */
 void initierNaboListe() {
    gNaboListe[0].push_back(5);    gNaboListe[0].push_back(4);
    gNaboListe[0].push_back(2);    gNaboListe[0].push_back(3);
    gNaboListe[1].push_back(3);    gNaboListe[1].push_back(1);
                                   gNaboListe[1].push_back(6);
    gNaboListe[2].push_back(2);    gNaboListe[2].push_back(1);
    gNaboListe[3].push_back(1);    gNaboListe[3].push_back(6);
                                   gNaboListe[3].push_back(5);
    gNaboListe[4].push_back(1);    gNaboListe[4].push_back(4);
    gNaboListe[5].push_back(4);    gNaboListe[5].push_back(2);
}


 /**
  *  Nullstiller/initierer de globale variablene 'gBesoktSomNr' og 'gBesokt'.
  */
 void nullstill() {
    gBesoktSomNr = 0;
    for (int i = 0;  i < ANTNODER;  i++)
        gBesokt[i] = USETT;
}


 /**
  *  Skriver ut på skjermen HELE arrayen 'gBesokt' sitt innhold.
  */
 void skriv() {
    for (int i = 0;  i < ANTNODER;  i++)
        cout << ' ' << gBesokt[i];
    cout << '\n';
}
