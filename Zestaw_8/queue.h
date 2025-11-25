/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 27.11.25

Implementacja realizujaca ADT QUEUE na bazie listy
powiazanej podwojnie.
Czesc funkcji jest testowana przez nia sama,
przy uzyciu funkcji assert.
-----------------------------------------------*/
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>  // deklaracje strumieni cout, cin, cerr
#include <cassert>  // assert()
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
class MyQueue {
    DoubleNode<T> *head, *tail;
    std::size_t lenght = 0;
public:
    MyQueue() : head(nullptr), tail(nullptr) {}
    ~MyQueue(); // tu trzeba wyczyscic wezly

	// copy constructor
    // usage:   DoubleList<int> list2(list1);
    MyQueue(const MyQueue& other){
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

	// copy assignment operator, return *this
    // usage:   list2 = list1;
    MyQueue& operator=(const MyQueue& other){
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

	//Sprawdza czy lista jest pusta
    bool empty() const { return head == nullptr; }

    //Zwraca liczbe elementow listy - O(1)
	std::size_t size() const {return lenght;}

    // Wstawia ostatni element - O(1)
	void push(const T& item);
    void push(T&& item);

    // zwraca poczatek, nie usuwa
	T& front() const { return head->value; }

	// zwraca koniec, nie usuwa
	T& back() const { return tail->value; }

    // usuwa pierwszy dodany element O(1)
	void pop();

	// czyszczenie listy z elementow O(n)
	void clear();

    //Wyswietlanie - O(n)
	void display();

    //Wypisanie w odwrotnej kolejnosci - O(n)
	void display_reversed();

};

template <typename T>
MyQueue<T>::~MyQueue() {
    //I sposob.
    for (DoubleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    lenght = 0;
}

template <typename T>
void MyQueue<T>::display(){
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
void MyQueue<T>::display_reversed(){
	if(empty()){
		return;
	}
	DoubleNode<T> *node = tail;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->prev;
    }
    std::cout << std::endl;
}

template <typename T>
void MyQueue<T>::push(const T& item) {
    lenght++;
	if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void MyQueue<T>::push(T&& item) {
    lenght++;
	if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void MyQueue<T>::pop(){
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
void MyQueue<T>::clear(){
	assert(!empty());
		while(head != nullptr){
			pop();
		}
}

#endif //QUEUE_H