/**
 *   Programeksempel nr 16 - (Rekursive) operasjoner på trær - case 2.
 *
 *   For programmets funksjonalitet se:  TreCase2.pdf
 *
 *   (Dette var oppg.nr.3 på eksamen 17/8-2000 i L189A-Algoritmiske metoderI)
 *
 *   @file     EKS_16_Tre_Case2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <iomanip>           //  setw
#include <cstdlib>           //  (s)rand
using namespace std;


/**
 *  Node (med verdi, ID/data, summen av begge subtrærnes verdi,
 *  venstre/høyre pekere til nodens barn og peker til forelder/mor).
 */
struct Node {
    int   verdi;              //  Nodens verdi. Sortert på denne (IKKE ID!).
    char  ID;                 //  Nodens ID/navn (en bokstav).
    int   sum;                //  Summen av alle barnas verdi.
    Node* left;               //  Peker til venstre subtre.
    Node* right;              //  Peker til høyre subtre.
    Node* forelder;           //  Peker til nodens forelder/"mor".
};


void  besok(Node* node); 
Node* generate(const int depth, const int probability);
void  settForelder(Node* node);            //  OPPGAVE 3B
void  settSum(Node* node);                 //  OPPGAVE 3A
void  traverse(Node* node);                //  Alle de tre andre funksjonene   
                                           //    er ekstra kode, KUN for å    
                                           //    vise/skrive ut at oppgavens
                                           //    funksjoner fungerer korrekt.

Node* gRoot = nullptr;        ///<  Peker til treets rot.
int   gNumber = 0;            ///<  Første node har verdi=1 og ID='A'.
                              //      Brukes for å auto-generere et testtre.


/**
 *  Hovedprogrammet:
 */
int main() {
    char ch;

    srand(0);                   //  Brukes ifm. tilfeldighet/randomisering.

    cout << "\nNodene i starttreet:\n";
                                //  Genererer et testtre (max. 6 nivåer,
    gRoot = generate(5, 80);    //      80% sjanse for å lage et subtre)
    traverse(gRoot);            //  Traverserer (og viser) treet.
    cin >> ch;

    cout << "\n\nTester oppgave A - Nodene etter at 'sum' er satt:\n";
    settSum(gRoot);
    traverse(gRoot);
    cin >> ch;

    cout << "\n\nTester oppgave B - Nodene etter at 'forelder' er satt:\n";
    settForelder(gRoot);
    traverse(gRoot);

    cout << "\n\n";
    return 0;
}


/**
 *  Besøker/visit/skriver ut en nodes innhold/data.
 *
 *  @param   node  -  Aktuell node å skrive ut
 */
void besok(Node* node) {
    cout << setw(4) << node->verdi << " -  ID: " << node->ID
         << "   sum:" << setw(4) << node->sum;
    if (node->forelder)  cout << "   'mor': " << node->forelder->ID;
    cout << '\n';
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
                                           //  4x linjer med "besok":
            rot->verdi = ++gNumber;             //  Legger inn egen verdi.
            rot->ID = static_cast <char> ('A'-1+gNumber);  //  Legger inn ID.
            rot->sum = 0;                       //  Nullstiller egen sum.
            rot->forelder = nullptr;            //  Nullstiller egen forelder.

            rot->right = generate(depth-1, probability); //Lager evt h.subtre.
        }
    }
    return rot;                     //  Returnerer generert tre eller nullptr.
}


/**
 *  OPPGAVE B - ALLE nodene i (sub)treet under 'node' sin 'forelder' 
 *              settes rekursivt.
 *
 *  @param   node  -  Aktuell node å behandle og dens evt subtrær
 */
void settForelder(Node * node) { 
    if (node) {                               //  Noden/roten er ikke tom:
        settForelder(node->left);             //  Rekursiv setting av foreldre
        settForelder(node->right);            //    i hvert av subtrærne.
        node->forelder = nullptr;             //  Setter EGEN forelder.
        if (node->left)   node->left->forelder = node;  // Setter evt hvert
        if (node->right)  node->right->forelder = node; //  av barnas  
    }                                                   //  'forelder' til
}                                                       //  å være en selv.


/**
 *  OPPGAVE A - 'node' sin 'sum' settes rekursivt til å være egen 'verdi'
 *              PLUSS SUMMEN av verdiene i begge subtrærne.
 *
 *  @param   node  -  Aktuell node å behandle
 */
void settSum(Node * node) {
    if (node) {                                 //  Noden/roten er ikke tom:
        settSum(node->left);                    //  Rekursiv setting av summen
        settSum(node->right);                   //    i hvert av subtrærne.
        node->sum = node->verdi;                        // Initierer egen sum.
        if (node->left)   node->sum += node->left->sum; // Legger evt til 
        if (node->right)  node->sum += node->right->sum; //  summen for hvert
    }                                                  //  av barna/subtrærne.
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