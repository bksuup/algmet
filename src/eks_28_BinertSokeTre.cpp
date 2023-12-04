/**
 *   Programeksempel nr 28 - Bin�rt s�ketre (BST) - selvlaget enkel klasse.
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen BST.
 *   Denne inneholder IKKE bare 'data' (ID/key/n�kkel), som i de foreg�ende
 *   eksemplene, men ogs� tilknyttede data ('merData').
 *
 *   Det er laget kode for f�lgende funksjoner:
 *     - BST
 *     - ~BST
 *     - void    display() const;
 *     - void    insert(const Data verdi, const MerData merData);
 *     - bool    remove(const Data verdi);
 *     - MerData search(const Data verdi) const;
 *     - void    traverserInorder(Node* node) const;
 *
 *
 *   Orden ( O(...)):
 *    For et BST bygd av N noder, krever search/insert omtrent  2 ln N
 *    sammenligninger i gjennomsnitt. I "worst case" kreves N sammenligninger.
 *    (Dette er n� ALLE nodene KUN har ETT venstre ELLER h�yre barn,
 *    dvs. hele treet er egentlig en LISTE, og man skal finne/sette inn
 *    etter den ALLER siste.)
 *
 *
 *   NB:  - I et bin�rt s�ketre er ALT til venstre for en node ALLTID MINDRE
 *          enn verdien i selve noden, og ALT til h�yre er ST�RRE ELLER LIK.
 *        - LIKE 'data'/ID/key KAN dermed spres til h�yre for hverandre ulikt
 *          nedover i treet, men de vil ALLTID komme rett etter hverandre om
 *          man skriver ut treets noder i INORDER rekkef�lge!
 *        - Ved 'remove' skal ALLTID en node erstattes med den SEKVENSIELT
 *          etterf�lgende noden (om den finnes). For denne vil ALDRI da ha
 *          noe venstre barn, men evt. kun et h�yre subtre.
 *        - 'merData' er laget for � vise at EGENTLIG er det sjeldent at
 *          bare 'data' er det eneste og mest relevante, men at den som
 *          oftest egentlig er n�kkelen til en tilknyttet datamengde.
 *          Dog er 'merData' i dette eksemplet KUN en eneste liten 'string'.
 *
 *   @file     EKS_28_BinertSokeTre.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>          //  cout
#include <string>            //  string
using namespace std;


/**
 *  Container-klassen Bin�rt s�ketre (BST)
 *
 *  Inneholder et bin�rt s�ketre best�ende av 'Node'-structer,
 *  og har et "dummy" 'hode' som har 'data' (ID/key) mindre enn alt annet
 *  i treet. 'hode->right' peker til treets reelle rot !!!
 *
 */
template <typename Data, typename MerData>  //  Vanlig ogs� med 'T', 'T2', ...
class BST {
  private:
      struct Node {                   //  Nodene i det bin�re s�ketreet.
          Data data;                  //  ID/key.
          MerData merData;            //  Tilleggsdata/-info til IDen/keyen.
          Node* left, * right;        //  Peker til venstre/h�yre subtre/barn.
                                      //  Constructor:
          Node(const Data d, const MerData md)  {  data = d;  merData = md;
                                                   left = right = nullptr;  }
      };

      Node*  hode;       //  Dummy-hode, der 'hode->right' er treets rot !!!!!
                         //  Hensiktsmessig � ha n�r rota selv skal slettes.

      void traverserInorder(Node* node) const {
          if (node) {
             traverserInorder(node->left);
             cout << '\t' << node->data;    //  Skriver nodens data/ID/key.
                   if (node->left)          //  Skriver evt. venstre barn:
                           cout << "    V.barn: " << node->left->data;
                   if (node->right)         //  Skriver evt. h�yre barn:
                           cout << "    H.barn:    " << node->right->data;
             cout << '\n';
             traverserInorder(node->right);
          }
      }

  public:
     BST() {                //  Initierer 'hode' - ut fra datatypene:
       hode = new Node(Data(), MerData());
     }

     ~BST()  {    /*  delete <hele treet>   */    }


     void display() const {                 //  Skriver inorder ut HELE treet:
        traverserInorder(hode->right);      //  Starter i den reelle roten.
    }

                  //  Setter inn 'verdi' med tilknyttet 'merData' inn i treet:
     void insert(const Data verdi, const MerData merData) {
       Node * mor = hode,            //  Mor til 'node' (henger hakket etter).
            * node = hode->right;

       if (node) {                   //  Er MINST en node/rot der allerede:
          while (node) {             //  Blar til der skal settes inn NEDERST:
             mor = node;             //  'mor' f�lger etter.
                                     //  'node' leter videre nedover:
             node = (verdi < node->data) ? node->left : node->right;
          }
          node = new Node(verdi, merData);          //  Lager ny som skal inn.
          if (verdi < mor->data)  mor->left = node; //  Hekter inn til v.
          else mor->right = node;                   //    eller h. ift. 'mor'.
       } else                        //  1.noden i treet (rota):
          hode->right = new Node(verdi, merData);
     }

                                          //  Fjerner og returnerer (om mulig)
     bool remove(const Data verdi) {      //    node med IDen 'verdi':
       Node *morFjernes, 	              //  "Mora" til 'fjernes'.
            *fjernes, 	                  //  Den som skal removes/slettes.
            *morEtterfolger,              //  "Mora" til 'etterfolger'.
            *etterfolger;		          //  Den SEKVENSIELT etterf�lgende.

       morFjernes = hode;                 //  Initierer 2x pekere:
       fjernes = hode->right;
                                          //  Blar seg fram til 'verdi'(?):
       while (fjernes  &&  verdi != fjernes->data) {
           morFjernes = fjernes;          //  'morFjernes' hopper etter.
                                          //  'fjernes' blar venstre/h�yre:
           fjernes = (verdi < fjernes->data) ? fjernes->left : fjernes->right;
       }

       if (!fjernes)  return false;       //  Noden ble IKKE funnet.

       etterfolger = fjernes;    //  'fjernes' ER noden som skal slettes !!!
                                 //  CASE 1: =================================
       if (!fjernes->right)      //  Har ingen H�YERE/ST�RRE etterf�lger!
          etterfolger = etterfolger->left; // Etterf�lger er VENSTRE subtre!
                                 //  CASE 2: =================================
       else if (!fjernes->right->left) {
          etterfolger = etterfolger->right; // Etterf�lger er H�YRE subtre!
          etterfolger->left = fjernes->left; //Overtar v.subtre fra 'fjernes'.
       }
                                 //  CASE 3: =================================
       else {                    // M� lete MER etter SEKVENSIELL etterf�lger:
          morEtterfolger = etterfolger->right; // Initierer 'morEtterfolger'.

          while (morEtterfolger->left->left)   //  Blar til NEST nederste
              morEtterfolger = morEtterfolger->left; //  venstre node:

          etterfolger = morEtterfolger->left;  //  'etterfolger' er noden
                                               //     HELT nede til venstre.
                                               //  Overf�rer evt h�yre subtre:
          morEtterfolger->left = etterfolger->right;  // Har jo IKKE v.subtre!

          etterfolger->left = fjernes->left;   // 'etterfolger' tar 'fjernes'
          etterfolger->right = fjernes->right; //    sin plass.
       }

       delete fjernes;	               	//  'fjernes' removes/slettes/fjernes.

                                        //  Flyttet node ('etterfolger')
                                        //  hektes korrekt under 'morfjernes':
       if (verdi < morFjernes->data) morFjernes->left = etterfolger;
       else morFjernes->right = etterfolger;

       return true;                    //  Noden funnet og fjernet.
     }

                                  //  Leter etter node med 'data' lik 'verdi'.
                                  //  Om mulig returneres dens 'merData':
     MerData search(const Data verdi) const {
         Node* node = hode->right;             //  Initierer til rota.
        while (node  &&  node->data != verdi)  //  Leter til funn eller bunns.
              node = (verdi < node->data) ? node->left : node->right;

        if (node) return node->merData;     //  Funnet - 'merData' returneres.
        else return hode->merData;          //  IKKE funnet!
    }
};


/**
 *  Hovedprogrammet:
 */
int main() {
    BST <char, string> bst;

    bst.insert('L', "Liam");     /*  Bygger s�ketreet (inni 'BST'):     */
    bst.insert('C', "Charlie");  /*               L                     */
    bst.insert('F', "Frank");    /*          /         \                */
    bst.insert('T', "Tony");     /*        C             T              */
    bst.insert('P', "Pat");      /*          \          /               */
    bst.insert('N', "Nigel");    /*           F        P                */
    bst.insert('S', "Steve");    /*            \     /   \              */
    bst.insert('R', "Ray");      /*             I   N      S            */
    bst.insert('I', "Ian");      /*                  \    /             */
    bst.insert('O', "Oliver");   /*                   O  R              */
    bst.display();   cout << "\n\n";

    cout << "MerData hentet: " << bst.search('C') << '\n';
    cout << "MerData hentet: " << bst.search('N') << '\n';
    cout << "MerData hentet: " << bst.search('Q') << '\n';   //  Finnes ikke!

    if (bst.remove('L'))  cout << "\nFjernet 'L':\n";        //  Case 3
    bst.display();

    if (bst.remove('T'))  cout << "\nFjernet 'T':\n";        //  Case 1
    bst.display();

    if (bst.remove('C'))  cout << "\nFjernet 'C':\n";        //  Case 2
    bst.display();

    cout << "\n\n";
    return 0;
}
