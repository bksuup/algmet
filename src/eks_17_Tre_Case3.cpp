/**
 *   Programeksempel nr 17 - (Rekursive) operasjoner på trær - case 3.
 *
 *   For programmets funksjonalitet se:  TreCase3.pdf
 *
 *   (Dette var oppg.nr.3 på eksamen 13/12-1999 i L189A-Algoritmiske metoderI)
 *
 *   @file     EKS_17_Tre_Case3.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <cstdlib>           //  (s)rand
using namespace std;


/**
 *  Node (med ID/key/data, nivå og venstre/høyre pekere til nodens barn).
 */
struct Node {
    char ID;		            //  Nodens ID/key/navn (en bokstav).
    int  nivaa;	                //  Nodens nivå i treet ift. rotnoden.
    Node* left;	                //  Peker til venstre subtre, evt nullptr.
    Node* right;                //  Peker til høyre subtre, evt nullptr.
    Node() { ID = '-';  nivaa = 0;  left = right = nullptr; }
};


void  besok(Node* node);
void  bladTilRot(Node* node, Node* blad);
void  finnVerdier(Node* node, int & sumNivaa, int & antall);    //  OPPGAVE B
Node* generate(const int depth, const int probability);
void  settNivaa(Node* node);                                     //  OPPGAVE A
void  skrivForfedre(Node* node);                                 //  OPPGAVE C
void  traverse(Node* node);                  //  Alle de fem andre funksjonene
                                             //    er ekstra kode, KUN for å
                                             //    vise/skrive ut at oppgavens
                                             //    funksjoner fungerer korrekt.

Node* gRoot;                 ///<  Peker til treets rot.
int   gNumber = 65;          ///<  Første node er 'A' (ASCII-tegn nr.65).


/**
 *  Hovedprogrammet:
 */
int main() {
    int sumNiva = 0, antall = 0;  //  Viktig at begge er nullstilt.
    char ch;

    srand(0);                     //   Brukes ifm. tilfeldighet/randomisering.

    cout << "\nNodene i starttreet:\n";
                                  //  Genererer et testtre (max. 6 nivåer,
    gRoot = generate(5, 80);      //      80% sjanse for å lage et subtre)
    traverse(gRoot);              //  Traverserer (og viser) treet.
    cin >> ch;

    cout << "\n\nTester oppgave A - Nodene etter at 'nivaa' er satt:\n";
    settNivaa(gRoot);             //  Setter ALLE nodenes nivå.
    traverse(gRoot);              //  Traverserer (og viser) treet.
    cin >> ch;

    cout << "\n\nTester oppgave B - Finner nivåer TOTALT og antall noder:\n";
    finnVerdier(gRoot, sumNiva, antall);   //  Finner summen av nodenes nivå
                                           //      og antall.
    cout << "Sum nivå:  " << sumNiva << "\tAntall: " << antall << '\n';

    cout << "Gjennomsnittsnivået i treet:  "         //  Regner ut gj.snittlig
         << static_cast <float> (sumNiva) / antall;  //    nivå.
    cin >> ch;

    cout << "\n\nTester oppgave C - Alle bladnodenes forfedre:\n";
    skrivForfedre(gRoot);         //  Skriver forgjengere til ALLE bladnodene.
    cout << "\n\n";
    return 0;
}


/**
 *  Besøker/visit/skriver ut en nodes innhold/data.
 *
 *  @param   node  -  Aktuell node å skrive ut
 */
void besok(Node* node) {       //  Viser innholdet i EN node.
    cout << ' ' << node->ID << ":  " << node->nivaa << '\n';
}


/**
 *  Skriver rekursivt (baklengs) nodenes ID på vei fra 'node' til 'blad'.
 *
 *  Funksjonen er en alternativ delløsning av oppgave C.
 *
 *  @param   node  -  Rota i nåværende subbtre
 *  @param   blad  -  Bladnoden det skrives stien frem til
 */
void  bladTilRot(Node* node, Node* blad) {
    if (node != blad) {             //  Har IKKE nådd fram:
                                    //  Bladnoden er ned til venstre (mindre):
        if (blad->ID < node->ID)  bladTilRot(node->left, blad);
                                    //  Bladnoden er til høyre (større):
        else bladTilRot(node->right, blad);
    }
    cout << node->ID << ' ';         //  Skriver nodens ID.
    if (node == gRoot) cout << '\n'; //  Skriver '\n' når nådd rota.
}


/**
 *  OPPGAVE B - Summerer (rekursivt) opp TOTALT antall nivåer og antall noder.
 *
 *  @param   node      -  Aktuell node å behandle
 *  @param   sumNivaa  -  Nodenes TOTALE nivå summert (referanseoverført)
 *  @param   antall    -  Totalt antall noder i treet (referanseoverført)
 */
void finnVerdier(Node* node, int & sumNivaa, int & antall) {
    if (node) {                     //  Noden er en reell node:
        sumNivaa += node->nivaa;    //  Summerer opp nodenes nivåer TOTALT.
        antall++;                   //  Teller opp deres totale antall.
                                    //  NB: Ovenstående to linjer står her
                                    //      preorder, men de kunne like gjerne
                                    //      stå inorder eller postorder !!!
        finnVerdier(node->left,  sumNivaa, antall);   //  Besøker v.subtre.
        finnVerdier(node->right, sumNivaa, antall);   //  Besøker h.subtre.
    }
}


/**
 *  Rekursiv funksjon som (om mulig) genererer en node
 *  og KANSKJE dets venstre og/eller høyre subtre.
 *
 *  @param    depth        -  Aktuell (dybde)nivå i treet
 *  @param    probability  -  Sannsynlighet for å lage subtre
 *  @return   Peker til det genererte (sub)treet
 */
Node* generate(const int depth, const int probability) {
    Node* rot = nullptr;                   //  Peker til det som returneres.
                                           //  NB: Initieres til 'nullptr'!
    if (depth > 0) {                       //  Kan fortsatt legge til et nivå:
        if (rand() % 100 < probability) {  //  Trukket tall i rett intervall:
            rot = new Node;                //  Lager en ny node.
            rot->left = generate(depth-1, probability); //Lager evt v.subtre.
            rot->ID = static_cast <char> (gNumber++);  //  Legger inn egen ID.
            rot->right = generate(depth-1, probability); //Lager evt h.subtre.
        }
    }
    return rot;                     //  Returnerer generert tre eller nullptr.
}


/**
 *  OPPGAVE A - Setter (rekursivt) alle treets noders nivå ift. rota.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void settNivaa(Node* node) {
                           //  NB: Vet at 'node' ALLTID er ulikt 'nullptr' !!!
                           //       (pga. forutsetningen og kallene nedenfor)
    if (node->left) {                      //  Har et reelt venstre barn:
        node->left->nivaa = node->nivaa+1; //  Setter barnets nivå.
        settNivaa(node->left);             //  Det samme rekursivt for v.barn.
    }

    if (node->right) {                      //  Har et reelt høyre barn:
        node->right->nivaa = node->nivaa+1; //  Setter barnets nivå.
        settNivaa(node->right);             // Det samme rekursivt for h.barn.
    }
}


/**
 *  OPPGAVE C - Skriver (rekursivt) ALLE bladnodenes sti fra rota.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void skrivForfedre(Node* node) {
    if (node) {                               //  Noden er reell:
        if (!node->left  &&  !node->right) {  //  Noden er en bladnode:
                           //  Går fra roten og skriver ut nodene på veien ned
                           //    til bladnoden. Finner veien dit da treet er
                           //    et binært søketre, og kjenner bladnodens ID:
            cout << '\t';                     //  Innrykk FØR utskriften.
            Node* q = gRoot;                  //  Starter i rota.
            while (q)  {                      //  Løkke til passert bladnoden:
                                //  Kan IKKE skrive: while (q != node),
                                //    for da vil ikke selve bladnoden selv bli
                                //    skrevet ut. Dog kan den selvsagt skrives
                                //    ut manuelt etter selve while-løkka.
                cout << q->ID << ' ';        //  Skriver nodes (forfedres) ID.
                                // Blar videre, helt til har PASSERT 'node'.
                q = (node->ID < q->ID) ? q->left : q->right;
            }
            cout << '\n';                    //  '\n' ETTER utskriften.

//  Istedet for while-løkka over KUNNE vi ha laget en rekursiv funksjon som
//  starter i rota og leter ned til bladnoden vha. treets binære sortering.
//  Den skriver ut nodenes navn BAKLENGS (FRA bladnode og OPP TIL rota) når
//  den trekker seg tilbake/terminerer:
//          bladTilRot(gRoot, node);

        } else {                         //  IKKE bladnode:  Finner og skriver
            skrivForfedre(node->left);       //    forfedre for bladnoder i
            skrivForfedre(node->right);      //    venstre og høyre subtrær.
        }
    }
}


/**
 *  Traverserer/går gjennom et tre rekursivt på en INORDER måte.
 *
 *  @param   node  -  Aktuell node å behandle
 *  @see     besok(...)
 */
void traverse(Node* node) {
    if (node) {
        traverse(node->left);
        besok(node);
        traverse(node->right);
    }
}
