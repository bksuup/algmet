/**
 *   Programeksempel nr 35 - A*.
 *
 *   Algoritme for effektivt � finne korteste/raskeste vei fra EN gitt
 *   startnode til EN spesifikk slutt-/m�lnode ("Pathfinding").
 *   Bes�ker IKKE ALLE nodene, men prim�rt de som f�rer til/mot m�let.
 *   A* er ofte brukt ifm. rutenett (spill) og kunstig intelligens.
 *
 *   Algoritme/virkem�te:
 *      A*  =  Dijkstra +  heuristikk
 *
 *      Der heuristikken omhandler � UNDERESTIMERE veien/avstanden fra
 *      n�v�rende node/rute og til m�let.
 *      Avstanden til m�let (f) er derfor SUMMEN av reell avlagt avstand fra
 *      startnoden (g, jfr.Dijkstra), PLUSS estimert avstand til m�let (h).
 *
 *   Orden ( O(...)):
 *     - Tids-kompleksiteten til A* er avhengig av heuristikk funksjonen
 *     - d = reell funnet avstand til m�let
 *     - b = forgreningsfaktoren til s�ketreet,
 *           dvs. gjennomsnittlig ut-kanter fra hver node
 *     - Beste fall:    b * d
 *     - Gjennomsnittlig/verste fall:  b**d  ('b' opph�yd i 'd')
 *
 *   NB: - Heuristikken er case-spesifikk. Den kan f.eks. v�re:
 *         Manhatten distanse, Euklidsk avstand eller hentet fra en tabell.
 *       - A* er:  Komplett,  Optimal  og  Optimalt effektiv
 *
 *   @file     EKS_35_AStar.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <cmath>                     //  sqrt
#include "fringe.h"                  //  Datatypen/-strukturen "Fringe"
using namespace std;


const int DIMENSJON =    20;         ///<  Antall ruter horisontalt/vertikalt.
const int ARRLEN    = DIMENSJON*101; ///<  Rutens nummer 'i' er indeks nr.'i'.
const int USETT     =  -999;         ///<  IKKE sett - "stort" negativt tall.
const int MAALRUTE =   1814;         ///<  Ruten det letes etter.
const int STARTRUTE =   208;         ///<  Ruten det startes � lete fra.
                                     //    Endre til f.eks. 202 eller 220

bool AStar();
int  heuristics(int nr);
void lagOgSkrivRute();

                                     //  RANDKANT RUNDT HELE RUTEBRETTET !!!
char gRutenett[DIMENSJON+2][DIMENSJON+3]  ///<  Rutenettet/grafen m/randkant:
   = { "XXXXXXXXXXXXXXXXXXXXXX",     //  Rutenumre (=ID'en for ruten/noden):
       "X        XXXXXX      X",     //   101, 102, 103, ....., 119, 120
       "X             X      X",     //   201, 202, 203, ....., 219, 220
       "X   X                X",     //   301, 302, 303, ....., 319, 320
       "X   X           X    X",     //   401, .....
       "X   X           X    X",     //   501, .....
       "X   XXXXXXX     XXX  X",     //   601, .....
       "X      X        X    X",     //   701, .....
       "X     XX        X    X",     //   801, .....
       "X     X  XXXXXXXX    X",     //   901, .....
       "X                    X",     //  1001, .....
       "X   XX XXXXXXXXXX    X",     //  1101, .....
       "X   X         X      X",     //  1201, .....
       "X   X       XXX      X",     //  1301, .....
       "X             X      X",     //  1401, .....
       "X          XXXX      X",     //  1501, .....
       "XXXXXXXXXX           X",     //  1601, .....
       "X          XXXXXX    X",     //  1701, .....
       "X   XXXX        X    X",     //  1801, .....
       "X   XXXX        XXX  X",     //  1901, 1902, 1903, ....., 1919, 1920
       "X                    X",     //  2001, 2002, 2003, ....., 2019, 2020
       "XXXXXXXXXXXXXXXXXXXXXX" };
//      0123456789012345678901


Fringe gFringe(DIMENSJON*DIMENSJON); ///<  Fringe (ihvertfall stor nok!).
int    gKantVekt[ARRLEN+1];          ///<  'gKantVekt[k]' er TOTAL vekt til
int    gTilknytning[ARRLEN+1];       ///<    'k' fra STARTRUTE via den siste
                                     ///<    naboruten 'gTilknytning[k]'.

/**
 *  Hovedprogrammet:
 */
int main() {

  for (int i = 101;  i <= (ARRLEN);  i++)   // Alle nodene settes til USETT:
      gKantVekt[i] = USETT;
                                            //  Finner(?) effektivt kort vei
  if (AStar())                              //    fra STARTRUTE til MAALRUTE.
      lagOgSkrivRute();
  else
      cout << "\n\n\tIkke mulig � finne vei fra "
           << STARTRUTE << " til " << MAALRUTE;

  cout << "\n\n";
  return 0;
}


/**
 *  Pr�ver effektivt/raskt � finne en kort vei mellom to ruter i et rutenett.
 *
 *  @return   Om fant fram fra STARTRUTE til MAALRUTE eller ei
 *  @see      heuristics(...)
 */
bool AStar() {
   int i,                       //  L�kkevariabel
       nr = STARTRUTE,          //  N�v�rende aktuelle rute/node.
       nabo,                    //  En aktuell naborute til 'nr'.
       x, y,                    //  Rutenummer omgjort til ruteindekser.
       vekt,                    //  TOTAL vekt fra STARTRUTE til 'nabo'.
       tillegg;                 //  "Kantvekten" fra 'nr' til 'nabo'.

//                              int ant = 0;

   gFringe.update(nr, -USETT);          //  Ruten er STARTRUTE,
   gTilknytning[nr] = 0;                //    og har dermed ingen tilknytning:
   gKantVekt[nr] = 0;

   while (!gFringe.empty())  {  //  Fortsatt ubehandlede (p� "Fringen"),
                                //    og enn� ikke n�dd MAALRUTE:
     nr = gFringe.remove();     //  Henter den f�rst p� fringen.
//                               cout << ++ant << ":  " << nr << '\n';
     if (nr == MAALRUTE) return true; //  N�dd MAALRUTE - avslutter letingen.
                                      //  Tilknyttes 'gTilknytning' for godt,
     gKantVekt[nr] = -gKantVekt[nr];  //    omgj�r neg. til pos. kantverdi.

     for (i = 1;  i <= 8;  i++)  {    //  For hver av naborutene:
       switch (i)  {                  //  Finner deres rutenummer/ID:
         case 1:  nabo = nr-100; tillegg = 2; break; // Rett opp.
         case 2:  nabo = nr-99;  tillegg = 3; break; // P� skr� opp til h�yre.
         case 3:  nabo = nr+1;   tillegg = 2; break; // Til h�yre.
         case 4:  nabo = nr+101; tillegg = 3; break; // P� skr� ned til h�yre.
         case 5:  nabo = nr+100; tillegg = 2; break; // Rett ned.
         case 6:  nabo = nr+99;  tillegg = 3; break; // P� skr� ned til vens.
         case 7:  nabo = nr-1;   tillegg = 2; break; // Til venstre.
         case 8:  nabo = nr-101; tillegg = 3; break; // P� skr� opp til vens.
       }
//  Evt. at for-l�kka g�r bare til 4, da det ikke er mulig � g� diagonalt:
/*       case 1:  nabo = nr-100; tillegg = 2; break; // Rett opp.
         case 2:  nabo = nr+1;   tillegg = 2; break; // Til h�yre.
         case 3:  nabo = nr+100; tillegg = 2; break; // Rett ned.
         case 4:  nabo = nr-1;   tillegg = 2; break; // Til venstre.
*/
                 //  Omgj�r rutenummeret YYXX til  XX (i 'x')  og  YY (i 'y'):
       x = nabo%100;  y = nabo/100;
                            //  Tilgjengelig naborute, og er p� Fringen/USETT:
       if ((gRutenett[y][x] != 'X')  &&  (gKantVekt[nabo] < 0))  {
          vekt = gKantVekt[nr]+tillegg;  //  Totalvekten frem til "mor" (nr)
                                         //    PLUSS "vekten" bort til 'nabo'.
                                         //  Ny eller lavere kantvekt:
                        //  LAGRER P� "Fringen" OGS� ANSL�TT/HEURISTISK
                        //    AVSTAND FRA 'nabo' til MAALRUTE !!!!:
          if (gFringe.update(nabo, vekt+heuristics(nabo)) ) {
             gKantVekt[nabo]    = -vekt; //  Oppdaterer med ny TOTALvekt
             gTilknytning[nabo] =  nr;   //    og ny tilknytning.
          }
       }
     }
   }
   return false;                         //  MAALRUTE ikke funnet.
}


/**
 *  Beregner "luftlinje-avstanden"
 *      ( = hypotenusen i en trekant, dvs. Euklidsk avstand) mellom to ruter.
 *
 *  @param    nr  -  Rutenummer/-ID
 *  @return   Beregnet "luftlinje" fra rute 'nr' til MAALRUTE
 */
int heuristics(int nr)  {   //  "Luftlinjen" fra 'nr' til 'MAALRUTE'.
   int dx = ((nr % 100) - (MAALRUTE % 100)),    //  Katet nr.1.
       dy = ((nr / 100) - (MAALRUTE / 100));    //  Katet nr.2.
   float luftlinje = sqrt((dx*dx) + (dy*dy));   //  Beregner hypotenusen.
   return (2*luftlinje);                        //  Dobler, s� lenge kantvekt
}                                               //    mot nabonoder er doblet.


/**
 *  Finner stien som er g�tt, "tegner" inn p� rutenettet og skriver ut dette.
 */
void lagOgSkrivRute()  {
  int i, j,                                       //  L�kkevariable.
      nr;                                         //  Aktuelt rutenummer.

  cout << "\n\n";

  gRutenett[STARTRUTE/100][STARTRUTE%100] = 'S';  //  Legger inn STARTRUTE
  gRutenett[MAALRUTE/100][MAALRUTE%100]   = 'M';  //    og MAALRUTE.

  nr = gTilknytning[MAALRUTE];                    //  MAALRUTE's "mor"-rute.
  while (gTilknytning[nr] != 0)  {                //  Ikke n�dd STARTRUTE:
      gRutenett[nr/100][nr%100] = '.';            //  Tegner '.' i ruten.
//                                             cout << ' ' << gKantVekt[nr];
      nr = gTilknytning[nr];                      //  'nr' blir "mor"-ruten.
  }

  for (i = 0;  i < DIMENSJON+2;  i++)  {          //  Skriver s� ut hele
    for (j = 0;  j < DIMENSJON+2;  j++)           //   rutenettets utseende:
       cout << gRutenett[i][j];
    cout << '\n';
  }
}
