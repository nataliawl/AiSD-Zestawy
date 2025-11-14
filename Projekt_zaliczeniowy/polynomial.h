/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 09.11.25

Implementacjê realizujaca wielomiany na bazie listy
pojedynczo powiazanej.
Funkcje sa testowane w main
-----------------------------------------------*/
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>   
#include <cassert>    
#include <algorithm>
template <typename T>
struct Term {
    T value; //wspolczynnik
    int variable; //stopien jednomianu
    Term *next;
    Term() : value(T()), variable(0) , next(nullptr) {} // konstruktor domyslny - nie bedziemy z niego korzystac
    Term(const T& item, int degree, Term *ptr=nullptr) : value(item), variable(degree), next(ptr) {}	
    ~Term() {} // destruktor
};

template <typename T>
class Poly{
	Term<T> *head, *tail;
	int degree = -1; //Stopien wielomianu

public:
	Poly() : head(nullptr), tail(nullptr) {}
    ~Poly();
    
    // copy constructor 
    // usage:   Poly<int> wielomian2(wielomian1);
	Poly(const Poly& other){
		if(other.empty()){
			std:: cout << "Wielomian ktory chcesz skopiowac jest pusta!";
			head = tail = nullptr;
			return;
		}
		head = new Term<T>(other.head->value, other.head->variable);
		degree = other.degree;
		Term<T> *our_term = head;
		Term<T> *other_term = other.head->next;
		while(other_term != nullptr){
			if(other_term->next == nullptr){
				//std:: cout << our_node->value << " ";
				tail = new Term<T>(other_term->value, other_term->variable);
				our_term->next = tail;
				return;
			}
			else {
				our_term->next = new Term<T>(other_term->value, other_term->variable);
				our_term = our_term->next;
				other_term = other_term->next;

			}
		}
	}
	//Copy assigment constructor
	// usage:  wielomian2 = wielomian1
	Poly& operator=(const Poly& other){
		std:: cout << "Cokolwiek?";
		if(other.empty()){
			std:: cout << "Wielomian ktory chcesz skopiowac jest pusta!";
			head = tail = nullptr;
			return *this;
		}
		this->clear();
		head = new Term<T>(other.head->value, other.head->variable);
		degree = other.degree;
		Term<T> *our_term = head;
		Term<T> *other_term = other.head->next;
		while(other_term != nullptr){
			if(other_term->next == nullptr){
				std:: cout << our_term->value << " ";
				tail = new Term<T>(other_term->value, other_term->variable);
				our_term->next = tail;
				return *this;
			}
			else {
				std:: cout << our_term->value << " ";
				our_term->next = new Term<T>(other_term->value, other_term->variable);
				our_term = our_term->next;
				other_term = other_term->next;

			}
		}
		return *this;
	}
	
	//Dzialania na wielomianach:
	
	Poly operator+(const Poly& other); //Dodawanie
	Poly operator-(const Poly& other); //Odejmowanie
	Poly operator*(const Poly& other); //Mnozenie
	Poly operator/(const T& item); // Dzielenie metoda hornera
	bool operator==(const Poly& other); // Czy równe ==
	bool operator!=(const Poly& other); //Czy rozne !=
	
	void display(); //Wypisywanie wielomianu
	void add_term(const T& item, int number); //Zrobione!
	void remove_term(int number); //Do usuwania
	
	//Sprawdzanie, czy lista jest pusta
    bool empty() const { return head == nullptr; }
    
    bool if_degree(int number); //Sprawdzamy czy jest juz taki wspolczynnik
	T& operator[](int number); //odczyt wspolczynnika przy danej potêdze x
	int get_degree() const {return degree;} //Stopien wielomiany
    void clear(); //Do  czysczenia
    
};

template <typename T>
Poly<T> Poly<T>::operator/(const T& item){
	assert(!empty());
	T values[degree];
	T end_values[degree];
	Poly<T> pom_poly;
	for(int i = degree; i >= tail->variable; i--){
		if(if_degree(i)){
			values[i] = this->operator[](i);	
		}
		else {
			values[i] = 0;
		}
		if(i == 0){
			break;
		}
	}

	for(int i = degree; i >= tail->variable; i--){
		if(i == degree){
			end_values[i] = values[i];
		}
		else{
			end_values[i] = item*end_values[i + 1] + values[i];
		}
		
		if(i == 0){
			break;
		}
	}
	
	for(int i = degree; i >= tail->variable; i--){
		if(i == tail->variable){
			pom_poly.add_term(end_values[i], i);
			break;
		}
		pom_poly.add_term(end_values[i], i - 1);
	}

	return pom_poly;
	
}

template <typename T>
Poly<T> Poly<T>::operator*(const Poly &other){
	Term<T> *term = head;
	Poly<T> pom_poly;
	if (this->empty() || other.empty()) {
		return pom_poly;
	}
	while(term != nullptr){
		Term<T> *other_term = other.head;
		while(other_term != nullptr){
			T pom_value = term->value * other_term->value;
			int pom_degree = term->variable + other_term->variable;
			pom_poly.add_term(pom_value, pom_degree);
			other_term = other_term->next;
		}
		term = term->next;
	}
	return pom_poly;
}

template <typename T>
bool Poly<T>::operator==(const Poly& other){
	Poly<T> if_equal = *this - other;
	if(if_equal.empty()){
		return true;
	}
	else return false;
	
}

template <typename T>
bool Poly<T>::operator!=(const Poly& other){
	Poly<T> if_equal = *this - other;
	if(if_equal.empty()){
		return false;
	}
	else return true;
	
}

template <typename T>
void Poly<T>::clear(){
	while(head != nullptr){
		Term<T> *term = head; // zapamietujemy
    	if (head == tail) { // jeden wezel na liscie
        	head = tail = nullptr;
    	} 
		else { // wiecej niz jeden wezel na liscie
        	head = head->next;
    	}
    	delete term;
	}
	degree = -1;
}

template <typename T>
Poly<T> Poly<T>::operator+(const Poly& other){
	Poly<T> new_poly;
	Term<T> *one_term = other.head;
	Term<T> *two_term = head;
	while(one_term != nullptr){
		new_poly.add_term(one_term->value, one_term->variable);
		one_term = one_term->next;
	}
	while(two_term != nullptr){
		new_poly.add_term(two_term->value, two_term->variable);
		two_term = two_term->next;
	}
	return new_poly;
}

template <typename T>
Poly<T> Poly<T>::operator-(const Poly& other){
	Poly<T> new_poly;
	Term<T> *one_term = head;
	Term<T> *two_term = other.head;
	while(one_term != nullptr){
		new_poly.add_term(one_term->value, one_term->variable);
		one_term = one_term->next;
	}
	while(two_term != nullptr){
		new_poly.add_term(-two_term->value, two_term->variable);
		two_term = two_term->next;
	}
	return new_poly;
}

template <typename T>
T& Poly<T>::operator[](int number){
	Term<T> *pom_term = head;
	while(pom_term->variable != number && pom_term != nullptr){
		if(!if_degree(number)){
			Term<T> *term = new Term<T>(-1, 0);
			return term->value;
		}
		pom_term = pom_term->next;
	}
	
	return pom_term->value;
}

template <typename T>
void Poly<T>::display(){
	if(empty()){
    	return;
	}
	Term<T> *term = head;
    while (term != nullptr){
        if(term->next == nullptr){
        	std::cout << term->value << "*x^" << term->variable;
        	std::cout << std::endl;
        	return;
		}
		std::cout << term->value << "*x^" << term->variable << " + ";
        term = term->next;
    }
    std::cout << std::endl;
}

template <typename T>
void Poly<T>::add_term(const T& item, int number){
	if(empty()){
		head = tail = new Term<T>(item, number);
		degree = number;
	}
	//Dodaje na poczatek
	else if(number > head->variable){
		head = new Term<T>(item, number, head);
		degree = number;
	}
	//Dodaje jednomian na koniec
	else if(number < tail->variable){
			tail->next = new Term<T>(item, number);
        	tail = tail->next;
	}
	else {
		Term<T> *pom_term = head;
		bool if_found = false;
		while(pom_term != nullptr && !if_found ){
			//Zamieniam wartosc juz istniejacego jednomianu
			if(number == pom_term->variable){
				pom_term->value = pom_term->value + item;
				if_found = true;
			}
			//Dodajemy nowy jednomian pomiedzy istniejace
			else if(number < pom_term->variable && number > pom_term->next->variable ){
				pom_term->next = new Term<T>(item, number, pom_term->next);
				if_found = true;
			}
			else pom_term = pom_term->next;
		}
	}
	if(operator[](number) == 0){
		remove_term(number);
	}
}

template <typename T>
void Poly<T>::remove_term(int number){
		assert(!empty());
		if(number == degree){
			Term<T> *head_term = head; // zapamietujemy
    		if (head == tail) { // jeden wezel na liscie
        		head = tail = nullptr;
        		degree = -1;
    		} else { // wiecej niz jeden wezel na liscie
        		degree = head->next->variable;
				head = head->next;
    		}
    		delete head_term;
			return;
		}
		if(number == tail->variable){
			Term<T> *tail_term = tail; // zapamietujemy
    		if (head == tail) { // jeden wezel na liscie
        		head = tail = nullptr;
        		degree = -1;
    		} else { // wiecej niz jeden wezel na liscie
        		// Szukamy poprzednika ogona.
        		Term<T> *before=head;
        		while (before->next != tail) {
            		before = before->next;
        		}
        		tail = before;
        		tail->next = nullptr;
    		}
    			delete tail_term;
				return;
		}
		
		Term<T> *before_term = head;
		Term<T> *pom_term = head->next;
		
		for(int i = 2; i < number; i++){
			before_term = pom_term;
			pom_term = pom_term->next;
		}
		
		before_term->next = pom_term->next;
		delete pom_term;
}

template <typename T>
bool Poly<T>::if_degree(int number){
	Term<T> *pom_term = head;
	while(pom_term != nullptr){
		if(number == pom_term->variable){
			return true;
		}
		pom_term = pom_term->next;
	}
	return false;
}

template <typename T>
Poly<T>::~Poly() {
    for (Term<T> *term; !empty(); ) {
        term = head->next; // zapamietujemy
        delete head;
        head = term; // kopiowanie wskaznika
    }
    degree = -1;
}

#endif
