/**
 *   Programeksempel nr 15 - (Rekursive) operasjoner på trær - case 1.
 *
 *   For programmets funksjonalitet se:  TreCase1.pdf
 *
 *  (Dette var oppg.nr.3 på eksamen 20/12-2011 i IMT2021-Algoritmiske metoder)
 *
 *   @file     EKS_15_Tre_Case1.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>             //  cout
using namespace std;


/**
 *  Node (med ID/key/data og venstre/høyre pekere til nodens barn).
 */
struct Node {
    int ID;
    Node *left, *right;                //  Initierende constructor:
    Node(const char id, Node* l, Node* r) {
        ID = id;  left = l;  right = r; 
    }
};


Node*  gRoot = nullptr;        ///<  Peker til treets rot.


/**
 *  OPPGAVE A - Skriver stien fra 'gRoot' til bladnoden lengst til høyre.
 */
void hoyreGren() {
    Node* node = gRoot;               //  Starter i rota.
    while (node) {                    //  Så lenge ikke nådd helt ned:
        cout << node->ID << ' ';      //  Skriver nodes ID.
                                      //  Går PRIMÆRT TIL HØYRE, subsidiært
        node = (node->right) ? node->right : node->left; // til venstre.
    }
}


/**
 *  OPPGAVE B - Skriver stien fra 'gRoot' til bladnoden 'node'.
 *
 *  @param   node  -  Aktuell node det skal skrives stien ned til
 */
void gren(Node* node) {
    int  id = node->ID;                //  Gjemmer unna søkt bladnodes ID.
    node = gRoot;                      //  Starter i rota.
    while (node) {                     //  Så lenge ikke nådd helt ned:
        cout << node->ID << ' ';       //  Skriver nodes ID (på vei ned).
                                       //  Går til venstre eller høyre:
        node = (id < node->ID) ? node->left : node->right;  
    }                                  //    Blar videre fra duplikate - 
}                                      //      da ikke nådd helt ned ennå!!!


/**
 *  OPPGAVE C - Skriver stiene ned til ALLE bladnoder.
 *
 *  @param   node  -  Aktuell node å undersøke om er bladnode
 */
void grener(Node* node) {
    if (node) {                    //  Bladnode - skriver stien ned til den:
        if (!node->left  &&  !node->right)  {  gren(node);  cout << '\n'; }
        else {                     //  Leter videre nedover etter bladnoder:
            grener(node->left);    //  Besøker venstre subtre.
            grener(node->right);   //  Besøker høyre subtre.
        }
    }
}


/**
 *  Hovedprogrammet:
 */
int main() {
    Node  *n6, *n8, *n11a, *n11b, *n12, *n13a, *n13b,
          *n17, *n28, *n31, *n33, *n34, *n35a, *n35b, *n39;
/*
Bygger treet:          17
                   /        \
                  11         33
                /    \     /    \
               6      13 28     35
                \    /  \ \     / \
                 8  12  13 31  34 39
                    /            /
                   11           35
*/
    n8   = new Node(8, nullptr, nullptr);
    n11b = new Node(11, nullptr, nullptr);
    n13b = new Node(13, nullptr, nullptr);
    n31  = new Node(31, nullptr, nullptr);
    n34  = new Node(34, nullptr, nullptr);
    n35b = new Node(35, nullptr, nullptr);
    n12  = new Node(12, n11b, nullptr);
    n39  = new Node(39, n35b, nullptr);
    n6   = new Node(6, nullptr, n8);
    n13a = new Node(13, n12, n13b);
    n28  = new Node(28, nullptr, n31);
    n35a = new Node(35, n34, n39);
    n11a = new Node(11, n6, n13a);
    n33  = new Node(33, n28, n35a);
    n17  = new Node(17, n11a, n33);
    gRoot  = n17;


    cout << "\n\nTester oppgave A:\n";
    hoyreGren(); cout << "\n\n\n";   //  Utskrift:  17 33 35 39 35


    cout << "Tester oppgave B:\n";
    gren(n31);   cout << '\n';       //  Utskrift:  17 33 28 31
    gren(n8);    cout << '\n';       //  Utskrift:  17 11 6 8
    gren(n35b);  cout << '\n';       //  Utskrift:  17 33 35 39 35
    gren(n13b);  cout << '\n';       //  Utskrift:  17 11 13 13
    gren(n11b);  cout << '\n';       //  Utskrift:  17 11 13 12 11
    gren(n34);   cout << "\n\n\n";   //  Utskrift:  17 33 35 34


    cout << "Tester oppgave C:\n";
    grener(gRoot);                 //  Samme utskrift som seks forrige linjer,
                                   //     bare litt annen linjerekkefølge.

    cout << "\n\n";
    return 0;
}