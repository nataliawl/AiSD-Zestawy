/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 27.11.25
-----------------------------------------------*/
#include "queue.h"

int main() {
    //Sprawdzamy dodawanie i wyswietlamy
    MyQueue<int> test_1;
    std :: cout << "Wyswietlam kolejke pierwsza:\n";
    test_1.push(4);
    test_1.push(3);
    test_1.push(2);
    test_1.push(1);
    test_1.display();
    test_1.display_reversed();
    std::cout << "Ostatni dodany element: " << test_1.front() << std::endl;
    std::cout << "Pierwszy dodany element: " << test_1.back() << std::endl;
    std::cout << "Rozmiar kolejki: " << test_1.size() << std::endl;

    //Sprawdzamy kopiowanie
    std :: cout << "Wyswietlam druga kolejke:\n";
    MyQueue<int> test_2;
    test_2 = test_1;
    test_2.push(5);
    test_2.display();
    test_2.display_reversed();
    std::cout << "Ostatni dodany element: " << test_2.front() << std::endl;
    std::cout << "Pierwszy dodany element: " << test_2.back() << std::endl;
    std::cout << "Rozmiar kolejki: " << test_2.size() << std::endl;

    std :: cout << "Wyswietlam trzecia kolejke:\n";
    MyQueue<int> test_3(test_1);
    test_3.push(0);
    test_3.display();
    test_3.display_reversed();
    std::cout << "Ostatni dodany element: " << test_3.front() << std::endl;
    std::cout << "Pierwszy dodany element: " << test_3.back() << std::endl;
    std::cout << "Rozmiar kolejki: " << test_3.size() << std::endl;

    //Sprawdzamy czy nie jest puste
    if (test_1.empty()) std::cout << "Jest pusta!\n";
    else std:: cout << "Nie jest pusta!\n";

    //Sprawdzamy usuwanie
    std :: cout << "Wyswietlam kolejke pierwsza:\n";
    test_1.pop();
    test_1.pop();
    test_1.display();
    test_1.display_reversed();
    std::cout << "Ostatni dodany element: " << test_1.front() << std::endl;
    std::cout << "Pierwszy dodany element: " << test_1.back() << std::endl;
    std::cout << "Rozmiar kolejki: " << test_1.size() << std::endl;

    //Sprawdzamy czyszczenie
    std :: cout << "Wyswietlam kolejke pierwsza:\n";
    test_1.clear();
    test_1.display();

}