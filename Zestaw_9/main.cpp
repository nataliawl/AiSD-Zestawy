/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 03.12.25
-----------------------------------------------*/
#include "adt_tree.h"

int main() {
    //Tworzymy drzewo o 7 dzieciach
    std::cout << "Wyswietlam piersze drzewo:" << std::endl;
    RandomBinaryTree<int> tree_first;
    tree_first.my_insert(1);
    tree_first.my_insert(2);
    tree_first.my_insert(3);
    tree_first.my_insert(4);
    tree_first.my_insert(5);
    tree_first.my_insert(6);
    tree_first.my_insert(7);
    tree_first.my_insert(8);
    tree_first.my_insert(9);
    tree_first.my_insert(10);
    tree_first.my_insert(11);
    tree_first.my_insert(12);
    tree_first.my_insert(13);
    tree_first.my_insert(14);
    assert(!tree_first.empty());
    tree_first.display();
    tree_first.rec_calc_leaves();
    std :: cout << "Liczba dzieci: " << tree_first.number_of_leaves() << std :: endl;
    tree_first.iter_calc_leaves();
    std :: cout << "Liczba dzieci: " << tree_first.number_of_leaves() << std :: endl;

    //Drzewo skladajace sie tylko z korzenia
    std::cout << "Wyswietlam drugie drzewo:" << std::endl;
    RandomBinaryTree<int> tree_second;
    tree_second.my_insert(1);
    assert(!tree_first.empty());
    tree_second.display();
    tree_second.rec_calc_leaves();
    std :: cout << "Liczba dzieci: " << tree_second.number_of_leaves() << std :: endl;
    tree_second.iter_calc_leaves();
    std :: cout << "Liczba dzieci: " << tree_second.number_of_leaves() << std :: endl;

    //Drzewo puste
    RandomBinaryTree<int> tree_third;
    tree_third.rec_calc_leaves();
    std :: cout << "Liczba dzieci trzeciego drzewa: " << tree_third.number_of_leaves() << std :: endl;
    tree_third.iter_calc_leaves();
    std :: cout << "Liczba dzieci trzeciego drzewa: " << tree_third.number_of_leaves() << std :: endl;
}