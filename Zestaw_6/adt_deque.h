/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 12.11.25

Implementacja ADT DEQUE na bazie tablicy o
stalym rozmiarze.
Funkcje sa testowane w main oraz za pomoca
assert
-----------------------------------------------*/
#ifndef ADT_DEQUE_H
#define ADT_DEQUE_H
#include <cassert>
#include <iostream>

template <typename T>
class MyDeque {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    explicit MyDeque(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyDeque() { delete [] tab; }

    MyDeque(const MyDeque& other) { // copy constructor
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        tab = new T[msize];
        for(std::size_t i = head; i != tail; i=(i+1) % msize) {
            tab[i] = other.tab[i];
        }
    }

    MyDeque& operator=(const MyDeque& other) { // copy assignment operator, return *this
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        tab = new T[msize];
        for(std::size_t i = head; i != tail; i=(i+1) % msize) {
            tab[i] = other.tab[i];
        }
        return *this;
    }

    bool empty() const { return head == tail; } //Sprawdza czy jest pusta
    bool full() const { return (tail + 1) % msize == head; } //Sprawdza czy nie jest pelna
    std::size_t size() const { return (tail - head + msize) % msize; } //Sprawdza aktualny rozmiar listy
    std::size_t max_size() const { return msize-1; } //Zwraca maksymalny rozmiar listy
    void push_front(const T& item); // dodanie na początek O(1)
    void push_back(const T& item); // dodanie na koniec O(1)
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec
    void pop_front(); // usuwa początek kolejki O(1)
    void pop_back(); // usuwa koniec kolejki O(1)
    void clear(); // czyszczenie listy z elementów
    void display(); //Wyswietlanie listy
    void display_reversed(); //Wyswietlanie w odwrotnej kolejnosci

    std::size_t get_head() const { return head; }; //Indeks glowy
    std::size_t get_tail() const { return tail; }; //Indeks ogona

    // Operacje z indeksami
    T& operator[](std::size_t pos); // podstawienie L[pos]=item, odczyt L[pos]
    void erase(std::size_t pos); //Usuwanie po indeksie
    int index(const T& item); // jaki index na liście (-1 gdy nie ma)
    void insert(std::size_t pos, const T& item); // inserts item before pos
};

template<typename T>
void MyDeque<T>::erase(std::size_t pos) {
    assert(!empty());
    assert(!(pos >= tail && pos < head ));
    assert(pos < msize - 1);
    if (pos == head) pop_front(); //Dziala
    else if (pos == tail - 1) pop_back(); //Dziala
    else if (pos < tail - 1){ //Dziala!
        T pom = tab[tail - 1]; //Zapisujemy koniec
        for (std:: size_t i = tail - 2; i >= pos; i-- ) {
            T wanted = tab[i];
            tab[i] = pom;
            pom = wanted;
        }
        tail--;
    }
    else {
        T pom = tab[head];
        for (std::size_t i = head + 1; i <= pos; i++) {
            T wanted = tab[i];
            tab[i] = pom;
            pom = wanted;
        }
        head++;
    }
}

template<typename T> //Chyba dziala!
void MyDeque<T>::insert(std::size_t pos, const T &item) {
    //Indeks nie moze byc niepowiazany z innymi elementami listy!
    assert(!full());
    assert(!(pos >= (tail + 2) && pos <= head - 1));
    //assert(pos < size());
    //Gdy przed pierwszy wolnym, to zamieniamy z ostatnim elemetem?
    //Albo przesuwamy ostatni w sumie - dziala!
    if (pos == tail) {
        T pom = tab[tail - 1];
        tab[tail - 1] = item;
        tab[tail] = pom;
        tail++;
    }
    //Wstawiamy na pierwszym nowym elemencie -dziala!
    else if (pos == tail + 1) {
        tab[tail] = item;
        tail++;
    }
    //Jesli wstawiamy przed pierwszym zajetym to zmniejszamy glowe
    else if (pos == head) {
        tab[pos - 1] = item;
        head = pos -1;
    }
    else if (pos > head) {
        T wanted = item;
        for (std:: size_t i = pos - 1 ; i >= head - 1; i--) {
            T pom = tab[i];
            tab[i] = wanted;
            wanted = pom;
        }
        head--;
    }
    else { //Zostalo przed ogonem
        T wanted = item;
        for (std::size_t i = pos - 1; i <= tail; i++) {
            T pom = tab[i];
            tab[i] = wanted;
            wanted = pom;
        }
        tail++;
    }
}

template<typename T>
int MyDeque<T>::index(const T &item) {
    for (std::size_t i = head; i != tail; i=(i+1) % msize) {
        if(tab[i] == item) {
            return i;
        }
    }
    return -1;
}


template<typename T>
T& MyDeque<T>::operator[](std::size_t pos) {
    assert(!empty());
    assert(pos < msize);
    assert(!(pos >=tail && pos < head));
    return tab[pos];
}


template<typename T>
void MyDeque<T>::pop_back() {
    assert(!empty());
    tail = tail - 1;
    if (tail < 0) tail = 0;

}

template<typename T>
void MyDeque<T>::pop_front() {
    assert(!empty());
    head = head + 1;
    if (head == msize) {
        head = 0;
    }
}


template<typename T>
void MyDeque<T>::clear() {
    tail = head = 0;
}

template<typename T>
void MyDeque<T>::display_reversed() {
    std::size_t i = tail - 1;
    while(i != head - 1) {
        std::cout << tab[i] << " ";
        if (i == 0) {
            i = msize - 1;
        }
        else i--;
    }
    std::cout << std::endl;
}

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    assert(!full());
    head = (head + msize -1) % msize;
    tab[head] = item;
}
template <typename T>
void MyDeque<T>::push_back(const T& item) {
    assert(!full());
    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::display() {
    for (std::size_t i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout <<std::endl;
}

#endif //ADT_DEQUE_H