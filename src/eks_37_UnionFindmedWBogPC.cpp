/**
 *   Programeksempel nr 37 - Union-Find med
 *                           Weight Balancing og Path Compression.
 *
 *   For � holde tr�rne som bygges ved unionering litt mer kompakte og
 *   balanserte s� benyttes teknikker med:
 *    - Weight Balancing (WB) - vektbalansering
 *      Minste tre legges under det st�rste, og ikke n�dvendisgvis
 *      alltid 'nr2' under 'nr.1' (som i EKS_36_UnionFind.cpp).
 *   og
 *   - Path Compression (PC) - stikompresjon
 *     N�r en node oppdages i IKKE v�re et barn av rota i et tre,
 *     s� flyttes ALLE nodene p� stien opp til rota til � v�re barn av rota.
 *     Dette foretas f�r WB.
 *
 *
 *   Algoritme/virkem�te:
 *     'gForeldre' og 'unioner' er det samme som i EKS_36, bare at:
 *
 *     gForeldre[i] < 0 (=x)  n�r node nr.'i' totalt har absoluttverdien(x)
 *                            barn tilsammen under seg i subtr�rne
 *
 *
 *   *************************************************************************
 *   *************************************************************************
 *   **   ERSTATT 'unionerOgFinn(...)' I EKS_36 MED 'unionerOgFinn2(...)'.  **
 *   **   Stryk de tre linjene med 'cout' etter 'skriv()' i 'main'.         **
 *   *************************************************************************
 *   *************************************************************************
 *
 *   N�r PC og WB utf�res p� kantene i EKS_36, s� skjer f�lgende ifm. kantene:
 *     - HB:  Weight Balancing
 *     - GE:  Path Compression
 *     - FE:  Weight Balancing
 *     - IH:  Path Compression
 *
 *
 *   @file     EKS_37_UnionFindmedWBogPC.CPP
 *   @author   Frode Haug, NTNU
 */


/**
 *  Om 'unioner' er 'true' vil node 'nr1' og 'nr2' bli satt til � v�re
 *  i samme komponent, ellers returneres det om de allerede ER det.
 *
 *  Identisk til 'unionerOgFinn(...)' i 'EKS_36_UnionFind.cpp' bare at
 *  koden inneholder ogs� Path Compression (PC) og Weight Balancing (WB).
 *
 *  @param    nr1      -  Indeks for 1.node (blir mor til eller barn av 'nr2')
 *  @param    nr2      -  Indeks for 2.node (blir mor til eller barn av 'nr1')
 *  @param    unioner  -  Skal nodene havne i samme komponent eller ei
 *  @return   Er 'nr1' og 'n2' i samme komponent eller ei?
 */
bool unionerOgFinn2(int nr1, int nr2, const bool unioner) {
    int i = nr1, j = nr2;                         //  Initierer indekser.

    while (gForeldre[i] > 0)  i = gForeldre[i];   //  Finner rot for i/nr1.

    while (gForeldre[j] > 0)  j = gForeldre[j];   //  Finner rot for j/nr2.


//  **************************************************************************
//  NYTT (ned til stjernelinje) ift. EKS_36 ifm. Path Compression (PC):

    int indeks = 0;          //  ALLE p� stien fra 'nr1' flyttes opp til rota:
    while (gForeldre[nr1] > 0) {    //  Enn� ikke n�dd rota:
        indeks = nr1;               //  'indeks' er aktuell node.
        nr1 = gForeldre[nr1];       //  'nr1' settes til mora.
        gForeldre[indeks] = i;      //  'indeks' flyttes oppunder rota.
    }
                             //  ALLE p� stien fra 'nr2' flyttes opp til rota:
    while (gForeldre[nr2] > 0) {
        indeks = nr2;
        nr2 = gForeldre[nr2];
        gForeldre[indeks] = j;
    }

//  **************************************************************************
//  NYTT (ned til stjernelinje) ift. EKS_36 ifm. Weight Balancing (WB):

    if (unioner  &&  (i != j)) {                //  Hekter evt. sammen.
        if (gForeldre[j] < gForeldre[i])  {     //  'j' sitt tre er st�rst:
             gForeldre[j] += gForeldre[i]-1;    //  �ker antall barn under seg
                                                //    -1 pga. nr.'i'.
             gForeldre[i] = j;                  //  Hekter 'i' under 'j'.
        } else  {                     //  'i' sitt tre er st�rst (eller lik!):
            gForeldre[i] += gForeldre[j]-1;     //  �ker antall barn under seg
                                                //   -1 pga. nr.'j'
            gForeldre[j] = i;                   //  Hekter 'j' under 'i'.
        }
    }
//  **************************************************************************

    return (i == j);     //  Returnerer om i samme komponent eller ei.
                         //    (Aktuelt KUN n�r 'unioner' er 'false'
}                        //    dvs. ved 'Finn').
