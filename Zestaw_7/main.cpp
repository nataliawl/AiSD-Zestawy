#include "adt_stack.h"

int main() {
//Sprawdzamy tworzenie stosu i dodawanie elementow
	std:: cout <<"Wyswietlam pierwszy stos\n";
	MyStack<int> test1;
	test1.push(5);
	test1.push(4);
	test1.push(3);
	test1.push(2);
	test1.push(1);
	test1.display();

	//Sprawdzamy  wywietlanie ostatniego dodanego elementu oraz rozmiaru stosu
	std:: cout << "Ostatni dodany element stosu:";
	std:: cout << test1.top() << "\n";
	std:: cout << "Rozmiar stosu wynosi: ";
	std:: cout << test1.size() << "\n";

	//Sprawdzamy kopiowanie
	MyStack<int> test2(test1);
	std:: cout <<"\nWyswietlam drugi stos\n";
	test2.pop();
	test2.push(0);
	test2.display();
	std:: cout << "Ostatni dodany element stosu:";
	std:: cout << test2.top() << "\n";
	std:: cout << "Rozmiar stosu wynosi: ";
	std:: cout << test2.size() << "\n";

	std:: cout <<"\nWyswietlam trzeci stos\n";
	MyStack<int> test3;
	test3 = test1;
	test3.pop();
	test3.pop();
	test3.push(10);
	test3.display();
	std:: cout << "Ostatni dodany element stosu:";
	std:: cout << test3.top() << "\n";
	std:: cout << "Rozmiar stosu wynosi: ";
	std:: cout << test3.size() << "\n";

	//Sprawdzamy usuwanie elementow ze stosu oraz czyszcenie calego stosu
	std:: cout <<"\nWyswietlam pierwszy stos\n";
	test1.pop();
	test1.display();

	std:: cout << "Rozmiar stosu wynosi: ";
	std:: cout << test1.size() << "\n";

	std:: cout <<"Wyswietlam pierwszy stos\n";
	test1.clear();
	test1.display();

	std:: cout << "Rozmiar stosu wynosi: ";
	std:: cout << test1.size() << "\n";
	test1.display();

	//Sprawdzamy funkcje empty
	if(test1.empty()){
		std:: cout << "Stos jest pusta\n";
	}
	else std :: cout << "Stos nie jest pusta\n";

	//Sprawdzam dzialanie funkcji dla pustych stosow
	MyStack<int> test4;
	MyStack<int> test5(test4);
	std:: cout <<"\nWyswietlam czwarty stos\n";
	test5.display();
	MyStack<int> test6;
	test6 = test4;
	std:: cout <<"\nWyswietlam piaty stos\n";
	test6.display();

}