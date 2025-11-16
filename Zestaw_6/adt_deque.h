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


    // Operacje z indeksami - 0 to head, size - 1 to tail
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos] - poprawione
    void erase(int pos); //Usuwanie po indeksie - poprawione!
    int index(const T& item); // jaki index na liście (-1 gdy nie ma) - poprawione!
    void insert(int pos, const T& item); // inserts item before pos
};

template<typename T>
void MyDeque<T>::erase(int pos) {
    assert(!empty());
    assert(pos < size());
    if (pos == 0) pop_front(); //Dziala
    else if (pos == size() - 1) {
        pop_back(); //Dziala
    }
    else if (head + pos > msize - 1){ //Dziala!
        int margin = (msize - 1) - head;
        pos = pos - margin - 1;
        T pom = tab[tail - 1]; //Zapisujemy koniec
        for (int i = tail - 2; i >= pos; i-- ) {
            T wanted = tab[i];
            tab[i] = pom;
            pom = wanted;
        }
        tail--;
    }
    else {
        T pom = tab[head];
        for (int i = 1; i <= pos; i++) {
            T wanted = tab[head + i];
            tab[head + i] = pom;
            pom = wanted;
        }
        head++;
    }
}

template<typename T> //Chyba dziala!
void MyDeque<T>::insert(int pos, const T &item) {
    //Indeks nie moze byc niepowiazany z innymi elementami listy!
    assert(!full());
    assert(pos <= size());
    //assert(pos < size());
    //Gdy przed pierwszy wolnym, to zamieniamy z ostatnim elemetem?
    //Albo przesuwamy ostatni w sumie - dziala!
    //Wstawiamy na pierwszym nowym elemencie -dziala!
    if (pos == size()) push_back(item);
    //Jesli wstawiamy przed pierwszym zajetym to zmniejszamy glowe
    else if (pos == 0) push_front(item);
    else if (head + pos > msize - 1) {
        int margin = (msize - 1) - head;
        pos = pos - margin - 1;
        std:: cout << pos << std::endl;
        T wanted = item;
        for (int i = pos  ; i <= tail; i++) {
            std:: cout << tab[i] << std:: endl;
            T pom = tab[i];
            tab[i] = wanted;
            wanted = pom;
        }
        tail++;
    }
    else {
        T wanted = item;
        for (int i = head + pos - 1; i >= head - 1; i--) {
            std::cout << i << " " << tab[i] << std::endl;
            T pom = tab[i];
            tab[i] = wanted;
            wanted = pom;
        }
        head--;
    }
}

template<typename T>
int MyDeque<T>::index(const T &item) {
    int index = 0;
    for (int i = head; i != tail; i=(i+1) % msize) {
        if(tab[i] == item) {
            return index;
        }
        index++;
    }
    return -1;
}


template<typename T>
T& MyDeque<T>::operator[](int pos) {
    assert(!empty());
    assert(pos < size());
    if (head + pos > msize - 1) {
        int pom = (msize - 1) - head;
        pos = pos - pom;
        return tab[pos -1];
    }
    return tab[head + pos];
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