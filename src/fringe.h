/**
 *   H-fil med klassen Fringe, som holder orden på en (del)grafs grensekanter.
 *
 *   Fringe betyr noe sånt som:  Grensekanter / Ytterkanten / Fronten
 *   Dvs. ALLE aktuelle kanter som TILSAMMEN går inn til/ut fra en DELGRAF.
 *
 *   NB:  Her lagres det KUN noder med 'int' som key/ID/data.
 *        Dvs. den er IKKE gjort generell ved bruk av Templates.
 *
 *   @file     FRINGE.H
 *   @author   Frode Haug, NTNU
 */


#ifndef __FRINGE_H            //  For at evt. bare skal includes EN gang:
#define __FRINGE_H


/**
 *  Enum med om utskrift av Fringens key som bokstav eller tall.
 */
 enum Utskrift  { Bokstav, Tall};


/**
 *  Klasse Fringe (med antall i hver av arrayene og to arrayer med
 *                 henholdsvis key/ID/data for en node og hittil lavest
 *                 registrerte/fundne vekt på kanten inn til denne noden).
 */
class Fringe  {
  private:
    int* keyene;        //  'vektene[i]' er den så langt fundne
    int* vektene;       //    minste vekten inn til noden 'keyene[i]'.
    int  antall;        //  = siste indeks brukt i både "keyene" og "vektene".

  public:
    Fringe(const int max = 200)
         {  keyene = new int[max];   vektene = new int[max];  antall = 0;  }
    ~Fringe()
       {  delete [] keyene;  delete [] vektene;  }

    void display(const Utskrift skriv) const  {
        std::cout << "\tFringe:\t";
        for (int i = 0;  i < antall;  i++)  {
             if (skriv == Bokstav)
                std::cout << char(keyene[i]+'A'-1);
             else
                std::cout <<  keyene[i];
             std::cout << ':' << vektene[i] << "  ";
        }
    }

    bool empty() const  {  return  (antall == 0);  }

   /**
    *  Legger inn en node (key) inn i/på Fringen dersom den ER NY eller at
    *  kanten inn til/ut fra den har LAVERE VEKT enn det hittil registrert.
    *
    *  NB:  LEGGES FORAN EVT. ANDRE ALLEREDE EKSISTERENDE MED LIK VEKT !!!
    *
    *  @param    key   - Evt. innlagt nodes key/ID/data
    *  @param    vekt  - Vekten på aktuell kant inn til/ut fra denne noden
    *  @return   Om noden ble lagt inn på/i Fringen eller ei
    */
    bool update(const int key, const int vekt)  {
       int j,                                    //  Løkkevariabel.
           i = 0;                                //  Nodes evt. fundne indeks.
                                                 //  Finnes 'key' allerede?
       while ((keyene[i] != key)  &&  (i < antall))  i++;
       if ((i < antall)  &&  (vekt >= vektene[i])) //  Ja,
          return false;                            //    men har lavere vekt.
                                                   //  Avslutter innlegging.
       if (i < antall)  {                          //  Ja, og har høyere vekt.
          for (j = i;  j < antall-1;  j++)         //    Tas derfor ut:
              {  keyene[j] = keyene[j+1];   vektene[j] = vektene[j+1];  }
          --antall;                                //  Reduserer antallet.
       }
                                                // Leter etter plassen der ny
       i = 0;                                   //   eller oppdatert skal inn:
       while ((vektene[i] < vekt)  &&  (i < antall))  i++;
       ++antall;                                //  Antallet telles opp igjen.
       for (j = antall-1; j > i; j--)           //  Flytter alle etter opp ett
          {  keyene[j] = keyene[j-1];  vektene[j] = vektene[j-1];  }  // hakk.
        keyene[i] = key;  vektene[i] = vekt;    //  Smetter innimellom.
       return true;                             //  Ny/oppdatert er lagt inn.
    }


   /**
    *  Fjerner og returnerer det aller første elementet i/på fringen.
    *
    *  @return   Fringens aller første element
    */
    int remove()  {
      int key = keyene[0];                //  Gjemmer unna det 1.elementet.
      for (int i = 0;  i < antall-1;  i++)  { //  ALLE etterfølgende elementer
          keyene[i] = keyene[i+1];            //  flyttes ned ETT hakk i BEGGE
          vektene[i] = vektene[i+1];          //  arrayer (venstre-shift).
      }
      --antall;                           //  Antallet i/på fringen reduseres.
      return key;                         //  Returnerer det 1.elementet.
    }
};

#endif
