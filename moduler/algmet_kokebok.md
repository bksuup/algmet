# Algmet Kokebok

## Abstrakte Datatyper

### Vector

``` c++
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

``` c++
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

``` c++
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

``` c++
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
``` c++
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
``` c++
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
``` c++
struct Node{
	char ID;
	Node *left, *right;
	Node(char id){
		ID = id;
		left = right = nullptr;
	}
}
```

``` c++
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
``` c++
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
``` c++
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
``` c++
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

``` c++
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
``` c++
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
``` c++
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
``` c++
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
``` c++
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

## Permutering
Plassombytting  / annen rekkefølge