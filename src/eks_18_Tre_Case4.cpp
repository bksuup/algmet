/**
 *   Programeksempel nr 18 - (Rekursive) operasjoner på trær - case 4.
 *
 *   For programmets funksjonalitet se:  TreCase4.pdf
 *
 *   Mye bruk av rekursive 'traverser'-funksjoner fra:
 *          EKS_12_RekursivTreTraversering.cpp
 *   Oppgaven har ellers mye likhet med oppgave nr.6 i oppgaveheftet.
 *
 *   Viktig nylaget kode er:
 *       Oppgave A:
 *          - Innmaten i 'besokOppgA'
 *       Oppgave B:
 *          - Linjen  " gKeyer[++gNr] = node->ID; "  i 'traverserOppgB'
 *          - Linjen  " node->ID = gKeyer[++gNr]; "  i 'traverserInorder2'
 *          Samt at man foretar stigende sortering av arrayen 'gKeyer'
 *          (vilkårlig hvilken sorteringsmetode/-algoritme man bruker).
 *       Oppgave C:
 *          - Kun innmaten i 'besokOppgC'  (og 'finnNoder')
 *
 *  (Dette var oppg.nr.3 på eksamen 19/12-2017 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_18_Tre_Case4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>             //  cout
using namespace std;


/**
 *  Node (med ID/key/data og venstre/høyre pekere til nodens barn).
 */
struct Node {
    char ID;                 //  Nodens ID/key/nøkkel/navn (en bokstav).
    Node *left, *right;      //  Peker til begge subtrærne (evt. 'nullptr').
    Node(char id)  {  ID = id;   left = right = nullptr;  }
};


Node* gRoot = nullptr;       ///<  Rotpeker til hele treet.
Node* gNoder[10];            ///<  For å opprette og behandle treet/noder.
Node *gNode1 = nullptr,      ///<  Node nr.1 på feil plass.           (Oppg.C)
     *gNode2 = nullptr,      ///<  Node nr.2 på feil plass.           (Oppg.C)
     *gForrige = nullptr;    ///<  Hjelpepeker for å finne 'gNode1/2' (Oppg.C)
int   gMaxHOB = -1;          ///<  = HoydeOddetallsBladnode           (Oppg.A)
int   gNivaa = -1;           ///<  Aktuell nodes nivå.                (Oppg.A)
char  gKeyer[101];           ///<  Array med plass til ALLE treets ID'er.  (B)
int   gNr = 0;               ///<  Aktuell indeks i 'gKeyer'          (Oppg.B)


void  besokOppgA(Node* node);                                  //  Oppgave A
void  besokOppgC(Node* node);                                  //  Oppgave C
Node* byggTre();                                               //  Extra
void  finnNoder(Node* node);                                   //  Oppgave C
void  insertionSort(char arr[], const int N);                  //  Oppgave B
void  traverserInorder(Node* node);                            //  Extra
void  traverserInorder2(Node* node);                           //  Oppgave B
void  traverserOppgA(Node* node);                              //  Oppgave A
void  traverserOppgB(Node* node);                              //  Oppgave B


/**
 *  Hovedprogrammet:
 */
int main() {
    char ch;

    gRoot = byggTre();                    //  Bygger treet i oppgaveteksten.
    traverserInorder(gRoot);              //  Utskriften!  :-)


  cout << "\n\nTester oppgave A - Finner maxnivået for oddetalls bladnode:\n";
    traverserOppgA(gRoot);
    cout << "Høyeste nivå for oddetalls terminalnode er: " << gMaxHOB << '\n';


    cout << "\n\nTester oppgave B - Gjør om til binært søketre:\n";
    //  Uten å endre et tres struktur/form, gjøres et vilkårlig binært tre
    //  om til et binært SØKETRE (vha. de tre neste funksjonene):
    gNr = 0;
    traverserOppgB(gRoot);        //  Henter alle treets IDer.
    gKeyer[0] = '\0';             //  'insertionSort' krever 'sentinel key'!
    insertionSort(gKeyer, gNr);   //  Sorterer disse stigende alfabetisk!

    gNr = 0;                    //  Setter alle treets IDer igjen, så får et
    traverserInorder2(gRoot);   //    binært søketre. Dette MÅ gjøres inorder!

   cout << "Binært søketre, traversert inorder (dvs. alfabetisk utskrift):\n";
   traverserInorder(gRoot);    //  Skriver ut nytt søketres innhold (sortert).


    cout << "\n\n\nTester oppgave C - Finner to stk ombyttede noder:\n";
    cout << "Bytter 'G' og 'S'. \n";
    ch = gNoder[7]->ID;  gNoder[7]->ID = gNoder[9]->ID;  gNoder[9]->ID = ch;
    traverserInorder(gRoot);

    finnNoder(gRoot);

    cout << "\nBytter tilbake 'node1' og 'node2'. \n";
    ch = gNode1->ID;   gNode1->ID = gNode2->ID;   gNode2->ID = ch;
    traverserInorder(gRoot);

    gNode1 = gNode2 = gForrige = nullptr;
    cout << "\n\nBytter 'E' (rota) og 'O'. \n";
    ch = gNoder[1]->ID;  gNoder[1]->ID = gNoder[8]->ID;  gNoder[8]->ID = ch;
    traverserInorder(gRoot);

    finnNoder(gRoot);

    cout << "\nBytter tilbake 'node1' og 'node2'. \n";
    ch = gNode1->ID;   gNode1->ID = gNode2->ID;   gNode2->ID = ch;
    traverserInorder(gRoot);

    cout << "\n\n";
    return 0;
}


/**
 *  OPPGAVE A - Finner ut om noden er på et høyere enn hittil
 *              registrert oddetalls nivå.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void besokOppgA(Node* node) {       //  Bladnode, på oddetalls nivå og høyest:
  if (!node->left  &&  !node->right  &&  (gNivaa % 2)  &&  (gNivaa > gMaxHOB))
     gMaxHOB = gNivaa;
}


/**
 *  OPPGAVE C - Finner ut om 'node' er på feil plass
 *              - oppdaterer isåfall 'gNode1' eller 'gNode2'.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void besokOppgC(Node* node) {
    if (gForrige) {                 //  Er IKKE 1.noden i inorder rekkefølge:
        if (gForrige->ID > node->ID) {       //  Forrige har større ID:
            if (!gNode1)  gNode1 = gForrige; //  FORRIGE var den 1.ombyttede.
            else gNode2 = node;              //  NÅVÆRENDE er den 2.ombyttede.
        }
    }
    gForrige = node;                         //  'gForrige' hopper etter.
}


/**
 *  Bygger et binært tre - likt med venstre figur i oppgave B.
 *
 *  @return   Peker til rota i treet som er bygd
 */
Node* byggTre() {
    gNoder[1] = new Node('A');       gNoder[2] = new Node('G');     //  Setter
    gNoder[3] = new Node('E');       gNoder[4] = new Node('O');     //  opp
    gNoder[5] = new Node('S');       gNoder[6] = new Node('A');     //  level-
    gNoder[7] = new Node('R');       gNoder[8] = new Node('N');     //  order:
    gNoder[9] = new Node('L');
    gNoder[1]->left  = gNoder[2];    gNoder[1]->right = gNoder[3];  //  Kobler
    gNoder[2]->right = gNoder[4];    gNoder[3]->left  = gNoder[5];  //  sammen
    gNoder[3]->right = gNoder[6];    gNoder[5]->left  = gNoder[7];  //  hele
    gNoder[6]->left  = gNoder[8];    gNoder[6]->right = gNoder[9];  //  treet:
    return gNoder[1];                              //  Returnerer rota ('A').
}


/**
 *  OPPGAVE C - Finner og setter pekere til to byttede noder i et bin.søketre.
 *
 *  @param   node  -  Aktuell node å behandle
 *  @see     besokOppgC(...)
 */
void finnNoder(Node* node) {
    if (node) {
        finnNoder(node->left);
        besokOppgC(node);
        finnNoder(node->right);
    }
}


/**
 *  Oppgave B - Sorterer 'arr' i stigende rekkefølge (jfr forelesning 10).
 *
 *  @param   arr  -  Array som skal sorteres stigende
 *  @param   N    -  Antall elementer å sortere i arrayen
 */
void insertionSort(char arr[], const int N) {
    int i, j;
    char v;
    for (i = 2; i <= N; i++) {
        v = arr[i];   j = i;
        while (arr[j - 1] > v) {
            arr[j] = arr[j - 1];   j--;
        }
        arr[j] = v;
    }
}


/**
 *  EXTRA - Traverser rekursivt inorder et binært tre og skriver dets innhold.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void traverserInorder(Node* node) {
    if (node) {
        traverserInorder(node->left);
        cout << ' ' << node->ID;            //  = 'besok'
        traverserInorder(node->right);
    }
}


/**
 *  OPPGAVE B - Setter rekursivt inorder nodenes fortløpende sorterte ID'er,
 *              slik at treet blir et binært søketre.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void traverserInorder2(Node* node) {
    if (node) {                    //  Treet MÅ traverseres inorder!!!
        traverserInorder2(node->left);
        node->ID = gKeyer[++gNr];  //  = 'besok', som setter nodenes ID ved å
                                   //    sekvensielt fortløpende hente den fra
                                   //    den sorterte arrayen 'gKeyer'.
        traverserInorder2(node->right);
    }
}


/**
 *  OPPGAVE A - Finner rekursivt maxnivået for evt oddetalls bladnode(r).
 *
 *  @param   node  -  Aktuell node å behandle
 */
void traverserOppgA(Node* node) {
    if (node) {
        gNivaa++;                        //  Går til ett høyere nivå.
        besokOppgA(node);                //  Vilkårlig om treet visiteres
        traverserOppgA(node->left);      //  pre-, in- eller postorder.
        traverserOppgA(node->right);     //  Dvs. 'besokOppgA' kan stå før,
                                         //  mellom eller etter kallene!
        gNivaa--;                        // Går tilbake til 'mor' igjen.
    }
}


/**
 *  OPPGAVE B - Uten å endre et tres struktur/form, gjøres et vilkårlig
 *              binært tre om til et binært søketre.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void traverserOppgB(Node* node) {
    if (node) {
        traverserOppgB(node->left);   //  Vilkårlig om treet visiteres
        traverserOppgB(node->right);  //     pre-, in- eller postorder.
        gKeyer[++gNr] = node->ID;     //  = 'besok', som samler opp alle
    }                                 //     nodenes ID'er i en egen array.
}
