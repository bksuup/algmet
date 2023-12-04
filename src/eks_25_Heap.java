/**
 *   Programeksempel nr 25 - Heap (prioritetskø) - selvlaget enkel klasse.
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen Heap.
 *   Det er laget kode for følgende funksjoner:
 *
 *     - Heap(final int lengde)                             //  default = 200
 *     - void change(final int keyNr, final T nyVerdi)      //  Oppgave nr.15
 *     - void display()
 *     - void downHeap(T[] arr, final int ant, int keyNr)
 *     - void extract(final int keyNr)                      //  Oppgave nr.15
 *     - void insert(final T verdi)
 *     - T    remove()
 *     - T    replace(final T verdi)
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
 *
 *   @file     EKS_25_Heap.java
 *   @author   Marius Lindvall, NTNU
 */

import java.io.IOException;
import java.lang.reflect.Array;

public class EKS_25_Heap {
    
    /**
     *  Container-klassen Heap.
     *
     *  Inneholder en array ('data') av typen 'T', to int'er som angir heapens
     *  max.lengde og nåværende antall elementer i arrayen, samt en sentinel key.
     */
    static class Heap<T extends Comparable<T>> { //  'T': fleksibel datatype!
        private T[] data;               //  PEKER til array av typen 'T'.
        private int lengde,             //  Heapens max.lengde. 
                    antall;             //  Nåværende antall elementer i arrayen.
        private T   sentinelKey;        //  Stopp-verdi i element nr.0.
        private Class<T> type;          //  Se vedlegg nederst i fila.
        
        //  PRIVATE funksjon - da KUN brukes av EGNE funksjoner!
                                        //  Flytter evt. initielle data[keyNr]
        private void upHeap(int keyNr) {//    opp forbi alle mindre foreldre:
            T verdi = data[keyNr];      //  Elementet som evt. flyttes opp.
            data[0] = sentinelKey;      //  Legger inn sentinel key.
            while (data[keyNr/2].compareTo(verdi) < 0) {
                                                //  Foreldre er mindre:
                data[keyNr] = data[keyNr/2];    //  Flytter foreldre ned.
                keyNr = keyNr/2;                //  Indeksen blir foreldre sin.
            }
            data[keyNr] = verdi;        //  Setter/smetter inn der stanset.
        }
        
                                        //  I Java finnes ikke default parameter slik
                                        //  som i C++. Løsningen er i stedet å lage to
                                        //  konstruktorer, én med og én uten parameter,
                                        //  og la sistnevnte kalle førstnevnte med
                                        //  verdien(e) som skal være default.
        public Heap(Class<T> type) { this(type, 200); };
                                        //  Initierende constructor:
        public Heap(Class<T> type, final int len)  {
            data = (T[]) Array.newInstance(type, len);  lengde = len;  antall = 0;
            if (type.isAssignableFrom(Integer.class))
                sentinelKey = type.cast(1000000);               //  Setter ut
            else if (type.isAssignableFrom(Character.class))    //  fra T !!!
                sentinelKey = type.cast((char)255);
        }
                                        //  Endrer 'data[keyNr]'  til  'nyVerdi':
        public void change(final int keyNr, final T nyVerdi) {

            //  LAG IMNMATEN  ifm.  Oppgave nr.15
        }
        
        public void display() {         //  Skriver ut HELE heapens innhold:
            for (int i = 1; i <= antall; i++)  System.out.print(" " + data[i]);
        }
        
                            //  Flytter evt. element ned forbi alle større barn:
                            //  MÅ HA PARAMETRE, DA OGSÅ SKAL KALLES/BRUKES UTENFRA!
        public void downHeap(T arr[], final int ant, int keyNr) {
            int j;                      //  Indeksen for et av barna.
            T verdi = arr[keyNr];       //  Elementet som evt. flyttes ned.
            while (keyNr <= ant/2) {    //  De før halvveis har barn:
                j = 2 * keyNr;          //  Venstre barnet indeks.
                                        //  OM har høyre barn og dette er større,
                                        //    oppdaterer til DETS indeks:
                if (j < ant  &&  arr[j].compareTo(arr[j+1]) < 0)  j++;
                if (verdi.compareTo(arr[j]) >= 0)
                                        //  Aktuelt barn er IKKE større,
                   break;               //    avbryter letingen nedover. 
                arr[keyNr] = arr[j];    //  Flytter opp barnet.
                keyNr = j;              //  Ny indeks blir dette barnet.
            }
            arr[keyNr] = verdi;         //  Setter/smetter inn der stanset.
        }
        
                                        //  Sletter element nr.'keyNr' fra heapen:
        public void extract(final int keyNr) {

            //  LAG IMNMATEN  ifm.  Oppgave nr.15
        }
        
                                        //  Setter om mulig inn ny verdi i heapen:
        public void insert(final T verdi) {
            if (antall < lengde - 1) {  //  Er plass:    
                data[++antall] = verdi; //  Settes/legges inn aller bakerst.
                upHeap(antall);         //  Evt. flyttes opp (upHeapes).
            }  else                     //  Er IKKE plass:
                System.out.println("\nHeapen er full med " + lengde
                                 + " elementer (inkl. sentinel key)!\n");
        }
        
                                        //  Fjerner og returnerer (om mulig)
        public T remove() {             //    den største/første fra heapen:
            if (antall > 0) {           //  Heapen er IKKE tom:
                T verdi = data[1];      //  Lagrer unna den første.
                data[1] = data[antall--];   //  Aller bakerste flyttes HELT frem.
                downHeap(data, antall, 1);  //  DownHeaper denne.
                return verdi;           //  Returnerer den første (unnalagrede).
            }  else {                   //  Heapen ER tom:
                System.out.println("\nHeapen er helt tom - ingenting i 'remove'!\n");
                return sentinelKey;
            }
        }
        
                        //  Erstatter det første elementet med en ny verdi,
                        //    og returnere det NÅ største elementet i heapen:
        public T replace(final T verdi) {      
            data[0] = verdi;            //  Legger inn i element nr.0 !!!
            downHeap(data, antall, 0);  //  Downheaper.
            return data[0];             //  Største er etterpå i element nr.0!
        }                               //   Og er da ENTEN det nye (som er størst!),
    }                                   //    ELLER det som initielt var rota (nr.1).

    /**
     *  Hovedprogrammet:
     */
    public static void main(String[] args) {
        Heap <Integer>        heap = new Heap<>(Integer.class);
    //  Heap <Character>      heap2 = new Heap<>(Character.class);

        try {
            System.out.print("\n\nViser bruken av heapen.");
            heap.insert(1);   System.out.print("\nInsert 1 :  "); heap.display(); System.in.read();
            heap.insert(5);   System.out.print("\nInsert 5 :  "); heap.display(); System.in.read();
            heap.insert(2);   System.out.print("\nInsert 2 :  "); heap.display(); System.in.read();
            heap.insert(6);   System.out.print("\nInsert 6 :  "); heap.display(); System.in.read();
            heap.replace(4);  System.out.print("\nReplace 4:  "); heap.display(); System.in.read();
            heap.insert(8);   System.out.print("\nInsert 8 :  "); heap.display(); System.in.read();
            heap.remove();    System.out.print("\nRemove   :  "); heap.display(); System.in.read();
            heap.insert(7);   System.out.print("\nInsert 7 :  "); heap.display(); System.in.read();
            heap.insert(3);   System.out.print("\nInsert 3 :  "); heap.display(); System.in.read();
    
            System.out.println("\n\n\nTester to selvlagde funksjoner fra oppgave nr.15:");
            heap.change(4, 5); System.out.print("\nChange #4 til 5: "); heap.display(); System.in.read();
            heap.change(3, 1); System.out.print("\nChange #3 til 1: "); heap.display(); System.in.read();
            heap.extract(2);   System.out.print("\nExtract #2:   ");    heap.display(); System.in.read();
            heap.extract(2);   System.out.print("\nExtract #2:   ");    heap.display(); System.in.read();
            heap.extract(1);   System.out.print("\nExtract #1:   ");    heap.display();
        } catch (IOException ex) {
            // Se vedlegg nederst.
        }

        System.out.println('\n');
    }

}

/* KOMMENTARER TIL VESENTLIGE ENDRINGER I KODEN:

I Java så blir generic types "visket ut" (såkalt type erasure) ved kompilering. Dette
gjør at man ikke kan bruke f.eks. "new T[]" eller "instanceof T" og andre type-relaterte
operasjoner. En måte å omgå dette er å sende med klassen til T når man konstruerer en
instans av klassen med generics. Da kan man bruke f.eks. "Array.newInstance(type,
length)" og "type.isAssignableFrom(otherType)". Dette fører til mer tilsynelatende
"unødvendig" kode, men er den eneste praktiske måten å kunne bruke selve typen i klassen.

Ang. innmaten i main(): System.in.read() i Java kan medføre en IOException, som må fanges
for at programmet skal kunne kompilere. I C++ vil "cin >> ch;" bare kræsje dersom cin
ikke er tilgjengelig. Det er heller ikke behov for å lese inn til en char i Java, derfor
er "char ch;" utelatt i Java-koden. MERK: Du trenger heller ikke å skrive et tegn i
inputen i Java! Det holder å bare trykke Enter for å fortsette kjøringen av koden. */
