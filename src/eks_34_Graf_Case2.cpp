/**
 *   Programeksempel nr 34 - (Rekursive) operasjoner p� graf - case 2.
 *
 *   For programmets funksjonalitet se:  GrafCase2.pdf
 *
 *  (Dette var oppg.nr.3 p� eksamen 12/12-1995 i LO164A-Algoritmiske metoder)
 *
 *   @file     EKS_34_Graf_Case2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>              //  cout, cin
#include <fstream>               //  ifstream
#include <cctype>                //  toupper
using namespace std;


const int MAXNODER = 100;        ///<  Max.antall noder.
const int MAXNABOER = 10;        ///<  Max.antall naboer EN node kan ha.
enum  Status { USETT, SETT};     ///<  Status for hver enkelt node.
                                 //    Brukes KUN i 'skrivGraf/nullGraf'.


/**
 *  Struct node (med ID/key/n�kkel, antall kanter ut/naboer, pekere/referanse
 *               til naboene, evt. peker til en kopi av en selv og status om
 *               noden er sett eller ei).
 */
struct Node {
    int   ID;                  //  Nodens ID/navn/key.
    int   antKanter;           //  Antall naboer/kanter ut fra node.
    Node* nabo[MAXNABOER];     //  Pekere til naboene.
    Node* kopi;                //  Peker til evnt. duplikat av en selv.
    Status  status;            //  Brukes KUN i 'skrivGraf/nullGraf'.
    Node(const int id, const int ant) {
        ID = id;  antKanter = ant;  kopi = nullptr;  status = USETT;  }
};


Node* gNoder[MAXNODER];      ///<  Array med peker til hver enkelt node i
                             ///<    grafen. Brukes KUN i "kopierIterativt".
                             //    Bruker indeksene 0 til  'gTotAntNoder'-1
int   gTotAntNoder;          ///<  Totalt antall noder i grafen.
Node* gGrafen;               ///<  Peker til startnoden i HELE grafen.


void kopierIterativt();
void kopierRekursivt(Node* node);
void lesGrafFraFil();
void nullGraf(Node* node);
void skrivGraf(Node* node);


/**
 *  Hovedprogrammet:
 */
int main() {
    char valg;

    lesGrafFraFil();

    gGrafen = gNoder[0];

    cout << "Initiell graf - etter at lest fra fil:";
    skrivGraf(gNoder[0]);   nullGraf(gNoder[0]);

    cout << "\n\n\nVil du teste I(terativt) eller R(ekursivt):  ";
    cin >> valg;   valg = toupper(valg);

    if (valg == 'I') {

        kopierIterativt();

        cout << "\n\nKopi-grafen ved TO gjennomganger vha. for-l�kker:";
        skrivGraf(gNoder[0]->kopi);   nullGraf(gNoder[0]->kopi);
    } else {

        kopierRekursivt(gGrafen);

        cout << "\n\nKopi-grafen ved EN gjennomgang vha. rekursjon:";
        skrivGraf(gGrafen->kopi);   nullGraf(gGrafen->kopi);
    }

    cout << "\n\n";
    return 0;
}


/**
 *  G�r iterativt igjennom og KOPIERER HELE grafen tilknyttet 'node'.
 *
 *  G�r gjennom arrayen TO ganger: En gang for � lage kopi-noder,
 *  en annen gang for � lage tilsvarende pekere mellom disse kopiene.
 */
void kopierIterativt() {
    int i, j;                          //  L�kkevariable.
    for (i = 0; i < gTotAntNoder; i++) //  Lager kopi med like data  (+100
                                       //   (KUN for � SE at er en kopi-node):
        gNoder[i]->kopi = new Node(gNoder[i]->ID + 100, gNoder[i]->antKanter);

    for (i = 0; i < gTotAntNoder ; i++) {   //  G�r gjennom alle kopi-nodene,
       for (j = 0; j < gNoder[i]->antKanter; j++)   //  og oppretter pekere
         gNoder[i]->kopi->nabo[j] = gNoder[i]->nabo[j]->kopi; // nabo-kopiene.
    }
}


/**
 *  G�r rekursivt igjennom og KOPIERER HELE grafen tilknyttet 'node'.
 *
 *  @param    node  -  Noden � kopiere, og ALLE dens etterf�lgere
 */
void kopierRekursivt(Node* node)  {
    int j;                        //  L�kkevariabel.
    if (node->kopi == nullptr) {  //  Noden er enn� ikke kopiert(!)
                                  //  (+200 KUN for � SE at er en kopi-node):
        node->kopi = new Node(node->ID + 200, node->antKanter);

        for (j = 0; j < node->antKanter; j++) {
            kopierRekursivt(node->nabo[j]); // Bes�ker rekursivt ALLE naboene
                                            // ALLE disse kopieres(!)
            node->kopi->nabo[j] = node->nabo[j]->kopi; // Kan trygt bare sette
        }                                              //  pekere til kopiene!
    }
}


/**
 *  Leser inn og oppretter HELE den aktuelle grafen fra fil.
 */
void lesGrafFraFil() {
    int i, j,                                 //  L�kkevariable.
        id, antKanter;                        //  Verdier p�/fra filen.

    ifstream innfil("EKS_34_Graf_Case2.DTA");

    if (innfil) {                             //  Filen er funnet:
        cout << "\n\nLeser inn grafen fra 'EKS_34_Graf_Case2.DTA' .....\n\n";

        innfil >> gTotAntNoder;               //  Leser antall noder i grafen.
        for (i = 0; i < gTotAntNoder; i++) {
            innfil >> antKanter;              //  Antall kanter for hver node.
            gNoder[i] = new Node(i, antKanter);   //  Oppretter nye node.
        }

        for (i = 0; i < gTotAntNoder; i++)  // Fyller ALLE nodenes nabo-array:
            for (j = 0; j < gNoder[i]->antKanter; j++) {  //  For hver node:
                innfil >> id;                      //  Leser nabonodens ID.
                gNoder[i]->nabo[j] = gNoder[id];   //  Setter peker til den.
            }
    } else
        cout << "\n\nFinner ikke filen EKS_34_Graf_Case2.DTA'!\n\n";
}


/**
 *  Nullstiller at "ikke-bes�kt" HELE grafen tilknyttet 'node'.
 *
 *  @param    node  -  Noden � sette "ikke-bes�kt", og ALLE dens etterf�lgere
 */
void nullGraf(Node* node) {
    if (node->status == SETT) {     //  Noden er "bes�kt":
        node->status = USETT;       //  Setter at "ikke-bes�kt".
                                    //  Gj�r de samme for ALLE naboer:
        for (int i = 0;  i < node->antKanter;  i++)
            nullGraf(node->nabo[i]);
    }
}


/**
 *  Skriver rekursivt ut HELE grafen tilknyttet 'node'.
 *
 *  @param    node  -  Noden � skrive ut, og ALLE dens etterf�lgere
 */
void skrivGraf(Node* node) {
    int i;                         //  L�kkevariabel.
    if (node->status == USETT) {   //  Noden er enn� ikke bes�kt:
        node->status = SETT;       //  Setter at SETT, og skriver dens ID:
        cout << "\n\tNode nr." << node->ID << ", har naboene:   ";
        for (i = 0; i < node->antKanter; i++) //  Skriver ALLE naboenes ID:
            cout << node->nabo[i]->ID << "  ";
        for (i = 0; i < node->antKanter; i++) // Skriver/bes�ker ALLE naboene:
            skrivGraf(node->nabo[i]);
    }
}

/*    Grafen:         0 ---- 6
                    / | \    |
                   /  |  \   |
                  1   2   5  |
                         / \ |
                        /   \|
                       3 --- 4
*/
