/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 22.10.25

Implementacjê realizuj¹c¹ ADT LIST na bazie tablicy 
o sta³ym rozmiarze (tablica statyczna), 
ustalanym w czasie tworzenia listy, oraz testy
implementacji.
Czesc funkcji jest testowana przez nia sama, 
przy uzyciu funkcji assert.
-----------------------------------------------*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>   // assert()
#include <algorithm>

template <typename T>
class ArrayList {
	T* tab;
    std::size_t msize; // najwieksza mozliwa liczba elementow
    std::size_t last; // pierwsza wolna pozycja
public:
	
	// default constructor
    ArrayList(std::size_t s=10) : msize(s), last(0) {
        assert( s > 0 );
        tab = new T[s];
        assert( tab != nullptr );
    } 
    
	~ArrayList() { delete [] tab; } // destruktor
	
	//copy constructor
	// usage: ArrayList<int> list2(list1);
    ArrayList(const ArrayList& other){
		msize = other.msize;
		last = other.last;
		tab = new T[msize];
		tab = other.tab;
		assert( tab != nullptr );
			
	}
	
	// move constructor NIEOBOWIAZKOWE
    // usage:   ArrayList<int> list2(std::move(list1));
    ArrayList(ArrayList&& other) : msize(other.msize), last(0) {
    		// Wstawiamy elementy tablicy other
			tab = new T[msize];
			tab = other.tab;
    		last = other.last;
    		
    		//Usuwamy elementy tablicy other
    		other.tab = nullptr;
    		other.last = 0;
    		
    		assert( tab != nullptr );
    		assert( other.tab == nullptr );
    	
	} 
	
	// copy assignment operator, return *this
    // usage:   list2 = list1;
    ArrayList& operator=(const ArrayList& other){
   	msize = other.msize;
		last = other.last;
		tab = new T[msize];
		tab = other.tab;
		
		assert( tab != nullptr );
	} 
	
	
	// move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE
    ArrayList& operator=(ArrayList&& other){
    	assert( msize > 0 );
    	if(this != &other){
    		
    		//Usuwamy elementy tablicy
			delete[] tab;
    		
    		//Zastepujemy elementami drugiej
			tab = new T[msize];
			tab = other.tab;
    		last = other.last;
    		
    		other.tab = nullptr;
    		other.last = 0;
    		assert( tab != nullptr );
    		assert( other.tab == nullptr );
    		
		}
		return *this;
	}
	
	// checks if the container has no elements
    bool empty() const { 
		if(last != 0){
			return false;
		}
		return true; 
	}
	
	// checks if the container is full
    bool full() const { 
		if(last != msize){
			return false;	
		}
		return true; 
	} 
	
	// liczba elementow na liscie
    std::size_t size() const { 
		return last; 
	} 
    
    // najwieksza mozliwa liczba elementow
	std::size_t max_size() const { 
		return msize;
	} 
	
	// dodanie na poczatek
    void push_front(const T& item){
		if(full()){
			std::cout << "Lista jest pelna! Nie mozesz dodac wiecej elementow!\n";
			return;
		}
		
		T a;
		T b = item;
		for(std::size_t i = 0; i < last + 1; i++){
			a = tab[i];
			tab[i] = b;
			b = a;
		}
		
		last++;
		assert(tab[0] == item);
		
	}
	  
	// dodanie na koniec
	void push_back(const T& item){
    	if(full()){
			std::cout << "Lista jest pelna! Nie mozesz dodac wiecej elementow!\n";
			return;
		}
		
		tab[last] = item;
		last++;
		
		assert(tab[last - 1] == item);
		
	};
 
    // zwraca poczatek, nie usuwa, error dla pustej listy
	T& front(){
		assert(!empty());
		return tab[0];	
	}
	
	// zwraca koniec, nie usuwa, error dla pustej listy
    T& back(){
    	assert(!empty());
    	return tab[last - 1];
	} 
	
	// usuwa poczatek, error dla pustej listy
    void pop_front(){
		assert(!empty());
		T a = tab[0];
		for(std:: size_t i = 0; i < last - 1; i ++){
			tab[i] = tab[i + 1];
		}
		last--;
		assert(tab[0] != a);
	}
	
	// usuwa koniec, error dla pustej listy
    void pop_back(){
    	assert(!empty());
    	T a = tab[last - 1];
		tab[last - 1] = 0;
    	last --;
		assert(tab[last] != a);	
	}
	
	// czyszczenie listy z elementow
    void clear(){
    	assert(!empty());
    	delete[] tab;
		last = 0;
		assert(tab != nullptr);
	}
	 
    // lepiej zdefiniowac operator<<
	void display(){
    	for(std::size_t i = 0; i < last; i++){
    			std::cout << tab[i] << "\n";
		}
		std::cout << "\n";
	} 
	
	// odwracanie kolejnosci
    void reverse(){
    	assert(size() >= 2);
    	T a;
    	T* pom_tab;
    	pom_tab = new T[msize];
		pom_tab = tab;
		
		std:: size_t i = 0;
    	std:: size_t j = last - 1;
    	while(i != j && i < last/2){
    		a = tab[i];
    		tab[i] = tab[j];
    		tab[j] = a;
    		j--;
    		i++;
		}
		assert(pom_tab == tab);
	} 
	
	// sortowanie listy
    void sort(){
		int j;
		T insert_number;
		for(std::size_t i = 1; i < last; i++){
			insert_number = tab[i];
			j = i - 1;
			while(j >= 0 && tab[j] > insert_number){
				tab[j+ 1] = tab[j];
				j--;
			}
			tab[j+ 1] = insert_number;
		}
		
	}
	
	//Sprawdzanie czy lista jest posortowana
	bool if_sorted(){
		for(std::size_t i = 0; i< last - 1; i++){
			if(tab[i] > tab[i + 1]){
				return false;
			}
		}
		return true;
	}

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (std::size_t i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }
        return os;
    } // usage:   std::cout << L << std::endl;
};

#endif

// EOF
