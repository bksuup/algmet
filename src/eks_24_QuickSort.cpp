/**
 *   Programeksempel nr 24 - Quicksort.
 *
 *   Algoritme/virkemåte:
 *        Prinsippet: Splitt og hersk, partisjonere i to, sortere hver del.
 *        Dette løses/gjøres ved å:
 *         - velge arr[hoyre] som et tilfeldig element/verdi å sortere ut fra.
 *           Det valgte elementet kalles "partisjonselementet".
 *         - lete fra venstre etter en større eller lik verdi, og fra høyre
 *           etter en mindre eller lik verdi, og så bytte om på disse to.
 *         - gjenta det forrige punktet inntil letingen har passert hverandre.
 *         - til slutt bytte arr[hoyre] (partisjonselementet) med den
 *           HELT TIL HØYRE I VENSTRE DELARRAY (nr.'i').
 *        Alt dette medfører at:
 *         - Partisjonselementet i arr[i] er på sin endelige plass for godt
 *         - ALLE verdier i arr[venstre] til arr[i-1] er MINDRE ELLER LIK
 *         - ALLE verdier i arr[i+1] til arr[hoyre] er STØRRE ELLER LIK
 *
 *   Orden ( O(...)):
 *        Quicksort bruker i gjennomsnitt omtrent  2N ln N  sammenligninger.
 *        (som er omtrent  1.39N lg N)     "Worst case":  (N*N)/2
 *
 *   NB:  - Koden i funksjonen 'partisjoner' kan/burde også bare flyttes inn
 *          i funksjonen 'quickSort' - så går den ENDA raskere.
 *        - Skal elementet HELT til høyre eller venstre velges som
 *          partisjonselement?  Dette er en smakssak, og gjøres litt ulikt
 *          i de forskjellige kodesnutter, visualiseringer og animasjoner.
 *          Det viktigste er at man gjør ET VALG, og er konsekvent mot dette !
 *          ==================================================================
 *          I koden nedenfor er det brukt det HELT TIL HØYRE i delarrayen, og
 *          DETTE ER DET OGSÅ FORUTSATT AT MAN GJØR IFM. OPPGAVER/PÅ EKSAMEN !
 *          ==================================================================
 *        - Quicksort bytter også om på elementer som er likt med
 *          partisjonselementet. Hadde det KUN vært LIKE elementer i hele
 *          arrayen så ville vi ellers ha fått et "worst case". Men gjøres
 *          det slik, så vil gi hele tiden få en EKSAKT todeling/halvering av
 *          av arrayen - som jo er en god, rask og effektiv måte.
 *        - Bruker også SENTINEL KEY - i tilfelle partisjonselementet
 *          er det aller minste
 *        - Stabil?  NEI - da bl.a. bytter om like elementer
 *
 *        - Siden Quicksort er en av de aller raskeste sorteringsmetoder som
 *          er laget/utviklet, så er det også sett på mye hvordan gjøre den
 *          ENDA raskere. Tre forbedringer i så møte KAN være:
 *             1) Fjerne rekursjon - heller bruke Stack:
 *                Rekursjon er ofte elegant og den enkleste måten å løse en
 *                del problemer på. Men den er også litt ekstra ressurs-
 *                krevende, ved at data (adresser i hukommelsen og lokale
 *                variable må pushes på "programstacken"). Fjerner man derfor
 *                rekursjon og heller pusher på en egen stack 'venstre'- og
 *                'hoyre'-intervaller som koden har igjen å jobbe med, så vil
 *                hastigheten kunne gå litt/noe opp.
 *             2) Spesialhåndtere mindre/kortere delarrayer:
 *                Når delarrayen som skal sorteres vha. Quicksort blir rimelig
 *                kort (typisk 5-25 elementer), så kan man la være å sortere
 *                disse vha. rekursive Quicksort, men la de forbli usortert.
 *                HELT TIL SLUTT går man gjennom HELE arrayen og sorterer den
 *                vha. f.eks. Insertion sort. Da vil den jo bestå av masse
 *                delarrayer, der ALLE elementer i en delarray er større enn
 *                de i den forrige, og mindre enn ALLE i den neste. Dermed vil
 *                ikke Insertion sort flytte elementene så langt bakover.
 *             3) Median-of-three:
 *                I stedet for å bare ta høyre/venstre element som partisjons-
 *                element, som jo blir en meget tilfeldig verdi, så prøver man
 *                å finne en verdi som kanskje er LITT mer representativ for
 *                gjennomsnittet av verdiene i delarrayen. Dette gjør man ved
 *                å se på venstre, midtre og høyre element. Bytte om på disse,
 *                slik at de blir i stigende rekkefølge, bytte arr[midtre] opp
 *                til arr[hoyre-1], og så sortere delarrayen arr[venstre+1] og
 *                opp til arr[hoyre-2]. Slipper da også sentinel key!
 *          Men, selv med alle alt dette blir Quicksort bare 25-30% raskere.
 *
 *   @file     EKS_24_QuickSort.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <string>            //  string
#include <cstdlib>           //  (s)rand
using namespace std;


const int N = 20;            ///<  Antall elementer i array som skal sorteres.


void bytt(char & tegn1, char & tegn2);
void display(const string & tekst, const char arr[],
             const int venstre, const int hoyre);
int  partisjoner(char arr[], const int venstre, const int hoyre);
void quickSort(char arr[], const int venstre, const int hoyre);


/**
 *  Hovedprogrammet:
 */
int main() {
    char array[N+1];                 //  Array som skal sorteres.
                                     //  Bruker indeksene 1-N
                                     //    da det ligger SENTINEL KEY
                                     //    (STOPPVERDI) i element nr.0 !!!

    srand(0);                      //  Brukes ifm. tilfeldighet/randomisering.

    array[0] = ' ';                //  Legger inn SENTINEL KEY !!!

    for (int i = 1; i <= N; i++) //  Array med tilfeldige bokstaver A-Z:
        array[i] = static_cast <char> ('A' + (rand() % 26));

    display("\n\nArrayen FØR sortering:\n", array, 1, N);


    quickSort(array, 1, N);      //  QUICKSORT SORTERER !!!

                                   //  Skriver array ETTER sortering:
    display("\n\nArrayen ETTER QUICKSORT sortering:\n", array, 1, N);

    cout << "\n\n";
    return 0;
}


/**
 *  Bytter om to referanseoverførte variables innhold.
 *
 *  @param   tegn1  -  Verdien som skal byttes med 'tegn2' (referanseoverført)
 *  @param   tegn2  -  Verdien som skal byttes med 'tegn1' (referanseoverført)
 */
void bytt(char & tegn1, char & tegn2) {
    char temp = tegn1;           //  Midlertidig (temporary) unnalagring.
    tegn1 = tegn2;
    tegn2 = temp;
}


/**
 *  Skriver ut (deler av) arrayen 'arr' sitt innhold.
 *
 *  @param   tekst    -  Ledetekst som skrives aller først
 *  @param   arr      -  Arrayen som får (deler av) innholdet skrevet ut
 *  @param   venstre  -  Nedre/venstre indeks for utskrift
 *  @param   hoyre    -  Øvre/høyre    indeks for utskrift
 */
void display(const string & tekst, const char arr[],
             const int venstre, const int hoyre) {
    char tegn;
    cout << tekst << "\t";
    for (int i = venstre;  i <= hoyre;  i++)
        cout << arr[i];
    cin >> tegn;                        //  Venter på ETT tegn og '\n'.
}


/**
 *  Flytter elementer i (deler av) array ut fra HØYRE partisjonselement,
 *  slik at ALT til venstre er mindre/lik, og ALT til høyre er større/lik.
 *
 *  @param    arr      -  Arrayen som skal partisjoneres
 *  @param    venstre  -  Nedre/venstre indeks for partisjonering
 *  @param    hoyre    -  Øvre/høyre    indeks for partisjonering
 *  @return   Indeksen der partisjonselementet havnet/ble plassert
 *  @see      display(...)
 */
int partisjoner(char arr[], const int venstre, const int hoyre) {
    if (hoyre > venstre) {              //  Minst TO elementer:
        int i, j;                       //  Indekser som går mot hverandre.
        char partisjonsElement;         //  Partisjonselementet.

        partisjonsElement = arr[hoyre]; //  Initierer til HØYRE element.
        i = venstre-1;                  //  Initierer indeksene til ETT
        j = hoyre;                      //    hakk utenfor intervallet.
                             //  NB:  'i' og 'j' økes/minskes FØR bruk.
                             //       Derfor er de initiert utenfor grensene.
                             //       De stopper dermed på de aktuelle
                             //       indekser UTEN å "hoppe" en for langt.
//                            display("\nFør:", arr, venstre, hoyre);
        while (true) {                  //  Looper til breaker ut:
                                        //  Leter etter STØRRE ELLER LIK:
            while (arr[++i] < partisjonsElement)   ;   //  NB:  Tom innmat !!!
                                        //  Leter etter MINDRE ELLER LIK:
            while (arr[--j] > partisjonsElement)   ;   //  NB:  Tom innmat !!!

//                             cout << "i: " << i << "  j: " << j << "   - "
//                                  << ((i < j) ? "Bytte" : "BREAK") << '\n';
            if (i >= j)  break;         //  Indekser nådd/passert hverandre.
            bytt(arr[i], arr[j]);       //  Bytter der stanset med 'i' og 'j'.
        }

        bytt(arr[i], arr[hoyre]);     //  Bytter/setter (for godt) partisjons-
                                      //    elementet med det HELT TIL HØYRE I
                                      //    VENSTRE HALVDEL (dvs. der 'i' er).
//                             display("Etter:", arr, venstre, hoyre);
        return i;                     //  Returnerer der partisjonselementet
    }                                 //    havnet/ble plassert.
    return 0;                         //  Mindre enn to elementer:
}                                     //    returnerer "dummy" verdi.


/**
 *  Sorterer REKURSIVT en char-array STIGENDE med QUICKSORT.
 *
 *  @param   arr      -  Arrayen som skal sorteres
 *  @param   venstre  -  Nedre/venstre indeks for sorteringsintervall
 *  @param   hoyre    -  Øvre/høyre    indeks for sorteringsintervall
 *  @see     partisjoner(...)
 */
void quickSort(char arr[], const int venstre, const int hoyre)  {
    if (hoyre > venstre) {                  //  MINST TO elementer:
        int indeks = partisjoner(arr, venstre, hoyre);    //  Partisjonerer!!!
        quickSort(arr, venstre, indeks-1);  //  Gjør det samme for venstre og
        quickSort(arr, indeks+1, hoyre);    //    høyre halvdel ift. 'indeks'.
    }
}
