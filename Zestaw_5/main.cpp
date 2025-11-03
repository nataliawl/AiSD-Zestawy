/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 29.10.25

Main() pokazuje dzialanie klasy SingleList oraz
testuje jej metody.
-----------------------------------------------*/
#include "doublelist.h"
int main(){
	
	//Sprawdzamy dodawanie - dziala
	DoubleList<int> test1;
	test1.push_front(2);
	test1.push_front(1);
	test1.push_back(3);
	test1.push_back(4);
	std :: cout << "Wyswietlam liste pierwsza: \n";
	test1.display();
	std:: cout << "Pierwszy element: " << test1.front() << "\n";
	std:: cout << "Ostatni element: " << test1.back() << "\n";
	std:: cout << "Rozmiar listy: " << test1.size() << "\n";
	std :: cout << "Wyswietlam liste pierwsza w odwrotnej kolejnosci: \n";
	test1.display_reversed();
	
	//Sprawdzamy usuwanie - dziala
	std :: cout << "\nWyswietlam liste pierwsza w odwrotnej kolejnosci: \n";
	test1.pop_front();
	test1.pop_back();
	test1.display();
	
	//Sprawdzamy kopiowanie - dziala!
	DoubleList<int> test2(test1);
	std :: cout << "\nWyswietlam liste druga: \n";
	test2.push_front(0);
	test2.display();
	test2.display_reversed();
	std:: cout << "Pierwszy element: " << test2.front() << "\n";
	std:: cout << "Ostatni element: " << test2.back() << "\n";
	std:: cout << "Rozmiar listy: " << test2.size() << "\n";
	
	std :: cout << "\nWyswietlam liste trzecia: \n";
	DoubleList<int> test3;
	test3 = test1;
	test3.push_front(10);
	test3.display();
	test3.display_reversed();
	std:: cout << "Pierwszy element: " << test3.front() << "\n";
	std:: cout << "Ostatni element: " << test3.back() << "\n";
	std:: cout << "Rozmiar listy: " << test3.size() << "\n";
	
	//Sprawdzamy usuwanie listy - nie dziala!
	test3.clear();
	std :: cout << "\nWyswietlam liste trzecia: \n";
	test3.display();
	test3.display_reversed();
	std:: cout << "Rozmiar listy: " << test3.size() << "\n";
	
}
