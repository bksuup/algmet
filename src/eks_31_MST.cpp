/**
 *   Programeksempel nr 31 - MST.
 *
 *   Vi ser her på VEKTEDE grafer.
 *
 *   Eksemplet viser EN implementasjon av MST (Minimum-Spanning-Tree)
 *   - Prims algoritme, på en (liten) vektet graf.
 *
 *   Hovedideen:
 *     Gitt en eller annen inndeling av en graf i to komponenter/subgrafer.
 *     Minimums spenntreet vil da inneholde DEN kanten som har lavest vekt
 *     mellom de to komponentene.
 *
 *   Algoritme/virkemåte:
 *     1. Noder er enten:
 *           - i det hittil oppbygde minimums spenntreet (MST),
 *           - på Fringen eller
 *           - USETT
 *     2. Finner man en node som allerede er på Fringen:
 *           Skal den oppdateres med enda lavere vekt?
 *     3. 'gTilknytning[k]' er noden som sørget for at noden 'k':
 *           ble flyttet fra Fringen til grafen   eller
 *           fikk sin minimale verdi (vekt) på Fringen hittil
 *     4. 'gKantVekt[k]' er vekten på kanten mellom 'k' og 'gTilknytning[k]'.
 *     5. Noder på Fringen er (i 'gKantVekt') markert med negativ vekt,
 *           og USETT er et stort negativt tall (-999)
 *
 *   Orden ( O(...)):
 *     For en tynn graf (hver node har få naboer ift totalt antall noder (V)),
 *     og ved bruk av NABOLISTE, vil stegene/trinnene for å finne MST være:
 *         (E + V) * log V
 *
 *   NB: Det er som oftest mulig å konstruere flere ulike MST ut fra den samme
 *       grafen. Er en node tilknyttet andre via kanter med samme minimums-
 *       vekt, så er det bare spørsmål om hvem av dem man velger for å
 *       tilknytte den til de andre i grafen. Det er spesielt her de ulike
 *       algoritmene skiller seg, og om hvordan grensekantene mellomlagres
 *       (Fringe, Heap, (u)sortert array), ...), samt hvordan naboene er
 *       representert (naboliste eller -matrise).
 *
 *   @file     EKS_31_MST.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <iomanip>           //  setw
#include "fringe.h"          //  Datatypen/-strukturen "Fringe"
using namespace std;


const int ANTNODER =     8;           ///<  Antall noder i grafen (V).
const int USETT    =  -999;           ///<  IKKE sett - "stort" negativt tall.


void finnMST(int nr);
void skriv();


int  gNaboMatrise[ANTNODER+1][ANTNODER+1]  ///<  Nabomatrise for grafen:
   = { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },      //    NB:  Bruker IKKE indeks 0 !!!
       { 0, 0, 3, 2, 0, 0, 0, 1, 0 },   // A = 1     B -------- F -------- H
       { 0, 3, 0, 0, 0, 0, 2, 0, 0 },   // B = 2     |     2    |   3    / |
       { 0, 2, 0, 0, 0, 1, 0, 3, 0 },   // C = 3    3|         2|       /  |
       { 0, 0, 0, 0, 0, 2, 0, 3, 1 },   // D = 4     |     1    |     2/   |
       { 0, 0, 0, 1, 2, 0, 0, 1, 0 },   // E = 5     A -------- G------    | 1
       { 0, 0, 2, 0, 0, 0, 0, 2, 3 },   // F = 6     |        / | \        |
       { 0, 1, 0, 3, 3, 1, 2, 0, 2 },   // G = 7    2|  ------  |  ------  |
       { 0, 0, 0, 0, 1, 0, 3, 2, 0 } }; // H = 8     | /  3    1|    3   \ |
//          A  B  C  D  E  F  G  H                   C -------- E -------- D
//                                                        1          2


Fringe gFringe;                               ///<  Lager Fringe.
int    gKantVekt[ANTNODER+1];                 ///<  'gKantVekt[k]' er kantens
int    gTilknytning[ANTNODER+1];              ///<     vekt mellom 'k' og dens
                                              ///<     'gTilknytning[k]'.

/**
 *  Hovedprogrammet:
 */
int main() {

  for (int i = 1;  i <= ANTNODER;  i++)
      gKantVekt[i] = USETT;


  finnMST(1);  //  Starter i node A. Forutsetter at man når HELE grafen fra
               //  startnoden. Dvs. den er sammenhengendem altså EN komponent.

  cout << "\n\n";
  return 0;
}


/**
 *  Finner ETT minimums spenntre for en sammenhengende graf/komponent.
 *
 *  @param   nr  -  Grafens startnode, som inni funksjonen brukes/oppdateres
 *                  til å være aktuell besøkt node
 */
void finnMST(int nr) {
   int j,
       vekt;
                              //  Noden er ny og har dermed ingen tilknytning:
   if (gFringe.update(nr, -USETT))  gTilknytning[nr] = 0;

   while (!gFringe.empty())  {  //  Fortsatt ubehandlede (på "Fringen"):
                                  cout << "\n\nOPPSTART:";      skriv();
       nr = gFringe.remove();   //  Henter den først på fringen.
       gKantVekt[nr] = -gKantVekt[nr];  //  Omgjør neg. til pos.verdi.
                                  cout << "\nNr.1 (" << char ('A'+nr-1)
                                       << ") fjernet:";         skriv();
                                  //  Den hentede er noden uten tilknytning:
       if (gKantVekt[nr] == -USETT)  gKantVekt[nr] = 0;

       for (j = 1;  j <= ANTNODER;  j++) {       //  Går gjennom alle naboer:
            vekt = gNaboMatrise[nr][j];          //  Henter kantvekt.
            if (vekt > 0  &&                     //  Er naboer  og  er på
                gKantVekt[j] < 0)  {             //    Fringen eller USETT
                                                 //    (negativ 'gKantVekt'):
                if (gFringe.update(j, vekt) ) {  //  Ny eller lavere kantvekt:
                   gKantVekt[j]    = -vekt;      //    Oppdaterer med ny vekt
                   gTilknytning[j] =  nr;        //    og ny tilknytning.
                                  cout << "\nOppdatering:";     skriv();
               }
            }
       }
   }
}


/**
 *  Skriver ut på skjermen fringen og alle globale variable (arrayer).
 */
void skriv()  {
  gFringe.display(Bokstav);               //  Fringens innhold skrives.

  cout << "\n\t\t\t";
  for (int i = 1;  i <= ANTNODER;  i++)   //  Skriver nodenavn:  A, B, C, ...
      cout << setw(5) << char('A'+i-1) << ':';
  cout << "\n\tgKantVekt:     ";
  for (int i = 1;  i <= ANTNODER;  i++)   //  Vekt på (potensiell) tilknytning
      cout << setw(6) << gKantVekt[i];
  cout << "\n\tgTilknytning:  ";
  for (int i = 1;  i <= ANTNODER;  i++)   //  Tilknyttet node ('dad').
      cout << setw(6) << ((gTilknytning[i] > 0) ?
                           char('A'+gTilknytning[i]-1) : '0');
  char ch;  cin >> ch;                    //  Venter på ett tegn og '\n'.
}
