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
			//SingleNode<T> *our_node;
			//our_node->value = other.head->value;
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

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));
	
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

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE
	
	//Sprawdza czy lista jest pusta -zrobione
    bool empty() const { return head == nullptr; }
    
    //Zwraca liczbe elementow listy - O(1) - zrobione!
	std::size_t size() const {return lenght;} 
    
    // Umieszcza element na poczatku - O(1)
	void push_front(const T& item); //zrobione!
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    
	// Umieszcza element na poczatku - O(1)
	void push_back(const T& item); // O(1) 
    //void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    
    // zwraca poczatek, nie usuwa 
	T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    
	// zwraca koniec, nie usuwa
	T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    
	void pop_front(); // usuwa poczatek O(1)-zrobione!
    
	void pop_back(); // usuwa koniec O(1)-zrobione!
    
	void clear(); // czyszczenie listy z elementow O(n)
    
	void display();// O(n)-zrobione!
    
	void display_reversed(); // O(n)-zrobione!

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](std::size_t pos) const; // dostep do obiektu const
    void erase(std::size_t pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(std::size_t pos, const T& item); // inserts item before pos,
    void insert(std::size_t pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

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
