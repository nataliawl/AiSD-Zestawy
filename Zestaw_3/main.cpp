/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 22.10.25

Main() pokazuje dzialanie klasy ArrayList oraz
testuje jej metody.
-----------------------------------------------*/
#include "arraylist.h"

int main(){
	
	//Tworzymy obiekty klasy
	ArrayList<int> array1;
	array1.push_front(1);
	array1.push_front(11);
	array1.push_front(98);
	array1.push_back(13);
	array1.push_back(5);
	array1.push_back(0);
	array1.push_back(10);
	std :: cout <<"Wypisuje pierwsza liste:\n";
	array1.display();
		
	
	//Wypisuje dane o pierwszej tablicy
	std::cout << "Na liscie sa " << array1.size() << " elementy\n"; 
	std::cout << "Lista maksymalnie miesci " << array1.max_size() << " elementow\n";
	std:: cout << "Pierwszy element listy pierwszej: " << array1.front() << "\n";
	std:: cout << "Ostatni element listy pierwszej: " << array1.back() << "\n";
	
	//Sprawdzamy czy tablica sa puste czy pelne
	if(array1.empty() == true){
		std::cout << "Lista jest pusta!\n";
	}
	else std::cout << "Lista nie jest pusta!\n";
	
	if(array1.full() == true){
		
	}
	else std::cout << "Lista nie jest pelna! Pozostalo jesze: " << array1.max_size() - array1.size() << " miejsc\n";
	
	//Usuwamy ostatni i pierwszy element
	array1.pop_back();
	array1.pop_front();
	std :: cout <<"Wypisuje pierwsza liste po usunieciu dwoch elementow:\n";
	array1.display();
	
	//Odwarcamy kolejnosc listy
	array1.reverse();
	std :: cout <<"Wypisuje pierwsza liste po odwroceniu kolejnosci:\n";
	array1.display();
	
	//Sortujemy liste
	array1.sort();
	std :: cout <<"Wypisuje pierwsza liste po sortowaniu:\n";
	assert(array1.if_sorted());
	array1.display();
	
	//Kopiowanie obiektu
	ArrayList<int> array2(array1);
	std :: cout <<"Wypisuje druga liste:\n";
	array2.display();
	std :: cout <<"Wypisuje trzecia liste:\n";
	ArrayList<int> array3;
	array3 = array1;
	array3.display();
	
	//Przenosznie nowego obiektu bez kopiowania;
	ArrayList<int> array4(std::move(array2));
	std :: cout <<"Wypisuje czwarta liste liste:\n";
	array4.display();
	
	ArrayList<int> array5;
	array5 = std::move(array4);
	std :: cout <<"Wypisuje piata liste liste:\n";
	array5.display();

	return 0;
}
