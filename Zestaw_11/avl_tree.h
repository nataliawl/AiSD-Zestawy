/* ----------------------------------------------
Autorka: Natalia Wlodyka           Data: 18.12.25

Implementacja realizujaca AVL TREE dla
zadania 11.1
-----------------------------------------------*/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>

template <typename T>
struct AVLNode {
    T value;
    int balance;
    AVLNode *left, *right, *parent;
    // kostruktor domyślny
    AVLNode() : value(T()), balance(0),
        left(nullptr), right(nullptr), parent(nullptr) {}
    AVLNode(const T& item, AVLNode *p) : value(item), balance(0),
        left(nullptr), right(nullptr), parent(p) {}
    ~AVLNode() { delete left; delete right; } // destruktor
};
// Szablon dla drzewa AVL.
template <typename T>
class AVLTree {
private:
    AVLNode<T> *root;
    int height(AVLNode<T> *node);
    void rebalance(AVLNode<T> *node);
    AVLNode<T>* rotateLeft(AVLNode<T> *node);
    AVLNode<T>* rotateRight(AVLNode<T> *node);
    AVLNode<T>* rotateLeftThenRight(AVLNode<T> *node);
    AVLNode<T>* rotateRightThenLeft(AVLNode<T> *node);
    void setBalance(AVLNode<T> *node);
    void printBalance(AVLNode<T> *node);
public:
    AVLTree() : root(nullptr) {}
    virtual ~AVLTree() { delete root; } // trzeba wyczyścić
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    bool insert(const T& item);
    void remove(const T& item);
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T* search_iter(const T& item) const { // wg libavl
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

    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void bfs(); // przejście poziomami (wszerz)
    T* find_max() const;
    T* find_min() const;
    void display() { display(root, 0); } //dziala!
    virtual void visit(AVLNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }

    // Metody bezpośrednio odwołujące się do node.
    void display(AVLNode<T> *node, int level);
    AVLNode<T> * search(AVLNode<T> *node, const T& item) const;
    void preorder(AVLNode<T> *node);
    void inorder(AVLNode<T> *node);
    void postorder(AVLNode<T> *node);

};

template<typename T>
T* AVLTree<T>::find_max() const {
    if (empty()) return nullptr;
    AVLNode<T> *node = root;
    while (true) {
        if (node->right == nullptr) return &(node->value);
        node = node->right;
    }
}

template<typename T>
T* AVLTree<T>::find_min() const {
    if (empty()) return nullptr;
    AVLNode<T> *node = root;
    while (true) {
        if (node->left == nullptr) return &(node->value);
        node = node->left;
    }
}

template <typename T>
void AVLTree<T>::bfs() {
    if (root == nullptr) return;
    std::queue<AVLNode<T>*> Q; // wskaźniki do wezłów
    AVLNode<T> *node = root;
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
void AVLTree<T>::inorder(AVLNode<T> *node) {
    if (node == nullptr) return;
    inorder(node->left);
    visit(node);
    inorder(node->right);
}

template <typename T>
void AVLTree<T>::preorder(AVLNode<T> *node) {
    if (node == nullptr) return;
    visit(node);
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void AVLTree<T>::postorder(AVLNode<T> *node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    visit(node);
}


template <typename T>
AVLNode<T> * AVLTree<T>::search(AVLNode<T> *node, const T& item) const {
    if (node == nullptr || node->value == item) {
        return node;
    } else if (item < node->value) {
        return search(node->left, item);
    } else {
        return search(node->right, item);
    }
}

template <typename T>
void AVLTree<T>::display(AVLNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << "(" << node->balance << ")" << std::endl;
    display(node->left, level + 1);
}

template <class T>
void AVLTree<T>::rebalance(AVLNode<T> *node) {
    setBalance(node);

    if (node->balance == -2) {
        if (height(node->left->left) >= height(node->left->right))
            node = rotateRight(node);
        else
            node = rotateLeftThenRight(node);
    }
    else if (node->balance == 2) {
        if (height(node->right->right) >= height(node->right->left))
            node = rotateLeft(node);
        else
            node = rotateRightThenLeft(node);
    }

    if (node->parent != NULL) {
        rebalance(node->parent);
    }
    else {
        root = node;
    }
}

template <class T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T> *node) {
    AVLNode<T> *b = node->right;
    b->parent = node->parent;
    node->right = b->left;

    if (node->right != NULL)
        node->right->parent = node;

    b->left = node;
    node->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == node) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(node);
    setBalance(b);
    return b;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T> *node) {
    AVLNode<T> *b = node->left;
    b->parent = node->parent;
    node->left = b->right;

    if (node->left != NULL)
        node->left->parent = node;

    b->right = node;
    node->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == node) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(node);
    setBalance(b);
    return b;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotateLeftThenRight(AVLNode<T> *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

template <class T>
AVLNode<T>* AVLTree<T>::rotateRightThenLeft(AVLNode<T> *node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

template <class T>
bool AVLTree<T>::insert(const T& item) {
    if (root == nullptr) {
        root = new AVLNode<T>(item, NULL);
    }
    else {
        AVLNode<T> *n = root;

        while (true) {
            if (n->value == item)
                return false;

            AVLNode<T> *parent = n;

            bool goLeft = n->value > item;
            n = goLeft ? n->left : n->right;

            if (n == nullptr) {
                if (goLeft) {
                    parent->left = new AVLNode<T>(item, parent);
                }
                else {
                    parent->right = new AVLNode<T>(item, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}

template <class T>
int AVLTree<T>::height(AVLNode<T> *node) {
    if (node == nullptr)
        return -1;
    return 1 + std::max(height(node->left), height(node->right));
}

template <class T>
void AVLTree<T>::setBalance(AVLNode<T> *node) {
    node->balance = height(node->right) - height(node->left);
}

template <class T>
void AVLTree<T>::printBalance(AVLNode<T> *node) {
    if (node != nullptr) {
        printBalance(node->left);
        std::cout << node->balance << " ";
        printBalance(node->right);
    }
}

template<typename T>
void AVLTree<T>::remove(const T &item) {
    if (root == nullptr)
        return;

    AVLNode<T>
        *n       = root,
        *parent  = root,
        *delNode = nullptr,
        *child   = root;

    while (child != nullptr) {
        parent = n;
        n = child;
        child = item >= n->value ? n->right : n->left;
        if (item == n->value)
            delNode = n;
    }

    if (delNode != nullptr) {
        delNode->value = n->value;

        child = n->left != NULL ? n->left : n->right;

        if (root->value == 0) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}

#endif //AVL_TREE_H