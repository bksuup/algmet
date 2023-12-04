/**
 *   Programeksempel nr 10 - Tre stk helt uavhengige eksempler på rekursjon.
 *
 *   Tre stk. små, korte og TOTALT uavhengige eksempler som viser
 *   rekursjon på en "enkel" måte.
 *
 *   @file     EKS_10_3xRekursjonsEks.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <string>                    //  STLs string-klasse.
using namespace std;


int fibonacci2(const int n);         //    Brukes ifm. DYNAMISK programmering.
int gFibotall[1000] = { 1, 1 };      ///<  Fibonacci-tall tatt vare på.
                                     //     (initierer KUN element nr.0 og 1!)


/**
 *  Beregner og returnerer hva n! (n-fakultet) er vha rekursjon.
 *
 *  @param    n  -  Skal finne svaret på hva 'n'-fakultet (n!) er
 *  @return   Svaret på 'n'-fakultet (n!)
 */
int fakultet(const int n) {
    if (n <= 1)  return 1;                    //   0!  =  1!  =  1
    return  n * fakultet(n-1);                //   n!  =  n * (n-1)!
}


/**
 *  Beregner og returnerer hva det n'te Fibonacci-tallet er vha rekursjon.
 *
 *  @param    n  -  Skal finne svaret på hva det n'te Fibonacci-tallet er
 *  @return   Svaret på det n'te Fibonacci-tallet
 */
int fibonacci(const int n) {
    if (n <= 1)  return 1;                    //  fib(0) = fib(1) = 1
    return (fibonacci(n-1) + fibonacci(n-2)); //  fib(n) = fib(n-1) + fib(n-2)
}


/**
 *  Snur en tekst baklengs (reverserer teksten) vha rekursjon.
 *
 *  @param   s      - Teksten som skal snus. MÅ referanseoverføres !!!
 *  @param   left   - Minste/nedre indeks i 's' som skal byttes
 *  @param   right  - Høyeste/øvre indeks i 's' som skal byttes
 */
void reverser(string & s, const int left, const int right) {
    if (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        reverser(s, left+1, right-1);
    }
}


/**
 *  Hovedprogrammet:
 */
int main()  {

    string tekst = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    cout << "\n\nTeksten:         " << tekst << '\n';
    reverser(tekst, 0, tekst.length()-1);
    cout << "Snudd baklengs:  " << tekst << '\n';


// --------------------------------------------------------------------------
//    2x standard eksempler på rekursjon i "alle" lærebøker/fremstillinger:


    cout << "\n\n5! er:     " << fakultet(5) << '\n';


// --------------------------------------------------------------------------
// Fibonacci-tall:
//  Nr:    0    1    2    3    4    5    6    7    8    9   10   11   12   13
//         1    1    2    3    5    8   13   21   34   55   89  144  233  377

    cout << "\n\nFibonacci-tall nr.44 er:     " << fibonacci(44) << "\n\n\n";





// --------------------------------------------------------------------------
//  EKSTRA - DYNAMISK PROGRAMMERING (lagrer mellomresultater/-beregninger):

    cout << "\n\nFibonacci-tall nr.44 er:   " << fibonacci2(43);

    cout << "\n\nLagrede Fibonaccitall:\n";
    for (int i = 0;  i <= 43; i++)
        cout << gFibotall[i] << "  ";
    cout << "\n\n";

    return 0;
}



/**
 *  Beregner og returnerer hva det n+1'te Fibonacci-tallet er
 *    vha rekursjon OG DYNAMISK PROGRAMMERING.
 *
 *  @param    n  -  Skal finne svaret på hva det n+1'te Fibonacci-tallet er
 *  @return   Svaret på det n+1'te Fibonacci-tallet
 */
int fibonacci2(const int n) {
    if (gFibotall[n] == 0)
       gFibotall[n] = fibonacci2(n-1);
    return (gFibotall[n] + gFibotall[n-1]);
}
