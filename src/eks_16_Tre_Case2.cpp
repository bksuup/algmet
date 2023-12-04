/**
 *   Programeksempel nr 16 - (Rekursive) operasjoner p� tr�r - case 2.
 *
 *   For programmets funksjonalitet se:  TreCase2.pdf
 *
 *   (Dette var oppg.nr.3 p� eksamen 17/8-2000 i L189A-Algoritmiske metoderI)
 *
 *   @file     EKS_16_Tre_Case2.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <iomanip>           //  setw
#include <cstdlib>           //  (s)rand
using namespace std;


/**
 *  Node (med verdi, ID/data, summen av begge subtr�rnes verdi,
 *  venstre/h�yre pekere til nodens barn og peker til forelder/mor).
 */
struct Node {
    int   verdi;              //  Nodens verdi. Sortert p� denne (IKKE ID!).
    char  ID;                 //  Nodens ID/navn (en bokstav).
    int   sum;                //  Summen av alle barnas verdi.
    Node* left;               //  Peker til venstre subtre.
    Node* right;              //  Peker til h�yre subtre.
    Node* forelder;           //  Peker til nodens forelder/"mor".
};


void  besok(Node* node); 
Node* generate(const int depth, const int probability);
void  settForelder(Node* node);            //  OPPGAVE 3B
void  settSum(Node* node);                 //  OPPGAVE 3A
void  traverse(Node* node);                //  Alle de tre andre funksjonene   
                                           //    er ekstra kode, KUN for �    
                                           //    vise/skrive ut at oppgavens
                                           //    funksjoner fungerer korrekt.

Node* gRoot = nullptr;        ///<  Peker til treets rot.
int   gNumber = 0;            ///<  F�rste node har verdi=1 og ID='A'.
                              //      Brukes for � auto-generere et testtre.


/**
 *  Hovedprogrammet:
 */
int main() {
    char ch;

    srand(0);                   //  Brukes ifm. tilfeldighet/randomisering.

    cout << "\nNodene i starttreet:\n";
                                //  Genererer et testtre (max. 6 niv�er,
    gRoot = generate(5, 80);    //      80% sjanse for � lage et subtre)
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
 *  Bes�ker/visit/skriver ut en nodes innhold/data.
 *
 *  @param   node  -  Aktuell node � skrive ut
 */
void besok(Node* node) {
    cout << setw(4) << node->verdi << " -  ID: " << node->ID
         << "   sum:" << setw(4) << node->sum;
    if (node->forelder)  cout << "   'mor': " << node->forelder->ID;
    cout << '\n';
}


/**
 *  Rekursiv funksjon som (om mulig) genererer en node 
 *  og KANSKJE dets venstre og/eller h�yre subtre.
 *
 *  @param    depth        -  Aktuell (dybde)niv� i treet
 *  @param    probability  -  Sannsynlighet for � lage subtre
 *  @return   Peker til det genererte (sub)treet
 */
Node* generate(const int depth, const int probability) {
    Node* rot = nullptr;                   //  Peker til det som returneres.
                                           //  NB: Initieres til 'nullptr'!
    if (depth > 0) {                       //  Kan fortsatt legge til et niv�:
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
 *  @param   node  -  Aktuell node � behandle og dens evt subtr�r
 */
void settForelder(Node * node) { 
    if (node) {                               //  Noden/roten er ikke tom:
        settForelder(node->left);             //  Rekursiv setting av foreldre
        settForelder(node->right);            //    i hvert av subtr�rne.
        node->forelder = nullptr;             //  Setter EGEN forelder.
        if (node->left)   node->left->forelder = node;  // Setter evt hvert
        if (node->right)  node->right->forelder = node; //  av barnas  
    }                                                   //  'forelder' til
}                                                       //  � v�re en selv.


/**
 *  OPPGAVE A - 'node' sin 'sum' settes rekursivt til � v�re egen 'verdi'
 *              PLUSS SUMMEN av verdiene i begge subtr�rne.
 *
 *  @param   node  -  Aktuell node � behandle
 */
void settSum(Node * node) {
    if (node) {                                 //  Noden/roten er ikke tom:
        settSum(node->left);                    //  Rekursiv setting av summen
        settSum(node->right);                   //    i hvert av subtr�rne.
        node->sum = node->verdi;                        // Initierer egen sum.
        if (node->left)   node->sum += node->left->sum; // Legger evt til 
        if (node->right)  node->sum += node->right->sum; //  summen for hvert
    }                                                  //  av barna/subtr�rne.
}


/**
 *  Traverserer/g�r gjennom et tre rekursivt p� en INORDER m�te.
 *
 *  @param   node  -  Aktuell node � behandle
 *  @see     besok(...)
 */
void traverse(Node* node) {
    if (node) {
        traverse(node->left);
        besok(node);
        traverse(node->right);
    }
}