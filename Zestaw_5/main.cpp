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
	test1.push_back(5);
	test1.push_back(6);
	std :: cout << "Wyswietlam liste pierwsza: \n";
	test1.display();
	std:: cout << "Pierwszy element: " << test1.front() << "\n";
	std:: cout << "Ostatni element: " << test1.back() << "\n";
	std:: cout << "Rozmiar listy: " << test1.size() << "\n";
	std :: cout << "Wyswietlam liste pierwsza w odwrotnej kolejnosci: \n";
	test1.display_reversed();
	
	//Sprawdzamy index - dziala
	std :: cout << "\nIndeksy liczb na liscie zaczynaja sie od 0\n";
	std :: cout << "Indeks liczby 1 wynosi " << test1.index(1) << "\n";
	std :: cout << "Indeks liczby 2 wynosi " << test1.index(2) << "\n";
	std :: cout << "Indeks liczby 10 wynosi " << test1.index(10) << "\n";
	
	//Sprawdzamy usuwanie po indeksie - dziala
	std:: cout <<"Wyswietlam pierwsza liste\n";
	test1.erase(2);
	test1.display();
	
	test1.erase(10);
	
	std :: cout << "Indeks liczby 3 wynosi " << test1.index(3) << "\n";
	
	//Sprawdzamy dodawanie po indeksie - poprawic!
	std:: cout <<"\nWyswietlam pierwsza liste\n";
	test1.insert(0,0);
	test1.insert(test1.size(), 9);
	test1.insert(1, 15);
	test1.display();
	std:: cout << "Rozmiar listy wynosi: ";
	std:: cout << test1.size() << "\n";
	
	//Sprawdzamy pobieranie elementow - dziala
	int test_node = test1.operator[](1);
	std:: cout << "Element dostarczony przez liste wynosi: " << test_node << "\n";
	test_node = test1.operator[](100);
	
	
	//Sprawdzamy usuwanie - dziala 
	std :: cout << "\nWyswietlam liste pierwsza: \n";
	test1.pop_front();
	test1.pop_back();
	test1.display();
	test1.display_reversed();
	
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
