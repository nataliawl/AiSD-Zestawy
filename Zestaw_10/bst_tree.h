/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 08.12.25

Implementacja realizujaca BST TREE dla
zadania 10.1
-----------------------------------------------*/

#ifndef BST_TREE_H
#define BST_TREE_H

#include <iostream>
#include <cassert>

// Szablon dla węzła drzewa BST.
template <typename T>
struct BSTNode {
    T value;
    BSTNode *left, *right;
    //BSTNode *parent;   // używane w pewnych zastosowaniach
    // kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() { delete left; delete right; } // destruktor rekurencyjny

};

// Szablon dla binarnego drzewa poszukiwań.
template <typename T>
class BinarySearchTree {
    BSTNode<T> *root;

public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    ~BinarySearchTree() { delete root; }
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    void remove(const T& item); // usuwanie przez złączanie

    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T* iter_search(const T& item) const { // wg libavl
        for (auto node=root; node != nullptr; ) {
            if (item == node->value) {
                return &(node->value);
            } else if (item < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }
    T* find_min() const;
    T* find_max() const;
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void display() { display(root, 0); }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const; // zwraca węzeł
    BSTNode<T> * remove(BSTNode<T> *node); // zwraca nowy korzeń poddrzewa
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

template<typename T>
T* BinarySearchTree<T>::find_max() const {
    if (empty()) return nullptr;
    BSTNode<T> *node = root;
    while (true) {
        if (node->right == nullptr) return &(node->value);
        node = node->right;
    }
}

template<typename T>
T* BinarySearchTree<T>::find_min() const {
    if (empty()) return nullptr;
    BSTNode<T> *node = root;
    while (true) {
        if (node->left == nullptr) return &(node->value);
        node = node->left;
    }
}

template <typename T>
void BinarySearchTree<T>::inorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void BinarySearchTree<T>::preorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void BinarySearchTree<T>::postorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}


template <typename T>
BSTNode<T> * BinarySearchTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (item < node->value) {
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}

// Druga wersja display() z rysowaniem krawędzi drzewa (Maksymilian Brzozowski).
template <typename T>
void BinarySearchTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}

template <typename T>
void BinarySearchTree<T>::remove(const T& item) { // usuwanie przez złączanie
    // Najpierw znajdujemy węzeł i jego rodzica.
    BSTNode<T> *node = root;
    BSTNode<T> *prev = nullptr;
    while (node != nullptr) {
        if (node->value == item)
            break;
        prev = node;
        if (item < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    // Szukamy przyczyny przerwania pętli while.
    if (node != nullptr && node->value == item) {
        // node ma być usunięty.
        if (node == root) {
            root = remove(node);
        } else if (prev->left == node) {
            prev->left = remove(node);
        } else {
            prev->right = remove(node);
        }
    } else if (root != nullptr) {
        ; // klucza nie znaleziono
    } else { // root == nullptr
        ; // drzewo jest puste
    }
}

template <typename T>
BSTNode<T> * BinarySearchTree<T>::remove(BSTNode<T> *node) {
    // Mamy usunąć węzeł i zwrócić nowy korzeń poddrzewa.
    assert(node != nullptr);
    BSTNode<T> *new_root;
    if (node->right == nullptr) { // node nie ma prawego dziecka
        new_root = node->left;
    } else if (node->left == nullptr) { // node nie ma lewego dziecka
        new_root = node->right;
    } else { // obecne lewe i prawe dziecko
        new_root = node; // zapisujemy stary korzeń
        node = node->left; // idziemy w lewo
        while (node->right != nullptr) { // idziemy w prawo do końca
            node = node->right;
        }
        node->right = new_root->right; // prawe poddrzewo przełączone
        node = new_root; // węzeł do usunięcia
        new_root = node->left; // nowy korzeń
    }
    delete node;
    return new_root;
}

#endif //BST_TREE_H