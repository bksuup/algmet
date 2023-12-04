/**
 *   Programeksempel nr 38 - Transitive Closure og Alle Shortest Paths.
 *
 *   Vi ser her på RETTEDE (og VEKTEDE) grafer.
 *
 *   ETT aktuelt aspekt er å finne ut hvilke noder som kan nås fra hvilke noder.
 *   Dette gjør vi vha. 'Transitive Closure' (Warshalls algoritme).
 *
 *   Ett ANNET aspekt er å finne ALLE korteste stier fra ENHVER node
 *   (Floyds algoritme).
 *
 *
 *   Algoritme/virkemåte:
 *    - Transitive Closure (Warshalls algoritme):
 *      Når man oppdager at det finnes en vei fra A til B (via en eller flere
 *      andre noder), så legger man inn en ny kant i nabomatrisen. Dette er
 *      'Transitive Closure'. Nabomatrisen kan da ofte bli meget TETT.
 *
 *      Warshalls algoritme sier: "Om det finnes en vei fra node x til node y,
 *      og det finnes en vei fra y til j, da finnes det en vei fra x til j."
 *      Trikset er at det er mulig å si/gjøre dette enda litt sterkere,
 *      slik at beregningen kan kan gjøres ved faktisk bare EN gjennomgang av
 *      nabomatrisen: "Om det finnes en vei fra node x til node y BARE
 *      BRUKENDE NODER MED INDEKS MINDRE ENN y, og det finnes en vei fra y
 *      til j, da finnes det en vei fra x til j BARE BRUKENDE NODER MED
 *      INDEKS MINDRE ENN y+1."
 *
 *
 *     - ALLE korteste stier fra ENHVER node (Floyds algoritme):
 *       "Den korteste veien fra node x til node j BARE BRUKENDE NODER MED
 *       INDEKS MINDRE ENN y+1 er ENTEN den korteste veien fra x til j
 *       BRUKENDE BARE NODER MED INDEKS MINDRE ENN y, ELLER, dersom det er
 *       kortere, den korteste veien fra x til Y PLUSS distansen fra y til j."
 *
 *
 *   Orden:
 *    - Transitive Closure:
 *      Dybde-Først-Søk (DFS) kan brukes for å beregne Transitive Closure
 *      for en retted graf. Da er ordenen:  O( V * (E + V) ) for en tynn graf,
 *      og  O( V * V * V)  for en tett graf.
 *
 *    - ALLE korteste stier:
 *      Ordenen for Floyds algoritme er:  O( V * V * V)
 *
 *
 *   @file     EKS_38_TransClos_AlleSP.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>      //  cout
#include <iomanip>       //  setw
using namespace std;


const int  ANTNODER = 10;           ///<  Antall noder i grafen (A-J).


int gNM1[ANTNODER][ANTNODER] =      ///<  Nabomatrisen UTEN vekter.
           //     A  B  C  D  E  F  G  H  I  J    (se grafen ALLER nederst)
              { { 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },    // A
                { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },    // B
                { 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },    // C
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },    // D
                { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },    // E
                { 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },    // F
                { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },    // G
                { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },    // H
                { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },    // I
                { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 } };  // J


int gNM2[ANTNODER][ANTNODER] =      ///<  Nabomatrisen MED vekter.
           //     A  B  C  D  E  F  G  H  I  J    (se grafen ALLER nederst)
              { { 0, 1, 0, 0, 2, 0, 0, 0, 0, 0 },    // A
                { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 },    // B
                { 0, 2, 0, 4, 0, 3, 0, 0, 0, 3 },    // C
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },    // D
                { 0, 3, 0, 0, 0, 1, 0, 0, 0, 0 },    // E
                { 0, 0, 3, 0, 1, 0, 0, 3, 0, 0 },    // F
                { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },    // G
                { 0, 0, 0, 0, 0, 3, 0, 0, 0, 0 },    // H
                { 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 },    // I
                { 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 } };  // J


/**
 *  Skriver ut arrayen 'a's innhold linjevis på skjermen.
 *
 *  @param   a  - Arrayen hvis innhold blir skrevet ut
 *  @param   n  - Arrayens dimensjoner/størrelse
 */
void display(const int a[][ANTNODER], const int n)  {
  int i, j;
  cout << "\n\t";
  for (i = 0;  i < n;  i++)  cout << setw(3) << char('A'+i);
  cout << '\n';
  for (i = 0;  i < n;  i++)  {
      cout << "\n      " << char('A'+i) << ' ';
      for (j = 0;  j < n;  j++)
          cout << setw(3) << a[i][j];
  }
}


/**
 *  Hovedprogrammet:
 */
int main()  {
  int j, x, y;
  char ch;


//  ******************************************************
//  **   Transitive Closure  (Warshalls algoritme):     **
//  ******************************************************

  for (y = 0;  y < ANTNODER;  y++)
      for (x = 0;  x < ANTNODER;  x++)
        if (gNM1[x][y])                           //  Vei fra x til y:
             for (j = 0;  j < ANTNODER;  j++)  {
               if (gNM1[y][j]  &&  !gNM1[x][j]) { //  Vei fra y til j og ennå
                                                  //  ikke funnet fra x til j:
                   gNM1[x][j] = 1;       //  Legger inn at mulig fra x til j.

//  Ekstra utskrift:
//            cout << "\n\nFra: "  << char(x+'A') << " (X: " << x << ")"
//                 << "\t\tTil: "  << char(j+'A') << " (J: " << j << ")"
//                 << "\t\tVia: "  << char(y+'A') << " (Y: " << y << ")";
//            display(gNM1, ANTNODER);
//            cin >> ch;
                 }
             }

  display(gNM1, ANTNODER);
  cout << "\n\n\nFerdig med å finne 'Transitive Closure'.\n\n";  cin >> ch;



// **************************************************************************
// **************************************************************************
// **************************************************************************


//  ******************************************************
//  **   ALLE korteste stier (Floyds algoritme):        **
//  ******************************************************

  for (y = 0;  y < ANTNODER;  y++)
      for (x = 0;  x < ANTNODER;  x++)
          if (gNM2[x][y])                        //  Vei fra x til y:
             for (j = 0;  j < ANTNODER;  j++)  {
                if (gNM2[y][j])                  //  Vei fra y til j:
                  if (!gNM2[x][j]  ||            //  Ingen vei foreløpig
                                                 //    fra x til j ELLER
                                                 //    ny kortere sti(!):
                     (gNM2[x][y]+gNM2[y][j] < gNM2[x][j]))  {  //  Oppdaterer
                         gNM2[x][j] = gNM2[x][y]+gNM2[y][j];   //  korteste
                                                               //  sti hittil.
//  Ekstra utskrift:
//            cout << "\n\nFra: "  << char(x+'A') << " (X: " << x << ")"
//                 << "\t\tTil: "  << char(j+'A') << " (J: " << j << ")"
//                 << "\t\tVia: "  << char(y+'A') << " (Y: " << y << ")";
//            display(gNM2, ANTNODER);
//            cin >> ch;
                    }
             }

  display(gNM2, ANTNODER);
  cout << "\n\n\nFerdig med å finne 'Alle korteste stier'.\n\n";

  return 0;
}


/*    Grafen i dette eksemplet er:

      G             J
      |             ^
     2|             |3
      v  1      2   v   4
      A ---> B <--> C ----> D
      |     ^      ^
     2|   /3      /3
      v /        v
      E <-----> F <---> H <--- I
           1        3       2

*/
