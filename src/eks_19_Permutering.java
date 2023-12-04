/**
 *   Programeksempel nr 19 - Permutering (plassombytting/annen rekkefølge).
 *
 *   Eksemplet viser ombytting på ALLE tenkelige måter av ALLE elementer
 *   i en (int-)array.
 *   N ULIKE elementer kan permuteres på N! ulike måter.
 *
 *   Mer forklaring av algoritmen/funksjonaliteten på:  Permutering.pdf
 *
 *   For visuell visning av alle (rekursive) funksjonskall ved
 *   int-arrayer med "123" og "1234", se:
 *      - Eks19_(rekursive)_funksjonskall_ved_array123.pdf   og
 *      - Eks19_(rekursive)_funksjonskall_ved_array1234.pdf
 *   Omtrent det samme oppnås/sees ved å fjerne de fire '//'
 *   ifm. 'cout'ene inni funksjonene 'display' og 'permuter'
 *
 *   @file     EKS_19_Permutering.java
 *   @author   Marius Lindvall, NTNU
 */

public class EKS_19_Permutering {
    
    static final int N = 4;             ///<  Arrayens lengde.

    /**
     *  Hovedprogrammet:
     */
    public static void main(String[] args) {
        int[] array = new int[N];       //  Array som skal permuteres.

        for (int i = 0; i < N; i++)     //  Fyller array med: 1, 2, 3, ..., N
            array[i] = i+1;

        permuter(array, 0, N);          //  Lager (og skriver) permutasjoner av
                                        //    ALLE arrayelementene.
        System.out.println();
        display(array, N);              //  Skriver array etter at ferdig
                                        //    (for å vise at origisnal er gjenopprettet).

        System.out.println('\n');
    }
    
    
    /**
     *  Bytter om to elementer i arrayen.
     *  
     *  Se notat nederst i fila om referanseoverføring.
     *
     *  @param   arr    -  Arrayen som verdier skal bytte plass i
     *  @param   tall1  -  Indeksen til verdien som skal bytte plass med indeks 'tall2'
     *  @param   tall2  -  Indeksen til verdien som skal bytte plass med indeks 'tall1'
     */
    static void bytt(int[] arr, int tall1, int tall2) {
        int temp = arr[tall1];        //  Midlertidig (temporary) unnalagring.
        arr[tall1] = arr[tall2];
        arr[tall2] = temp;
    }
    
    
    /**
     *  Skriver ut HELE arrayen 'arr' sitt innhold.
     *
     *  @param   arr  -  Arrayen som får hele sitt innhold skrevet ut
     *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
     */
    static void display(final int arr[], final int n) {
        for (int i = 0;  i < n;  i++)
            System.out.print(" " + arr[i]);
        System.out.println();
    }
    
    
    /**
     *  Genererer rekursivt ALLE mulige permutasjoner av innholdet i 'arr'.
     *
     *  @param   arr  -  Arrayen som skal permuteres
     *  @param   i    -  Indeksen som ALLE ETTERFØLGENDE verdier skal flyttes til
     *  @param   n    -  Antall elementer i arrayen (siste indeks brukt er n-1)
     *  @see     bytt(...)
     *  @see     display()
     *  @see     roterVenstre(...)
     */
    static void permuter(int arr[], final int i, final int n) {
        if (i == n-1)                       //  Nådd en ny permutasjon:
            display(arr, n);                //  Skriver ut arrayens innhold.
        else {                              //  Skal permutere:
            permuter(arr, i+1, n);          //  Beholder nåværende nr.'i'.
                                            //    Permuterer resten.
            for (int t = i+1;  t < n;  t++) {
                bytt(arr, i, t);            //  Bytter nr.'i' etter tur med
                                            //    ALLE de andre etterfølgende.
                permuter(arr, i+1, n);      //  For hver av ombyttene: permuterer
            }                               //     resten av de etterfølgende.
            roterVenstre(arr, i, n);        //  Gjenoppretter opprinnelig array!!!
        }
    }
    
    
    /**
     *  Venstreroterer en array innhold.
     *
     *  @param   arr  -  Arrayen som får (deler av) sitt innhold venstrerotert
     *  @param   i    -  Laveste indeks som skal venstreroteres
     *  @param   n    -  'n-1' er høyeste indeks som venstreroteres
     */
    static void roterVenstre(int arr[], final int i, final int n) {
        int venstreVerdi = arr[i];            //  Tar vare på første.
        for (int k = i+1;  k < n;  k++)       //  Roterer (flytter alle ned
            arr[k-1] = arr[k];                //     ETT hakk/indeks).
        arr[n-1] = venstreVerdi;              //  Legger første inn bakerst.
    }

}

/***************************************************************************************

 Noen viktige og påkrevde forskjeller ift. C++-versjonen:

 REFERANSEOVERFØRING

 I Java så har vi ikke det som i C++ kalles referanseoverføring. Vanligvis i Java så er
 det slik at hvis du kaller en funksjon med noen parametre, og du endrer på verdien til
 parameterne inne i funksjonen, så vil ikke tallene som du sendte inn, der du kalte på
 funksjonen, også endres. Endringen skjer bare inne i funksjonen og påvirker ikke noe
 utenfor. Dette kalles verdioverføring.

 Med referanseoverføring er det slik at dersom du endrer på variabelen inne i
 funksjonen, så endres også variabelen der du kaller funksjonen. Dette er fordi du i
 stedet for å sende med en kopi av variabelens verdi til funksjonen, så sender du en
 referanse til den originale variabelen og oppdaterer den direkte. Derfor kalles dette
 referanseoverføring. Referanseoverførte variabler i C++ vises med tegnet &.

 Det er flere måter å "emulere" referanseoverføring i Java. En av dem er å sende inn
 arrayen direkte, siden Java da sender med en peker til arrayen til funksjonen, i stedet
 for å lage en kopi av hele arrayen. Dermed kan man endre på verdier inne i arrayen, og
 dette vil også oppdatere arrayen der du kaller funksjonen.

***************************************************************************************/