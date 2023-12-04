/**
 *   Programeksempel nr 42 - Algoritmisk problem - case 3.
 *
 *   For programmets funksjonalitet se:  AlgCase3.pdf
 *
 *  (Dette var oppg.nr.4 på eksamen 18/12-2013 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_42_Alg_Case3.CPP.
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include <cstring>      //  strncmp, strlen
using namespace std;


const int LEN = 9;      ///<  Max. sifre i et telefonnummer, inkl. '\0'.
const int N   = 8;      ///<  Antall ulike telefonnumre.


//  Brukes for å teste  prefixA:
char txt0[N][LEN] =  { "0403", "05043", "05047",  "113", "1143", "11612345",
                       "11812345", "62529903" };
char txt1[N][LEN] =  { "0403", "05043", "05047",  "113", "1134", "11612345",
                       "11812345", "62529903" };
char txt2[N][LEN] =  { "0403", "05043", "050437", "113", "1143", "11612345",
                       "11812345", "62529903" };

//  Brukes for å teste  prefixB:
int num[][N]= {{ 113, 403, 1143, 5043, 5047,  11612345, 11812345, 62529903 },
               { 113, 403, 1134, 5043, 5047,  11612345, 11812345, 62529903 },
               { 113, 403, 1143, 5043, 50437, 11612345, 11812345, 62529903 }};

//  Brukes for å teste  prefixC:
char txt3[N][LEN] =  { "113", "0403", "1143", "05043", "05047",  "11612345",
                       "11812345", "62529903" };
char txt4[N][LEN] =  { "113", "0403", "1134", "05043", "05047",  "11612345",
                       "11812345", "62529903" };
char txt5[N][LEN] =  { "113", "0403", "1143", "05043", "050437", "11612345",
                       "11812345", "62529903" };


/**
 *  Alternativ A:
 *             Sjekker om 't' inneholder verdier som er prefiks av hverandre.
 *
 *  Datatype:    char'er (tekster/strenger)
 *  Sortering:   Lexicografisk/alfabetisk sortert (som tekst)
 *  Metode:      Sjekk om nr.'i' er et prefiks av nr.'i+1'
 *
 *  @param    t  -  Arrayen som skal sjekkes for prefiks verdier
 *  @return   Om det finnes prefikser av hverandre i arrayen 't'
 */
bool prefixA(const char t[N][LEN])  {
  for (int i = 0;  i < N-1;  i++)  {               //  Går gjennom arrayen:
      if (!strncmp(t[i], t[i+1], strlen(t[i]))) {  //  Prefiks av NESTE verdi?
         cout << "\t\t" << t[i] << " er et prefiks av " << t[i+1] << '\n';
         return true;                              //  "Ja" - returner true.
      }
  }
  return false;  //  Loop gått ferdig. Ingen prefikser funnet. Returner false.
}


/**
 *  Alternativ B:
 *             Sjekker om 't' inneholder verdier som er prefiks av hverandre.
 *
 *  Mer "selvsagt" metode(?) enn A, men litt mer kode/tuklete.
 *  Datatype:    int'er
 *  Sortering:   Numerisk
 *  Metode:      Ta vekk ett og ett siffer bakfra i nr.'i'. For hver gang,
 *               sjekke om "det nye tallet" forekommer i intervallet 'i-1'
 *               ned til 1.
 *
 *  @param    t  -  Arrayen som skal sjekkes for prefiks verdier
 *  @return   Om det finnes prefikser av hverandre i arrayen 't'
 */
bool prefixB(const int n[N])  {
  int i, j, tall;                    //  Løkkevariable og sammenligningstall.
                                     //  Går fra største/lengste og
  for (i = N-1; i > 0;  i--)  {      //    ned til minste/kortest:
      tall = n[i];                   //  Initierer med originalt tall.
      while (tall > 0)  {            //  Sålenge sifre igjen i tallet:
        for (j = i-1; j >= 0;  j--)  //  Går gjennom alle tall FØR i arrayen:
            if (tall == n[j])  {     //  Er prefiks av tallet?
               cout << "\t\t" << n[j] << " er et prefiks av " << n[i] << '\n';
               return true;          //  "Ja" - returner true.
             }
        tall /= 10;                  //  Tar bort bakerste/siste siffer.
      }
  }
  return false;  //  Loop gått ferdig. Ingen prefikser funnet. Returner false.
}


/**
 *  Alternativ C:
 *             Sjekker om 't' inneholder verdier som er prefiks av hverandre.
 *
 *  Datatype:    char'er (tekster/strenger)
 *  Sortering:   Primært sortert etter stigende tekstlengde. Sekundært er de
 *               med samme lengde innbyrdes alfabetisk/lexicografisk/numerisk
 *               sortert stigende.
 *  Metode:      Sjekk om nr.'i' er et prefiks av nr.'i+1' til 'N-1'.
 *
 *  @param    t  -  Arrayen som skal sjekkes for prefiks verdier
 *  @return   Om det finnes prefikser av hverandre i arrayen 't'
 */
bool prefixC(const char t[N][LEN])  {
  int i, j;
  for (i = 0;  i < N-1;  i++)  {                 //  Går gjennom arrayen:
	  for (j = i+1;  j <= N-1;  j++)             //  Prefiks av en av
      if (!strncmp(t[i], t[j], strlen(t[i])))  { //    ALLE de neste?
         cout << "\t\t" << t[i] << " er et prefiks av " << t[j] << '\n';
         return true;                            //  "Ja" - returner true.
      }
  }
  return false;  //  Loop gått ferdig. Ingen prefikser funnet. Returner false.
}


/**
 *  Hovedprogrammet:
 */
int main()  {

  cout << "txt0 er " << ((prefixA(txt0)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt1 er " << ((prefixA(txt1)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt2 er " << ((prefixA(txt2)) ? "IKKE " : "") << "OK\n\n";
  cout << "\n\n";

  cout << "num[0] er " << ((prefixB(num[0])) ? "IKKE " : "") << "OK\n\n";
  cout << "num[1] er " << ((prefixB(num[1])) ? "IKKE " : "") << "OK\n\n";
  cout << "num[2] er " << ((prefixB(num[2])) ? "IKKE " : "") << "OK\n\n";
  cout << "\n\n";

  cout << "txt3 er " << ((prefixC(txt3)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt4 er " << ((prefixC(txt4)) ? "IKKE " : "") << "OK\n\n";
  cout << "txt5 er " << ((prefixC(txt5)) ? "IKKE " : "") << "OK\n\n";
  cout << "\n\n";

  return 0;
}
