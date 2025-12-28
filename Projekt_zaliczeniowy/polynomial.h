/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 28.12.25

Implementacjê realizujaca wielomiany na bazie listy
pojedynczo powiazanej.
Funkcje sa testowane w main
-----------------------------------------------*/
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>   
#include <cassert>    
template <typename T>
struct Term {
    T value; //wspolczynnik
    int variable; //stopien jednomianu
    Term *next;
    Term() : value(T()), variable(0) , next(nullptr) {} // konstruktor domyslny - nie bedziemy z niego korzystac
    Term(const T& item, const int degree, Term *ptr=nullptr) : value(item), variable(degree), next(ptr) {}
    ~Term() = default; // destruktor
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
	Poly horner(const T& item); // Dzielenie metoda hornera
	bool operator==(const Poly& other); // Czy równe ==
	bool operator!=(const Poly& other); //Czy rozne !=
	
	void display(); //Wypisywanie wielomianu
	void add_term(const T& item, int liczba); //Zrobione!
	void remove_term(int liczba); //Do usuwania
	
	//Sprawdzanie, czy lista jest pusta
    [[nodiscard]] bool empty() const { return head == nullptr; }
    
    bool if_degree(int number); //Sprawdzamy czy jest juz taki wspolczynnik
	T& operator[](int number); //odczyt wspolczynnika przy danej potêdze x
	[[nodiscard]] int get_degree() const {return degree;} //Stopien wielomiany
    void clear(); //Do  czysczenia
    
};

template <typename T>
Poly<T> Poly<T>::horner(const T& item){
	assert(!empty());
	T values[degree];
	T end_values[degree];
	Poly<T> pom_poly;
	for(int i = degree; i >= tail->variable; i--){
		if(if_degree(i)){
			values[i] = (*this)[i];
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
	if(const Poly<T> if_equal = *this - other; if_equal.empty()){
		return true;
	}
	else return false;
	
}

template <typename T>
bool Poly<T>::operator!=(const Poly& other){
	if(const Poly<T> if_equal = *this - other; if_equal.empty()){
		return false;
	}
	else return true;
	
}

template <typename T>
void Poly<T>::clear(){
	while(head != nullptr){
		const Term<T> *term = head; // zapamietujemy
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
	for (int i = new_poly.degree; i >= 0; --i) {
		if(if_degree(i) && (*this)[i] == 0){
			remove_term(i);
		}
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

	for (int i = new_poly.degree; i >= 0; --i) {
		if(if_degree(i) && (*this)[i] == 0){
			remove_term(i);
		}
	}
	return new_poly;
}

template <typename T>
T& Poly<T>::operator[](int number){
	Term<T> *pom_term = head;
	while(pom_term->variable != number && pom_term != nullptr){
		if(!if_degree(number)){
			auto *term = new Term<T>(-1, 0);
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
void Poly<T>::add_term(const T& item, int liczba){
	if(empty()){
		head = tail = new Term<T>(item, liczba);
		degree = liczba;
	}
	//Dodaje na poczatek
	else if(liczba > head->variable){
		head = new Term<T>(item, liczba, head);
		degree = liczba;
	}
	//Dodaje jednomian na koniec
	else if(liczba < tail->variable){
			tail->next = new Term<T>(item, liczba);
        	tail = tail->next;
	}
	else {
		Term<T> *pom_term = head;
		bool if_found = false;
		while(pom_term != nullptr && !if_found ){
			//Zamieniam wartosc juz istniejacego jednomianu
			if(liczba == pom_term->variable){
				pom_term->value = pom_term->value + item;
				if_found = true;
			}
			//Dodajemy nowy jednomian pomiedzy istniejace
			else if(liczba < pom_term->variable && liczba > pom_term->next->variable ){
				pom_term->next = new Term<T>(item, liczba, pom_term->next);
				if_found = true;
			}
			else pom_term = pom_term->next;
		}
	}
	if((*this)[liczba] == 0){
		remove_term(liczba);
	}
}

template <typename T>
void Poly<T>::remove_term(int liczba) {
	assert(!empty());
	Term<T> *before_term = head;
	Term<T> *pom_term = head->next;

	if(liczba == degree){
		if (head == tail) { // jeden wezel na liscie
			head = tail = nullptr;
			degree = -1;
		} else { // wiecej niz jeden wezel na liscie
			degree = pom_term->variable;
			head = pom_term;
		}
		delete before_term;
		return;
	}

	for(int i = degree - 1; i > liczba; i--){
		if (!if_degree(i)) continue;
		before_term = pom_term;
		pom_term = pom_term->next;
	}

	if (liczba == tail->variable) tail = before_term;
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
