/**
 *   Programeksempel nr 14 - Plassering av 8x dronninger p� et 8x8 sjakkbrett,
 *                           uten at de klarer � sl� hverandre.
 *
 *   Programmet pr�ver REKURSIVT � plassere MAX sjakk-dronninger USL�TT p� et
 *   MAX x MAX brett. Dvs. to dronninger kan hverken st� p� samme linje (i),
 *   kolonne (j) eller diagonal, ellers "sl�r/tar" de hverandre.
 *
 *   NB:
 *     Programmet siler IKKE vekk l�sninger som egentlig er funnet tidligere,
 *     n�r det som synes � v�re en "ny" l�sning egentlig er en:
 *        - speiling om horisontal/vertikal midtlinje   og/eller
 *        - speiling om hoved-/bidiagonal (mellom motsatte hj�rner)  og/eller
 *        - rotasjon (f.eks. MED klokka) p� 90, 180 eller 270 grader
 *     av den allerede fundne l�sningen.
 *     Dette medf�rer at for et 8x8 brett s� vil programmet angi 92 l�sninger,
 *     n�r det egentlig bare er 12 UNIKE l�sninger. (For et NxN brett er det
 *     f�lgende antall IKKE-UNIKE l�sninger:  4: 2,   5: 10,   6: 4,   7: 40.)
 *
 *   @file     EKS_14_DronningPlassering.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>    //  cout
using namespace std;

const int MAX = 8;     ///<  Brettets st�rrelse.

bool gBrett[MAX][MAX]; ///<  Sjakkbrettet. Bruker 0-(MAX-1) i begge retninger.
                       //    Hele brettet blir automatisk satt til 'false'.
int  gAntallLosninger = 0;  ///<  Teller opp antallet l�sninger funnet.


/**
 *  Skriver ut brettets innhold (true = '1', false = '0').
 */
void skrivBrettet() {            //  Skriver ut brettets innhold.
    int i, j;
    char tegn;

    cout << "\n\n\nL�sning nr." << ++gAntallLosninger << ":\n\t";
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++)
            cout << gBrett[i][j] << "  ";
        cout << "\n\t";
    }
    cout << "\t\t\tSkriv ett tegn .....";   cin >> tegn;
}


/**
 *  Sjekker om en dronning kan plasseres i posisjon [linje][kolonne].
 *
 *  Dette gj�res ved � teste om det allerede er 'true' p� vedkommende 'linje'
 *  eller en av diagonalene p� kolonnene til VENSTRE for 'kolonne'.
 *
 *  @param    linje    -  Aktuell dronning sin egen plassering p� 'linje'
 *  @param    kolonne  -  Aktuell dronning sin egen plassering p� 'kolonne'
 *  @return   Om dronningen kan usl�tt st� p� denne posisjonen eller ei.
 */
bool lovligPosisjon(int linje, int kolonne) {
    int i;

    for (i = 0; i < kolonne; i++)            //  Sjekker om noen annen brikke:
        if (gBrett[linje][i])  return false; //    - p� samme linje:

    for (i = kolonne - 1; i >= 0; i--) {     //    - p� en av diagonalene:
        if (linje - (kolonne - i) >= 0)            //  Dersom inne p� brettet:
            if (gBrett[linje - (kolonne - i)][i])  //  Opptatt p� diagonal
                return false;                      //    OPP til venstre.
        if (linje + (kolonne - i) < MAX)           //  Dersom inne p� brettet:
            if (gBrett[linje + (kolonne - i)][i])  //  Opptatt p� diagonal
                return false;                      //    NED til venstre.
    }
    return true;                                   //  Usl�tt plassering.
}


/**
 *  Pr�ver rekursivt � plassere en dronning etter tur i ALLE
 *  lovlige posisjoner p� kolonne 'j'.
 *
 *  @param   j  -  Kolonnen dronningen skal fors�kes usl�tt � plasseres p�.
 */
void settDronning(int j) {
    int i;
    if (j == MAX)              //  Brettet er fullt, dvs. n�dd en l�sning.
       skrivBrettet();         //  Skriver/tegner l�sningen.
    else
       for (i = 0; i < MAX; i++)     //  G�r gjennom ALLE linjene p� kolonnen:
                                     //  1.kolonne eller lov � plassere:
          if (j == 0  ||  lovligPosisjon(i, j)) {
             gBrett[i][j] = true;    //  Setter posisjonen som opptatt.
             settDronning(j + 1);    //  Plasserer dronning p� neste kolonne.
             gBrett[i][j] = false;   //  Frigir posisjonen - BACKTRACKER !!!
          }
}


/**
 *  Hovedprogrammet:
 */
int main() {

    settDronning(0);                         //  Finner l�sninger ?

    if (gAntallLosninger == 0)               //  Ingen l�sninger funnet.
        cout << "\n\nINGEN L�SNINGER !";

    cout << "\n\n";
    return 0;
}


/*
  ALTERNATIV L�SNING:
     Problemet kunne ogs� ha v�rt l�st ved permutasjon (forelesning 9a) av
     tallene 0 til MAX-1. Indeksen/elementnummeret angir kolonnenummer,
     mens tallet som st�r p� den aktuelle plassen angir linjenummeret.
     Dermed slipper man � teste p� om to dronninger st�r p� samme linje
     (s� lenge alle tallene er unike). Man m� "bare" teste at ingen nabotall
     er +/- 1 (en) ift. tilhverandre, at ingen med avtand to imellom er
     +/- 2 (to) ift hverandree, osv..... oppover til MAX-1.

     Avskj�ringene ovenfor (speilinger/rotasjoner) kunne ha v�rt ivaretatt
     ved � utf�re ulike transformasjoner p� den permuterte arrayen. Dersom
     en ny array som s�ledes fremkommer totalt utgj�r et tall (av alle sifrene
     0-9 i den) som er mindre enn den permuterte arrayens tall, s� har man
     allerede funnet (og skrevet ut) denne l�sningen tidligere.
*/
