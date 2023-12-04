/**
 *   Programeksempel nr 14 - Plassering av 8x dronninger på et 8x8 sjakkbrett,
 *                           uten at de klarer å slå hverandre.
 *
 *   Programmet prøver REKURSIVT å plassere MAX sjakk-dronninger USLÅTT på et
 *   MAX x MAX brett. Dvs. to dronninger kan hverken stå på samme linje (i),
 *   kolonne (j) eller diagonal, ellers "slår/tar" de hverandre.
 *
 *   NB:
 *     Programmet siler IKKE vekk løsninger som egentlig er funnet tidligere,
 *     når det som synes å være en "ny" løsning egentlig er en:
 *        - speiling om horisontal/vertikal midtlinje   og/eller
 *        - speiling om hoved-/bidiagonal (mellom motsatte hjørner)  og/eller
 *        - rotasjon (f.eks. MED klokka) på 90, 180 eller 270 grader
 *     av den allerede fundne løsningen.
 *     Dette medfører at for et 8x8 brett så vil programmet angi 92 løsninger,
 *     når det egentlig bare er 12 UNIKE løsninger. (For et NxN brett er det
 *     følgende antall IKKE-UNIKE løsninger:  4: 2,   5: 10,   6: 4,   7: 40.)
 *
 *   @file     EKS_14_DronningPlassering.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>    //  cout
using namespace std;

const int MAX = 8;     ///<  Brettets størrelse.

bool gBrett[MAX][MAX]; ///<  Sjakkbrettet. Bruker 0-(MAX-1) i begge retninger.
                       //    Hele brettet blir automatisk satt til 'false'.
int  gAntallLosninger = 0;  ///<  Teller opp antallet løsninger funnet.


/**
 *  Skriver ut brettets innhold (true = '1', false = '0').
 */
void skrivBrettet() {            //  Skriver ut brettets innhold.
    int i, j;
    char tegn;

    cout << "\n\n\nLøsning nr." << ++gAntallLosninger << ":\n\t";
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
 *  Dette gjøres ved å teste om det allerede er 'true' på vedkommende 'linje'
 *  eller en av diagonalene på kolonnene til VENSTRE for 'kolonne'.
 *
 *  @param    linje    -  Aktuell dronning sin egen plassering på 'linje'
 *  @param    kolonne  -  Aktuell dronning sin egen plassering på 'kolonne'
 *  @return   Om dronningen kan uslått stå på denne posisjonen eller ei.
 */
bool lovligPosisjon(int linje, int kolonne) {
    int i;

    for (i = 0; i < kolonne; i++)            //  Sjekker om noen annen brikke:
        if (gBrett[linje][i])  return false; //    - på samme linje:

    for (i = kolonne - 1; i >= 0; i--) {     //    - på en av diagonalene:
        if (linje - (kolonne - i) >= 0)            //  Dersom inne på brettet:
            if (gBrett[linje - (kolonne - i)][i])  //  Opptatt på diagonal
                return false;                      //    OPP til venstre.
        if (linje + (kolonne - i) < MAX)           //  Dersom inne på brettet:
            if (gBrett[linje + (kolonne - i)][i])  //  Opptatt på diagonal
                return false;                      //    NED til venstre.
    }
    return true;                                   //  Uslått plassering.
}


/**
 *  Prøver rekursivt å plassere en dronning etter tur i ALLE
 *  lovlige posisjoner på kolonne 'j'.
 *
 *  @param   j  -  Kolonnen dronningen skal forsøkes uslått å plasseres på.
 */
void settDronning(int j) {
    int i;
    if (j == MAX)              //  Brettet er fullt, dvs. nådd en løsning.
       skrivBrettet();         //  Skriver/tegner løsningen.
    else
       for (i = 0; i < MAX; i++)     //  Går gjennom ALLE linjene på kolonnen:
                                     //  1.kolonne eller lov å plassere:
          if (j == 0  ||  lovligPosisjon(i, j)) {
             gBrett[i][j] = true;    //  Setter posisjonen som opptatt.
             settDronning(j + 1);    //  Plasserer dronning på neste kolonne.
             gBrett[i][j] = false;   //  Frigir posisjonen - BACKTRACKER !!!
          }
}


/**
 *  Hovedprogrammet:
 */
int main() {

    settDronning(0);                         //  Finner løsninger ?

    if (gAntallLosninger == 0)               //  Ingen løsninger funnet.
        cout << "\n\nINGEN LØSNINGER !";

    cout << "\n\n";
    return 0;
}


/*
  ALTERNATIV LØSNING:
     Problemet kunne også ha vært løst ved permutasjon (forelesning 9a) av
     tallene 0 til MAX-1. Indeksen/elementnummeret angir kolonnenummer,
     mens tallet som står på den aktuelle plassen angir linjenummeret.
     Dermed slipper man å teste på om to dronninger står på samme linje
     (så lenge alle tallene er unike). Man må "bare" teste at ingen nabotall
     er +/- 1 (en) ift. tilhverandre, at ingen med avtand to imellom er
     +/- 2 (to) ift hverandree, osv..... oppover til MAX-1.

     Avskjæringene ovenfor (speilinger/rotasjoner) kunne ha vært ivaretatt
     ved å utføre ulike transformasjoner på den permuterte arrayen. Dersom
     en ny array som således fremkommer totalt utgjør et tall (av alle sifrene
     0-9 i den) som er mindre enn den permuterte arrayens tall, så har man
     allerede funnet (og skrevet ut) denne løsningen tidligere.
*/
