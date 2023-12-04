/**
 *   Programeksempel nr 4 - List (selvlaget enkel klasse).
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen List.
 *   Det er laget kode for følgende funksjoner:
 *
 *     -  List()
 *     -  void     display()
 *     -  boolean  empty()
 *     -  boolean  find(final T t)
 *     -  void     insert(final T t)
 *     -  boolean  remove(final T t)
 *     -  T        removeNo(final int no)   // Fra 1-en (ikke 0-null) og oppover!
 *     -  int      size()
 *
 *
 *   Generelt om forskjellen ift. C++-koden:  Se HELT til slutt i denne filen.
 *
 *   @file     EKS_04_List.java
 *   @author   Marius Lindvall, NTNU
 */


/**
 *  Container-klassen List, som er en selvlaget versjon av STLs <list> i C++.
 *
 *  Inneholder en privat class 'Node', kun med ett datamedlem og en referanse til
 *  neste i listen. I tillegg er det en referanse ('hode') til starten på lista,
 *  og antall noder i listen. Lista er sortert på 'T' i stigende rekkefølge.
 */
public class EKS_04_List {
    static class List<T extends Comparable<T>> {  //  'T': fleksibel datatype!
        private class Node {
            public T data;              //  Unnalagrede 'data'.
            Node neste;                 //  Peker til neste i listen.
            Node(final T d) { data = d;  neste = null; }  //  Constructor
        }

        private Node  hode;             //  Dummy hode for å forenkle mye av koden.
        private int   antallNoder;      //  Nåværende antall i listen.

                                        //  Initierer medlemmene:
        public List(final T t) { hode = new Node(t); antallNoder = 0; }
        
        public void display() {         //  Skriver listens innhold:
            Node np = hode.neste;       //  Hopper over selve hodet.
            while (np != null) {        //  Ikke nådd listens slutt:
                System.out.println("\t" + np.data);  //  Skriver nodens data.
                np = np.neste;          //  Hopper/går til neste i listen.
            }
            System.out.println("\n\tAntall noder i listen:  " + antallNoder);
        }
        
                                        //  Returnerer om listen er tom eller ei:
        public boolean empty() { return antallNoder == 0; }
        
                                        //  Returnerer om 't' er å finne eller ei:
        public boolean find(final T t) {
            Node np = hode.neste;       //  Hopper over selve hodet.
                                        //  Blar til der noe evt. ligger:
            while (np != null && np.data.compareTo(t) < 0)
                np = np.neste;
            return np != null && np.data.equals(t);  //  Funnet eller ei?
        }
        
        public void insert(final T t) { //  Setter inn ny node sortert:
            Node np = hode,             //  Initierer til selve hodet.
                 nyNode = new Node(t);  //  Oppretter den nye noden.
            
                        //  Neste finnes, og den er < enn den nyeste
                        //      (dvs. ved identiske legges den nye forrest):
            while (np.neste != null && np.neste.data.compareTo(nyNode.data) < 0)
                np = np.neste;          //  Blar frem til neste node.
            
            nyNode.neste = np.neste;    //  Hekter inn mellom to noder
            np.neste = nyNode;          //    (evt. helt til slutt):
            antallNoder++;              //  Øker totalantallet noder.
        }
        
        public boolean remove(final T t) {  //  Returnerer om fjernet eller ei:
            Node np = hode,             //  Initierer til selve hodet.
                 np2 = hode.neste;      //  Initierer til etter hodet.
                                        //  Blar til der evt. ligger:
            while (np2 != null && np2.data.compareTo(t) < 0) {
                np = np2;               //  Hopper hakket etter.
                np2 = np2.neste;        //  Blar til neste.
            }
            
            if (np2 != null && np2.data.equals(t)) {  //  Funnet:
                np.neste = np2.neste;   //  Hekter ut 'np2':
                np2.neste = null;
                antallNoder--;          //  Minsker totalantallet noder.
                return true;            //  Retunerer at er fjernet.
            }
            else                        //  Retunerer at er IKKE fjernet.
                return false;
        }
        
        public T removeNo(final int no) {  //  Returnerer (om mulig) node nr.'no':
            Node np = hode,             //  Initierer til selve hodet.
                 np2 = hode.neste;      //  Initierer til etter hodet.
            if (no >= 1 && no <= antallNoder) {  //  'no' i rett intervall:
                for (int i = 1; i < no; i++) {  //  Blar frem til nr.'no': 
                    np = np2;    np2 = np2.neste;  // Pekerne flyttes fremover:
                }
                np.neste = np2.neste;   //  Hekter ut 'np2':
                np2.neste = null;
                antallNoder--;          //  Minsker totalantallet noder.
                return np2.data;        //  Returnerer nodens 'data'.
            } else
                                        //  Egen melding ??
                System.out.println("\nNumber out of bounds .....\n");
            return null;
        }
        
                                        //  Returnerer antall noder i listen:
        public int size() { return antallNoder; }
    }


    
    /**
     * Hovedprogrammet:
     */
    public static void main(String[] args) {
        List<String> liste = new List<>("");
        
        liste.insert("Oslo");   liste.insert("Bergen");     liste.insert("Molde");
        liste.insert("Nas");    liste.insert("Armenistis"); liste.insert("Hamar");
        liste.display();
        
        System.out.print("\nHamar finnes");
        if (!liste.find("Hamar"))  System.out.print(" IKKE!");
        System.out.print("\nLarvik finnes");
        if (!liste.find("Larvik")) System.out.print(" IKKE!");
        System.out.print('\n');
        
        if (liste.remove("Molde") == null)
            System.out.println("Å fjerne 'Molde' mislyktes!");
        if (liste.remove("Oslo")  == null)
            System.out.println("Å fjerne 'Oslo' mislyktes!");
        if (liste.remove("Gjøvik") == null)
            System.out.println("Å fjerne 'Gjøvik' mislyktes!");
        
        liste.display();

        System.out.print("Fjernet nr.3: " + liste.removeNo(3));   liste.display();
        System.out.print("Fjernet nr.3: " + liste.removeNo(3));   liste.display();
        System.out.print("Fjernet nr.1: " + liste.removeNo(1));   liste.display();
        
        liste.removeNo(4);  System.out.println("Fjernet nr.4: ");   liste.display();
        
// ============================   LISTE MED INT'er:   ==================================
        
        List<Integer> liste2 = new List<>(0);
        liste2.insert(29);  liste2.insert(17);  liste2.insert(22);
        liste2.display();
        
        if (liste2.remove(312) == null)  System.out.println("\n\nFant ikke 312!");
        if (liste2.removeNo(6) == null)  System.out.println("Fant ikke nr.6!");
        
        System.out.println("\n\n");
    }
}


/*************************************************************************************** 

 Noen viktige og påkrevde forskjeller ift. C++-versjonen:

 - Destructor finnes ikke i Java på samme måte som i C++; garbage collector tar seg av 
   rydding i minnet automatisk, så dette er utelatt.
 - Java har også generics som likner på templates i C++, så generics er brukt. "return 0;"
   er ikke gyldig i Java når funksjonen er definert med en annen return type enn tall.
   "return null;" er brukt i stedet, som tilsvarer nullptr.
 - < og > kan ikke brukes for å sammenligne objekter i Java, så der det er brukt generics
   er det satt at `T extends Comparable` og .compareTo brukt i stedet for < og >.

****************************************************************************************/
