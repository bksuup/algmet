/**
 *   Programeksempel nr 18 - (Rekursive) operasjoner p� tr�r - case 4.
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
 *          (vilk�rlig hvilken sorteringsmetode/-algoritme man bruker).
 *       Oppgave C:
 *          - Kun innmaten i 'besokOppgC'  (og 'finnNoder')
 *
 *  (Dette var oppg.nr.3 p� eksamen 19/12-2017 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_18_Tre_Case4.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>             //  cout
using namespace std;


/**
 *  Node (med ID/key/data og venstre/h�yre pekere til nodens barn).
 */
struct Node {
    char ID;                 //  Nodens ID/key/n�kkel/navn (en bokstav).
    Node *left, *right;      //  Peker til begge subtr�rne (evt. 'nullptr').
    Node(char id)  {  ID = id;   left = right = nullptr;  }
};


Node* gRoot = nullptr;       ///<  Rotpeker til hele treet.
Node* gNoder[10];            ///<  For � opprette og behandle treet/noder.
Node *gNode1 = nullptr,      ///<  Node nr.1 p� feil plass.           (Oppg.C)
     *gNode2 = nullptr,      ///<  Node nr.2 p� feil plass.           (Oppg.C)
     *gForrige = nullptr;    ///<  Hjelpepeker for � finne 'gNode1/2' (Oppg.C)
int   gMaxHOB = -1;          ///<  = HoydeOddetallsBladnode           (Oppg.A)
int   gNivaa = -1;           ///<  Aktuell nodes niv�.                (Oppg.A)
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


  cout << "\n\nTester oppgave A - Finner maxniv�et for oddetalls bladnode:\n";
    traverserOppgA(gRoot);
    cout << "H�yeste niv� for oddetalls terminalnode er: " << gMaxHOB << '\n';


    cout << "\n\nTester oppgave B - Gj�r om til bin�rt s�ketre:\n";
    //  Uten � endre et tres struktur/form, gj�res et vilk�rlig bin�rt tre
    //  om til et bin�rt S�KETRE (vha. de tre neste funksjonene):
    gNr = 0;
    traverserOppgB(gRoot);        //  Henter alle treets IDer.
    gKeyer[0] = '\0';             //  'insertionSort' krever 'sentinel key'!
    insertionSort(gKeyer, gNr);   //  Sorterer disse stigende alfabetisk!

    gNr = 0;                    //  Setter alle treets IDer igjen, s� f�r et
    traverserInorder2(gRoot);   //    bin�rt s�ketre. Dette M� gj�res inorder!

   cout << "Bin�rt s�ketre, traversert inorder (dvs. alfabetisk utskrift):\n";
   traverserInorder(gRoot);    //  Skriver ut nytt s�ketres innhold (sortert).


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
 *  OPPGAVE A - Finner ut om noden er p� et h�yere enn hittil
 *              registrert oddetalls niv�.
 *
 *  @param   node  -  Aktuell node � behandle
 */
void besokOppgA(Node* node) {       //  Bladnode, p� oddetalls niv� og h�yest:
  if (!node->left  &&  !node->right  &&  (gNivaa % 2)  &&  (gNivaa > gMaxHOB))
     gMaxHOB = gNivaa;
}


/**
 *  OPPGAVE C - Finner ut om 'node' er p� feil plass
 *              - oppdaterer is�fall 'gNode1' eller 'gNode2'.
 *
 *  @param   node  -  Aktuell node � behandle
 */
void besokOppgC(Node* node) {
    if (gForrige) {                 //  Er IKKE 1.noden i inorder rekkef�lge:
        if (gForrige->ID > node->ID) {       //  Forrige har st�rre ID:
            if (!gNode1)  gNode1 = gForrige; //  FORRIGE var den 1.ombyttede.
            else gNode2 = node;              //  N�V�RENDE er den 2.ombyttede.
        }
    }
    gForrige = node;                         //  'gForrige' hopper etter.
}


/**
 *  Bygger et bin�rt tre - likt med venstre figur i oppgave B.
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
 *  OPPGAVE C - Finner og setter pekere til to byttede noder i et bin.s�ketre.
 *
 *  @param   node  -  Aktuell node � behandle
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
 *  Oppgave B - Sorterer 'arr' i stigende rekkef�lge (jfr forelesning 10).
 *
 *  @param   arr  -  Array som skal sorteres stigende
 *  @param   N    -  Antall elementer � sortere i arrayen
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
 *  EXTRA - Traverser rekursivt inorder et bin�rt tre og skriver dets innhold.
 *
 *  @param   node  -  Aktuell node � behandle
 */
void traverserInorder(Node* node) {
    if (node) {
        traverserInorder(node->left);
        cout << ' ' << node->ID;            //  = 'besok'
        traverserInorder(node->right);
    }
}


/**
 *  OPPGAVE B - Setter rekursivt inorder nodenes fortl�pende sorterte ID'er,
 *              slik at treet blir et bin�rt s�ketre.
 *
 *  @param   node  -  Aktuell node � behandle
 */
void traverserInorder2(Node* node) {
    if (node) {                    //  Treet M� traverseres inorder!!!
        traverserInorder2(node->left);
        node->ID = gKeyer[++gNr];  //  = 'besok', som setter nodenes ID ved �
                                   //    sekvensielt fortl�pende hente den fra
                                   //    den sorterte arrayen 'gKeyer'.
        traverserInorder2(node->right);
    }
}


/**
 *  OPPGAVE A - Finner rekursivt maxniv�et for evt oddetalls bladnode(r).
 *
 *  @param   node  -  Aktuell node � behandle
 */
void traverserOppgA(Node* node) {
    if (node) {
        gNivaa++;                        //  G�r til ett h�yere niv�.
        besokOppgA(node);                //  Vilk�rlig om treet visiteres
        traverserOppgA(node->left);      //  pre-, in- eller postorder.
        traverserOppgA(node->right);     //  Dvs. 'besokOppgA' kan st� f�r,
                                         //  mellom eller etter kallene!
        gNivaa--;                        // G�r tilbake til 'mor' igjen.
    }
}


/**
 *  OPPGAVE B - Uten � endre et tres struktur/form, gj�res et vilk�rlig
 *              bin�rt tre om til et bin�rt s�ketre.
 *
 *  @param   node  -  Aktuell node � behandle
 */
void traverserOppgB(Node* node) {
    if (node) {
        traverserOppgB(node->left);   //  Vilk�rlig om treet visiteres
        traverserOppgB(node->right);  //     pre-, in- eller postorder.
        gKeyer[++gNr] = node->ID;     //  = 'besok', som samler opp alle
    }                                 //     nodenes ID'er i en egen array.
}
