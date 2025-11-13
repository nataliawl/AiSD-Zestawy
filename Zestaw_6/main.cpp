/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 13.11.25

Main() pokazuje dzialanie klasy MyDeque oraz
testuje jej metody.
-----------------------------------------------*/
#include "adt_deque.h"

int main() {
    MyDeque<int> test_1;

    //Sprawdzamy dodawanie i wyswietlanie
    test_1.push_front(3);
    test_1.push_front(2);
    test_1.push_front(1);
    test_1.push_front(0);
    test_1.push_back(4);
    test_1.push_back(5);
    test_1.push_back(6);
    test_1.push_back(7);
    std:: cout << "Wyswietlam pierwsza liste:\n";
    test_1.display();

    //Sprawdzamy usuwanie i wyswietlanie
    test_1.pop_front();
    test_1.pop_back();
    std:: cout << "Wyswietlam pierwsza liste:\n";
    test_1.display();
    std:: cout << "Wyswietlam pierwsza liste w odwrotnej kolejnosci:\n";
    test_1.display_reversed();
    std:: cout << "Pierwszy element: " << test_1.front() <<"\n";
    std:: cout << "Ostatni element: " << test_1.back() << "\n";
    std:: cout << "Indeks pierwszego zajetej pozycji: " << test_1.get_head() << std::endl;
    std:: cout << "Indeks pierwszej wolnej pozycji: " << test_1.get_tail() << std::endl;
    std:: cout <<"Liczba elementow na liscie: " << test_1.size() << std::endl;
    std:: cout <<"Maksymalna ilos elementow na liscie: " << test_1.max_size() << std::endl;

    //Sprawdzamy kopiowanie:
    MyDeque<int> test_2(test_1);
    test_2.push_front(10);
    std:: cout << "\nWyswietlam druga liste:\n";
    test_2.display();
    std:: cout << "Wyswietlam druga liste w odwrotnej kolejnosci:\n";
    test_2.display_reversed();
    MyDeque<int> test_3 = test_1;
    test_3.push_back(8);
    std:: cout << "\nWyswietlam trzecia liste:\n";
    test_3.display();
    std:: cout << "Wyswietlam trzecia liste w odwrotnej kolejnosci:\n";
    test_3.display_reversed();

    std:: cout << "\nWracamy do listy pierwszej\n";
    //Sprawdzamy dzialanie na indeksach
    std:: cout << "Indeks liczby 3: " << test_1.index(3) << std::endl;
    std:: cout << "Indeks liczby 13: " << test_1.index(13) << std::endl;
    std:: cout << "Liczba o indeksie 10: " << test_1.operator[](10) << std::endl;
    std:: cout << "Liczba o indeksie 1: " << test_1.operator[](1) << std::endl;
    test_1.insert(2,10);
    std:: cout << "Liczba o indeksie 1: " << test_1.operator[](1) << std::endl;
    test_1.erase(1);
    std:: cout << "Liczba o indeksie 1: " << test_1.operator[](1) << std::endl;

    return 0;
}