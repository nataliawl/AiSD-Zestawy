/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 18.12.25
-----------------------------------------------*/
#include  "avl_tree.h"

int main() {
    //Sprawdzamy dodawanie i wyswietlanie
    AVLTree<int> test_1;
    if (test_1.empty()) {
        std::cout << "Drzewo jest puste" << std::endl;
    }
    else std::cout << "Drzewo nie jest puste" << std::endl;

    test_1.insert(12);
    test_1.insert(8);
    test_1.insert(18);
    test_1.insert(5);
    test_1.insert(11);
    test_1.insert(17);
    test_1.insert(4);
    test_1.display();

    if (test_1.empty()) {
        std::cout << "Drzewo jest puste" << std::endl;
    }
    else std::cout << "Drzewo nie jest puste" << std::endl;

    //Sprawdzamy wyszukiwanie najmniejszego i najwiekszego elementu
    const int *min_1 = test_1.find_min();
    std::cout << "Minimalny element drzewa pierwszego: " << *min_1 << std::endl;
    const int *max_1 = test_1.find_max();
    std::cout << "Maksymalny element drzewa pierwszego: " << *max_1 << std::endl;
    const int root = test_1.top();
    std:: cout << "Wartosc korzenia:" << root << std::endl;

    //Sprawdzamy przeszukiwanie
    std:: cout << "Przechodzenie wszerz:" << std::endl;
    test_1.bfs();
    std::cout << std::endl;

    //Sprawdzamy ordery
    std:: cout << "Przechodzenie bezposrednie:" << std::endl;
    test_1.inorder();
    std::cout << std::endl;
    std:: cout << "Przechodzenie z opoznieniem:" << std::endl;
    test_1.postorder();
    std::cout << std::endl;
    std:: cout << "Przechodzenie z wyprzedzeniem:" << std::endl;
    test_1.preorder();
    std::cout << std::endl;

    //Sprawdzamy usuwanie elementow
    test_1.remove(12);
    test_1.remove(11);
    test_1.display();

    //Sprawdzamy clear
    test_1.clear();
    test_1.display();
}