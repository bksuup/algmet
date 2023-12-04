/**
 *   Programeksempel nr 13 - Skriver linjer med ulikt antall stjerner/innrykk.
 *
 *   Eksempel som viser hvordan rekursivt skrive følgende/lage mønster:
 *
 *         *                        Dvs. ser vi dette ut fra 8-stjernene, 
 *         * *                      så skal det tegnes 4 stjerner startende
 *           *                      der 8'eren starter, og 4 stjerner fra
 *         * * * *                  midten av 8'eren.
 *             *                    For hver 4'er med stjerner, så skal det
 *             * *                  tegnes to stjerner der 4'eren starter,
 *               *                  og to stjerner fra midten av 4'eren.
 *         * * * * * * * *          For hver 2'er med stjerner, så skal det
 *                 *                tegnes en stjerne der 2'eren starter,
 *                 * *              og en stjerne fra midten av 2'eren
 *                   *              (der den altså slutter).
 *                 * * * *
 *                     *
 *                     * *
 *                       *
 *
 *   (Dette var oppg.nr.4 på eksamen 13/8-2001 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_13_SkrivStjerner.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
using namespace std;

/**
 *  Etter 'antBlanke' innledende blanke tegn, skrives 'antStjerner' stjerner.
 *
 *  @param   antStjerner  -  Antall stjerner som skal skrives/tegnes
 *  @param   antBlanke    -  Antall innledende blanke før stjernene
 */
void skrivStjerner(int antStjerner, int antBlanke) {
    int i;                               //  Løkkevariabel.

    if (antStjerner >= 1) {              //  Skal fortsatt skrive stjerner:

                                         //  Skriver halvparten så mange
                                         //    stjerner, STARTENDE I SAMME 
                                         //    KOLONNE SOM EN SELV (samme
        skrivStjerner(antStjerner/2, antBlanke);   //  antall blanke):

        for (i = 1;  i <= antBlanke;  i++)   //  Skriver innledende blanke:
            cout << "  ";

        for (i = 1;  i <= antStjerner;  i++) //  Skriver rett antall stjerner:
            cout << "* ";
        cout << '\n';                        //  Skriv linjeskift.

                                             //  Skriver halvparten så mange
                                             //   stjerner ETTERPÅ, STARTENDE       
        skrivStjerner(antStjerner/2,         //   RETT ETTER EGET MIDTPUNKT: 
                      antBlanke + (antStjerner/2));
    } 
}


/**
 *  Hovedprogrammet:
 */
int main() {

    skrivStjerner(8, 0);       //  8 kan gjerne byttes med 16, 32, 64, ...,
                               //    men da begynner utskriften å bli lang.
    cout << '\n';
    return 0;
}