/**
 *   Programeksempel nr 44 - Algoritmisk problem - case 5.
 *
 *   For programmets funksjonalitet se:  AlgCase5.pdf
 *
 *  (Dette var oppg.nr.4 p� eksamen 19/12-1996 i L171A-Algoritmiske metoder I)
 *
 *   @file     EKS_44_Alg_Case5.CPP.
 *   @author   Frode Haug, NTNU
 */


#include <iostream>            //  cout
#include <fstream>             //  ifstream
using namespace std;


const int MAXONSKER =   3;     ///<  Max. antall �nsker for EN person.
const int MAXGJENST = 200;     ///<  Max. antall gjenstander til fordeling
const int MAXPERS   = 100;     ///<  Max. antall personer som har �nsker.


int  gAntPersoner,             ///<  Aktuelt antall personer.
     gAntGjenstander;          ///<  Aktuelt antall gjenstander til fordeling.

int  gOnsker[MAXPERS][MAXONSKER];  ///<  Personenes tre �nsker.
int  gGjenstand[MAXGJENST];        ///<  �yeblikkets gjenstandfordeling.
int  gBesteFordeling[MAXGJENST];   ///<  Beste fordeling av gjenstander.
bool gLosningFunnet = false;       ///<  Noen l�sning funnet?
int  gBestePrioritet = (MAXPERS*MAXONSKER)+1;   ///<  Beste TOTALE prioritet.
int  gTotalPrioritet = 0;                       ///<  N�v�rende totale prior.


/**
 *  Leser inn antall gjenstander/personer og bruker�nskene fra fil.
 */
void lesFraFil()  {         //  Leser �nskene fra fil:
  ifstream innfil("EKS_44_ONSKER.DTA");

  if (innfil) {                  //  Filen funnet:
                                 //  Leser antall gjenstander og personer:
     innfil >> gAntGjenstander >> gAntPersoner;
                                 //  Minst en verdi utenfor aktuelt intervall:
     if (gAntGjenstander < 0  ||  gAntGjenstander >= MAXGJENST  ||
         gAntPersoner < 0     ||  gAntPersoner >= MAXPERS)
	     cout << "\n'gAntGjenstander' / 'gAntPersoner' i feil intervall\n";
     else                        //  Leser og lagrer personenes tre �nsker:
        for (int i = 0;  i < gAntPersoner;  i++) {
            innfil >> gOnsker[i][0] >> gOnsker[i][1] >> gOnsker[i][2];
                                 //  Bruker�nsker 1,2,.. lagres som 0, 1, ...:
            gOnsker[i][0]--;   gOnsker[i][1]--;   gOnsker[i][2]--;
        }

  } else
    cout << "\n\n\tFant ikke filen 'EKS_44_ONSKER.DTA'!\n\n";
}


/**
 *  Kopierer alle brukte elementer fra en array og over til en annen array.
 *
 *  @param   arrFra  -  Arrayen det kopieres FRA
 *  @param   arrTil  -  Arrayen det kopieres TIL
 */
void kopier(const int arrFra[], int arrTil[])  {
  for (int i = 0;  i < gAntGjenstander;  i++)   arrTil[i] = arrFra[i];
}


/**
 *  (Om mulig) optimal (rekursiv) fordeling av gjenstander til personer.
 *  NB: Genererer ALLE mulige kombinasjoner av fordeling av gjenstandene
 *      (unntatt de som blir avskj�rt, da ny bestenotering ikke kan oppn�s).
 *
 *  @param   n  -  Personnummeret det skal fordeles gjenstand til
 */
void fordelGjenstander(const int n)  {
  if (n == gAntPersoner)  {                  //  Ny beste fordeling funnet:
     gLosningFunnet = true;                  //  Minst en l�sning funnet.
     gBestePrioritet = gTotalPrioritet;      //  Oppdaterer beste pri.totalt.
     kopier(gGjenstand, gBesteFordeling);    //  Lagrer unna den hittil beste.
  }  else  {
     for (int i = 0;  i < MAXONSKER;  i++)  //  G�r gjennom en brukers �nsker:
	   if (!gGjenstand[gOnsker[n][i]])  {   //  Gjenstanden er IKKE opptatt:
	      gTotalPrioritet += (i+1);         //  Teller opp total-prioriteten.
                                       //  NB:  AVSKJ�RING:
	      if (gTotalPrioritet < gBestePrioritet) { //    Ny rekord mulig?
	         gGjenstand[gOnsker[n][i]] = n+1;      //  Gjenstanden er opptatt.
	         fordelGjenstander(n+1);               //  Neste evt. tildeles.
	         gGjenstand[gOnsker[n][i]] = 0;        //  Setter som ledig igjen.
	      }
	      gTotalPrioritet -= (i+1);    //  Teller ned igjen total-prioriteten.
	   }
  }
}


/**
 *  Hovedprogrammet:
 */
int main ()  {

   lesFraFil();

   fordelGjenstander(0);

   if (gLosningFunnet)  {
      cout << "\n\n" << gAntGjenstander << " gjenstander til fordeling p� "
           << gAntPersoner << " personer:\n\n";
      cout << "Totalt beste prioritet ble " << gBestePrioritet
           << ", i forhold til minimumet som er " << gAntPersoner
           << ".\n\nBeste l�sning er:\n";
      for (int i = 0;  i < gAntGjenstander;  i++)  {
	      cout << "\tGjenstand nr."  << i+1 << " til ";
	      if (gBesteFordeling[i])
	         cout << "person nr." << gBesteFordeling[i] << '\n';
          else
             cout << "INGEN\n";
      }
   } else
     cout << "\n\nIngen fordeling mulig, da for mange "
	  << "personer �nsker seg de samme gjenstandene!";

   cout << "\n\n";
   return 0;
}
