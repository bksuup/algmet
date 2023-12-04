/**
 *   Programeksempel nr 39 - Huffman koding.
 *
 *   Program som teller forekomster av ulike bokstaver i en tekst.
 *   Bygger kodingstrie, bestemmer bitmønsteret og antall bit i mønsteret
 *   for hver enkelt bokstav i teksten.
 *
 *
 *   Algoritme/virkemåte:
 *     1) Tell forekomster ('gFrekvens')
 *     2) Bestemme/fylle 'gForelder'-array / kodingstrie
 *        (Frekvensen i BLADNODENE erstattes med aktuell bokstav)
 *     3) Finne bitmønstre og dets lengder ('gKode' og 'gLengde')
 *
 *
 *   NB:
 *     - Bitmønster og indeksverdi til venstre/høyre barn:
 *                   A
 *             0 + /   \ 1  -
 *                /     \
 *               B       C
 *
 *     - Intet tre, med den samme bokstavfrekvensen, har lavere
 *       VEKTED EKSTERN STILENGDE (VES) enn et Huffman-tre.
 *       (VES = summen av: antall kanter/bit ned til enhver bladnode/bokstav
 *              ganget med antallet av denne bokstaven)
 *
 *     - Lengden til den kodede meldingen/teksten er lik den
 *       VEKTEDE EKSTERNE STILENGDEN av Huffman frekvenstreet.
 *
 *     - Må sende med kodingsarrayen (også elementene med '0').
 *       Derfor er Huffman ikke effektiv når lite data skal komprimeres.
 *     - Totalt random tegn => lik frekvens => lite å spare ved komprimering
 *
 *     - Alle funksjonene opererer på globale arrayer/variable,
 *       derfor sendes lite med som parametre.
 *
 *
 *   @file     EKS_39_Huffman.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>    //  cout
#include <iomanip>     //  setw
#include <ctype.h>     //  toupper, isalpha
#include "fringe.h"    //  Bruker "Fringe"(!) til å lagre indekser og frekvens
using namespace std;


const int ANTBOKSTAVER = 27;   ///<  Bokstavene A-Z/a-z og ' '(blank) (27 stk).


int gFrekvens[ANTBOKSTAVER*2]; ///<  Totalfrekvensen av i/under en node.
int gForelder[ANTBOKSTAVER*2]; ///<  'gForelder[i]' er "mora" til nr.'i'.
int gKode[ANTBOKSTAVER];       ///<  Bitmønster for bokstavene.
int gLengde[ANTBOKSTAVER];     ///<  Antall bit i hver bokstavs bitmønster.
int gSisteIndeks;         ///<  Siste brukte indeks i 'gForelder'/'gFrekvens'.
Fringe gFringe;           ///<  Indeks å hente (ut fra laveste frekvens).

                          //  NB: HUSK AT SISTE ANKOMNE LIGGER FØRST/ØVERST
                          //      IFT. ANDRE MED SAMME FREKVENS/FOREKOMST !!!

int  beregnVES();
void bestemForeldre();
void finnBitmonsterOgLengde();
void lesOgTellFrekvens();
void skriv(const int nr);


/**
 *  Hovedprogrammet:
 */
int main()  {

  lesOgTellFrekvens();
  skriv(1);

  bestemForeldre();
  skriv(2);

  finnBitmonsterOgLengde();
  skriv(3);

  cout << "\n\nLengden til kodet melding (VES):  " << beregnVES() << "\n\n";

  return 0;
}


/**
 *  Beregner Vekted Ekstern Stilengde (VES) for den bygde Huffman-trien.
 *
 *  @return  Antall BIT i den ferdig kodede/komprimerte meldingen
 */

int beregnVES()  {
  int sum = 0;
  for (int i = 0;  i < ANTBOKSTAVER;  i++)  { //  Går gjennom ALLE bokstavene:
      if (gFrekvens[i])
         sum += (gFrekvens[i] * gLengde[i]);
  }
  return sum;
}



/**
 *  Bygger kodingstreet/-trien (bestemmer alle nodenes foreldre/mor).
 */
void bestemForeldre() {
  int i,                     //  Løkkevariabel.
      nodeV,                 //  Indeks for venstre node til 'i'.
      nodeH;                 //  Indeks for høyre node til 'i'.

  for (i = 0;  i < ANTBOKSTAVER;  i++) // Legger inn alle bokstavenes frekvens:
    if (gFrekvens[i]) gFringe.update(i, gFrekvens[i]);
                                       // NB: 'i' er nå 'ANTBOKSTAVER' !!!
  for (  ;  !gFringe.empty();  i++)  { // Kodingstrien ennå ikke ferdig bygd:
    nodeV = gFringe.remove();  nodeH = gFringe.remove(); //  Henter to minste.
    gForelder[i] = 0;                // Nr.'i' hittil uten forelder/mor.
    gForelder[nodeV] = i;            // Blir venstre barn til 'i'.
    gForelder[nodeH] = -i;           // Blir høyre barn til 'i'.
                                     // Mor med frekvens lik summen av barnas:
    gFrekvens[i] = gFrekvens[nodeV] + gFrekvens[nodeH];
                                     // Minst en annen til også igjen:
    if (!gFringe.empty())  gFringe.update(i, gFrekvens[i]);
  }
  gSisteIndeks = i;                  // Rotas (den sistes) indeks.
}


/**
 *  Beregner bitmønsteret og antall bit for å kode hver enkelt bokstav.
 */
void finnBitmonsterOgLengde() {
    int i,                         //  Løkkevariabel.
        antBit,                    //  Antall bit for å kode en bokstav.
        monster,                   //  Binært mønster (1, 2, 4, 8, 16, 32,...)
        kode,                      //  Totalt binært mønster (int).
        mor;                       //  Indeks for forelder/mor til en node.

    for (i = 0;  i < ANTBOKSTAVER;  i++)  {  //  Går gjennom ALLE bokstavene:
         antBit = 0;                         //  Nullstiller/initierer
         kode = 0;                           //    viktige/brukte variable:
         monster = 1;
         if (gFrekvens[i])  {           //  Bokstaven forekommmer:
            for (mor = gForelder[i];    //  Initierer til bokstavens forelder.
                 mor != 0;              //  Ennå ikke nådd rota.
                 mor = gForelder[mor],  //  Hopper opp til neste forelder.
                 monster *=2,           //  Adder til '1' FORAN i mønster !!!
                 antBit++)              //  Øker antall kodingsbit med 1.
            if (mor < 0)  {             //  Er et HØYRE barn:
               kode += monster;         //  Mønsteret får en ny '1' forrest.
               mor = -mor;              //  Negativ indeks -> positiv
            }
         }
        gKode[i] = kode;                //  Lagrer bitmønsteret (int'en).
        gLengde[i] = antBit;            //  Lagrer antall bit i mønsteret.
    }
}


/**
 *  Leser og teller antall BOKSTAVER (A-Z) innskrevet av bruker.
 */
void lesOgTellFrekvens() {
  char tegn;                              //  Innlest tegn fra bufferen.
  cout << "\n\nSkriv bokstaver, avslutt med '!':\n";
  tegn = getchar();                       //  Leser ett tegn.
  while (tegn != '!')  {                  //  Ennå ikke avslutte:
    tegn = toupper(tegn);                 //  Gjør om til stor bokstav.
    if (tegn == ' ') gFrekvens[0]++;      //  Spesialbehandler ' ' (space).
    else if (isalpha(tegn))               //  Er en bokstav A-Z:
        gFrekvens[static_cast <int> (tegn-'A'+1)]++; // Teller opp forekomster.
   tegn = getchar();                      //  Leser ett tegn til.
  }
}


/**
 *  Skriver ut på skjermen innholdet i de ulike arrayene.
 *
 *  @param   nr  - Hvilke arrayer som skal skrives ut
 */
void skriv(const int nr) {
  int i, n;
                                      //  Setter for-løkkenes sluttverdi:
  n = ((nr != 2) ? ANTBOKSTAVER : gSisteIndeks+1);

  cout << "\n\n";
  if (gFrekvens[0]) cout << " ' '";   //  Skriver indeksene/bokstavene:
  for (i = 1;  i < n;  i++)
      if (gFrekvens[i])  {
         if (i < ANTBOKSTAVER) cout << setw(4) << static_cast <char> ('A'+i-1);
         else cout << setw(4) << i;
      }

  if (nr <= 2)  {                     //  Skriver frekvensen/forekomsten:
     cout << "\ngFrekvens:\n";
     for (i = 0;  i < n;  i++)
         if (gFrekvens[i]) cout << setw(4) << gFrekvens[i];
  }

  if (nr == 2)  {                     //  Skriver forelder/mor:
     cout << "\ngForelder:\n";
     for (i = 0;  i < n;  i++)
         if (gFrekvens[i]) cout << setw(4) << gForelder[i];
  }

  if (nr == 3)  {                     //  Skriver kode/bitmønsteret som 'int':
     cout << "\ngKode:\n";
     for (i = 0;  i < n;  i++)
         if (gFrekvens[i]) cout << setw(4) << gKode[i];

     cout << "\ngLengde:\n";          //  Skriver antall bit i koden:
     for (i = 0;  i < n;  i++)
         if (gFrekvens[i]) cout << setw(4) << gLengde[i];
  }
  cout << "\n\n";
}
