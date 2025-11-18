/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 29.10.25

Implementacja realizujaca ADT STACK na bazie listy
pojedynczo powiazanej. (zadanie 7.3)
Czesc funkcji jest testowana przez nia sama,
przy uzyciu funkcji assert.
-----------------------------------------------*/
#ifndef ADT_STACK_H
#define ADT_STACK_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()
#include <algorithm>

template <typename T>
struct SingleNode {
    T value;
    SingleNode *next;
    SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
    SingleNode(const T& item, SingleNode *ptr=nullptr) : value(item), next(ptr) {}
    ~SingleNode() {} // destruktor
};

template <typename T>
class MyStack {
    SingleNode<T> *head;
    std :: size_t lenght = 0;
public:
    MyStack() : head(nullptr) {} //bazowy konstruktor
    ~MyStack(); // tu trzeba wyczyscic wezly

    // copy constructor
    // usage:   MyStack<int> stos2(stos1);
    MyStack(const MyStack& other) {
        if(other.empty()){
            //std:: cout << "Lista ktora chcesz skopiowac jest pusta!";
            head = nullptr;
            return;
        }
        //else{
        head = new SingleNode<T>(other.head->value);
        lenght++;
        SingleNode<T> *our_node = head;
        SingleNode<T> *other_node = other.head->next;
        while(other_node != nullptr){
            if(other_node->next == nullptr){
                //std:: cout << our_node->value << " ";
                our_node->next = new SingleNode<T>(other_node->value);
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

    // copy assignment operator, return *this
    // usage:   stos2 = stos1;
    MyStack& operator=(const MyStack& other){
        if(other.empty()){
            return *this;
        }
        head = new SingleNode<T>(other.head->value);
        lenght++;
        SingleNode<T> *our_node = head;
        SingleNode<T> *other_node = other.head->next;
        while(other_node != nullptr){
            if(other_node->next == nullptr){
                our_node->next = new SingleNode<T>(other_node->value);
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
        //assert(!empty());
        return *this;
    }

    bool empty() const { return head == nullptr; } // Sprawdza czy stos nie ma elementow
    std::size_t size() const {return lenght;}
    void push(const T& item);
    T& top() const {return head->value;} // zwraca ostatni dodany element, nie usuwa
    void pop(); // usuwa ostatni dodany element
    void clear(); //Czysci liste
    void display(); //Wyswietla liste

};

template <typename T>
MyStack<T>::~MyStack() {
    for (SingleNode<T> *node; !empty(); ) {
        node = head->next; // zapamietujemy
        delete head;
        head = node; // kopiowanie wskaznika
    }
    lenght = 0;
}

template <typename T>
void MyStack<T>::push(const T& item) {
    if (!empty()) {
        head = new SingleNode<T>(item, head);
    } else {
        head = new SingleNode<T>(item);
    }
    lenght++;
}

template <typename T>
void MyStack<T>::pop() {
    assert(!empty());
    const SingleNode<T> *node = head; // zapamietujemy
    if (head->next == nullptr) { // jeden wezel na liscie
        head = nullptr;
    } else { // wiecej niz jeden wezel na liscie
        head = head->next;
    }
    delete node;
    lenght--;
}

template <typename T>
void MyStack<T>::clear(){
    assert(!empty());
    while(head != nullptr){
        pop();
    }
}

template <typename T>
void MyStack<T>::display() {
    if(empty()){
        return;
    }
    SingleNode<T> *node = head;
    while (node != nullptr){
        std::cout << node->value << " ";
        node = node->next;
    }
    std::cout << std::endl;
}

#endif //ADT_STACK_H