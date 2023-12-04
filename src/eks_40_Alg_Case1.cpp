/**
 *   Programeksempel nr 40 - Algoritmisk problem - case 1.
 *
 *   For programmets funksjonalitet se:  AlgCase1.pdf
 *
 *  (Basert p� oppg.nr.4 p� eksamen 8/12-2005 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_40_Alg_Case1.CPP.
 *   @author   Frode Haug, NTNU
 */


#include <fstream>
#include <iostream>
using namespace std;


const int ANTX   = 9, ANTY = 9,  ///<  Brettets dimensjoner/st�rrelse.
          N      = ANTX*ANTY,    ///<  Totalt antall ruter p� brettet.
          STRLEN = 80;           ///<  "-----------"-linje fra/p� filen.

int gBrett[ANTX][ANTY];          ///<  Selve Sudoku-brettet.


void finnLosning(const int n);
void lesFraFil();
void skrivLosning();


/**
 *  Hovedprogrammet:
 */
int main()  {

  lesFraFil();

  finnLosning(0);

  return 0;
}


/**
 *  Finner rekursivt l�sning(ene) p� enhver l�sbar Sudoku.
 *
 *  @param   n  - Aktuelt rutenummer (0, 1, ... ANTX*ANTY) � sette tall inn i
 */
void finnLosning(const int n) {
  bool brukt[ANTX+1] = { false, false, false, false, false, false,
                         false, false, false, false }; // Tall allerede brukt.

  int i = n/ANTX, j = n%ANTY;       //  Konverterer 'n' til i=[0-8] j=[0-8] !!
  int ii, jj, k,                    //  L�kkevariable.
      tall,                         //  Aktuelt allerede brukt tall.
      dx1, dx2, dy1, dy2;           //  Aktuelt tillegg/fratrekk i 9x9-rute.


  if (n == N)                       //  Brettet er fylt ut ferdig:
      skrivLosning();               //  Skriver EN l�sning.

  else if (gBrett[i][j] == 0)  {    //  Aktuell rute er tom/ufylt:

//  ******************************************************************
//  Finner hvilke tall som allerede er brukt (og dermed er uaktuelle):

      for (jj = 0;  jj < ANTY;  jj++)  {  //  Finner tallene brukt p� raden:
          tall = gBrett[i][jj];           //  Henter evt. allerede brukt tall.
          if (tall  &&  !brukt[tall]) brukt[tall] = true; //  Setter at brukt.
      }

      for (ii = 0;  ii < ANTX;  ii++) {   // Finner tallene brukt p� kolonnen:
          tall = gBrett[ii][j];           //  Henter evt. allerede brukt tall.
          if (tall  &&  !brukt[tall]) brukt[tall] = true; //  Setter at brukt.
      }

                                          //  De brukt i AKTUELL 3x3 rute:
      ii = i % 3;  jj = j % 3;            //  Hvor 'i' og 'j' er i ruten.
      switch (ii)  {                      //  Bestemmer naborutenes relative
        case 0:  dx1 = 1;   dx2 = 2;  break;  //  posisjon ift. 'i' og 'j':
        case 1:  dx1 = -1;  dx2 = 1;  break;
        case 2:  dx1 = -2;  dx2 = -1; break;
      }
      switch (jj)  {
        case 0:  dy1 = 1;   dy2 = 2;  break;
        case 1:  dy1 = -1;  dy2 = 1;  break;
        case 2:  dy1 = -2;  dy2 = -1; break;
      }

      for (k = 1;  k <= ANTX;  k++)  {    //  G�r gjennom 3x3 ruten:
          switch(k)  {                    //  Beregner absolutt ruteindeks:
            case 1: ii = i;      jj = j;      break;
            case 2: ii = i+dx1;  jj = j;      break;
            case 3: ii = i+dx2;  jj = j;      break;
            case 4: ii = i;      jj = j+dy1;  break;
            case 5: ii = i+dx1;  jj = j+dy1;  break;
            case 6: ii = i+dx2;  jj = j+dy1;  break;
            case 7: ii = i;      jj = j+dy2;  break;
            case 8: ii = i+dx1;  jj = j+dy2;  break;
            case 9: ii = i+dx2;  jj = j+dy2;  break;
          }
          tall = gBrett[ii][jj];          //  Henter evt. allerede brukt tall.
          if (tall  &&  !brukt[tall]) brukt[tall] = true; //  Setter at brukt.
      }

//  ******************************************************************
//  Pr�ver med ALLE aktuelle/ubrukt tall i ruten, og pr�ver rekursivt
//  videre med den neste ruten, for � finne en totall�sning:

      for (k = 1;  k <= ANTX;  k++)       //  G�r gjennom ALLE tallene:
          if (!brukt[k]) {                //  Ikke brukt/pr�vd tallet:
              gBrett[i][j] = k;           //  Pr�ver med dette tallet.
              finnLosning(n+1);           //  Neste rute fylles (om mulig).
              gBrett[i][j] = 0;           //  Tar vekk igjen pr�vet tall.
         }

  } else                  //  Ruten er fylt allerede, g�r rett til neste rute:
    finnLosning(n+1);
}


/**
 *  Leser inn HELE det INITIELLE brettet fra fil.
 */
void lesFraFil()  {
  ifstream innfil("eks_40_SUDOKU.dta");
  int i, j;
  char dummy;               //  For � lese inn/skippe '|' mellom 9x9-rutene.
  char buffer[STRLEN];      //  For � lese inn/skippe "-------------"-linje.

  if (innfil)  {            //  Filen finnes:
   cout << "\n\nLeser fra filen 'EKS_40_SUDOKU.DTA' .....\n";
   for (i = 0;  i < ANTX;  i++)  {
      for (j = 0;  j < ANTY;  j+=3) {        //  Leser 3 og 3 tall ad gangen:
        innfil >> gBrett[i][j] >> gBrett[i][j+1] >> gBrett[i][j+2];
        if (j+2 < ANTY-1) innfil >> dummy;   //  Skipper '|' inne p� brettet.
      }
      innfil.ignore();                       //  Skipper prikket linje:
      if ((i==2  ||  i==5)) innfil.getline(buffer, STRLEN);
   }
  } else
    cout << "\n\n\tFant ikke filen 'EKS_40_SUDOKU.DTA'!\n\n";
}


/**
 *  Skriver ut p� skjermen HELE brettets n�v�rende innhold/l�sning.
 */
void skrivLosning()  {
   int i, j;

   cout << "\n\nL�SNING:";
   for (i = 0;  i < ANTX;  i++)  {
      cout << "\n\t";
      for (j = 0;  j < ANTY;  j++)
         cout << gBrett[i][j] << ' ';
   }
   cout << "\n\n";
}
