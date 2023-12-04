/**
 *   Programeksempel nr 45 - Algoritmisk problem - case 6.
 *
 *   For programmets funksjonalitet se:  AlgCase6.pdf
 *
 *   (Dette var oppg.nr.4 på eksamen 5/8-2019 i IMT2021-Algoritmiske metoder)
 *
 *   Programmet fyller og skriver ut en array med tallene fra 1 til MAXTALL.
 *   MEN: Om et tall er heltallelig delelig med 7 eller inneholder minst ett
 *        7-siffer, så erstattes det med det innlagte relevante fortløpende
 *       stigende tallet/nummeret fra begynnelsen av tallrekken/arrayen igjen.
 *   FEIL LØSNING: Det er IKKE å bare endre/telle opp antall tall som er
 *                 delelig med 7 eller inneholder sifferet '7':
 *
 *   @file     EKS_45_Alg_Case6.CPP.
 *   @author   Frode Haug, NTNU
 */


#include <iostream>              //  cout
#include <cstring>               //  strstr
#include <cstdlib>               //  itoa   (evt. _itoa_s )
using namespace std;


const int MAXTALL = 1000;        ///<  Antall tall i arrayen.


int gTall[MAXTALL+1];            ///<  Arrayen med tallene.


/**
 *  Finner ut (og returnerer) om et tall inneholder minst ett '7' eller ei
 *
 *  @param    n  -  Talltet som skal sjekkes om inneholder '7'-siffer
 *  @return   Om 'n' inneholder minst ett '7'-siffer eller ei
 */
bool inneholder7(const int n) {
    char t[10];                  //  Tallet omgjort til tekst.
    itoa(n, t, 10);              //  Gjør om tallet 'n' til teksten 't'.
    return (strstr(t, "7"));     //  Inneholder minst ett 7-siffer?
}


/**
 *  Hovedprogrammet:
 */
int main() {
    int i,                       //  Løkkevariabel
        c = 0;                   //  Teller for å hente rett tidligere tall.


    for (i = 1;  i <= MAXTALL;  i++)    //  Legger inn aktuelt tall (!!!):
        gTall[i] = (i % 7 == 0 || inneholder7(i)) ? gTall[++c] : i;

    for (i = 1; i <= MAXTALL; i++)      //  Skriver hele arrayens innhold:
        cout << "  " << gTall[i];



    c = 0;                              //  Viktig at tilbakestilles(!).
    cout << "\n\n\nDet samme, bare at spesialtilfellene "
         << "(fet og understreket) skrives på egne linjer:\n";

    for (i = 1;  i <= MAXTALL;  i++) {        //  Delelig med '7' eller
        if (i % 7 == 0 || inneholder7(i)) {   //    inneholder '7'-siffer.
            gTall[i] = gTall[++c];            //  Henter tidligere verdi/tall.
            cout << '\n' << gTall[i] << '\n';
        } else {
            gTall[i] = i;                     //  Element nr.i blir bare 'i':
            cout << "  " << gTall[i];
        }
    }

    cout << "\n\n";
    return 0;
}
