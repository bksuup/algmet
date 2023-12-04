/**
 *   Programeksempel nr 25 - Heap (prioritetskø) - selvlaget enkel klasse.
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen Heap.
 *   Det er laget kode for følgende funksjoner:
 *
 *     - Heap(const int lengde = 200)
 *     - ~Heap
 *     - void change(const int keyNr, const T nyVerdi)      //  Oppgave nr.15
 *     - void display()
 *     - void downHeap(T arr[], const int ant, int keyNr)
 *     - void extract(const int keyNr)                      //  Oppgave nr.15
 *     - void insert(const T verdi)
 *     - T    remove()
 *     - T    replace(const T verdi)
 *     - void upHeap(int keyNr)
 *
 *   For mer forklaring av prinsipper og koden, se:  Heap.pdf
 *
 *   Orden ( O(...)):
 *        Alle operasjonene (insert, remove, replace, upHeap, downHeap,
 *        change og extract) krever færre enn  2 lg N  sammenligninger
 *        når utført på en heap med N elementer.
 *
 *   NB:  - Det er bare funksjonene 'insert' og 'remove' som er laget
 *          litt robuste. De andre ('change', 'extraxt' og 'replace')
 *          er IKKE det.
 *        - Heapen i denne koden fungerer ut fra at det er STØRSTE element
 *          som skal være i element nr.1. Men, koden kunne enkelt ha vært
 *          omskrevet slik at den i stedet fungerer for MINSTE element.
 *        - Er en .h-fil, da skal includes og brukes av EKS_26_HeapSort.CPP
 *
 *   @file     EKS_25_Heap.H
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <limits>            //  numeric_limits::max


/**
 *  Container-klassen Heap.
 *
 *  Inneholder en array ('data') av typen 'T', to int'er som angir heapens
 *  max.lengde og nåværende antall elementer i arrayen, samt en sentinel key.
 */
template <typename T>                //  'template'!  'T': fleksibel datatype!
class Heap {
  private:
    T*  data;                        //  PEKER til array av typen 'T'.
    int lengde,                      //  Heapens max.lengde.
        antall;                      //  Nåværende antall elementer i arrayen.
    T   sentinelKey;                 //  Stopp-verdi i element nr.0.

                      //  PRIVATE funksjon - da KUN brukes av EGNE funksjoner!
                                     //  Flytter evt. initielle data[keyNr]
    void upHeap(int keyNr) {         //    opp forbi alle mindre foreldre:
        T verdi = data[keyNr];       //  Elementet som evt. flyttes opp.
        data[0] = sentinelKey;       //  Legger inn sentinel key.
        while (data[keyNr/2] < verdi) {   //  Foreldre er mindre:
            data[keyNr] = data[keyNr/2];  //  Flytter foreldre ned.
            keyNr = keyNr/2;              //  Indeksen blir foreldre sin.
        }
        data[keyNr] = verdi;         //  Setter/smetter inn der stanset.
    }

  public:
      Heap(const int len = 200)  {   //  Initierende constructor:
          data = new T[len];  lengde = len;  antall = 0;
          sentinelKey = std::numeric_limits<T>::max();
//            std::cout << "\n\nsentinelKey:  " << (int)sentinelKey << "\n\n";
    }


    ~Heap() { delete [] data; }      //  Frigir allokert memory.

                                     //  Endrer 'data[keyNr]'  til  'nyVerdi':
    void change(const int keyNr, const T nyVerdi) {

        //  LAG IMNMATEN  ifm.  Oppgave nr.15
    }


    void display() const {           //  Skriver ut HELE heapens innhold:
        for (int i = 1; i <= antall; i++)  std::cout << ' ' << data[i];
    }

                      //  Flytter evt. element ned forbi alle større barn:
                      //  MÅ HA PARAMETRE, DA OGSÅ SKAL KALLES/BRUKES UTENFRA!
    void downHeap(T arr[], const int ant, int keyNr) {
        int j;                        //  Indeksen for et av barna.
        T verdi = arr[keyNr];         //  Elementet som evt. flyttes ned.
        while (keyNr <= ant/2) {      //  De før halvveis har barn:
            j = 2 * keyNr;            //  Venstre barnet indeks.
                                      //  OM har høyre barn og dette er større,
                                      //    oppdaterer til DETS indeks:
            if (j < ant  &&  arr[j] < arr[j+1])  j++;
            if (verdi >= arr[j])      //  Aktuelt barn er IKKE større,
               break;                 //    avbryter letingen nedover.
            arr[keyNr] = arr[j];      //  Flytter opp barnet.
            keyNr = j;                //  Ny indeks blir dette barnet.
        }
        arr[keyNr] = verdi;           //  Setter/smetter inn der stanset.
    }


    void extract(const int keyNr) {  // Sletter element nr.'keyNr' fra heapen:

        //  LAG IMNMATEN  ifm.  Oppgave nr.15
    }


    void insert(const T verdi) {    //  Setter om mulig inn ny verdi i heapen:
        if (antall < lengde - 1) {  //  Er plass:
            data[++antall] = verdi; //  Settes/legges inn aller bakerst.
            upHeap(antall);         //  Evt. flyttes opp (upHeapes).
        }  else                     //  Er IKKE plass:
            std::cout << "\nHeapen er full med " << lengde
                      << " elementer (inkl. sentinel key)!\n\n";
    }

                                    //  Fjerner og returnerer (om mulig)
    T remove() {                    //    den største/første fra heapen:
        if (antall > 0) {           //  Heapen er IKKE tom:
            T verdi = data[1];      //  Lagrer unna den første.
            data[1] = data[antall--];   //  Aller bakerste flyttes HELT frem.
            downHeap(data, antall, 1);  //  DownHeaper denne.
            return verdi;           //  Returnerer den første (unnalagrede).
        }  else {                   //  Heapen ER tom:
            std::cout << "\nHeapen er helt tom - ingenting i 'remove'!\n\n";
            return sentinelKey;
        }
    }

                           //  Erstatter det første elementet med en ny verdi,
                           //    og returnere det NÅ største elementet i heapen:
    T replace(const T verdi) {
        data[0] = verdi;            //  Legger inn i element nr.0 !!!
        downHeap(data, antall, 0);  //  Downheaper.
        return data[0];             //  Største er etterpå i element nr.0!
    }                            //   Og er da ENTEN det nye (som er størst!),
};                               //    ELLER det som initielt var rota (nr.1).



//****************************************************************************
//       PROGRAMMET KAN TESTES/KJØRES SOM ET EGET PROGRAM VED Å:
//           - OMDØPE FILEN FRA .H til .CPP
//           - TA VEKK BORTKOMMENTERINGEN (/*......*/) AV 'MAIN' NEDENFOR
//****************************************************************************


/**
 *  Hovedprogrammet:
 */
/*
int main() {
  Heap <int>            heap;
//  Heap <unsigned char>  heap2;          //  Bruker 'unsigned char' !!!

  char ch;

  std::cout << "\n\nViser bruken av heapen.";
  heap.insert(1);  std::cout << "\nInsert 1 :  "; heap.display(); std::cin >> ch;
  heap.insert(5);  std::cout << "\nInsert 5 :  "; heap.display(); std::cin >> ch;
  heap.insert(2);  std::cout << "\nInsert 2 :  "; heap.display(); std::cin >> ch;
  heap.insert(6);  std::cout << "\nInsert 6 :  "; heap.display(); std::cin >> ch;
  heap.replace(4); std::cout << "\nReplace 4:  "; heap.display(); std::cin >> ch;
  heap.insert(8);  std::cout << "\nInsert 8 :  "; heap.display(); std::cin >> ch;
  heap.remove();   std::cout << "\nRemove   :  "; heap.display(); std::cin >> ch;
  heap.insert(7);  std::cout << "\nInsert 7 :  "; heap.display(); std::cin >> ch;
  heap.insert(3);  std::cout << "\nInsert 3 :  "; heap.display(); std::cin >> ch;

  std::cout << "\n\n\nTester to selvlagde funksjoner fra oppgave nr.15:\n";
  heap.change(4, 5); std::cout<<"\nChange #4 til 5: "; heap.display(); std::cin >> ch;
  heap.change(3, 1); std::cout<<"\nChange #3 til 1: "; heap.display(); std::cin >> ch;
  heap.extract(2);   std::cout<<"\nExtract #2:   ";    heap.display(); std::cin >> ch;
  heap.extract(2);   std::cout<<"\nExtract #2:   ";    heap.display(); std::cin >> ch;
  heap.extract(1);   std::cout<<"\nExtract #1:   ";    heap.display();

  std::cout << "\n\n";
  return 0;
}
*/
