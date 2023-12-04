/**
 *   Programeksempel nr 6 - Beregner/finner svaret på et postfix regneuttrykk.
 *
 *   Eksempel som viser bruk av stack i et helt konkret og praktisk tilfelle:
 *   Et postfix regneuttrykk leses og svaret på det beregnes/finnes.
 *   EKS_05_InfixTilPostfix.cpp gjør om infix-uttrykk til et postfix-uttrykk.
 *
 *   F.eks.  Svaret på   8 12 + 17 4 + *    er   420
 *
 *   Algoritme: - når finner '+' eller '*'  pop'es to tall/operander og
 *                deres sum/produkt beregnes og svaret push'es
 *              - når finner sifre, bygger dette evt. til et sammenhengende
 *                tall, og dette tallet push'es til slutt
 *
 *   NB: Postfix-utrykket MÅ ha minst EN blank etter hvert tall og operator,
 *       unntatt den aller siste operatoren.
 *
 *   @file     EKS_06_PostfixTilSvar.CPP
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
void skriv(stack <int> st)  {
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
    stack <int> stakk;                      //  Stakk med int'er.
    char tegn;                              //  Innlest tegn fra tastaturet.
    int  tall;

    cout << "\n\nSkriv et postfix-regneuttrykk:\n";
                                            //  Leser ALLE tegn, også ' '
    while ((tegn = cin.get()) != '\n') {    //    (blank), frem til '\n':
        tall = 0;                           //  Nullstiller.
        while (tegn == ' ') tegn = cin.get();  //  Skipper evt. flere blanke.

        if (tegn == '+')  {                       //  '+' er funnet:
            tall  = stakk.top();    stakk.pop();  //  Adderer 2x int'er øverst
            tall += stakk.top();    stakk.pop();  //    på stakken:
        } else if (tegn == '*') {                 //  '*' er funnet:
            tall = stakk.top();    stakk.pop();   //  Ganger 2x int'er øverst
            tall *= stakk.top();    stakk.pop();  //    på stakken:
        }

        while (tegn >= '0'  &&  tegn <= '9')  {   //  Bygger flersifret tall:
                                                  //  Ganger med ti, og legger
            tall = (10 * tall) + (tegn - '0');    //    til siffer bakerst.
            tegn = cin.get();                     //  Leser neste siffer?
        }

        stakk.push(tall);              //  Pusher UTREGNET ELLER OPPBYGD tall.

//        skriv(stakk);
    }
                                //  Kun ETT tall igjen på stakken - svaret(!):
    cout << "\n\nSvaret er:  " << stakk.top() << "\n\n";
    stakk.pop();

    return 0;
}
