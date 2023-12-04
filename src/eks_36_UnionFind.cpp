/**
 *   Programeksempel nr 36 - Union-Find.
 *
 *   Noen ganger er spørsmålet om node A er i samme komponent / (sub)graf /
 *   set / ekvivalensklasse som node B (path'en imellom er uinteressant).
 *   NB:  Det bygges IKKE en lignende graf, men et tre/flere trær av de som
 *        er i samme komponent/subgraf.
 *
 *   Funksjonen 'unionerOgFinn' setter noder til å være i samme komponent
 *   om 'unioner' er lik 'true', dvs. en unionering skal skje.
 *   Er 'unioner' lik 'false' er det interessant hva funksjonen returnerer,
 *   dvs. om nodene allerede befinner seg i samme komponent eller ei.
 *
 *
 *   Algoritme/virkemåte:
 *     gForeldre[i] > 0 (=x) når node nr.'i' har 'x' som foreldre/mor
 *     gForeldre[i] = 0      når node nr.'i' ennå ikke har noen foreldre,
 *                           eller ender opp som rot for et tre
 *     unioner = true      om noder skal knyttes sammen
 *             = false     om det skal finnes ut om noder er i samme komponent
 *
 *   @file     EKS_36_UnionFind.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <iomanip>                //  setw
using namespace std;


const int ANTNODER  = 10;         ///<  Nodene har 'ID' lik  'A'-'J'  (1-10).
const int ANTKANTER = 14;         ///<  Antall kanter i grafen.


int gForeldre[ANTNODER+1];        ///<  I "skuff" nr.i er foreldre til nr.i.
                                  //  NB: MEGET viktig at alle er nullstilt!
                                  //  Bruker indeksene 1 t.o.m. ANTNODER.

                                  ///<  Grafkantene:
char gKanter[ANTKANTER][3] = { "AB", "CG", "JI", "AJ", "BD", "HB", "DC",
                               "DE", "GE", "FE", "CH", "IH", "BJ", "BC" };

/*  Grafen ser slik ut:      A------------B---------D
                             |          / | \     /   \
                             |        /   |   \  /     \
                             |      /     |     C       E----F
                             |    /       |    / \     /
                             |  /         |  /    \   /
                             |/           | /      \ /
                             J------I-----H         G
*/

void skriv();
bool unionerOgFinn(int nr1, int nr2, const bool unioner);


/**
 *  Hovedprogrammet:
 */
int main() {
    int nr1 = 0, nr2 = 0;
    char tegn = ' ';

    for (int i = 0; i < ANTKANTER; i++) {
        nr1 = static_cast <int> (gKanter[i][0]-'A'+1);
        nr2 = static_cast <int> (gKanter[i][1]-'A'+1);

        unionerOgFinn(nr1, nr2, true);            //  Unionerer.
                                                  //  Skriver nodenes navn:
        cout << '\n' << gKanter[i][0] << ' ' << gKanter[i][1] << ':';
        skriv();
        cout << "\t\t'D' og 'H' er "           //  'D' = nr.4,  'H' = nr.8
             << (!unionerOgFinn(4, 8, false) ? "IKKE " : "")  // Finnes i samme
             << "i samme komponent";                          //   komponent?
        cin >> tegn;
    }

    cout << "\n\n";
    return 0;
}


/**
 *  Skriver 'gForeldres' innhold som bokstaver og evt. antall barn i subtre.
 */
void skriv() {
    cout << '\t';
    for (int i = 1; i <= ANTNODER; i++)     //  Linje med bokstavoverskrift:
        cout << "  " << static_cast <char> (i+'A'-1);
    cout << "\n\t";
    for (int i = 1; i <= ANTNODER; i++)     //  Går gjennom 'gForeldre':
        if (gForeldre[i] > 0)               //  Inneholder foreldre:
            cout << "  " << static_cast <char> (gForeldre[i]+'A'-1);
        else if (gForeldre[i] == 0)         //  Hittil ingen foreldre:
            cout << "  -";
        else                                //  Rot for -'gForeldre[i]' noder:
            cout << setw(3) << (-gForeldre[i]);  //  KUN aktuelt ved WB.
}


/**
 *  Om 'unioner' er 'true' vil node 'nr1' og 'nr2' bli satt til å være
 *  i samme komponent, eller returneres det om de allerede ER det.
 *
 *  @param    nr1      -  Indeks for 1.node (blir mor til eller barn av 'nr2')
 *  @param    nr2      -  Indeks for 2.node (blir mor til eller barn av 'nr1')
 *  @param    unioner  -  Skal nodene havne i samme komponent eller ei
 *  @return   Er 'nr1' og 'n2' i samme komponent eller ei?
 */
bool unionerOgFinn(int nr1, int nr2, const bool unioner) {
    int i = nr1, j = nr2;                         //  Initierer indekser.

    while (gForeldre[i] > 0)  i = gForeldre[i];   //  Finner rot for i/nr1.

    while (gForeldre[j] > 0)  j = gForeldre[j];   //  Finner rot for j/nr2.

    if (unioner && (i != j))  gForeldre[j] = i;   //  Hekter evt. sammen.

    return (i == j);     //  Returnerer om i samme komponent eller ei.
                         //    (Aktuelt KUN når 'unioner' er 'false'
}                        //    dvs. ved 'Finn').
