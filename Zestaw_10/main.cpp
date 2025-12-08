/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 11.12.25
-----------------------------------------------*/
#include "bst_tree.h"

int main() {
    //Tworzymy drzewo o 9 dzieciach
    std::cout << "Wyswietlam piersze drzewo:" << std::endl;
    BinarySearchTree<int> tree_1;
    tree_1.insert(8);
    tree_1.insert(3);
    tree_1.insert(10);
    tree_1.insert(1);
    tree_1.insert(6);
    tree_1.insert(14);
    tree_1.insert(13);
    tree_1.insert(4);
    tree_1.insert(7);
    tree_1.display();
    const int *min_1 = tree_1.find_min();
    std::cout << "Minimalny element drzewa pierwszego: " << *min_1 << std::endl;
    const int *max_1 = tree_1.find_max();
    std::cout << "Maksymalny element drzewa pierwszego: " << *max_1 << std::endl;

    //Tworzymy drzewo o jednym elemencie
    std::cout << "Dla jednoelementowego drzewa:" << std::endl;
    BinarySearchTree<int> tree_2;
    tree_2.insert(1);
    const int *min_2 = tree_2.find_min();
    std::cout << "Minimalny element drzewa drugiego: " << *min_2 << std::endl;
    const int *max_2 = tree_2.find_max();
    std::cout << "Maksymalny element drzewa drugiego: " << *max_2 << std::endl;

    //Tworzymy puste drzewo
    std::cout << "Dla pustego drzewa:" << std::endl;
    BinarySearchTree<int> tree_3;
    const int *min_3 = tree_3.find_min();
    if (min_3 == nullptr) std::cout <<"Drzewo nie ma elementow"<< std::endl;
    const int *max_3 = tree_3.find_max();
    if (max_3 == nullptr) std::cout <<"Drzewo nie ma elementow"<< std::endl;

}