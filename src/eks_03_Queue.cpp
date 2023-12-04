/**
 *   Programeksempel nr 3 - Queue (selvlaget enkel klasse).
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen Queue.
 *   Det er laget kode for følgende funksjoner:
 *
 *     -  Queue(const int lengde = 200)
 *     -  ~Queue
 *     -  void  display()
 *     -  bool  empty()
 *     -  T     get()
 *     -  void  put(const T t)
 *
 *     (IKKE laget funksjonene:  int capacity(),  void clear(),  int size(),
 *      men disse er HELT identiske til EKS_01_Vector.cpp.
 *      unntatt 'clear' som må endres LITT.)
 *
 *   NB: For å formodentlig øke leseligheten og oversikten er medlems-
 *       funksjonene bevisst IKKE kommentert etter Doxygen-standarden.
 *
 *   @file     EKS_03_Queue.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;


/**
 *  Container-klassen Queue, som er en selvlaget versjon av STLs <queue>.
 *
 *  Inneholder en array av typen 'T', og to int'er som angir total
 *  kapasitet/lengde (capacity), det nåværende antallet (size) og
 *  indeksene for henholdsvis første element og hvor neste (siste) skal inn.
 */
template <typename T>                //  'T': fleksibel datatype!
class Queue {

  private:
      T*  data;                      //  PEKER til array av typen 'T'.
      int kapasitet, antall,         //  Max.lengde og nåværende antall.
          forste, siste;             //  Indeks for første/siste element.

  public:                      //  Initierer medlemmer vha. default parameter:
      Queue(const int lengde = 200) {  data = new T[lengde];
                                       kapasitet = lengde;
                                       antall = forste = siste = 0;  }


      ~Queue()  {  delete [] data;  }  // Frigir allokert memory (vha.'new').


      void display() const {         //  Skriver HELE Queuens innhold:
          int indeks = forste;
          for (int i = 0; i < antall; i++) {
              cout << indeks << ": " << data[indeks++] << "  ";
              if (indeks == kapasitet) indeks = 0;
          }
          cout << "\n\t'antall': " << antall << "\t'forste': "
               << forste << "\t'siste': " << siste << '\n';
      }


      bool empty() const  {  return (antall == 0);  }   //  Tomt eller ei.


      T get() {                //  Returnerer (om mulig) det første elementet:
          T  verdi;            //  Elementet/verdien som skal returneres.
          if (!empty()) {      //  Elementer fortsatt igjen:
              verdi = data[forste++];  //  Tar vare på første. Øker til neste.
              antall--;                //  Totalantallet telles ned.
              if (forste == kapasitet) forste = 0;  //  Wrapper til starten?!!
              return verdi;            //  Returnerer unnalagret element.
          } else
              cout << "\nQueue is empty!\n\n";      //  Egen melding ??
          return T();
      }


      void put(const T t) {  //  Legger inn (om mulig) element bakerst i køen:
          if (antall < kapasitet) {    //  Fortsatt plass:
              data[siste++] = t;       //  Legger bakerst. Øker til neste inn.
              antall++;                //  Totalantallet telles opp.
              if (siste == kapasitet) siste = 0;    //  Wrapper til starten?!!
          } else
              cout << "\nQueue is already full!\n\n";      //  Egen melding ??
      }
};


/**
 *  Hovedprogrammet:
 */
int main()  {
    Queue <int> iKo;                   //  NB:   vs.  queue <int> iKo;
    Queue <char> cKo;                  //        fra OOProg, da med liten 'q'.
    Queue <string> sKo;


    iKo.put(29);  iKo.put(22);  iKo.put(17);
    iKo.put(7);   iKo.put(6);   iKo.display();

    cout << "\nget: " << iKo.get();  cout << "  get: " << iKo.get() << '\n';
    iKo.display();

    iKo.get();    iKo.get();    iKo.get();
    iKo.display();

    iKo.get();                         //  Ved siste 'get' er det tomt.

    iKo.put(304);  iKo.put(312);  iKo.get();  iKo.display();
    iKo.get();  iKo.display();


// ======================   QUEUE MED CHAR'er:   ============================

    cKo.put('G');
    cKo.get();    cKo.get();           //  Ved siste 'get' er det tomt.


// ======================   QUEUE MED STRING'er:   ==========================
    string st;

    sKo.put("Bananmos");

    st = sKo.get();
    cout << "\nget'et tekst: '" << st << "'\n\n";

    st = sKo.get();                 //  Ved siste 'get' er det tomt:
    cout << "get'et tekst: '" << st << "'\n\n";

    return 0;
}
