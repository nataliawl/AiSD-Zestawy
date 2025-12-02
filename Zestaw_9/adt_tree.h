/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 03.12.25

Implementacja realizujaca ADT TREE dla
zadania 9.1
-----------------------------------------------*/
#ifndef ADT_TREE_H
#define ADT_TREE_H

#include <iostream>
#include <cstdlib>   // std::rand(), RAND_MAX, std::srand()
#include <ctime>
#include <queue>
#include <stack>
#include <cassert>

// Szablon dla węzła drzewa binarnego i drzewa BST.
template <typename T>
struct BSTNode {
    // the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    //BSTNode *parent;   // używane w pewnych zastosowaniach
    // kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() { delete left; delete right; } // destruktor rekurencyjny
    // UWAGA Jeżeli w BSTNode będzie domyślny destruktor postaci
    // ~BSTNode() = default; lub
    // ~BSTNode() {}
    // to wtedy destruktor drzewa i metoda clear() muszą zwolnić pamięć
    // wszystkich węzłów.
};
// Szablon dla przypadkowego drzewa binarnego.

template <typename T>
class RandomBinaryTree {
    BSTNode<T> *root;
    int numb_leaves;
public:
    RandomBinaryTree() : root(nullptr) , numb_leaves(0){} // konstruktor domyślny
    ~RandomBinaryTree() { delete root; } // trzeba wyczyścić (rekurencyjnie)
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    //void remove(const T& item); // na razie nie usuwamy elementów
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    int number_of_leaves() const {return numb_leaves;}
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void bfs(); // przejście poziomami (wszerz)
    void display() { display(root, 0); }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const;
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }

    //Funkcje do zadania 9.1 oraz wlasny insert
    void iter_calc_leaves();
    void rec_calc_leaves(BSTNode<T> *node = nullptr);
    void my_insert(const T& item);
};

template<typename T>
void RandomBinaryTree<T>::iter_calc_leaves() {
    numb_leaves = 0;
    if(empty()) return;
    //Dla samego korzenia
    if (root->left == nullptr && root->right == nullptr) {
        numb_leaves = 1;
        return;
    }

    std:: queue<BSTNode<T>*> check;
    check.push(root);
    while (!check.empty()) {
        BSTNode<T> * current = check.front();
        check.pop();

        if (current->left == nullptr && current->right == nullptr) {
            numb_leaves++;
        }

        if (current->left != nullptr) {
            check.push(current->left);
        }
        if (current->right != nullptr) {
            check.push(current->right);
        }
    }

}

template<typename T>
void RandomBinaryTree<T>::rec_calc_leaves(BSTNode<T> *node) {
    if (empty()) {
        numb_leaves = 0;
        return;
    }
    if (node == nullptr) {
        node = root;
        numb_leaves = 0;
    }

    if (node->left == nullptr && node->right == nullptr) {
        numb_leaves++;
        return;
    }
    if (node->left != nullptr) rec_calc_leaves(node->left);
    if (node->right != nullptr) rec_calc_leaves(node->right);
    
}
template <typename T>
void RandomBinaryTree<T>::my_insert(const T& item) {
    BSTNode<T>* newNode = new BSTNode<T>(item);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    std::queue<BSTNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        BSTNode<T>* current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = newNode;
            return;
        } else {
            q.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = newNode;
            return;
        } else {
            q.push(current->right);
        }
    }
}

// Wyświetlanie obróconego (counterclockwise) drzewa binarnego.
template <typename T>
void RandomBinaryTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << std::endl;
    display(node->left, level + 1);
}

template <typename T>
BSTNode<T> * RandomBinaryTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    if (std::rand() % 2) { // można lepiej
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}

template <typename T>
BSTNode<T> * RandomBinaryTree<T>::search(BSTNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    }
    T* ptr;
    ptr = search(node->left, item);
    if (ptr == nullptr) {
        ptr = search(node->right, item);
    }
    return ptr;
}

template <typename T>
void RandomBinaryTree<T>::bfs() {
    if (root == nullptr) return;
    std::queue<BSTNode<T>*> Q; // wskaźniki do wezłów
    BSTNode<T> *node = root;
    Q.push(node);
    while (!Q.empty()) {
        node = Q.front(); // podglądamy
        Q.pop();        // usuwamy z kolejki
        visit(node); // tu jest właściwe przetworzenie węzła
        if (node->left != nullptr)
            Q.push(node->left); // pierwsze wyjdzie lewe, potem prawe
        if (node->right != nullptr)
            Q.push(node->right);
    }
}

template <typename T>
void RandomBinaryTree<T>::inorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::preorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void RandomBinaryTree<T>::postorder(BSTNode<T> *node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}

template <typename T>
void RandomBinaryTree<T>::iter_preorder() {
    if (root == nullptr) return;
    std::stack<BSTNode<T>*> S; // wskaźniki do węzłów
    BSTNode<T> *node = root;
    S.push(node);
    while (!S.empty()) {
        node = S.top(); // podglądamy
        S.pop();        // usuwamy ze stosu
        visit(node); // tu jest właściwe przetworzenie węzła
        if (node->right != nullptr) // najpierw prawe poddrzewo!
            S.push(node->right);
        if (node->left != nullptr)
            S.push(node->left);
    }
}

#endif //ADT_TREE_H