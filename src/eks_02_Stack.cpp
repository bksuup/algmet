/**
 *   Programeksempel nr 2 - Stack (selvlaget enkel klasse).
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen Stack.
 *   Det er laget kode for følgende funksjoner:
 *
 *     -  Stack(const int lengde = 200)
 *     -  ~Stack
 *     -  void  display()
 *     -  bool  empty()
 *     -  T     pop()
 *     -  void  push(const T t)
 *
 *     (IKKE laget funksjonene:  int capacity(),  void clear(),  int size(),
 *      men disse er HELT identiske til EKS_01_Vector.cpp)
 *
 *   NB: For å formodentlig øke leseligheten og oversikten er medlems-
 *       funksjonene bevisst IKKE kommentert etter Doxygen-standarden.
 *
 *   @file     EKS_02_Stack.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;


/**
 *  Container-klassen Stack, som er en selvlaget versjon av STLs <stack>.
 *
 *  Inneholder en array av typen 'T', og to int'er som angir total
 *  kapasitet/lengde (capacity) og det nåværende antallet (size).
 */
template <typename T>                //  'T': fleksibel datatype!
class Stack {

  private:
      T*  data;                      //  PEKER til array av typen 'T'.
      int kapasitet, antall;         //  Max.lengde og nåværende antall.

  public:                      //  Initierer medlemmer vha. default parameter:
      Stack(const int lengde = 200)  {  data = new T[lengde];
                                        kapasitet = lengde;  antall = 0;  }


      ~Stack()  {  delete [] data;  }  // Frigir allokert memory (vha.'new').


      void display() const {         //  Skriver HELE Stackens innhold:
          for (int i = 0;  i < antall;  i++)
              cout << i << ": " << data[i] << "  ";
          cout << "\n\t'antall': " << antall << '\n';
      }


      bool empty() const  {  return (antall == 0);  }   //  Tomt eller ei.

                                     //  Returnerer (om mulig) det første/
      T pop() {                      //    øverste elementet:
          if (!empty())              //  Ikke tomt (dvs. elementer igjen):
              return (data[--antall]);     //  Siste har indeks:  antall-1
          else
              cout << "\nStack is empty!\n\n";      //  Egen melding ??
          return T();
      }

                                     //  Legger inn (om mulig) nytt første/
      void push(const T t) {         //    øverste element:
          if (antall < kapasitet)    //  Fortsatt plass til elementer:
             data[antall++] = t;     //  Legger inn først/øverst, teller opp
          else                       //    til neste indeks.
              cout << "\nStack is already full!\n\n";      //  Egen melding ??
      }
};


/**
 *  Hovedprogrammet:
 */
int main()  {
    Stack <int> iStakk;                //  NB:   vs.  stack <int> iStakk;
    Stack <char> cStakk;               //        fra OOProg, da med liten 's'.
    Stack <string> sStakk;


    iStakk.push(29);  iStakk.push(22);  iStakk.push(17);
    iStakk.push(7);   iStakk.push(6);   iStakk.display();

    cout << "\npop: " << iStakk.pop();
    cout << "  pop: " << iStakk.pop() << '\n';
    iStakk.display();

    iStakk.pop();    iStakk.pop();    iStakk.pop();
    iStakk.display();

    iStakk.pop();                      //  Ved siste 'pop' er det tomt.


// ======================   STACK MED CHAR'er:   ============================

    cStakk.push('G');
    cStakk.pop();    cStakk.pop();     //  Ved siste 'pop' er det tomt.


// ======================   STACK MED STRING'er:   ==========================
    string st;

    sStakk.push("Bananmos");

    st = sStakk.pop();
    cout << "\npop'et tekst: '" << st << "'\n\n";

    st = sStakk.pop();                 //  Ved siste 'pop' er det tomt:
    cout << "pop'et tekst: '" << st << "'\n\n";

    return 0;
}
