/**
 *   Programeksempel nr 11 - Eksempel p� grafikk-rekursjon.
 *
 *   Eksempel som "viser" koden for EXE-filen angitt nedenfor.
 *   Den tegner et kryss inni en ramme. Dermed oppst�r fire
 *   nye rammer. Rekursivt f�r den tegnet kryss inni disse
 *   ogs�. Slik tegnes det kryss inni kryss inntil en dybde
 *   p� MAXDEPTH inni hverandre.
 *
 *   ************************************************
 *   **  Kj�r og se EKS_11_GrafikkRekursjon.EXE    **
 *   **  (kj�rer/virker dessverre KUN p� Windows!) **
 *   ************************************************
 *
 *   @file     EKS_11_GrafikkRekursjon.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
using namespace std;


const int MAXDEPTH = 5;              ///<  Max. dybde p� kryss-tegningen.


/**
 *  Tegner (vha 'line(...)') ETT kryss inni rammen angitt av parametrene.
 *
 *  @param  x1, y1  -  �vre/nedre VENSTRE hj�rne
 *  @param  x2, y2  -  Nedre/�vre H�YRE hj�rne
 *  @param  n       -  Rekursivt kall nr.'n'  (rekursjonsniv�et)
 */
void kryss(int x1, int y1, int x2, int y2, int n) {
    int dx = (x2 - x1) / 2;                 //  Beregner midtpunktet i rammen.
    int dy = (y2 - y1) / 2;

//  line(x1 + dx, y1, x1 + dx, y2);           //  Tegner kryss MIDT i rammen.
//  line(x1, y1 + dy, x2, y1 + dy);
                        cout << n << ' ';     //  I STEDET FOR 'line(...)' !!!

    if (n < MAXDEPTH) {                       //  Tegner i de fire nye rammene
        kryss(x1, y1, x1 + dx, y1 + dy, n + 1); //   som n� har oppst�tt:
        kryss(x1 + dx, y1, x2, y1 + dy, n + 1);
        kryss(x1, y1 + dy, x1 + dx, y2, n + 1);
        kryss(x1 + dx, y1 + dy, x2, y2, n + 1);
    }
}


/**
 *  Hovedprogrammet:
 */
int main()  {

//  rectangle(0, 0, 1919, 1079);      //  Tegner en ytre ramme rundt kryssene. 

    kryss(0, 0, 1919, 1079, 1);

    cout << "\n\n";
    return 0;
}