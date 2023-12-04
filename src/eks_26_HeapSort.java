/**
 *   Programeksempel nr 26 - Heapsort.
 *
 *   Algoritme/virkemåte:
 *        I arrayen som skal sorteres, startes det halveis uti, og det gås
 *        baklengs til dens start. For hvert element utføres 'downHeap'.
 *        Så når man har kommet til det første elementet, oppfyller HELE den
 *        originale arrayen heap-betingelsen. 
 *        Deretter bytter man om det aller første og det til enhver tid siste
 *        elementet, utfører 'downHeap' for hver gang, og teller stadig ned
 *        antall elementer i arrayen som er igjen å sortere. 
 *        Se koden for 'heapSort' ALLER nederst på denne filen.
 *
 *   Orden ( O(...)):
 *        Bruker FÆRRE (selv i "worst case"!) enn  2N lg N  sammenligninger 
 *        for å sortere N elementer.   
 *        (Siden hver heap-operasjon er av orden  2 lg N, og nå er det N
 *        elementer som skal sorteres, så blir dette "selvsagt" ordenen.)
 *        Dette er bare LITT saktere enn Quicksort, som er av orden:  2N ln N 
 *
 *   NB:  - Bottom-up heap-KONSTRUKSJON er tidslineær.
 *        - Ifm. bottom-up heapsortering er bruken av sentinel key i element
 *          nr.0 uinteressant. Dette fordi det bare brukes 'downHeap', 
 *          og denne bruker IKKE sentinel key (men det gjør 'remove' og 
 *          'replace'). Derfor settes det IKKE opp en sentinel key i 
 *          'gHeap' i 'main'. Dessuten MÅ det første elementet ligge i nr.1,
 *          og ikke nr.0 (som da synes ledig), fordi selve koden i 'heap' 
 *          forutsetter at det første elementet ligger i nr.1. 
 *        - Stabil?  NEI - da like elementer havner ulikt omkring i heapen
 *        - All koden i denne filen viser hvordan vi BOTTOM-UP heapsorter.
 *          Det finnes dog en annen metode, som kalles TOP-DOWN heapsortering.
 *          Denne går ut på å bruke heapen mer aktivt. ALT som skal sorteres
 *          legges inn ('insert') - hele tiden tilfredstillende heap-betingelsen.
 *          (Vi bruker dermed dobbelt så mye memory enn det som skal sorteres.)
 *          Deretter hentes ALT ut igjen ('remove'), og den originale arrayen
 *          fylles opp bakfra og fremover. Koden kunne da vært noe sånt som:
 *
 *                static void heapSort(Character arr[], final int n)  {
 *                     int i;
 *                     Heap <Character> heap = new Heap<>(Character.class, n+1);
 *                     for (i = 1;  i <= n;  i++)  heap.insert(arr[i]);
 *                     for (i = n;  i >= 1;  i--)  arr[i] = heap.remove();
 *                }
 *
 *   @file     EKS_26_HeapSort.java
 *   @author   Marius Lindvall, NTNU
 */

import java.io.IOException;
import java.util.Random;

public class EKS_26_HeapSort {
    
    static final int N = 20;            ///<  Antall elementer i array som skal sorteres.
                                        ///v  Array som fylles og sorteres.
    static EKS_25_Heap.Heap<Character> gHeap = new EKS_25_Heap.Heap<>(Character.class);

    /**
     *  Hovedprogrammet:
     */
    public static void main(String[] args) {
        Character[] array = new Character[N+1]; //  Array som skal sorteres.
                                        //  Bruker indeksene 1 til N.

        Random random = new Random(0);  //  Brukes ifm. tilfeldighet/randomisering.

        for (int i = 1;  i <= N;  i++)  //  Array med tilfeldige bokstaver a-z:
            array[i] = (char) ('a' + random.nextInt(26));
                                        //  Merk at Random i Java gir andre tegn enn
                                        //  rand() i C++ grunnet at Java bruker en
                                        //  annen formel for tallgenerering.

        System.out.println("\n\nArrayen FØR sortering:");
        display(array, N);


        heapSort(array, N);             //  HEAPSORT SORTERER !!!

                                        //  Skriver array ETTER sortering:
        System.out.println("\n\nArrayen ETTER HEAPSORT sortering:");
        display(array, N);

        System.out.println('\n');
    }
    
    /**
     *  Bytter om to referanseoverførte variables innhold.
     *  
     *  Denne er noe annerledes enn i C++ grunnet mangel på referanseoverføring.
     *  Se notat nederst i eksempel 19.
     *
     *  @param   arr    -  Arrayen som det skal byttes rundt i
     *  @param   tegn1  -  Indeksen som skal byttes med indeks 'tegn2'
     *  @param   tegn2  -  Indeksen som skal byttes med indeks 'tegn1'
     */
    static <T> void bytt(T[] arr, int tegn1, int tegn2) {   //  GENERISK FUNKSJON !!!
        T temp = arr[tegn1];            //  Midlertidig (temporary) unnalagring.
        arr[tegn1] = arr[tegn2];
        arr[tegn2] = temp;
    }
    
    /**
     *  Skriver ut hele en arrays innhold.
     *
     *  @param   arr      -  Arrayen som får hele innholdet skrevet ut
     *  @param   n        -  Antall elementer i 'arr'
     */
    static void display(final Character[] arr, final int n) {
        System.out.print('\t');
        for (int i = 1;  i <= n;  i++)
            System.out.print(arr[i]);
        try {
            System.in.read();           //  Venter på '\n'.
        } catch (IOException e) {
        }
    }
    
    /**
     *  Sorterer en unsigned char-array STIGENDE med (Bottom-Up) HEAPSORT.
     *
     *  @param   arr      -  Arrayen som skal sorteres
     *  @param   n        -  Antall elementer initielt i 'arr'
     *  @see     Heap.downHeap(...)
     *  @see     bytt(...)
     */
    static void heapSort(Character[] arr, int n)  {
        for (int keyNr = n/2;  keyNr >= 1;  keyNr--)    //  Arrayen heap-ordnes: !!!
            gHeap.downHeap(arr, n, keyNr);
//                                    display(arr, N);   System.out.println("\n\n");

        while (n > 1) {                                 //  Fortsatt igjen å sortere:
            bytt(arr, 1, n);                            //  Flytter 1. der 'n' er !!!
            gHeap.downHeap(arr, --n, 1);                //  Heap-ordner igjen!
//                                                display(arr, N);
        }
    }

}
