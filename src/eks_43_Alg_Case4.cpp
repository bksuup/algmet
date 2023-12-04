/**
 *   Programeksempel nr 43 - Algoritmisk problem - case 4.
 *
 *   For programmets funksjonalitet se:  AlgCase4.pdf
 *
 *  (Dette var oppg.nr.4 på eksamen 19/12-2017 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_43_Alg_Case4.CPP.
 *   @author   Frode Haug, NTNU
 */


#include <iostream>               //  cout
#include <iomanip>                //  setw
#include <cstring>                //  strlen
#include <cstdlib>                //  itoa   (evt. _itoa_s )
using namespace std;


/**
 *  Alternativ A:  Prøver å snu tallet 'n' opp/ned og returnere dette tallet.
 *
 *  @param    n  - Tall som skal forsøkes snudd opp/ned
 *  @return   Tallet snudd opp/ned (om mulig), ellers 0 (null)
 */
int snuOppNedA(int n) {
    int siffer,                   //  Bakerste/siste siffer i nåværende 'n'.
        tall = 0;                 //  Tallet som er bygd opp/ned.

    while (n > 0) {               //  Ennå igjen siffer i tallet:
        siffer = n % 10;          //  Henter det bakerste sifret.
        n = n / 10;               //  Tar vekk det bakerste sifret.
        if (siffer == 6) siffer = 9;       //  6 --> 9
        else if (siffer == 9) siffer = 6;  //  9 --> 6
                                           //  2, 3, 4, 5, 7 - "ulovlig":
        else if (siffer != 0 && siffer != 1 && siffer != 8) return 0;
        tall = tall * 10 + siffer;         //  Bygger nytt opp/ned-tall:
    }
    return tall;                  //  Returnerer opp/ned-tallet.
}



/**
 *  Alternativ B:  Prøver å snu tallet 'n' opp/ned og returnere dette tallet.
 *
 *  @param    n  - Tall som skal forsøkes snudd opp/ned
 *  @return   Tallet snudd opp/ned (om mulig), ellers 0 (null)
 */
int snuOppNedB(const int n) {
    char tekst[7];                //  Tallet omgjort til tekst.
    int i,                        //  Løkkevariabel.
        len,                      //  Tekstens lengde (antall sifre i tallet).
        tall = 0;                 //  Tallet som er bygd opp/ned.

    itoa(n, tekst, 10);           //  Gjør om tall 'n' til tekst.
    len = strlen(tekst);          //  Finner tekstens (tallets) lengde.
    for (i = 0;  i < len;  i++)   //  Går gjennom teksten (tallet 'n').
        if (tekst[i] == '6')      //  '6' gjøres om til '9':
            tekst[i] = '9';
        else if (tekst[i] == '9')    //  '9' gjøres om til '6':
            tekst[i] = '6';          //  Tallet ULIKT '0', '1' OG '8':
        else if (tekst[i] != '0'  &&  tekst[i] != '1'  &&  tekst[i] != '8')
            return 0;                //  Irrelevant å snu det opp/ned.
                                     //  Tallet KAN snus opp/ned:
    for (i = len-1;  i >= 0;  i--)   //  Baklengs bygges opp/ned-tall:
        tall = (tall * 10) + (tekst[i] - '0');

    return (tall);                   //  Returnerer opp/ned-tallet.
}


/**
 *  Hovedprogrammet:
 */
int main() {
    int i,                           //  Løkkevariabel.
        snudd,                       //  Opp/ned tallet eller 0 (null).
        antall = 0;                  //  Totalt antall opp/ned-tall.


//  Tester løsningsalternativ A:
    for (i = 1; i <= 100000; i++)    //  Går gjennom ALLE aktuelle tall:
                                     //  Mulig å snu opp/ned (ulikt null)
        if ((snudd = snuOppNedA(i)) &&  (i == snudd))   //  og er lik 'i':
           cout << '\t' << ++antall << ":" << setw(8) << snudd << '\n';

    cout << "\nAntall like opp/ned mellom 1 og 100000:  " << antall
         << "\n\n\n";


//  Tester løsningsalternativ B:
    antall = 0;
    for (i = 1; i <= 100000; i++)    //  Går gjennom ALLE aktuelle tall:
                                     //  Mulig å snu opp/ned (ulikt null)
        if ((snudd = snuOppNedB(i)) &&  (i == snudd))   //  og er lik 'i':
           cout << '\t' << ++antall << ":" << setw(8) << snudd << '\n';

    cout << "\nAntall like opp/ned mellom 1 og 100000:  " << antall
         << "\n\n\n";

    return 0;
}
