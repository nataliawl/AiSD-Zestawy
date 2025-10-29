/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 29.10.25

Main() pokazuje dzialanie klasy SingleList oraz
testuje jej metody.
-----------------------------------------------*/
#include "singlelist.h"

int main(){
	//Sprawdzamy tworzenie listy i dodawanie elementow dzia³a
	std:: cout <<"Wyswietlam pierwsza liste\n";
	SingleList<int> test1;
	test1.push_front(1);
	test1.push_front(2);
	test1.push_back(3);
	test1.push_back(4);
	test1.push_back(5);
	test1.display();
	
	//Sprawdzamy  wyœwietlanie pierwszego i ostatniego elementu, oraz dlugosci listy
	std:: cout << "Pierwszy element listy:";
	std:: cout << test1.front() << "\n";
	std:: cout << "Ostatni element listy:";
	std:: cout << test1.back() << "\n";
	std:: cout << "Rozmiar listy wynosi: ";
	std:: cout << test1.size() << "\n";
	
	//Sprawdzamy index
	std :: cout << "\nIndeksy liczb na liscie zaczynaja sie od 1\n";
	std :: cout << "Indeks liczby 1 wynosi " << test1.index(1) << "\n";
	std :: cout << "Indeks liczby 4 wynosi " << test1.index(4) << "\n";
	std :: cout << "Indeks liczby 6 wynosi " << test1.index(6) << "\n";
	
	//Sprawdzamy usuwanie po indeksie
	std:: cout <<"Wyswietlam pierwsza liste\n";
	test1.erase(2);
	test1.display();
	
	test1.erase(10);
	
	std :: cout << "Indeks liczby 3 wynosi " << test1.index(3) << "\n";
	
	//Sprawdzamy dodawanie po indeksie
	std:: cout <<"\nWyswietlam pierwsza liste\n";
	test1.insert(0,0);
	test1.insert(test1.size(), 9);
	test1.insert(1, 15);
	test1.display();
	std:: cout << "Rozmiar listy wynosi: ";
	std:: cout << test1.size() << "\n";
	
	//Sprawdzamy pobieranie elementow;
	int test_node = test1.operator[](1);
	std:: cout << "Element dostarczony przez liste wynosi: " << test_node << "\n";
	test_node = test1.operator[](100);
	
	//Sprawdzamy kopiowanie
	SingleList<int> test2(test1);
	std:: cout <<"\nWyswietlam druga liste\n";
	test2.display();
	std:: cout << "Pierwszy element listy:";
	std:: cout << test2.front() << "\n";
	std:: cout << "Ostatni element listy:";
	std:: cout << test2.back() << "\n";
	std:: cout << "Rozmiar listy wynosi: ";
	std:: cout << test2.size() << "\n";
	
	std:: cout <<"\nWyswietlam trzecia liste\n";
	SingleList<int> test3;
	test3 = test1;
	test3.display();
	std:: cout << "Pierwszy element listy:";
	std:: cout << test3.front() << "\n";
	std:: cout << "Ostatni element listy:";
	std:: cout << test3.back() << "\n";
	std:: cout << "Rozmiar listy wynosi: ";
	std:: cout << test3.size() << "\n";
	
	//Sprawdzamy usuwanie elementow z listy oraz czyszcenie calej listy
	std:: cout <<"\nWyswietlam pierwsza liste\n";
	test1.pop_back();
	test1.pop_front();
	
	test1.display();
	std:: cout << "Rozmiar listy wynosi: ";
	std:: cout << test1.size() << "\n";
	
	std:: cout <<"Wyswietlam pierwsza liste\n";
	test1.clear();
	test1.display();
	
	std:: cout << "Rozmiar listy wynosi: ";
	std:: cout << test1.size() << "\n";
	test1.display();
	
	//Sprawdzamy funkcje empty 
	if(test1.empty()){
		std:: cout << "Lista jest pusta\n";
	}
	else std :: cout << "Lista nie jest pusta\n";

	
}
