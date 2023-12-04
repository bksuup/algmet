/**
 *   Programeksempel nr 7 - Bygger et parse tre ut fra et postfix regneuttrykk.
 *
 *   Eksempel som viser hvordan man leser et postfix regneuttrykk, og samtidig
 *   bygger et tre i hukommelsen, nedenfra og opp, og vha. en stakk med pekere
 *   til noder. ALLE BLADNODENE inneholder EN bokstav/ETT siffer,
 *   og ALLE INTERNE noder inneholder KUN '+' eller '*'.
 *   Til slutt ligger det KUN en peker til treets rot tilbake på stakken.
 *
 *   Algoritme: - Leser ett og ett tegn (bokstav/siffer, '+' eller '*')
 *              - Er det en bokstav/siffer, push'es den bare på stakken
 *              - Er det '+' eller '*', pop'es av stakken noder som blir høyre
 *                og venstre subtre, før rotnoden selv push'es på stakken
 *
 *   NB: Postfix-utrykket MÅ bestå av kun EN bokstav/ETT siffer, '+' og '*'.
 *       Det trenger IKKE å være blanke mellom dem.
 *       Uttrykket kan IKKE avslutte med en eller flere blanke.
 *
 *   @file     EKS_07_ByggeParseTre.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>                  //  cout
#include <stack>                     //  stack fra STL
using namespace std;


/**
 *  Node (med ID/key/data og venstre oh høyre pekere til nodens barn).
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

                                         // Leser ALLE tegn, også ' ' og '\n'.
    while ((tegn = cin.get())!= '\n') {         //  Ennå ikke slutt på input:
        while (tegn == ' ')  tegn = cin.get();  //  Skipper alle ' ' (blanke).
        nyNode = new Node(tegn);                //  Lager en ny node.
        if (tegn == '+' || tegn == '*') {       //  Om er INTERN node:
            nyNode->right = stakk.top();   stakk.pop(); //  Hekter på høyre og
            nyNode->left  = stakk.top();   stakk.pop(); //   venstre subtre.
        }
        stakk.push(nyNode);                     //  Push'er (rot)noden.
    }



    //  EKSTRA:  Tester hvordan treet har blitt:
    //           NB: ENNÅ IKKE LÆRT OM HVORDAN KODE DETTE/TRAVERSERE TRÆR !!!
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



//  ================   EKSTRA (foreløpig litt kryptisk(?)):   ================

/**
 *  REKURSIV traversering (og utskrift) av et tre på en postorder måte.
 *
 *  @param   node  -  Peker til en node
 */
void travserPostorder(const Node* node) {
    if (node) {                          //  Peker til en reell node:
        travserPostorder(node->left);    //  Besøker venstre subtre/barn.
        travserPostorder(node->right);   //  Besøker høyre subtre/barn.
        cout << ' ' << node->ID;         //  Skriver ("besøker") seg selv.
    }
}


/**
 *  REKURSIV traversering (og utskrift) av et tre på en inorder måte.
 *
 *  @param   node  -  Peker til en node
 */
void travserInorder(const Node* node) {
    if (node) {                          //  Peker til en reell node:
        if (node->left) cout << '(';     //  Skriver '(' før subtreet.
        travserInorder(node->left);      //  Besøker venstre subtre/barn.
        cout << ' ' << node->ID;         //  Skriver ("besøker") seg selv.
        travserInorder(node->right);     //  Besøker høyre subtre/barn.
        if (node->right) cout << ')';    //  Skriver ')' etter subtreet.
    }
}
