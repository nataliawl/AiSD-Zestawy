/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 29.10.25

Main() pokazuje dzialanie klasy Poly oraz
testuje jej metody.

-----------------------------------------------*/
#include "polynomial.h"

int main(){
	//Sprawdzamy dodawanie elementu oraz wyswietlanie
	Poly<int> test1;
	test1.add_term(5, 1); //Dodawanie pierwszego elementu dziala
	test1.add_term(1, 1); //Dodawanie do istniejacego elementu 
	test1.add_term(2, 3); //Na koniec 
	test1.add_term(5, 2); //Dodawanie po srodku
	test1.add_term(10, 4);
	std:: cout << "Wyswietlam pierwszy wielomian:\n ";
	test1.display();
	
	//Sprawdzamy wyswietlanie informacji o wielomianach
	std:: cout << "Stopien wielomianu: " << test1.get_degree() << "\n";
	std:: cout << "Wartosc przy potendze 1: " << test1.operator[](1) << "\n";
	std:: cout << "Wartosc przy potendze 10: " << test1.operator[](10) << "\n";
	std:: cout << "Wartosc przy potendze 1: " << test1.operator[](1) << "\n";
	
	//Sprawdzamy kopiowanie
	Poly<int> test2;
	test2.add_term(10, 1); 
	test2.add_term(10, 5); 
	test2.add_term(10, 3); 
	test2.add_term(10, 0);
	test2.add_term(10, 4);
	
	Poly<int> test3(test2);
	Poly<int> test4;
	test4 = test3;
	
	std:: cout << "Wyswietlam drugi wielomian:\n ";
	test2.display();
	std:: cout << "Wyswietlam trzeci wielomian:\n ";
	test3.display();
	std:: cout << "Wyswietlam czwarty wielomian:\n ";
	test4.display();
	
	//Sprawdzamy porownywanie
	std:: cout << "Wielomiany test1 i test 2 sa: \n";
	if(test1 == test2){
		std:: cout << "Rowne\n";
	}
	else std:: cout << "Nierowne\n";
	
	std:: cout << "Wielomiany test3 i test 4 sa: \n";
	if(test3 != test4){
		std:: cout << "Nierowne\n";
	}
	else std:: cout << "Rowne\n";
	
	//Sprawdzamy dzialania na wielomianach
	std:: cout << "Wyswietlam wynik dodawania:\n ";
	test1 + test2;
	test1.display();
	std:: cout << "Wyswietlam wynik odejmowania:\n ";
	test1 - test2;
	test1.display();
	std:: cout << "Wyœwietlam wynik mnozenia:\n";
	Poly<int> test6;
	Poly<int> test7;
	test6.add_term(2, 1); //Dodawanie pierwszego elementu dziala
	test6.add_term(1, 0); //Dodawanie do istniejacego elementu 
	test7.add_term(1, 2); //Na koniec 
	test7.add_term(-3, 1); //Dodawanie po srodku
	test7.add_term(4, 0);
	test6 * test7;
	test6.display();
	
	//Sprawdzamy hornera
	Poly<int> test5;
	test5.add_term(1, 3); 
	test5.add_term(-4, 2);
	test5.add_term(3, 1); 
	test5.add_term(-5, 0); 
	std:: cout << "Wyœwietlam wielomian 5:\n";
	test5.display();
	std:: cout << "Stopien wielomianu: " << test5.get_degree() << "\n";
	std:: cout << "Wyœwietlam wynik dzielenia wielomianu przez 2:\n";
	test5.horner(2);
	test5.display();
	
	//Sprawdzamy czyszczenie:
	std:: cout << "Wyswietlam pierwszy wielomian:\n ";
	test1.clear();
	test1.display();

}
