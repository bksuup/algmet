/**
 *   Programeksempel nr 4 - List (selvlaget enkel klasse).
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen List.
 *   Det er laget kode for følgende funksjoner:
 *
 *     -  List()
 *     -  ~List
 *     -  void  display()
 *     -  bool  empty()
 *     -  bool  find(const T t)
 *     -  void  insert(const T t)
 *     -  bool  remove(const T t)
 *     -  T     removeNo(const int no)   // Fra 1-en (ikke 0-null) og oppover!
 *     -  int   size()
 *
 *   NB: For å formodentlig øke leseligheten og oversikten er medlems-
 *       funksjonene bevisst IKKE kommentert etter Doxygen-standarden.
 *
 *   @file     EKS_04_List.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <string>                    //  string
using namespace std;


/**
 *  Container-klassen List, som er en selvlaget versjon av STLs <list>.
 *
 *  Inneholder en privat struct 'Node', kun med ett datamedlem og en peker til
 *  neste i listen. I tillegg er det en peker ('hode') til starten på lista,
 *  og antall noder i listen. Lista er sortert på 'T' i stigende rekkefølge.
 */
template <typename T>                //  'T': fleksibel datatype!
class List {

  private:
      // NB  NB  NB:  "Java-struct" - se HELT TIL SLUTT på denne filen!
      struct Node {                  //  Skjult struct for liste med 'data'.
          T  data;                   //  Unnalagrede 'data'.
          Node* neste;               //  Peker til neste i listen.
          Node(const T d) { data = d;  neste = nullptr; }  //  Constructor.
      };

      Node*  hode;                 //  Dummy hode for å forenkle mye av koden.
      int    antallNoder;          //  Nåværende antall i listen.

  public:                            //  Initierer medlemmene:
      List(const T t)  {  hode = new Node(t);  antallNoder = 0;  }

      ~List()  {                     //  Destructor - sletter HELE listen:
          Node* np;                  //  Hjelpepeker til neste i listen.
          while (hode) {             //  Så lenge noe å slette:
              np = hode->neste;      //  Peker til den andre noden.
              delete hode;           //  Sletter den første noden.
              hode = np;             //  Setter 'hode' til å peke på
          }                          //     den nye første noden.
      }


      void display() const  {        //  Skriver listens innhold:
          Node* np = hode->neste;    //  Hopper over selve hodet.
          while (np) {               //  Ikke nådd listens slutt:
              cout << '\t' << np->data << '\n';  //  Skriver nodens data.
              np = np->neste;        //  Hopper/går til neste i listen.
          }
          cout << "\n\tAntall noder i listen:  " << antallNoder << '\n';
      }

                                     //  Returnerer om listen er tom eller ei:
      bool empty() const  {  return (antallNoder == 0);  }


      bool find(const T t) const  {  // Returnerer om 't' er å finne eller ei:
          Node* np = hode->neste;       //  Hopper over selve hodet.
          while (np  &&  np->data < t)  //  Blar til der noe evt. ligger:
              np = np->neste;
          return (np  &&  np->data == t);  //  Funnet eller ei?
      }


      void insert(const T t)  {      //  Setter inn ny node sortert:
          Node* np = hode,           //  Initierer til selve hodet.
              * nyNode = new Node(t);  //  Oppretter den nye noden.

                            //  Neste finnes, og den er < enn den nyeste
                            //    (dvs. ved identiske legges den nye forrest):
           while (np->neste  &&  np->neste->data < nyNode->data)
                  np = np->neste;      //  Blar frem til neste node.

           nyNode->neste = np->neste;  //  Hekter inn mellom to noder
           np->neste = nyNode;         //    (evt. helt til slutt):
           antallNoder++;              //  Øker totalantallet noder.
      }


      bool remove(const T t) {         //  Returnerer om fjernet eller ei:
          Node* np = hode,             //  Initierer til selve hodet.
              * np2 = hode->neste;     //  Initierer til etter hodet.
          while (np2  &&  np2->data < t) {  //  Blar til der evt. ligger:
              np = np2;               //  Hopper hakket etter.
              np2 = np2->neste;       //  Blar til neste.
          }

          if (np2  &&  np2->data == t) {  //  Funnet:
              np->neste = np2->neste;     //  Hekter ut 'np2':
              delete np2;                 //  Sletter noden 'np2'.
              antallNoder--;              //  Minsker totalantallet noder.
              return true;                //  Retunerer at er fjernet.
          }
          else                            //  Retunerer at er IKKE fjernet.
              return false;
      }


      T removeNo(const int no) {       //  Returnerer (om mulig) node nr.'no':
          Node* np = hode,                //  Initierer til selve hoet.
              * np2 = hode->neste;        //  Initierer til etter hodet.
          T returData;                    //  Evt. funnet nodes 'data'.
          if (no >= 1 && no <= antallNoder) {  //  'no' i rett intervall:
              for (int i = 1; i < no; i++) {  //  Blar frem til nr.'no':
                  np = np2;    np2 = np2->neste;  // Pekerne flyttes fremover:
              }
              np->neste = np2->neste;     //  Hekter ut 'np2':
              returData = np2->data;      //  Tar vare på dens 'data'.
              delete np2;                 //  Sletter noden 'np2'.
              antallNoder--;              //  Minsker totalantallet noder.
              return returData;           //  Returnerer unnalagrede 'data'.
          }
          else
              cout << "\nNumber out of bounds .....\n\n"; // Egen melding ??
          return T();
      }

                                         //  Returnerer antall noder i listen:
      int size() const  {  return antallNoder;  }
};


/**
 *  Hovedprogrammet:
 */
int main()  {
    List <string> liste("");           //  NB:   vs.  list <string> liste;
                                       //        fra OOProg, da med liten 'l'.

    liste.insert("Oslo");   liste.insert("Bergen");     liste.insert("Molde");
    liste.insert("Nas");    liste.insert("Armenistis"); liste.insert("Hamar");
    liste.display();

    cout << "\nHamar finnes";    if (!liste.find("Hamar"))  cout << " IKKE!";
    cout << "\nLarvik finnes";   if (!liste.find("Larvik")) cout << " IKKE!";
    cout << '\n';

    if (!liste.remove("Molde"))  cout << "Å fjerne 'Molde' mislyktes!\n";
    if (!liste.remove("Oslo"))   cout << "Å fjerne 'Oslo' mislyktes!\n";
                                             //  "Gjøvik" finnes ikke:
    if (!liste.remove("Gjøvik")) cout << "Å fjerne 'Gjøvik' mislyktes!\n";

    liste.display();

    cout << "Fjernet nr.3: " << liste.removeNo(3) << '\n';   liste.display();
    cout << "Fjernet nr.3: " << liste.removeNo(3) << '\n';   liste.display();
    cout << "Fjernet nr.1: " << liste.removeNo(1) << '\n';   liste.display();

                                            //  Nr.4 ikke finnes:
    liste.removeNo(4);  cout << "Fjernet nr.4:\n ";   liste.display();


// ======================   LISTE MED INT'er:   ==============================

    List <int> liste2(0);
    liste2.insert(29);     liste2.insert(17);    liste2.insert(22);
    liste2.display();

    if (liste2.remove(312) == 0)  cout << "\n\nFant ikke 312!\n";
    if (liste2.removeNo(6) == 0)  cout << "Fant ikke nr.6!\n";

    cout << "\n\n";
    return 0;
}


/*****************************************************************************

  "Java-struct":

   public class Node  {
       public  int/char/String  data;
       public  Node neste;                        //  Constructor:
       public  Node (const  int/char/String  d)  { data = d;  neste =  null; }
   }

*****************************************************************************/
