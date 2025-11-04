// doublelist.h

//zrobic clear!
//ewentualnie tez iteratory?
#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <algorithm>

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
    std::size_t lenght = 0;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly - zrobione?
	
	// copy constructor - dziala!
    // usage:   DoubleList<int> list2(list1);
    DoubleList(const DoubleList& other){
		if(other.empty()){
    		std:: cout << "Lista ktora chcesz skopiowac jest pusta!";
    		return;
		}
		else{
			head = new DoubleNode<T>(other.head->value);
			lenght++;
			DoubleNode<T> *our_node = head;
			DoubleNode<T> *other_node = other.head->next;
			while(other_node != nullptr){
				if(other_node->next == nullptr){
					//std:: cout << our_node->value << " ";
					tail = new DoubleNode<T>(other_node->value);
					tail->prev = our_node;
					our_node->next = tail;
					lenght++;
					return;
				}
				else {
					our_node->next = new DoubleNode<T>(other_node->value);
					our_node->next->prev = our_node;
					our_node = our_node->next;
					other_node = other_node->next;
					lenght++;
					
				}
			}
		}
	} 

	// copy assignment operator, return *this - dziala
    // usage:   list2 = list1;
    DoubleList& operator=(const DoubleList& other){
    	assert(!other.empty());
    	lenght++;
		head = new DoubleNode<T>(other.head->value);
		DoubleNode<T> *our_node = head;
		DoubleNode<T> *other_node = other.head->next;
		while(other_node != nullptr){
			if(other_node->next == nullptr){
				tail = new DoubleNode<T>(other_node->value);
				our_node->next = tail;
				tail->prev = our_node;
				lenght++;
				return *this;
					
			}
			else {
				our_node->next = new DoubleNode<T>(other_node->value);
				our_node->next->prev = our_node;
				our_node = our_node->next;
				other_node = other_node->next;
				lenght++;
					
				}
			}
			assert(!empty());
			return *this;
	}

	//Sprawdza czy lista jest pusta -zrobione
    bool empty() const { return head == nullptr; }
    
    //Zwraca liczbe elementow listy - O(1) - zrobione!
	std::size_t size() const {return lenght;} 
    
    // Umieszcza element na poczatku - O(1)
	void push_front(const T& item); //zrobione!
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    
	// Umieszcza element na poczatku - O(1)
	void push_back(const T& item); // O(1) 
    
    // zwraca poczatek, nie usuwa 
	T& front() const { return head->value; } 
    
	// zwraca koniec, nie usuwa
	T& back() const { return tail->value; } 
    
	void pop_front(); // usuwa poczatek O(1)-zrobione!
    
	void pop_back(); // usuwa koniec O(1)-zrobione!
    
	void clear(); // czyszczenie listy z elementow O(n)
    
	void display();// O(n)-zrobione!
    
	void display_reversed(); // O(n)-zrobione!

    // Operacje z indeksami. NIEOBOWIAZKOWE
	//zaczynamy od 0!
	//Sprawdzic dzialanie w domu!
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos] - sprawdzic!
    const T& operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos); //sprawdzic!
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)- sprawdzic!
    void insert(std::size_t pos, const T& item); // inserts item before pos, - sprawdzic!
    //void insert(std::size_t pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
T& DoubleList<T>::operator[](std::size_t pos){
	if(empty()){
			std :: cout << "Lista jest pusta!\n";
		}
		if(pos >= lenght || pos < 0){
			std:: cout << "\nIndeks jest niewlasciwy!\n";
			T error = -1;
			return error;
		}
		if(pos == 0){
			return head->value;
		}
		if(pos == lenght - 1){
			return tail->value;
		}
		
		DoubleNode<T> *pom_node = head;
		for(std::size_t i = 0 ; i < pos ; i ++){
			pom_node = pom_node->next;
		}
		return pom_node->value;
}

template <typename T>
void DoubleList<T>::insert(std::size_t pos, const T& item){
		if(pos > lenght || pos < 0){
			std:: cout << "Indeks jest niewlasciwy!\n";
			return;
		}
		if(pos == 0){
			push_front(item);
			return;
		}
		if(pos == lenght){
			push_back(item);
			return;
		}
		DoubleNode<T> *before_node = head; // 0
		DoubleNode<T> *after_node = head->next; //1
		for(std::size_t i = 0; i < pos; i++){
			before_node = after_node;
			after_node = after_node->next;
		}
		Doublenode<T> *node = new DoubleNode<T>(item, after_node, before_node); 
		before_node->next = node;
		after_node->prev = node;
		lenght++;
		
	}

template <typename T>
void DoubleList<T>::erase(std::size_t pos){
	if(empty()){
			std :: cout << "Lista jest pusta!\n";
		}
		if(pos >= lenght || pos < 0){
			std:: cout << "Indeks jest niewlasciwy!\n";
			return;
		}
		if(pos == 0){
			pop_front();
			return;
		}
		if(pos == lenght - 1){
			pop_back();
			return;
		}
		
		//SingleNode<T> *before_node = head;
		DoubleNode<T> *pom_node = head->next;
		
		for(std:: size_t i = 2; i < pos; i++){
			//before_node = pom_node;
			pom_node = pom_node->next;
		}
		
		pom_node->prev->next = pom_node->next;
		pom_node->next->prev = pom_node->prev;
		delete pom_node;
		lenght--;	
}

template <typename T>
int DoubleList<T>::index(const T& item){
	assert(!empty());
	DoubleNode<T> *pom_node = head;
	int index = 0; 
	while(pom_node != nullptr){
		if(pom_node->value == item){
			return index;
		}
		pom_node = pom_node->next;
		index++;
	}
		return -1;
}


template <typename T>
DoubleList<T>::~DoubleList() {
    //I sposob.
    for (DoubleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    lenght = 0;
    // II sposob.
    // while (!empty()) { pop_front(); }
}

//Dziala
template <typename T>
void DoubleList<T>::display(){
	//if(empty()){
	//	return;
	//}
	DoubleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void DoubleList<T>::display_reversed(){
	//if(empty()){
	//	return;
	//}
	DoubleNode<T> *node = tail;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->prev;
    }
    std::cout << std::endl;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    lenght++;
	if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    lenght++;
	if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

//Chyba dzia³a!
template <typename T>
void DoubleList<T>::push_back(const T& item){
	lenght++;
	if (!empty()) {
        tail = new DoubleNode<T>(item, nullptr, tail);
        tail->prev->next = tail;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}
	

template <typename T>
void DoubleList<T>::pop_front(){
	if(empty()){
		std:: cout <<"Nie ma czego usunac!";
		return;
	}
	
	DoubleNode<T> *pom = head;
	head = head->next;
	if(head!= nullptr){
		head->prev = nullptr;
	}
	delete pom;
	lenght--;
		
}

template <typename T>
void DoubleList<T>::pop_back(){
	if(empty()){
		std:: cout <<"Nie ma czego usunac!";
		return;
	}
	
	DoubleNode<T> *pom = tail;
	tail = tail->prev;
	if(tail!= nullptr){
		tail->next = nullptr;
	}
	delete pom;
	lenght--;
		
}
template <typename T> // z tym cos nie tak!
void DoubleList<T>::clear(){
	assert(!empty());
		while(head != nullptr){
			pop_front();
		}
		
}
#endif

// EOF
