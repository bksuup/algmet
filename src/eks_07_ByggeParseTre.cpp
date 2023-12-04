/**
 *   Programeksempel nr 7 - Bygger et parse tre ut fra et postfix regneuttrykk.
 *
 *   Eksempel som viser hvordan man leser et postfix regneuttrykk, og samtidig
 *   bygger et tre i hukommelsen, nedenfra og opp, og vha. en stakk med pekere
 *   til noder. ALLE BLADNODENE inneholder EN bokstav/ETT siffer,
 *   og ALLE INTERNE noder inneholder KUN '+' eller '*'.
 *   Til slutt ligger det KUN en peker til treets rot tilbake p� stakken.
 *
 *   Algoritme: - Leser ett og ett tegn (bokstav/siffer, '+' eller '*')
 *              - Er det en bokstav/siffer, push'es den bare p� stakken
 *              - Er det '+' eller '*', pop'es av stakken noder som blir h�yre
 *                og venstre subtre, f�r rotnoden selv push'es p� stakken
 *
 *   NB: Postfix-utrykket M� best� av kun EN bokstav/ETT siffer, '+' og '*'.
 *       Det trenger IKKE � v�re blanke mellom dem.
 *       Uttrykket kan IKKE avslutte med en eller flere blanke.
 *
 *   @file     EKS_07_ByggeParseTre.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <stack>                     //  stack fra STL
using namespace std;


/**
 *  Node (med ID/key/data og venstre oh h�yre pekere til nodens barn).
 */
struct Node {
    char ID;
    Node *left, *right;                    //  Initierende constructor:
    Node(char id)  {  ID = id;  left = right = nullptr;  }
};


void travserPostorder(const Node* node);   //  Deklarasjon av prototyper:
void travserInorder(const Node* node);


/**
 *  Hovedprogrammet:
 */
int main()  {
    stack <Node*> stakk;                 //  Stakk med Node-pekere!!!
    char tegn;                           //  Innlest tegn fra tastaturet.
    Node* nyNode;                        //  Peker til ny node i treet.

    cout << "\n\nSkriv et postfix-regneuttrykk:\n";

                                         // Leser ALLE tegn, ogs� ' ' og '\n'.
    while ((tegn = cin.get())!= '\n') {         //  Enn� ikke slutt p� input:
        while (tegn == ' ')  tegn = cin.get();  //  Skipper alle ' ' (blanke).
        nyNode = new Node(tegn);                //  Lager en ny node.
        if (tegn == '+' || tegn == '*') {       //  Om er INTERN node:
            nyNode->right = stakk.top();   stakk.pop(); //  Hekter p� h�yre og
            nyNode->left  = stakk.top();   stakk.pop(); //   venstre subtre.
        }
        stakk.push(nyNode);                     //  Push'er (rot)noden.
    }



    //  EKSTRA:  Tester hvordan treet har blitt:
    //           NB: ENN� IKKE L�RT OM HVORDAN KODE DETTE/TRAVERSERE TR�R !!!
                                    cout << "\n\n";
    travserPostorder(stakk.top());  cout << "\n\n";
    travserInorder(stakk.top());    cout << "\n\n";

    return 0;
}


/*
   Sjekk/test:
   ===========

   Postorder-uttrykket:      3 4 + 3 2 * + 2 + 5 3 * 4 2 + * +

   Gir inorder-uttrykket:    ((((3 + 4) + (3 * 2)) + 2) + ((5 * 3) * (4 + 2)))

   Dette tilsvarer parse treet:                        +
                                                /             \
                                            +                    *
                                         /     \              /     \
                                      +         2            *       +
                                    /   \                   / \     / \
                                   +     *                 5   3   4   2
                                  / \   / \
                                 3   4 3   2
*/



//  ================   EKSTRA (forel�pig litt kryptisk(?)):   ================

/**
 *  REKURSIV traversering (og utskrift) av et tre p� en postorder m�te.
 *
 *  @param   node  -  Peker til en node
 */
void travserPostorder(const Node* node) {
    if (node) {                          //  Peker til en reell node:
        travserPostorder(node->left);    //  Bes�ker venstre subtre/barn.
        travserPostorder(node->right);   //  Bes�ker h�yre subtre/barn.
        cout << ' ' << node->ID;         //  Skriver ("bes�ker") seg selv.
    }
}


/**
 *  REKURSIV traversering (og utskrift) av et tre p� en inorder m�te.
 *
 *  @param   node  -  Peker til en node
 */
void travserInorder(const Node* node) {
    if (node) {                          //  Peker til en reell node:
        if (node->left) cout << '(';     //  Skriver '(' f�r subtreet.
        travserInorder(node->left);      //  Bes�ker venstre subtre/barn.
        cout << ' ' << node->ID;         //  Skriver ("bes�ker") seg selv.
        travserInorder(node->right);     //  Bes�ker h�yre subtre/barn.
        if (node->right) cout << ')';    //  Skriver ')' etter subtreet.
    }
}
