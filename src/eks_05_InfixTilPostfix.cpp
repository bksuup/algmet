/**
 *   Programeksempel nr 5 - Infix til Postfix regneuttrykk.
 *
 *   Eksempel som viser bruk av stack i et helt konkret og praktisk tilfelle:
 *   Et infix regneuttrykk leses og omgjøres (skrives ut på skjermen) til et
 *   postfix regnuttrykk.
 *   EKS_06_PostfixTilSvar.cpp finner svaret på et slikt postfix-uttrykk.
 *
 *   F.eks.  (( 8 + 12 ) * ( 17 + 4 ))  omgjøres til:   8 12 + 17 4 + *
 *
 *   Algoritme: - pusher operatorene '+' og '*'
 *              - skriver rett ut igjen sifre/tall
 *              - pop'er og skriver operator når finner en ')' (sluttparentes)
 *              - ignorerer '('  (startparentes)
 *
 *   NB: Infix-utrykket MÅ:
 *       - være et lovlig uttrykk (med korrekt operatorbruk/antall parenteser)
 *       - kun inneholde operatorene '+' og '*' (i tillegg til '(' og ')')
 *       - starte med '(', og avslutte med ')'
 *       - ha minst EN blank ETTER hvert tall (men ikke nødvendigvis FORAN)
 *
 *   @file     EKS_05_InfixTilPostfix.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <stack>                     //  stack fra STL
using namespace std;


/**
 *  Skriver HELE en stakks innhold.
 *
 *  @param   st - KOPI av medsendt stack-container (derfor tømmes den)
 */
void skriv(stack <char> st)  {
   while (!st.empty())  {              //  Ennå elementer igjen:
       cout << ' ' << st.top();        //  Skriver den nåværende første.
       st.pop();                       //  Tar ut/fjerner den første.
   }
   cout << '\n';
}


/**
 *  Hovedprogrammet:
 */
int main()  {
    stack <char> stakk;                     //  Stakk med char'er.
    char tegn;                              //  Innlest tegn fra tastaturet.

    cout << "\n\nSkriv et infix-regneuttrykk:\n";
                                            //  Leser ALLE tegn, også ' '
    while ((tegn = cin.get()) != '\n') {    //    (blank), frem til '\n':
        if (tegn == ')') {                  //  Sluttparentes funnet:
            cout << stakk.top();            //  Skriver stakkens øverste tegn.
            stakk.pop();                    //  Tar ut/fjernet operatoren.
                                            //  Pusher '+' og '*':
        } else if (tegn == '+' || tegn == '*')  stakk.push(tegn);
                                                //  Så lenge sifre i ETT tall:
        while (tegn >= '0'  &&  tegn <= '9') {  // Skriver ut flersifret tall:
            cout << tegn;                       // Skriver ETT siffer.
            tegn = cin.get();                   // Leser neste siffer/tegn.
        }

        if (tegn != '(')                    //  Skriver ut en blank (viktig at
            cout << ' ';                    //    gjøres etter hvert tall).
//     skriv(stakk);         //  Kommenter da vekk de 3x andre cout'ene.
                             //  Ignorer duplikate utskriftslinjer!
    }

    cout << "\n\n";
    return 0;
}
