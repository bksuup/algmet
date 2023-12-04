/**
 *   Programeksempel nr 28 - Binært søketre (BST) - selvlaget enkel klasse.
 *
 *   Eksemplet viser en selvlaget implementasjon av container-klassen BST.
 *   Denne inneholder IKKE bare 'data' (ID/key/nøkkel), som i de foregående
 *   eksemplene, men også tilknyttede data ('merData').
 *
 *   Det er laget kode for følgende funksjoner:
 *     - BST
 *     - void    display();
 *     - void    insert(final Data verdi, final MerData merData);
 *     - boolean remove(final Data verdi);
 *     - MerData search(final Data verdi);
 *     - void    traverserInorder(Node node);
 *
 *
 *   Orden ( O(...)):
 *    For et BST bygd av N noder, krever search/insert omtrent  2 ln N  
 *    sammenligninger i gjennomsnitt. I "worst case" kreves N sammenligninger.
 *    (Dette er nå ALLE nodene KUN har ETT venstre ELLER høyre barn, 
 *    dvs. hele treet er egentlig en LISTE, og man skal finne/sette inn 
 *    etter den ALLER siste.)
 *        
 *
 *   NB:  - I et binært søketre er ALT til venstre for en node ALLTID MINDRE
 *          enn verdien i selve noden, og ALT til høyre er STØRRE ELLER LIK.
 *        - LIKE 'data'/ID/key KAN dermed spres til høyre for hverandre ulikt
 *          nedover i treet, men de vil ALLTID komme rett etter hverandre om
 *          man skriver ut treets noder i INORDER rekkefølge! 
 *        - Ved 'remove' skal ALLTID en node erstattes med den SEKVENSIELT
 *          etterfølgende noden (om den finnes). For denne vil ALDRI da ha
 *          noe venstre barn, men evt. kun et høyre subtre.
 *        - 'merData' er laget for å vise at EGENTLIG er det sjeldent at
 *          bare 'data' er det eneste og mest relevante, men at den som 
 *          oftest egentlig er nøkkelen til en tilknyttet datamengde.
 *          Dog er 'merData' i dette eksemplet KUN en eneste liten 'String'.
 *
 *   @file     EKS_28_BinertSokeTre.java
 *   @author   Marius Lindvall, NTNU
 */
public class EKS_28_BinertSokeTre {
    
    /**
     *  Container-klassen Binært søketre (BST)
     *
     *  Inneholder et binært søketre bestående av 'Node'-structer,
     *  og har et "dummy" 'hode' som har 'data' (ID/key) mindre enn alt annet
     *  i treet. 'hode.right' peker til treets reelle rot !!!
     *  
     */
    static class BST<Data extends Comparable<Data>, MerData> {
        private class Node {            //  Nodene i det binære søketreet.
            Data data;                  //  ID/key.
            MerData merData;            //  Tilleggsdata/-info til IDen/keyen.
            Node left, right;           //  Peker til venstre/høyre subtre/barn.
                                        //  Constructor:
            Node(final Data d, final MerData md)  {  data = d;  merData = md;
                                                     left = right = null;  }
        }
        
        private Node  hode;     //  Dummy-hode, der 'hode.right' er treets rot !!!!!
                                //  Hensiktsmessig å ha når rota selv skal slettes.
        
        private void traverserInorder(Node node) {
            if (node != null) {
               traverserInorder(node.left);
               System.out.print("\t" + node.data);    //  Skriver nodens data/ID/key.
                     if (node.left != null)           //  Skriver evt. venstre barn:
                             System.out.print("    V.barn: " + node.left.data);
                     if (node.right != null)          //  Skriver evt. høyre barn:
                             System.out.print("    H.barn:    " + node.right.data);
               System.out.println();
               traverserInorder(node.right);
            }
        }
        
                            //  Initierer 'hode' - ut fra typen til 'Data' og 'MerData':
        public BST(Class<Data> dataClass, Class<MerData> merDataClass) {
            Data data = null;
            MerData merData = null;
            
                            // Begge må settes til riktig type:
            if (dataClass.isAssignableFrom(Integer.class))
                data = dataClass.cast(0);
            else if (dataClass.isAssignableFrom(Character.class))
                data = dataClass.cast('\0');
            else if (dataClass.isAssignableFrom(String.class))
                data = dataClass.cast("");
            
            if (merDataClass.isAssignableFrom(Integer.class))
                merData = merDataClass.cast(0);
            else if (merDataClass.isAssignableFrom(Character.class))
                merData = merDataClass.cast('\n');
            else if (merDataClass.isAssignableFrom(String.class))
                merData = merDataClass.cast("");
            
            hode = new Node(data, merData);
        }
        
        public void display() {                 //  Skriver inorder ut HELE treet:
            traverserInorder(hode.right);       //  Starter i den reelle roten.
        }
        
                            //  Setter inn 'verdi' med tilknyttet 'merData' inn i treet:
        void insert(final Data verdi, final MerData merData) {
            Node mor = hode, node = hode.right;
            if (node != null) {         //  Er MINST en node/rot der allerede:
                while (node != null) {  //  Blar til der skal settes inn NEDERST:
                    mor = node;         //  'mor' følger etter.
                                        //  'node' leter videre nedover:
                    node = (verdi.compareTo(node.data) < 0) ? node.left : node.right;
                }
                node = new Node(verdi, merData);               //  Lager ny som skal inn.
                if (verdi.compareTo(mor.data) < 0) mor.left = node; //  Hekter inn til v.
                else mor.right = node;                         //    eller h. ift. 'mor'.
            } else                      //  1.noden i treet (rota):
               hode.right = new Node(verdi, merData);
        }
        
                                            //  Fjerner og returnerer (om mulig)
        boolean remove(final Data verdi) {  //    node med IDen 'verdi':
            Node morFjernes,                //  "Mora" til 'fjernes'.
                 fjernes,                   //  Den som skal removes/slettes.
                 morEtterfolger,            //  "Mora" til 'etterfolger'.
                 etterfolger;               //  Den SEKVENSIELT etterfølgende.

            morFjernes = hode;              //  Initierer 2x pekere:
            fjernes = hode.right;
                                            //  Blar seg fram til 'verdi'(?):
            while (fjernes != null  &&  !verdi.equals(fjernes.data)) {
                morFjernes = fjernes;       //  'morFjernes' hopper etter.
                                            //  'fjernes' blar venstre/høyre:
                fjernes = (verdi.compareTo(fjernes.data) < 0)
                        ? fjernes.left : fjernes.right;
            }

            if (fjernes == null)  return false; //  Noden ble IKKE funnet.

            etterfolger = fjernes;          //  'fjernes' ER noden som skal slettes !!!
                                            //  CASE 1: =================================
            if (fjernes.right == null)      //  Har ingen HØYERE/STØRRE etterfølger!
                etterfolger = etterfolger.left; // Etterfølger er VENSTRE subtre!
                                            //  CASE 2: =================================
            else if (fjernes.right.left == null) {
                etterfolger = etterfolger.right; // Etterfølger er HØYRE subtre!
                etterfolger.left = fjernes.left; // Overtar v.subtre fra 'fjernes'.
            }
                                            //  CASE 3: =================================
            else {                          // MÅ lete MER etter SEKVENSIELL etterfølger:
                morEtterfolger = etterfolger.right; // Initierer 'morEtterfolger'.

                while (morEtterfolger.left.left != null)  //  Blar til NEST nederste 
                    morEtterfolger = morEtterfolger.left; //  venstre node:

                etterfolger = morEtterfolger.left;  //  'etterfolger' er noden
                                                    //     HELT nede til venstre.
                                                    //  Overfører evt høyre subtre:
                morEtterfolger.left = etterfolger.right;  // Har jo IKKE v.subtre!

                etterfolger.left = fjernes.left;    // 'etterfolger' tar 'fjernes'
                etterfolger.right = fjernes.right;  //    sin plass.
            }

                                            //  Flyttet node ('etterfolger')
                                            //  hektes korrekt under 'morfjernes':
            if (verdi.compareTo(morFjernes.data) < 0) morFjernes.left = etterfolger;
            else morFjernes.right = etterfolger;

            return true;                    //  Noden funnet og fjernet.
        }
        
        MerData search(final Data verdi) {
            Node node = hode.right;         //  Initierer til rota.
                                            //  Leter til funn eller bunns.
            while (node != null  &&  !node.data.equals(verdi))
                  node = (verdi.compareTo(node.data) < 0) ? node.left : node.right;

            if (node != null) return node.merData;  //  Funnet - 'merData' returneres.
            else return hode.merData;               //  IKKE funnet!
        }
    }

    /**
     *  Hovedprogrammet:
     */
    public static void main(String[] args) {
        BST<Character, String> bst = new BST<>(Character.class, String.class);
        
        bst.insert('L', "Liam");     /*  Bygger søketreet (inni 'BST'):     */
        bst.insert('C', "Charlie");  /*               L                     */
        bst.insert('F', "Frank");    /*          /         \                */
        bst.insert('T', "Tony");     /*        C             T              */
        bst.insert('P', "Pat");      /*          \          /               */
        bst.insert('N', "Nigel");    /*           F        P                */
        bst.insert('S', "Steve");    /*            \     /   \              */
        bst.insert('R', "Ray");      /*             I   N      S            */
        bst.insert('I', "Ian");      /*                  \    /             */
        bst.insert('O', "Oliver");   /*                   O  R              */
        bst.display();   System.out.println('\n');

        System.out.println("MerData hentet: " + bst.search('C'));
        System.out.println("MerData hentet: " + bst.search('N'));
        System.out.println("MerData hentet: " + bst.search('Q'));       //  Finnes ikke!

        if (bst.remove('L'))  System.out.println("\nFjernet 'L':");     //  Case 3
        bst.display();

        if (bst.remove('T'))  System.out.println("\nFjernet 'T':");     //  Case 1
        bst.display();

        if (bst.remove('C'))  System.out.println("\nFjernet 'C':");     //  Case 2
        bst.display();

        System.out.println('\n');
    }

}
