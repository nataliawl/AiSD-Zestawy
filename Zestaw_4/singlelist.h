/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 29.10.25

Implementacjê realizuj¹c¹ ADT LIST na bazie listy
pojedynczo powiazanej.
Czesc funkcji jest testowana przez nia sama, 
przy uzyciu funkcji assert.
-----------------------------------------------*/

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <algorithm>

template <typename T>
struct SingleNode {
// the default access mode and default inheritance mode are public
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode *ptr=nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T> *head, *tail;
    std :: size_t lenght = 0;
public:
    SingleList() : head(nullptr), tail(nullptr) {} //bazowy konstruktor
    ~SingleList(); // tu trzeba wyczyscic wezly
	
	// copy constructor
    // usage:   SingleList<int> list2(list1);
    SingleList(const SingleList& other){
    	if(other.empty()){
    		std:: cout << "Lista ktora chcesz skopiowac jest pusta!";
    		return;
		}
		else{
			//SingleNode<T> *our_node;
			//our_node->value = other.head->value;
			head = new SingleNode<T>(other.head->value);
			lenght++;
			SingleNode<T> *our_node = head;
			SingleNode<T> *other_node = other.head->next;
			while(other_node != nullptr){
				if(other_node->next == nullptr){
					//std:: cout << our_node->value << " ";
					tail = new SingleNode<T>(other_node->value);
					our_node->next = tail;
					lenght++;
					return;
				}
				else {
					our_node->next = new SingleNode<T>(other_node->value);
					our_node = our_node->next;
					other_node = other_node->next;
					lenght++;
					
				}
			}
		}	
	}
	
	// copy assignment operator, return *this
    // usage:   list2 = list1;
    SingleList& operator=(const SingleList& other){
		
		assert(!other.empty());
		head = new SingleNode<T>(other.head->value);
		lenght++;
		SingleNode<T> *our_node = head;
		SingleNode<T> *other_node = other.head->next;
		while(other_node != nullptr){
			if(other_node->next == nullptr){
				tail = new SingleNode<T>(other_node->value);
				our_node->next = tail;
				lenght++;
				return *this;
					
			}
			else {
				our_node->next = new SingleNode<T>(other_node->value);
				our_node = our_node->next;
				other_node = other_node->next;
				lenght++;
					
				}
			}
			assert(!empty());
			return *this;
		}	
	

	//Sprawdzanie, czy lista jest pusta
    bool empty() const { return head == nullptr; }
    
    //Dlugosc listy - O(1)
	std::size_t size() const{
		//Wezel pomocniczy
		/*SingleNode<T> *new_node = head;
		//Licznik elementow
		std::size_t number_of_nodes = 0;
		while(new_node != NULL){
			new_node = new_node->next;
			number_of_nodes++;
		}
		return number_of_nodes;*/
		return lenght;
	} 
	
	//Wstawianie elementu z przodu - O(1), L.push_front(item)
    void push_front(const T& item);
    
    //Wstawianie elementu na koniec -  O(1), L.push_back(item)
	void push_back(const T& item);
    
	// zwraca poczatek, nie usuwa
	T& front() const { return head->value; } 
    
	// zwraca koniec, nie usuwa
	T& back() const { return tail->value; } 
    
    // usuwa poczatek O(1)
	void pop_front();
    
    //usuwa koniec O(n)
	void pop_back();
    
    // czyszczenie listy z elementow O(n)
	void clear(){
		assert(!empty());
		while(head != nullptr){
			pop_front();
		}
	}
	
	//Wyswietlanie elementów - O(n)
    void display();
	
	// Operacje z indeksami. NIEOBOWIAZKOWE
    
	// jaki index na liscie (-1 gdy nie ma) O(n)
    int index(const T& item){ 
    	//Tworzymy wezel pomocniczy i zmienna index
		assert(!empty());
		SingleNode<T> *pom_node = head;
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
	void erase(std::size_t pos){
		if(empty()){
			std :: cout << "Lista jest pusta!\n";
		}
		if(pos >= lenght){
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
		
		SingleNode<T> *before_node = head;
		SingleNode<T> *pom_node = head->next;
		
		for(std:: size_t i = 2; i < pos; i++){
			before_node = pom_node;
			pom_node = pom_node->next;
		}
		
		before_node->next = pom_node->next;
		delete pom_node;
		lenght--;	
	}
	
	//Wstawianie elementu przed podanym indeksem
	void insert(std::size_t pos, const T& item){
		if(empty()){
			std :: cout << "Lista jest pusta!\n";
		}
		if(pos > lenght){
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
		SingleNode<T> *before_node = head; // 0
		SingleNode<T> *after_node = head->next; //1
		for(std::size_t i = 0; i < pos; i++){
			before_node = after_node;
			after_node = after_node->next;
		}
		SingleNode<T> *node = new SingleNode<T>(item, after_node); 
		before_node->next = node;
		lenght++;
		
	}
	
	//Pobieranie wartosci elementu o indeksie pos
	T& operator[](std::size_t pos){
		if(empty()){
			std :: cout << "Lista jest pusta!\n";
		}
		if(pos >= lenght){
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
		
		SingleNode<T> *pom_node = head;
		for(std::size_t i = 0 ; i < pos ; i ++){
			pom_node = pom_node->next;
		}
		return pom_node->value;
	}
   
};

template <typename T>
SingleList<T>::~SingleList() {
    //I sposob.
    for (SingleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    lenght = 0;
    // II sposob.
    // while (!empty()) { pop_front(); }
}


template <typename T>
void SingleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = tail = new SingleNode<T>(item);
    }
    lenght++;
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail->next = new SingleNode<T>(item);
        tail = tail->next;
    } else {
        head = tail = new SingleNode<T>(item);
    }
    lenght++;
}

template <typename T>
void SingleList<T>::display() {
    SingleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

template <typename T>
void SingleList<T>::pop_front() {
    if(empty()){
    	return;
	}
    SingleNode<T> *node = head; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;
    lenght--;
}

template <typename T>
void SingleList<T>::pop_back() {
    assert(!empty());
    SingleNode<T> *node = tail; // zapamietujemy
    if (head == tail) { // jeden wezel na liscie
        head = tail = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        // Szukamy poprzednika ogona.
        SingleNode<T> *before=head;
        while (before->next != tail) {
            before = before->next;
        }
        tail = before;
        tail->next = nullptr;
    }
    delete node;
    lenght--;
}

#endif
