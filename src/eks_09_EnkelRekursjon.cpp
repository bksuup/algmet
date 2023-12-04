/**
 *   Programeksempel nr 9 - Grunnleggende/enkle eksempler p� rekursjon.
 *
 *   Eksempler som viser rekursjon p� en grunnleggende/enkel m�te 
 *   vha.utskrifter av tall/tegn.
 *
 **************************************************************************
 *   REKURSJON:                                                          **
 *      - Brukes n�r et problem kan deles i mindre, enklere under-       **
 *        problemer som ligner p� hverandre. Hvert underproblem kan      **
 *        l�ses ved � anvende samme teknikk. HELE problemet l�ses        **
 *        ved � KOMBINERE l�sningen p� underproblemene.                  **
 *        Dvs. dette er en form for "splitt-og-hersk"-teknikk.           **
 *      - Ifm. programmering blir dette i praksis:                       **
 *           - En funksjon som bl.a. kaller/bruker seg selv for �        **
 *             komme frem til/finne l�sningen.                           **
 *           - Funksjonen M� ha en stoppbetingelse, dvs. en situasjon    **
 *             (if-else) der IKKE kaller seg selv lengre.                **
 *      - Eks: Traversering av tr�r og grafer, permutering, Quicksort,   **
 *        sette 8x dronninger p� et sjakkbrett uten at de sl�r hverandre **
 **************************************************************************
 *
 *   @file     EKS_09_EnkelRekursjon.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
using namespace std;


const int MAXCALL = 5;               ///<  Max. antall rekursive kall. 


/**
 *  Rekursiv funksjon som evt kaller seg selv HELT til slutt (=iterasjon).
 *
 *  @param   n  -  Teller om angir hvilket rekursive kall som foreg�r 
 */
void display1(int n)  {
    cout << n << ' ';
    if (n < MAXCALL)  display1(n+1);
}


/**
 *  Rekursiv funksjon som skriver 2x ganger og evt kaller seg selv
 *  HELT til slutt (=iterasjon).
 *
 *  @param   n  -  Teller om angir hvilket rekursive kall som foreg�r
 */
void display2a(int n) {
    cout << n << ' ';
    cout << n+100 << ' ';
    if (n < MAXCALL)  display2a(n+1);
}


/**
 *  Rekursiv funksjon som skriver 2x ganger og evt kaller seg selv
 *  MELLOM de to utskriftene.
 *
 *  NB: Forskjellen p� utskriften ift. 'display2a' !!!
 *
 *  @param   n  -  Teller om angir hvilket rekursive kall som foreg�r
 */
void display2b(int n) {
    cout << n << ' ';
    if (n < MAXCALL)  display2b(n+1);
    cout << n+100 << ' ';
}


/**
 *  Rekursiv funksjon som leser ETT tegn, kaller seg selv
 *  ELLER skriver '\n', og til slutt skriver ut sitt ENE innleste tegn.
 *
 *  NB: Legg merke til den baklengse utskriften av tegnene!
 *
 *  @param   n  -  Teller om angir hvilket rekursive kall som foreg�r
 */

void display3(int n) {
    if (n <= MAXCALL*2) {
        char ch;
        cin >> ch;
        display3(n+1);
        cout << ch << ' ';
    }
    else
        cout << "\n\n";
}


/**
 *  Rekursiv funksjon som uten stoppbetingelse kaller seg selv ("br�nn").
 *
 *  NB: Programmet krasjer !!!
 */
void display4(int n) {
    cout << n << ' ';
    display4(n+1);
}


/**
 *  Hovedprogrammet:
 */
int main() {
    char tegn;

    cout << "\nskriv og deretter REKURSJON:\n\t";
    display1(1);      cin >> tegn;

    cout << "\nskriv, skriv og deretter REKURSJON:\n\t";
    display2a(1);     cin >> tegn;

    cout << "\nskriv, REKURSJON og deretter skriv:\n\t";
    display2b(1);     cin >> tegn;

    cout << "\nSkriv inn " << MAXCALL * 2 << " tegn "
         << "(lese tegn og skrive dem baklengs ut igjen):\n\t";
    display3(1);      cin >> tegn;

    cout << "\nREKURSJON uten stoppbetingelse:\n";
    display4(1);

    cout << "\n\n";
    return 0;
}