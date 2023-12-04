/**
 *   Programeksempel nr 41 - Algoritmisk problem - case 2.
 *
 *   For programmets funksjonalitet se:  AlgCase2.pdf
 *
 *  (Dette var oppg.nr.4 på eksamen 15/12-2014 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_41_Alg_Case2.CPP.
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


const int SLUTT = 33550336;        ///<  Det 5.perfekte tallet.


/**
 *  Finner ut om 'n' er et perfekt tall eller ei.
 *
 *  Kode delvis hentet fra:  http://rosettacode.org/wiki/Perfect_numbers
 *
 *  @param    n  -  Tallet som skal sjekkes om er perfekt eller ei
 *  @return   Om tallet 'n' er perfekt eller ei
 */
bool erPerfekt(const int n) {
   int sum = 0, slutt = n/2;       //  Initierer 2x variable.

   for (int i = 1;  i <= slutt;  i++) {  //  Går gjennom alle tall å dele med:
       if (n % i == 0) sum += i;   //  Heltallig delelig: oppsummerer.
       if (sum > n) return false;  //  Har passert forbi 'n' i summeringen.
   }

   return (sum == n);              //  Er tallet perfekt (totalsum ER tallet)?
}


/**
 *  Hovedprogrammet:
 */
int main( ) {

   cout << "De fem første perfekte tallene:\n";

   for (int tall = 1; tall <= SLUTT; tall++)    //  Går gjennom aktuelle tall:
     if (erPerfekt(tall))                       //  Perfekt!
        cout << '\t' << tall << '\n';           //  Skriver tallet.


// Når man (TIL NÅ) mener at slike perfekte tall slutter på 6 eller 28,
// så kan den siste if-setningen effektiviseres adskillig vha:

//   if ((tall % 10 == 6  ||  tall % 100 == 28)  &&  erPerfekt(tall))
//      cout << tall << '\n';

   return 0;
}
