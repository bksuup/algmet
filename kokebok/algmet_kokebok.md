# Algmet Kokebok

## Abstrakte Datatyper

### Vector

``` cpp
template <typename T>
class Vector {

private:
	T* data;
	int kapasitet, antall;

public:

	/**
	* Construktor som lager en ny vektor av type T
	*/
	Vector(const int lengde = 200){
		data = new T[lengde];    // lager array av type T med lengde = 200
		kapasitet = lengde;      // Kapasitet = lengde siden arrayet er tomt
		antall = 0;              // antall elementer = 0 siden det er tomt
	}

	~Vector(){
		delete [] data;          // frigir allokert data
	}

	/**
	* Returnerer ledig kapasitet i vectoren
	*/
	int capacity(){
		return kapasitet;
	}

	/**
	* Clearer array ved å sette antall = 0, istedenfor å overskrive alle data
	*/
	void clear(){
		antall = 0;
	}

	/**
	* Skriver ut hele vectorens innhold
	*/
	void display() const{
		for (int i = 0; i < antall; i++)
			cout << i << ": " << data[i] << "  ";
		cout << "\n\t'antall': " << antall << '\n'
	}

	/**
	* Sjekker om vectoren er tom eller ikke
	*/
	bool empty() const{
		return (antall == 0);
	}

	/**
	* Henter innholdet i posisjon x og returnerer funnet hvis det eksisterer
	*/	
	T get(const int pos) const{
		if (pos >= 0 && pos < antall)
			return data[pos]
		else
			cout << "\nIndex out of bounds... \n"
		return T();
	}

	/**
	* Inserter et element i indeks 'pos'
	*/
	bool insert(const int pos, const T t){
		//sjekker om det er plass i Vectoren
		if (antall >= kapasitet){
			cout << "Vector er på full kapasitet"
			return false;
		}
		// Sjekker om Index er gyldig
		if (pos < 0 || pos > antall){
			cout << "Index out of bound"
			return false;
		}

		for (int i = antall; i > pos; i--) // alle etter pos
			data[i] = data[i-1];           // flyttes opp ett hakk
		data[pos] = t;
		antall++
		return true;
	}

	/**
	* Returnerer den siste 
	*/
	T pop_back(){
		if(empty()){
			cout << "Vector empty";
			return T();
		}
		T siste = data[antall-1]; // tar vare på den bakerste
		antall--;                 // teller ned, skriver ikke over
		return siste;             // returnerer den siste
	}

	/**
	* Popper av det første elementet hvis vectoren ikke er tom
	*/
	T pop_front(){
		if(empty()){
			cout << "Vector tom";
			return T();
		}
		T forste = data[0];
		remove(0);
		return forste;
	}

	/**
	* Legger til nytt element bakerst
	*/
	bool push_back(const T t){
		return insert(antall, t);
	}

	/**
	* Legger til et element først
	*/
	bool push_front(const T t){
		return insert(0, t);
	}

	bool remove(const int pos){
		if (pos < 0 || pos > antall){
			cout << "Index out of bounds";
			return false;
		}
		for (int i = pos; i < antall-1; i++)
			data[i] = data[i+1]; // flytter alle etter ned ett hakk
		antall--; // teller ned antall elementer
		return true;
	}

	void resize(const int nyLengde){
	
	}

	void set(const int pos, const T verdi) {
		if (pos >= 0 && pos < antall) // Lovlig indeks:
			data[pos] = verdi; // Setter til ny verdi.
		else
			cout << "\nIndex out of bounds .....\n\n"; // Egen melding ??
	}

	int size() const{
		return antall;
	}
}
```

### Stack

``` cpp
template <typename T>                //  'T': fleksibel datatype!
class Stack {

  private:
      T*  data;                      //  PEKER til array av typen 'T'.
      int kapasitet, antall;         //  Max.lengde og n�v�rende antall.

  public:                      //  Initierer medlemmer vha. default parameter:
    Stack(const int lengde = 200){
	    data = new T[lengde];
        kapasitet = lengde;  antall = 0;
    }

    ~Stack(){
	      delete [] data;
	}  // Frigir allokert memory (vha.'new').


      void display() const {         //  Skriver HELE Stackens innhold:
          for (int i = 0;  i < antall;  i++)
              cout << i << ": " << data[i] << "  ";
          cout << "\n\t'antall': " << antall << '\n';
      }


      bool empty()const{
	      return (antall == 0);
	}   //  Tomt eller ei.

                                     //  Returnerer (om mulig) det f�rste/
      T pop() {                      //    �verste elementet:
          if (!empty())              //  Ikke tomt (dvs. elementer igjen):
              return (data[--antall]);     //  Siste har indeks:  antall-1
          else
              cout << "\nStack is empty!\n\n";      //  Egen melding ??
          return T();
      }

                                     //  Legger inn (om mulig) nytt f�rste/
      void push(const T t) {         //    �verste element:
          if (antall < kapasitet)    //  Fortsatt plass til elementer:
             data[antall++] = t;     //  Legger inn f�rst/�verst, teller opp
          else                       //    til neste indeks.
              cout << "\nStack is already full!\n\n";      //  Egen melding ??
      }
};
```

### Queue

``` cpp
template <typename T>                //  'T': fleksibel datatype!
class Queue {

  private:
      T*  data;                      //  PEKER til array av typen 'T'.
      int kapasitet, antall,         //  Max.lengde og n�v�rende antall.
          forste, siste;             //  Indeks for f�rste/siste element.

  public:                      //  Initierer medlemmer vha. default parameter:
    Queue(const int lengde = 200){
	    data = new T[lengde];
        kapasitet = lengde;
        antall = forste = siste = 0;
    }


    ~Queue(){
	      delete [] data;
	}  // Frigir allokert memory (vha.'new').


    void display() const {         //  Skriver HELE Queuens innhold:
        int indeks = forste;
        for (int i = 0; i < antall; i++) {
	        cout << indeks << ": " << data[indeks++] << "  ";
		    if (indeks == kapasitet) indeks = 0;
          }
	    cout << "\n\t'antall': " << antall << "\t'forste': "
	        << forste << "\t'siste': " << siste << '\n';
      }


    bool empty()const{
	      return (antall == 0);
	}   //  Tomt eller ei.


      T get() {                //  Returnerer (om mulig) det f�rste elementet:
          T  verdi;            //  Elementet/verdien som skal returneres.
          if (!empty()) {      //  Elementer fortsatt igjen:
              verdi = data[forste++];  //  Tar vare p� f�rste. �ker til neste.
              antall--;                //  Totalantallet telles ned.
              if (forste == kapasitet) forste = 0;  //  Wrapper til starten?!!
              return verdi;            //  Returnerer unnalagret element.
          } else
              cout << "\nQueue is empty!\n\n";      //  Egen melding ??
          return T();
      }


      void put(const T t) {  //  Legger inn (om mulig) element bakerst i k�en:
          if (antall < kapasitet) {    //  Fortsatt plass:
              data[siste++] = t;       //  Legger bakerst. �ker til neste inn.
              antall++;                //  Totalantallet telles opp.
              if (siste == kapasitet) siste = 0;    //  Wrapper til starten?!!
          } else
              cout << "\nQueue is already full!\n\n";      //  Egen melding ??
      }
};
```

### List

``` cpp
template <typename T> // 'T': fleksibel datatype!
class List {
	private:
		struct Node { // Skjult struct for liste med 'data'.
			T data; // Unnalagrede 'data'.
			Node* neste; // Peker til neste i listen.
			Node(const T d) { data = d; neste = nullptr; } // Constructor.
		};
		
	Node* hode; // Dummy hode for � forenkle mye av koden.
	int antallNoder; // N�v�rende antall i listen.

	public: // Initierer medlemmene:
		List(const T t){
			hode = new Node(t); antallNoder = 0;
		}

		~List(){ // Destructor - sletter HELE listen:
			Node* np; // Hjelpepeker til neste i listen.
			while (hode) { // S� lenge noe � slette:
				np = hode->neste; // Peker til den andre noden.
				delete hode; // Sletter den f�rste noden.
				hode = np; // Setter 'hode' til � peke p�
			} // den nye f�rste noden.
		}  

		void display()const{ // Skriver listens innhold:
			Node* np = hode->neste; // Hopper over selve hodet.
			while (np) { // Ikke n�dd listens slutt:
				cout << '\t' << np->data << '\n'; // Skriver nodens data.
				np = np->neste; // Hopper/g�r til neste i listen.
			}
			cout << "\n\tAntall noder i listen: " << antallNoder << '\n';
		}

		// Returnerer om listen er tom eller ei:
		bool empty()const{
			return (antallNoder == 0);
		}


		bool find(const T t)const{ // Returnerer om 't' er � finne eller ei:
			Node* np = hode->neste; // Hopper over selve hodet.
			while (np && np->data < t) // Blar til der noe evt. ligger:
				np = np->neste;
			return (np && np->data == t); // Funnet eller ei?
		}

		void insert(const T t) { // Setter inn ny node sortert:
			Node* np = hode, // Initierer til selve hodet.
				* nyNode = new Node(t); // Oppretter den nye noden.
		// Neste finnes, og den er < enn den nyeste
		// (dvs. ved identiske legges den nye forrest):
			while (np->neste && np->neste->data < nyNode->data)
				np = np->neste; // Blar frem til neste node.

			nyNode->neste = np->neste; // Hekter inn mellom to noder
			np->neste = nyNode; // (evt. helt til slutt):
			antallNoder++; // �ker totalantallet noder.
		}

		bool remove(const T t) { // Returnerer om fjernet eller ei:
			Node* np = hode, // Initierer til selve hodet.
				* np2 = hode->neste; // Initierer til etter hodet.
			while (np2 && np2->data < t) { // Blar til der evt. ligger:
				np = np2; // Hopper hakket etter.
				np2 = np2->neste; // Blar til neste.
			}
			
			if (np2 && np2->data == t) { // Funnet:
				np->neste = np2->neste; // Hekter ut 'np2':
				delete np2; // Sletter noden 'np2'.
				antallNoder--; // Minsker totalantallet noder.
				return true; // Retunerer at er fjernet.
			}
			else // Retunerer at er IKKE fjernet.
				return false;
		}

		T removeNo(const int no) { // Returnerer (om mulig) node nr.'no':
			Node* np = hode, // Initierer til selve hoet.
				* np2 = hode->neste; // Initierer til etter hodet.
			T returData; // Evt. funnet nodes 'data'.
			if (no >= 1 && no <= antallNoder) { // 'no' i rett intervall:
				for (int i = 1; i < no; i++) { // Blar frem til nr.'no':
					np = np2; np2 = np2->neste; // Pekerne flyttes fremover:
				}
				np->neste = np2->neste; // Hekter ut 'np2':
				returData = np2->data; // Tar vare p� dens 'data'.
				delete np2; // Sletter noden 'np2'.
				antallNoder--; // Minsker totalantallet noder.
				return returData; // Returnerer unnalagrede 'data'.
			}
			else
				cout << "\nNumber out of bounds .....\n\n"; // Egen melding ??
			return T();
			}
			// Returnerer antall noder i listen:
			int size() const {
				return antallNoder;
			}
};
```

### Heap
#### Beskrivelse
En binary heap kan skrives som et komplett binært tre, hvor hver node sin verdi er mindre eller lik barna sine. Siden heapen skal være som et komplett binært tre, legger vi hele tiden på neste node på laveste nivå i treet, fra venstre mot høyre.
Siden treet skal være komplett, kan vi implementere heapen som et array, og bruke følgende metoder for å finne barna og foreldre nodene til en gitt node
```
leftChild:  2 * index +1
rightChild: 2 * index +2
parent:     (index - 1) / 2
	NB: Vi runder hele tiden ned for parent-node

hvor index = indexen til en gitt node i arrayet
```

#### UpHeap
Når vi legger til et element i Heapen, legger vi det hele tiden på neste ledige plass (som beskrevet ovenfor), deretter sammenligner vi verdien til den nye noden, med verdien til foreldre noden. Hvis verdien er mindre enn foreldre-noden, bytter nodene plass. Gjenta til noden er på korrekt plass.

#### DownHeap
Når vi erstatter verdien i rot noden med en ny verdi, er det ikke sikker at den nye verdien / noden er på riktig plass, derfor kaller vi DownHeap. Downheap sjekker om verdien til noden, er større enn sine barn, hvis noden er større ett av sine barn, bytter vi de to nodene (hvis noden er større en begge sine barn, bytter vi den med den av sine barn som har lavest verdi). Gjenta dette til noden er på sin korrekte plass (den er ikke mindre enn noen av sine barn).

#### Eksempel
| index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| verdi | 2 | 4 | 8 | 9 | 7 | 10 | 9 | 15 | 20 | 13 |

```
Barna til index 2 ('node' 8):
	2 * 2 + 1 = 5
	2 * 2 + 2 = 6

forelder til index 2 ('node' 8):
	(2 - 1) / 2 = 1/2 -> index 0

Barna til index 4 ('node' 7):
	2 * 4 + 1 = 9
	2 * 4 + 2 = 10

Forelder til index 4 ('node' 7):
	(4 - 1) / 2 = 3/2 -> index 1
```

``` cpp
template <typename T>
class Heap {
  private:
    T* data;
    int lengde, antall;
    T sentinelKey;

    void upHeap(int keyNr) {
        T verdi = data[keyNr];
        data[0] = sentinelKey;
        while (data[keyNr/2] < verdi) {
            data[keyNr] = data[keyNr/2];
            keyNr = keyNr/2;
        }
        data[keyNr] = verdi;
    }

  public:
    Heap(const int len = 200) {
        data = new T[len]; lengde = len; antall = 0;
        sentinelKey = std::numeric_limits<T>::max();
    }

    ~Heap() { delete [] data; }

    void change(const int keyNr, const T nyVerdi) {
    }

    void display() const {
        for (int i = 1; i <= antall; i++) std::cout << ' ' << data[i];
    }

    void downHeap(T arr[], const int ant, int keyNr) {
        int j;
        T verdi = arr[keyNr];
        while (keyNr <= ant/2) {
            j = 2 * keyNr;
            if (j < ant && arr[j] < arr[j+1]) j++;
            if (verdi >= arr[j])
               break;
            arr[keyNr] = arr[j];
            keyNr = j;
        }
        arr[keyNr] = verdi;
    }

    void extract(const int keyNr) {
    }

    void insert(const T verdi) {
        if (antall < lengde - 1) {
            data[++antall] = verdi;
            upHeap(antall);
        } else
            std::cout << "\nHeapen er full med " << lengde
                      << " elementer (inkl. sentinel key)!\n\n";
    }

    T remove() {
        if (antall > 0) {
            T verdi = data[1];
            data[1] = data[antall--];
            downHeap(data, antall, 1);
            return verdi;
        } else {
            std::cout << "\nHeapen er helt tom - ingenting i 'remove'!\n\n";
            return sentinelKey;
        }
    }

    T replace(const T verdi) {
        data[0] = verdi;
        downHeap(data, antall, 0);
        return data[0];
    }
};

```

### Fringe

### Binært Søketre
#### Orden
- Search / insert: 2 ln N (gjennomsnitt)
- worst case: N sammenligninger.
#### NB
- I et binært søketre er ALT til venstre for en node ALLTID mindre enn verdien i selve noden, og ALT til høyre er større eller lik
``` cpp
template <typename Data, typename MerData>
class BST {
  private:
      struct Node {
          Data data;
          MerData merData;
          Node* left, * right;

          Node(const Data d, const MerData md)  {  data = d;  merData = md;
                                                   left = right = nullptr;  }
      };

      Node*  hode; // dummy node hvor hode->right er roten på søketreet

      void traverserInorder(Node* node) const {
          if (node) {
             traverserInorder(node->left);
             cout << '\t' << node->data;
                   if (node->left)
                           cout << "    V.barn: " << node->left->data;
                   if (node->right)
                           cout << "    H.barn:    " << node->right->data;
             cout << '\n';
             traverserInorder(node->right);
          }
      }

  public:
     BST() {
       hode = new Node(Data(), MerData());
     }

     ~BST()  {}

     void display() const {
        traverserInorder(hode->right);
    }

     void insert(const Data verdi, const MerData merData) {
       Node * mor = hode,
            * node = hode->right;

       if (node) {
          while (node) {
             mor = node;
             node = (verdi < node->data) ? node->left : node->right;
          }
          node = new Node(verdi, merData);
          if (verdi < mor->data)  mor->left = node;
          else mor->right = node;
       } else
          hode->right = new Node(verdi, merData);
     }

     bool remove(const Data verdi) {
       Node *morFjernes,
            *fjernes,
            *morEtterfolger,
            *etterfolger;

       morFjernes = hode;
       fjernes = hode->right;

       while (fjernes  &&  verdi != fjernes->data) {
           morFjernes = fjernes;
           fjernes = (verdi < fjernes->data) ? fjernes->left : fjernes->right;
       }

       if (!fjernes)  return false;

       etterfolger = fjernes;
       if (!fjernes->right)
          etterfolger = etterfolger->left;
       else if (!fjernes->right->left) {
          etterfolger = etterfolger->right;
          etterfolger->left = fjernes->left;
       }
       else {
          morEtterfolger = etterfolger->right;

          while (morEtterfolger->left->left)
              morEtterfolger = morEtterfolger->left;

          etterfolger = morEtterfolger->left;
          morEtterfolger->left = etterfolger->right;

          etterfolger->left = fjernes->left;
          etterfolger->right = fjernes->right;
       }

       delete fjernes;

       if (verdi < morFjernes->data) morFjernes->left = etterfolger;
       else morFjernes->right = etterfolger;

       return true;
     }

     MerData search(const Data verdi) const {
         Node* node = hode->right;
        while (node  &&  node->data != verdi)
              node = (verdi < node->data) ? node->left : node->right;

        if (node) return node->merData;
        else return hode->merData;
    }
};

```
## Infix til Postfix

Infix er uttrykk som er skrevet på måten:
(( 8 + 12 ) * ( 17 + 4 ))

Postfix er uttrykk som er skrevet på måten:
8 12 + 17 4 + *
### Algoritme
1. Pusher alle operatorer '+' og '\*' på stacken
2. skriver rett ut igjenn sifre/tall
3. pop'er og skriver operator når vi finner en ')' sluttparantes.
4. ignorerer alle '(' startparantes.
### Kode
``` cpp
while ((tegn = cin.get()) != '\n'){ //leser alle tall og tegn fram til \n
	if(tegn == ')'){ //hvis den finner sluttparantes
		cout << stakk.top(); // skriver stackens øverste tegn
		stakk.pop            // fjerner tegnet
	}

		//hvis den finenr + || *, legges det til på stacken
	else if (tegn == '+' || tegn == '*') stakk.push(tegn);

	while (tegn >= '0' && tegn <= '9'){
		cout << tegn;
		tegn = cin.get();
	}

	if (tegn != '(')
		cout << ' ';
}
```


## Postfix til svar

regner ut postfix uttrykk som: 8 12 + 17 4 + \* = 420 ved bruk av stacken
### Algoritme
1. Når du finner '+' eller '\*' pop'es to tall/operander
2. Deres sum/produkt beregnes
3. svaret pushes til stack
4. Når man finner sifre, bygger dette evt. tile et sammenhengende tall, og pushes på stack

### Kode
``` cpp
while ((tegn = cin.get()) != '\n'){ // leser alt fram til \n
	tall = 0;                       // nullstiller
	while (tegn == ' ') tegn = cin.get(); //skipper blanke

		// hvis vi leser '+' eller '*' tar vi de to øverste tallene og gjør
		// tilsvarende operator på de
	if (tegn == '+'){
		tall = stakk.top(); stakk.pop(); //tall = øverste tallet på stakken
		tall += stakk.top(); stakk.pop(); // plusser på det nye tallet som nå er på toppen
	} else if (tegn == '*'){
		tall = stakk.top(); stakk.pop();
		tall *= stakk.top(); stakk.pop();
	}

		// bygger flersiffret tall
	while (tegn >= '0' && tegn <= '9'){
		tall = (10 * tall) + (tegn - '0'); //omgjør fra ascii til tall
		tegn = cin.get();
	}

	stakk.push(tall); //pusher oppbygde tall
}
```


## Parse Tre

Man kan bygge et parse-tre fra et postfix uttrykk.
Ett parse-tre er et binært tre hvor bladnodene har tall, og alle interne noder har operatorerne '+' eller '\*'
F.eks.
3 4 + 3 2 * + 2 + 5 3 * 4 2 + * +
gir parse treet:
![[Pasted image 20231204153618.png]]
### Algoritme
1. Leser ett og ett tegn (bokstav/siffer, '+' eller '\*')
2. Er det bokstav / siffer, pushes den til stakken
3. er det '+' eller '\*', pop'es av stakken det som blir høyre og venstre noder, så blir rotnoden pushet på stacken.

**NB:**
- postfix uttrykket må bestå av kun **EN** bokstav / **ETT** siffer, '+' og '\*'
- Uttrykket kan ikke avsluttes med en eller flere blanke

### Kode
``` cpp
struct Node{
	char ID;
	Node *left, *right;
	Node(char id){
		ID = id;
		left = right = nullptr;
	}
}
```

``` cpp
while ((tegn = cin.get()) != '\n'){
	while(tegn == ' ') tegn = cin.get();
	nyNode = new Node(tegn);
	if (tegn == '+' || tegn == '*'){
		nyNode->right = stakk.top(); stakk.pop();
		nyNode->left = stakk.top(); stakk.pop();
	}
	stakk.push(nyNode);
}
```


## TreTraversering

### Node
``` cpp
struct Node {
	char ID;
	bool besokt; // 'besokt' brukes KUN ifm. postorder.
	Node *left, *right; // Initierende constructor:
	Node(char id) { ID = id; left = right = nullptr; besokt = false; }
};
```

### Preorder

#### Algoritme
Besøker seg selv før den traverserer.
1. Besøk seg selv
2. Traverser Venstre
3. Traverser Høyre
#### Kode
``` cpp
void traverserPreorder(Node* node){
	if(node){
		gStakk.push(node);
		while (!gStakk.empty()){
			node = gStakk.top(); gStakk.pop();
			besok(node);
			if (node->right) gStakk.push(node->right);
			if (node->left) gStakk.push(node->left);
		}
	}
}
```

### Inorder
#### Algoritme
Besøker seg selv 'mellom' traverseringen
1. Traverser Venstre
2. Besøk seg selv
3. Traverser Høyre
#### Kode
``` cpp
void traverserInorder(Node* node){
	while (node || !gStakk.empty()){  //sjekke om reel node eller noe på stakk
		if (node) { // reel node
			gStakk.push(node); //noden legges på stakken
			node = node->left // går til venstre
		} else{ //node = nullprt
			node = gStakk.top(); gStakk.pop(); // poper en node
			besok(node); // besøker den
			node = node->right; // går til høyre
		}
	}
}
```

### Postorder

#### Algoritme
Besøker seg selv etter traversering
1. Traverser Venstre
2. Traverser Høyre
3. Besøk seg selv

if left != nullptr && node->left->besokt = false

``` cpp
void traverserPostorder (Node* node) {
	if (node) {
		gStakk.push(node);
		while (!gStakk.empty()){
			node = gStakk.top(); gStakk.pop();
			if (node->left->besokt = false) {
				gStakk.push(node->left);
			}
			if (node->right->besokt = flase) {
				gStakk.push(node->right);
			}
			besok(node);
		}
	}
}
```
### Levelorder
#### Algoritme
1. Leser treet linjevis
#### Kode
``` cpp
void traverserLevelorder(Node* node){
	if (node){
		gKo.push(node); // legger rota i køen
		while (!gKo.empty()){
			node = gKo.front(); gKo.pop(); //tar ut første node
			besok(node); // besøker den
			if(node->left) gKo.push(node->left); // leger til evt venstre og høyre
			if(node->right) gKo.push(node->right); //bakerst på køen
		}
	}
}
```

## Rekursjon
- Brukes når et problem kan deles i mindre, enklere under-deler
- Hvert underproblem kan løses ved å anvende samme teknikk
- Hele problemet løses ved å kombinere løsningene på underproblemene

**Rekusjon:** en funksjon som blant annet kaller/bruker seg selv, og ha en stoppe-betingelse som stopper den fra å kalle seg selv.

### Preorder Rekursiv
``` cpp
void traverserPreorder (Node* node) {
	if (node) {
		gNivaa++;
		besok(node);
		traverserPreorder(node->left);
		traverserPreorder(node->right);
		gNivaa--;
	}
}
```

### Inorder Rekursiv
``` cpp
void traverserInorder (Node* node) {
	if (node) {
		gNivaa++;
		traverserInorder(node->left);
		besok(node);
		traverserInorder(node->right);
		gNivaa--;
	}
}
```

### Postorder Rekursiv
``` cpp
void traverserPostorder (Node* node) {
	if (node) {
		gNivaa++;
		traverserPostorder(node->left);
		traverserPostorder(node->right);
		besok(node);
		gNivaa--;
	}
}
```

## Sortering

### Selection Sort
#### Framgangsmåte
1. Finn den minste verdien i det usorterte arrayet.
2. Bytt det med skuff\[0]
3. Finn den minste verdien i resten av det usorterte arrayet.
4. gjenta til arrayet er sortert.

#### Algoritme
1. Finner det minste elementet i resten av arrayen (f.o.m. nr 'i')
2. Legger det på plass nr 'i'
#### Orden
(N\*N)/2
**NB:**
- Er linær når verdiene som sammenlignes er små, og tilhørende data er store/mye.
- Ikke stabil: rekkefølgen på like elementer har ikke samme innbyrdes rekkefølge etter sortering.
#### Kode
``` cpp
/**
* @param arr - Arrayen som skal sorteres
* @param n   - Antall elementer i arrayen som skal sorteres
* @see   bytt()
*/
void selectionSort (int arr[], const int n) {
	int i, j,        // løkkevariabler
		minIndeks;   // indeks for den minste verdien

	for (i=0; i < n-1; i++) { // går til neste element
		minIndeks = i;        // initieres til første av de gjenværende
		for (j = i+1; j < n; j++) // finner minste etter nr.'i'
			if (arr[j] < arr[minIndeks]) minIndeks = j;
		bytt(arr[minIndeks], arr[i]); // bytter om på verdiene
	}
}
```

### Insertion Sort
#### Framgangsmåte
1. Start med element i indeks 1
2. Sammenlign element i forrige indeks
	1. Hvis indeks\[n+1] er mindre enn indeks\[n] -> flytt den mindre verdien til venstre, helt til den er større enn verdien som ligger i skuffen den sammenlignes med.
	2. Hvis indeks\[n+1] er større enn indeks\[n] -> la de være
3. Gå videre til neste element

#### Algoritme
1. Start i indeks 1 og gå videre ut i arrayet
2. For hver iterasjon, hent verdien til arr\[i]
3. Sammenlign arr\[i] med den sorterte delen av arrayet
	1. hvis et større element finnes, forskyv det en til plass til høyre
4. Sett inn nøkkelen i posisjonen (sorterte delen) hvor alle elementer til venstre er mindre eller lik, og alle elementer til høre er større eller lik
5. Repeat
#### Orden
~(N\*N)/4
**NB:**
- Er nærmest linær for så godt som ferdig sorterte arrayer.
- Veldig kjapp når et stort sortert array får flere verdies som legges til bakpå, og skal sorteres inn i arrayet.
#### Kode
``` cpp
/**
* @param arr - arrayen som skal sorteres
* @param n   - antall elementer i array n
*/
void insertionSort (int arr[], const int n) {
	int i, j,    // Løkkevariabler
		verdi;   // Verdien som skal sorteres inn

	for (i = 2; i < n; i++) { // starter i andre elementet
		verdi = arr[i];       // henter verdi som skal sorteres
		j = i;                // initierer aktuelt element
		while (arr[j-1] > verdi){ // så lenge tidligere er søtrre
			arr[j] = arr[j-1];
			j--;
		}
		arr[j] = verdi; // plaserer verdi det 'j' stanset
	}
}
```

### Shellsort
nb:
- bruker sentinel key
- Ikke stabil algoritme
#### Framgangsmåte
1. Velg en størrelse 'gap'
	1. vanligvis brukes n/2 hvor n er antall elementer i arrayet

2. Sorter arrayet for hver størrelse av 'gap'
	1. For hver verdi av 'gap' -> gjør en insertion sort med elementet som er i indeks: akutuell indeks + gap

3. Reduser størrelsen på 'gap'
	1. når du har sortert på en størrelse 'gap', reduser størrelsen
	2. gjør sortering på arrayet med den nye 'gap' størrelsen
	3. fortsett til 'gap' = 1

4. Insertion sort
	1. Når du har en 'gap' på 1, kjør en standard insertion-sort på arrayet.

#### Algoritme
1. Start med en predefinert størrelse 'gap'
2. Sammenlign element 'n', med element 'n+gap'
3. hvis element n > n+gap, så bytter elementene plass
4. Når alle elementene har blitt sammenlignet, halver størrelsen på 'gap'
5. Gjenta til gap = 1.
6. Kjør en vanlig insertion sort.
#### Orden
gjør aldri mer enn N^(3/2) sammenligninger.
#### Kode
``` cpp
/**
* @param arr - Arrayen som skal sorteres
* @param n   - antall elementer i array arr
*/
void shellSort(char arr[], const int n) {
	int i, j, h; // løkkevariabler
	char verdi;  // verdien/elementet som evt. skal flyttes bakover i subarrayen.

	for (h = 1; h <= n/9; h = (3*h)+1) ; // initierer h basert på hvor lang arrayen er

	while (h > 0) {
		for (i = h+1; i < n; i++) {
			verdi = arr[i];
			j = i;

			while (j > h && arr[j-h] > verdi) {
				arr[j] = arr[j-h];
				j -= h;
			}
			arr[j] = verdi;
		}

		h /= 3;
	}
	
}
```

### Quicksort
Prinsipp: Splitt og hersk.
- Splitt i to, og sorter hver del

#### Framgangsmåte
1. Velg en 'pivot' (gjerne midten av arrayet -> n/2 hvor n er antall elementer)

2. Partisjoner arrayet
	1. Plasser en peker på starten av arrayet, og en på slutten
	2. flytt pekerene mot hverandre, og sammenlign elementene de peker på
		1. bytt verdiene slik at alle elementer mindre enn pivot -> venstre for pivot, og alle elementer større enn pivot -> høre for pivot.
	3. når pekerene møtes, plasser elementet i 'pivot' i sin korrekte possisjon i det sorterte arrayet.

3. gjør steg 2 rekursivt til sub-arrayene

4. gjenta til arrayet er sortert.
#### Algoritme
1. Velg arr\[hoyre] som et tilfeldig element å sortere ut fra. (partisjonselementet)
2. Lete fra venstre etter >= verdi, og fra høyre etter <= verdi og så bytte om på disse
3. Gjenta til letingen har passert hverandre.
4. Bytt partisjonselementet med den helt til høyre i venstre delarray (nå er partisjonselementet i arr\[i] på sin endelige plass, og alle elementer til venstre er <= partisjonselementet, og alle elementer til høyre er >= partisjonselementet).
5. Gjenta rekursivt.
#### Orden
Quicksort bruker i gjennomsnitt `2N ln N` sammenligninger, worst case `(N*N)/2`
#### Kode
##### QuickSort
``` cpp
/**
* @param arr     - arrayen som skal sorteres
* @param venstre - venstre indeks for sorteringsintervall
* @param hoyre   - høyre indeks for sorteringsintervall
*/
void quickSort (char arr[], const int venstre, const int hoyre) {
	if (hoyre > venstre) {
		int indeks = partisjoner(arr, venstre, hoyre);
		quickSort(arr, venstre, indeks-1);
		quickSort(arr, indeks+1, hoyre);
	}
}
```
##### Partisjoner
``` cpp
/**
* @param arr     - Arrayen som skal partisjoneres
* @param venstre - venstre indeks for partisjonering
* @param hoyre   - høyre indeks for partisjonering
* @return        - Indeksen der partisjonselementet havnet / ble plassert
*/
int partisjoner(char arr[], const int venstre, const int hoyre) {
	if (hoyre > venstre) {
		int i, j; //indeksene som går mot hverandre
		char partisjonsElement;

		partisjonsElement = arr[hoyre];
		i = venstre-1;
		j = hoyre;

		while (true) {
			while (arr[++i] < partisjonsElement) ;
			while (arr[--j] > partisjonsElement) ;

			if (i >= j) break; //indeksene har passert hverandre
			bytt(arr[i], arr[hoyre]); // bytter innholdet i skuffene

			return i; // hvor partisjonselementet havnet
		}
		return 0; //mindre enn 2 elementer "dummy verdi"
	}
}
```
### Heapsort
#### Algoritme
1. Tar en array som skal sorteres og starter halvveis uti, og går baklengs til dens start.
	1. For hvert element utføres 'downHeap'.
2. Når man har kommet til første elementet, oppfyller hele den originale arrayen heap-betingelsen.
3. Bytt det aller første, og til enhver tid siste elementet, og utfører 'downHeap' for hver gang.
	1. Teller stadig ned antall elementer i arrayen som er igjenn å sortere.
#### Orden
bruker færre enn `2N lg N` sammenligninger (selv i 'Worst Case').
#### NB:
- Bottom-up heap-konstruksjon er tidslinær.
- Ustabil
#### Kode
``` cpp
/**
* @param arr - arrayen som skal sorteres
* @param n   - antall elementer initierlt i arr
* @see       - heap.downHeap()
*/
void heapSort(unsigned char arr[], int n) {
	for (int keyNr = n/2; keyNr >= 1; keyNr--) // arrayen blir til en heap
		gHeap.downHeap(arr, n, keyNr);

	while (n > 1) { // fortsatt igjen å sortere
		bytt <unsigned char> (arr[1], arr[n]);
		gHeap.downHeap(arr, --n, 1);
	}
}
```
## Hashing
### Separate Chaining
Det brukes en array/vector med Stacker eller LIFO-lister. Når en nøkkel hashes til en indeks
i arrayen/vectoren, så settes den bare inn aller først i stacken/listen. Er det derfor N nøkler
som skal hashes inn i en array/vector som er M lang, så vil det gjennomsnittlig være N/M
elementer/nøkler i hver stack/liste. Greit å bruke denne metoden når N er så stor at det er lite
hensiktsmessig i bruke en array/vector der det er plass til alle nøklene/elementene.

### Linear Probing
Nøkkelen hashes til indeksen der den bør legges. Er det allerede opptatt der, forsøkes den
lagt inn i første etterfølgende ledige indeks. Når man arrayens slutt, så startes det med leting
forfra igjen. Er arrayens lengde satt stor nok, så er vi garantert å finne en ledig plass!
#### Framgangsmåte
1. Finn hash-verdien for et element
2. Hvis plassen elementet skal plasseres er ledig -> plasser elementet på den plassen
	1. Hvis plassen ikke er ledig -> prøv plass+1 til du finner en ledig plass å plassere elementet
### Double Hashing
Den store ulempen med Linear Probing er «clustering». Dvs. sammenklumping av nøkler som
har blitt hashet til omtrent de samme indeksene. Dette kan forbedres ved at når en krasj
oppstår, så letes det ikke bare i en og en fortløpende indeks etterpå. I stedet får de ulike
nøklene litt forskjellige tilleggsverdier som det sjekkes om vedkommende indeks er ledig i
stedet. F.eks. at en nøkkel sjekker hver andre indeks utover, mens en annen sjekker hver
sjette. Nøklene får ulike tilleggsverdier ved å kjøre den også igjennom en annen hash-
funksjon. Denne kan f.eks. være: 6 - (nøkkel % 6) - som altså blir et tall i intervallet 1 til 6
#### Framgangsmåte
1. Hash elementet / verdien på 2 måter
	- Den første (hash1) bestemmer hvor vi skal prøve å plassere elementet først
	- Den andre (hash2) bestemmer hvor stor 'gap' vi skal hoppe for å prøve å plassere elementet hvis skuffen er opptatt.
2. Sjekk om plassen til det hashede elementet er opptatt eller ikke
	- Hvis ledig -> plasser elementet i (hash1)
	- Hvis ikke ledig -> sjekk hash1 + hash2 verdi
		- Gjenta til vi finner en ledig skuff
### Kode
``` cpp
enum HashType { LinearProbing, DoubleHashing };

class Hashing {
  private:
      char* tabell;
      int   lengde;
      HashType hType;

      int hash1(const int modVerdi, const int kVerdi) {
          return (kVerdi % modVerdi);
      }

      int hash2(const int hashVerdi, const int kVerdi) {
          return (hashVerdi - (kVerdi % hashVerdi));
      }

      int kVerdi(char bokstav) {
          bokstav = toupper(bokstav);
          if (bokstav >= 'A'  &&  bokstav <= 'Z')
              return (static_cast <int> (bokstav - 'A') + 1);
          else  return 0;
      }

  public:
      Hashing(const HashType hT, const int len) { // constructor
          lengde = len;    hType = hT;
          tabell = new char[len];
          for (int i = 0; i < lengde; i++)  tabell[i] = '-';
      }

      ~Hashing()  {  delete []  tabell;  } // destructor

      void display() const { // displayer hash-tabeller
          for (int i = 0; i < lengde; i++)         
              cout << setw(3) << i << ':';            cout << '\n';
          for (int i = 0; i < lengde; i++) 
              cout << "  " << tabell[i] << ' ';       cout << "\n\n";
      }

      void insert(const int hashVerdi, const char data) { // inserter data
          int dataTilK = kVerdi(data);
          int indeks   = hash1(lengde,    dataTilK); // finner hash-verdiene
          int tillegg  = hash2(hashVerdi, dataTilK); // denne brukes bare til Double

          while (tabell[indeks] != '-') {  
		          // sjekker om den skal utføre linear probing eller double hashing
              indeks = (hType == LinearProbing) ? (indeks+1) : (indeks+tillegg);
              indeks %= lengde; // wrapper tilbake til start hvis index er Out of
					            // bounds
          }                              
          tabell[indeks] = data;         display(); // plasserer verdien når den
											        // kommer til en tom skuff.
      }
};
```
### Merkle Tree
#### Beskrivelse
Et merkle tre er et binært tre sammensatt av hash-verdier.
##### Struktur
- **Blad-noder:**
	- Inneholder en Hash av en datablokk (datablokken er ikke en del av merkle treet).
- **Intermediate-noder:**
	- Inneholder en hash av sine 2 barn-noder (hash-barn1+hash-barn2, hashet).
- **Rot-node:**
	- Representerer en hash av alle underliggende data, og endres for hver gang noen av de underliggende dataene endres.
		- Dette gjør den sensitiv til dataendring.

## Søking
### Sekvensielt søk i usortert array
#### Orden
- N+1 sammenligninger ALLTID ved ikke-funn
- N/2 sammenligninger gjennomsnittlig ved funn
#### Kode
``` cpp
/**
* Søker sekvensiellt gjennom arrayet til den finner en index med medsendt verdi.
*
* @param arr   - usortert array som skal søkes i
* @param verdi - verdien som skal letes etter
* @param n     - antall elementer i arr
* @return      indeksen i 'arr' der 'verdi' ble funnet
*/
int sokSekvensielt (const int arr[], const int verdi, const int n) {
	int indeks = n+1;

	while (index > 0 && verdi != arr[index--]) ;
	return (index);
}
```

### Binært søk i en sortert array
#### Orden
- Ikke mer enn lgN +1 sammenligninger for søk som gir både funn og ikke-funn.
#### Kode
``` cpp
/**
* @param arr   - sortert array det skal søkes i
* @param verdi - verdien det skal søkes etter
* @param n     - antall elementer i 'arr'
* @return      - indeksen hvor 'verdi' ble funnet i 'arr'
*/
int sokBinært (const inst arr[], const int verdi, const int n) {
	int venstre = 1,
		hoyre = n,
		midten;

	while (venstre <= hoyre) {
		midten = (venstre + hoyre) / 2;

		if (verdi == arr[midten])
			return midten;

		if (verdi < arr[midten])
			hoyre = midten - 1;
		else venstre = midten + 1;
	}
}
```

### DFS - Dybde Først Søk
#### Kode
Sjekker rekursivt om en nodes naboer er besøkt eller ikke, og markerer noden som besøkt når den besøkes av DFS funksjonen
```cpp
/**
* @param nr - indeks (0 til ANTNODER-1) for noden som skal besøkes
*/
void DFS(const int nr) {
    gBesokt[nr] = ++gBesoktSomNr; // gir noden riktig "besøkt som" nr
    
    for (int j = 0;  j < ANTNODER;  j++) // sjekker hele "linjen" til noden i en nabo-matrise
        if (gNaboMatrise[nr][j]) // hvis forskjellig fra 0
            if (gBesokt[j] == USETT) DFS(j); // rekursivt besøk noden.
}
```
#### Framgangsmåte
1. Lag en stack og en besøkt-liste

2. Plasser startnoden på stacken

3. Begynn DFS loopen
	1. Så lenge stacken ikke er tom
		1. Pop en node fra stakken (aktuell node)
		2. besøk den aktuelle noden
		3. få alle nabo-noder til den aktuelle noden
		4. for hver nabo-node
			1. Marker som besøkt
			2. push på stakken

### Bredde først søk
#### Kode
Iterativ algoritme som gjør et bredde først søk.
``` cpp
/**
 *  @param   nr  - Indeks (0 til ANTNODER-1) for STARTNODEN i bes�ket
 */
 void BFS(int nr) {
    int j;                                     //  Indeks for aktuelle naboer.
    gBesokeSenere.push(nr);                    //  Legges BAKERST i besøkskø.
    while (!gBesokeSenere.empty()) {           //  Ennå noder å besøke igjen:
        nr = gBesokeSenere.front();            //  AVLES iden til første noden på køen
        gBesokeSenere.pop();                   //  FJERNER/TAR UT fra køen.
        gBesokt[nr] = ++gBesoktSomNr;          //  Setter besøksnummeret.
        for (j = 0;  j < ANTNODER;  j++)       //  Nodens linje i matrisen:
            if (gNaboMatrise[nr][j])           //  Er nabo med nr.j,
                if (gBesokt[j] == USETT) {     //    og denne er ubesøkt:
                    gBesokeSenere.push(j);     //  Legger nabo BAKERST i køen.
                    gBesokt[j] = SENERE;       //  Setter at delvis besøkt!!!
                }
    }
}
```
#### Fremgangsmåte
1. Lag en kø og en liste over besøkte noder
	- Køen brukes for å holde orden på hvilken node som skal besøkes neste
	- listen holder orden på hvilke noder som har blitt besøkt

2. Plasser startnoden på køen og marker den som besøkt

3. BFS Loop
	- Så lenge køen ikke er tom
		- hent neste node fra starten på køen (aktuell node)
		- besøk noden
		- Se alle noder som er sammenkoblet med den aktuelle noden.
		- for hver node som er sammenkoblet med den aktuelle noden -> marker den som besøkt, og plasser den på køen

4. Gjenta til køen er tom
	- Hvis en nabonode er markert besøkt -> ikke besøk noden på nytt igjenn.

### Minimum Spenn Tre (MST) - Prim
#### Algoritme
1. Noden er endten
	1. I det hittil oppbygde MST
	2. på Fringen
	3. Usett
2. Finner man en node som allerede er på Fringen
	1. Sjekk om den skal oppdateres med enda lavere vekt
3. 'gTilknyttning\[k]' er noden som sørget for at noden 'k':
	1. Ble flyttet fra Fringen til grafen
	2. Fikk sin minimale verdi (vekt) på Fringen hittil
4. 'gKantvekt\[k]' er vekten på kanten mellom 'k' og 'gTilknyttning\[k]'.
5. Noder på Fringen er (i 'gKantvekt') markert med negativ vekt (USETT = -999)

#### Framgangsmåte
1. Lag en prioritets-kø hvor nodene er rangert med hensyn på vekten til kanten som forbinder den med det allerede byg MST
2. Start i en node (startnode)
3. Så lenge MST ikke inneholder alle noder:
	1. Se på alle kanter som knytter en node til MST
	2. velg den kanten med lavest vekt (evt første noden i prioritetskøen)
	3. legg til denne kanten & noden til MST
4. Gjenta steg 3 til alle noder er en del av MST.

#### Orden
(E + V) * log V

#### Kode
``` cpp
/**
 *  Finner ETT minimums spenntre for en sammenhengende graf/komponent.
 *
 *  @param   nr  -  Grafens startnode, som inni funksjonen brukes/oppdateres
 *                  til å være aktuell besøkt node
 *  @see - fringe.h eksempelkode
 */
void finnMST(int nr) {
   int j,
       vekt;
                              //  Noden er ny og har dermed ingen tilknytning:
   if (gFringe.update(nr, -USETT))  gTilknytning[nr] = 0;

   while (!gFringe.empty())  {  //  Fortsatt ubehandlede noder (på "Fringen"):
       nr = gFringe.remove();   //  Henter den første noden på fringen.
       gKantVekt[nr] = -gKantVekt[nr];  //  Omgjør neg. til pos.verdi.
                                  //  Den hentede er noden uten tilknytning:
       if (gKantVekt[nr] == -USETT)  gKantVekt[nr] = 0;

       for (j = 1;  j <= ANTNODER;  j++) {       //  Går gjennom alle naboer:
            vekt = gNaboMatrise[nr][j];          //  Henter kantvekt.
            if (vekt > 0  &&                     //  Er naboer  og  er på
                gKantVekt[j] < 0)  {             //    Fringen eller USETT
                                                 //    (negativ 'gKantVekt'):
                if (gFringe.update(j, vekt) ) {  //  Ny eller lavere kantvekt:
                   gKantVekt[j]    = -vekt;      //    Oppdaterer med ny vekt
                   gTilknytning[j] =  nr;        //    og ny tilknytning.
               }
            }
       }
   }
}
```

### Shortest Path - Dijkstra
#### Framgangsmåte
1. Start med et sett med ubesøkte noder
	- initiellt vil dette inneholde alle nodene.

2. Så lenge det er ubesøkte noder
	- Velg den noden fra ubesøkte noder med lavest distanse fra startnoden.
		- På starten vil dette være start-noden
	- For denne noden, se alle nabo-noder
		- Kalkuler distansen til nabo-nodene med distansen / vekten fra start -> aktuell node + vekten på kanten fra aktuell node -> nabo-node.
			- hvis den nye distansen er mindre enn nabo-nodens tidligere kalkulerte distanse -> oppdater distansen til denne noden, og hvor hvilken node den kom fra.
			- Hvis større -> ignorer.
	- etter alle nabo-noder til den aktuelle noden har blitt sett, marker den aktuelle noden som besøkt. Denne noden vil ikke bli sjekket igjenn.

3. Gjenta til alle noder har blitt besøkt.
	- På "riktig" måte stopper algoritmen når "slutt" - noden er øverst i prioriterings-køen / har lavest distanse.

4. Start i "slutt" - noden og konstruer stien tilbake til starten ved å se på hvor hver node kommer fra. vekten på stien / lengden fra start til slutt, er summen av vekten på alle kantene i stien.

#### Algoritme
Algoritme/virkemåte: "Identisk" til Prim's algoritme, bare at avstanden fra node nr.'i' via node nr.'j' til node nr.'k' er avstanden fra nr.'j' til nr.'k' PLUSS minimumsavstanden fra nr.'i' til nr.'j'.
#### Kode
KODEN ER HELT IDENTISK TIL EKS_31_MST.CPP, BARE AT FØR LINJE NR.122 SMETTES FØLGENDE KODELINJE INN (!!!):
``` cpp
vekt += gKantVekt[nr]
```

``` cpp
/**
 *  Finner ETT minimums spenntre for en sammenhengende graf/komponent.
 *
 *  @param   nr  -  Grafens startnode, som inni funksjonen brukes/oppdateres
 *                  til å være aktuell besøkt node
 *  @see - fringe.h eksempelkode
 */
void finnMST(int nr) {
   int j,
       vekt;
                              //  Noden er ny og har dermed ingen tilknytning:
   if (gFringe.update(nr, -USETT))  gTilknytning[nr] = 0;

   while (!gFringe.empty())  {  //  Fortsatt ubehandlede noder (på "Fringen"):
       nr = gFringe.remove();   //  Henter den første noden på fringen.
       gKantVekt[nr] = -gKantVekt[nr];  //  Omgjør neg. til pos.verdi.
                                  //  Den hentede er noden uten tilknytning:
       if (gKantVekt[nr] == -USETT)  gKantVekt[nr] = 0;

       for (j = 1;  j <= ANTNODER;  j++) {       //  Går gjennom alle naboer:
            vekt = gNaboMatrise[nr][j];          //  Henter kantvekt.
            if (vekt > 0  &&                     //  Er naboer  og  er på
                gKantVekt[j] < 0)  {             //    Fringen eller USETT
                                                 //    (negativ 'gKantVekt'):
                vekt += gKantVekt[nr]; // ny linje
                if (gFringe.update(j, vekt) ) {  //  Ny eller lavere kantvekt:
                   gKantVekt[j]    = -vekt;      //    Oppdaterer med ny vekt
                   gTilknytning[j] =  nr;        //    og ny tilknytning.
               }
            }
       }
   }
}
```

### A Star
algoritme for å effektivt finne korteste / raskeste vei fra en startnode til en sluttnode.
A* = Dijkstra + Heuristikk
#### Heuristikk
Omhandler å estimere veien / avstanden fra nåværende node / rute og til målet.
Avstanden til målet (f) er derfor SUMMEN av reell avlagt avstand fra startnoden, PLUSS estimert avstand til målet.

#### Orden
Tidskompleksiteten avhenger av den heuristikke funksjonen.
- Beste fall: b * d
- Gjennomsnitt / verste fall: b^d

#### Framgangsmåte
1. Initialiser
- Lag to sett / mengder: 'Open Set' og 'Closed Set'.
	- Legg til startnoden til 'Open Set'

2. Definer kostnad-funksjonene
	- g(n): kostnaden fra startnoden til node 'n'.
	- h(n): Den heuristiske distansen fra node 'n' -> målet
	- f(n):  estimert totalkostnaden til node 'n' fra start til mål, g(n) + h(n)

3. Hovedfunksjon
	- Så lenge 'Open Set' ikke er tomt:
		- Velg den noden i Open Set med lavest f(n) - verdi. kall denne noden 'current'
		- hvis 'current' er målet, så er du ferdig.
		- hvis ikke, flytt current fra 'Open Set' -> 'Closed Set'

4. For hver nabo av 'current'
	- Hvis 'nabo' er i 'Closed Set' -> Ignorer
	- kalkuler g('nabo') med en sti gjennom 'current'.
	- hvis 'nabo' ikke er i 'Open Set' -> legg den til
	- Hvis 'nabo' er i 'Open Set' -> sjekk om g('nabo') er større enn den nodens tidligere g(n) verdi.
		- Hvis den er lavere -> oppdater g(n) for noden
		- Hvis den er større -> ignorer denne stien

5. Sti rekonstruksjon
	- Når du har kommet til mål, konstruer stien baklengs fra mål, til starten, ved å gå til hver node sin mor.


#### Kode
``` cpp
const int STARTRUTE = 208; // definerer hvor i rutenettet vi skal starte fra
const int USETT = -999; // usette noder / ruter, kan være uansett stort negativt tall
/**
 *  Pr�ver effektivt/raskt � finne en kort vei mellom to ruter i et rutenett.
 *
 *  @return   Om fant fram fra STARTRUTE til MAALRUTE eller ei
 *  @see      heuristics(...)
 */
 bool Astar() {
	 int i, // løkkevariabel
		 nr = STARTRUTE, // startnode
		 nabo, // naborute til aktuell node
		 x, y, // Rutenummer omgjort til indeks.
		 vekt, // Totalvekt fra startnode til nabo
		 tillegg; // kantvekten fra aktuell node 'nr' til 'nabo'

	gFringe.update(nr, -USETT); // legger startnode på Fringe
	gTilknytning[nr] = 0; // siden den er startnode har den ingen tilknyttning
	gKantVekt[nr] = 0; // 0 i totalvekt til noden fra start (siden den er start)

	while (!gFringe.empty()) { // fortstt ubehandlede noder på fringe
		nr = gFringe.remove(); // henter første på fringen
		if (nr == MAALRUTE) return true; // har vi nått målet
		gKantVekt[nr] = -gKantVekt[nr]; // omgår til positiv verdi verdi

		for (i = 1; i <= 8; i++) { // finn nabonoder sitt rutenummer
			switch (i) {
				 case 1:  nabo = nr-100; tillegg = 2; break; // Rett opp.
		         case 2:  nabo = nr-99;  tillegg = 3; break; // P� skr� opp til h�yre.
		         case 3:  nabo = nr+1;   tillegg = 2; break; // Til h�yre.
		         case 4:  nabo = nr+101; tillegg = 3; break; // P� skr� ned til h�yre.
		         case 5:  nabo = nr+100; tillegg = 2; break; // Rett ned.
		         case 6:  nabo = nr+99;  tillegg = 3; break; // P� skr� ned til vens.
		         case 7:  nabo = nr-1;   tillegg = 2; break; // Til venstre.
		         case 8:  nabo = nr-101; tillegg = 3; break; // P� skr� opp til vens.
			}
			x = nabo%100; y = nabo/100; // Omgjør til kordinater

			if ((gRutenett[y][x] != 'X') && (gKantVekt[nabo] < 0)) {
				vekt = gKantVekt[nr]+tillegg;

				if (gFringe.update(nabo, vekt+heuristics(nabo))) {
					gKantVekt[nabo] = -vekt;
					gTilknytning[nabo] = nr;
				}
			}
		}
	}
	return false; // målrute ikke funnet
 }
```

``` cpp
/**
 *  Beregner "luftlinje-avstanden"
 *      ( = hypotenusen i en trekant, dvs. Euklidsk avstand) mellom to ruter.
 *
 *  @param    nr  -  Rutenummer/-ID
 *  @return   Beregnet "luftlinje" fra rute 'nr' til MAALRUTE
 */
int heuristics(int nr)  {   //  "Luftlinjen" fra 'nr' til 'MAALRUTE'.
   int dx = ((nr % 100) - (MAALRUTE % 100)),    //  Katet nr.1.
       dy = ((nr / 100) - (MAALRUTE / 100));    //  Katet nr.2.
   float luftlinje = sqrt((dx*dx) + (dy*dy));   //  Beregner hypotenusen.
   return (2*luftlinje);                        //  Dobler, s� lenge kantvekt
}               
```

### Union Find
#### Frammgangsmåte

1. Initialize the Sets
	- Start with n elements (nodes).
	- Each element is in its own set, usually represented by a tree where each element is its own root.
	- You can visualize this as a list of elements, each pointing to themselves.

2. Union Operations
	- To "union" two elements means to connect their sets.
	- If they are already in the same set, do nothing. Otherwise, choose one of the sets and link its root to the root of the other set.

3. Find Operations
	- To "find" an element means to determine which set it belongs to. This is done by following the chain of parents until you reach the root.
	- The root uniquely identifies the set.
#### Pseudokode
``` less
Function unionerOgFinn(node1, node2, unioner):
    Set i to node1
    Set j to node2

    // Find the root of i
    While gForeldre[i] > 0:
        Set i to gForeldre[i]

    // Find the root of j
    While gForeldre[j] > 0:
        Set j to gForeldre[j]

    // Union operation
    If unioner and i is not equal to j:
        Set gForeldre[j] to i

    // Check if i and j are in the same component
    Return (i equals j)

```
#### Kode
``` cpp
bool unionerOgFinn(int nr1, int nr2, const bool unioner) {
    int i = nr1, j = nr2; // Initialize indices

    // Find the root of i (nr1)
    while (gForeldre[i] > 0) {
        i = gForeldre[i];
    }

    // Find the root of j (nr2)
    while (gForeldre[j] > 0) {
        j = gForeldre[j];
    }

    // Union operation: Attach j's tree to i's tree if they are different
    if (unioner && (i != j)) {
        gForeldre[j] = i;
    }

    // Return true if i and j are in the same component
    return (i == j);
}
```
For union find med **Weight balancing** og **Path Compression** se eksempel 37.

### Huffman
#### Framgangsmåte
1. Samle data og frekvens
	- Start med en streng, del denne opp i tegn og tell hvor ofte hvert tegn forekommer

2. Lag bladnoder
	- Lag en bladnode for hvert tegn
	- hver bladnode inneholder tegnet og frekvensen

3. Lag en prioritetskø
	- Plasser alle nodene i en prioritets-kø, hvor den noden med lavest frekvens er fremst i køen, og den med høyest frekvens er bakerst i køen.

4. Konstruer Huffman treet.
	- Så lenge det er mer enn en node i køen:
		- Fjern de to nodene med lavest frekvens fra køen
		- Lag en ny "intern" node med disse to nodene som barn, og med frekvensen lik summen av frekvensen til barna
		- Plasser den nye noden på prioritets-køen.
	- Den siste noden på prioritets-køen er roten til huffman treet

5. Generer Kode
	- Traverser treet fra Rot-noden til hver Blad-node og skriv ned "koden" til hvert tegn
		- for hver venstre-kant -> legg til en 0
		- for hver høyre-kant    -> legg til en 1

6. Encode dataen
	- Oversett hvert tegn i strengen med den nye koden fra huffman-kodingen for å få den nye dataen.

7. Decode dataen
	- følg stiene i huffman treet for å finne strengen.
		- hver 0 -> gå til venstre barn
		- hver 1 -> gå til høyre barn
		- hver bladnode -> skriv tegnet.

#### Kode
Se eks_39

### N-kompletthet
Se egen PDF