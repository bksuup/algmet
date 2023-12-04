/**
 *   Programeksempel nr 33 - (Rekursive) operasjoner på graf - case 1.
 *
 *   For programmets funksjonalitet se:  GrafCase1.pdf
 *
 *  (Dette var oppg.nr.4B på eksamen 15/12-1994 i LO164A-Algoritmiske metoder)
 *
 *   @file     EKS_33_Graf_Case1.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
using namespace std;


const int ANTKRYSS = 12;             ///<  Antall gatekryss/noder.

                                     // NB:  GRAFTEGNING NEDERST I FILEN.
int gGatenett[ANTKRYSS][ANTKRYSS] =  ///< Initierer nabomatrisen:
             { {  0, 40,  0,  0, 45,  0,  0,  0,  0,  0,  0,  0 },
               { 40,  0, 35,  0,  0, 45,  0,  0,  0,  0,  0,  0 },
               {  0, 35,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
               {  0,  0, 45,  0,  0,  0,  0, 40,  0,  0,  0,  0 },
               { 45,  0,  0,  0,  0,  0,  0,  0, 35,  0,  0,  0 },
               {  0, 45,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
               {  0,  0,  0,  0,  0, 45,  0, 45,  0,  0,  0,  0 },
               {  0,  0,  0, 40,  0,  0, 45,  0,  0,  0,  0, 40 },
               {  0,  0,  0,  0,  0,  0,  0,  0,  0, 40,  0,  0 },
               {  0,  0,  0,  0,  0, 40,  0,  0, 40,  0, 35,  0 },
               {  0,  0,  0,  0,  0,  0, 45,  0,  0,  0,  0,  0 },
               {  0,  0,  0,  0,  0,  0,  0, 40,  0,  0, 35,  0 } };

bool gKryssSett[ANTKRYSS];	  ///<  Gatekryss/node hittil besøkt/sett eller ei.


/**
 *  Finner rekursivt ut om det er en mulig vei i grafen fra 'fra' til 'til'
 *  med en viss høyde (kanten må MINST ha denne vekten).
 *
 *  @param   fra    -  Aktuell/nåværende node det søkes ut fra
 *  @param   til    -  Målnoden for hele søket ('til' forblir uforandret)
 *  @param   hoyde  -  Kantens vekt må være større eller lik 'hoyde'
 *  @return  Om det var mulig å komme frem til 'til' eller ei.
 */
bool muligVei(const int fra, const int til, const int hoyde)  {
    int i = 0;                    //  Løkkevariabel - nullstilles!
    bool funnetFrem = false;      //  Funnet/nådd 'til' eller ei.

//    cout << fra << '\n';          //  Enhver node som blir besøkt.
    gKryssSett[fra] = true;       //  Nå er 'fra' besøkt (for godt).

    if (fra != til) {                          //  IKKE nådd fram, og fortsatt
        while (!funnetFrem  &&  i < ANTKRYSS)  {  //  naboer å besøke:
          if (i != fra  &&                     //  Ikke en selv,
              gGatenett[fra][i] != 0  &&       //     er naboer,
              (!gKryssSett[i])  &&             //     naboen er IKKE besøkt
              hoyde <= gGatenett[fra][i])      //     og høyt nok i gata:
                funnetFrem = muligVei(i, til, hoyde); //  Besøker nabokrysset.
          i++;                                 //  Neste nabo.
        }
    } else
      funnetFrem = true;                    //  Funnet fram til aktuelt kryss.

    if (funnetFrem) cout << fra << "  ";    //  Skriver nodeindeks på vei
                                            //    tilbake i rekursjonen.
    return funnetFrem;                 //  Returnerer om funnet frem eller ei.
}


/**
 *  Hovedprogrammet:
 */
int main() {

    cout << "\n\n";

    if (!muligVei(2, 3, 35))
        cout << "Ikke mulig å finne en kjørbar vei!";

    cout << "\n\n";
    return 0;
}


/*  Grafen/gatenettet ser slik ut:

                  40                 35                  45
      ( 0 )<<---------->>( 1 )<<---------->>( 2 )<<------------( 3 )
        ^                  ^                                     ^
        |                  |                                     |
        |45                |45                                   |40
        |                  |                                     |
        V                  V         45                  45      V
      ( 4 )              ( 5 )<<------------( 6 )<<---------->>( 7 )
        |                  ^                  ^                  ^
        |                  |                  |                  |
        |35                |40                |45                |40
        |                  |                  |                  |
        V         40       |         35       |          35      V
      ( 8 )<<---------->>( 9 )------------>>( 10)<<------------( 11)

*/
