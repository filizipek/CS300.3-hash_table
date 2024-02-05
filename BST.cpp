#include "BST.h"
#include <iostream>
using namespace std;

//Most of the functions are retrieved from the lecture slides and adapted for this case

template <class Key, class Value>
BST<Key, Value>::BST() : root(nullptr), ITEM_NOT_FOUND(nullptr)
{
}

template <class Key, class Value>
BST<Key, Value>::BST(const BST &rhs) : root(nullptr), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
    *this = rhs;
}

template <class Key, class Value>
BST<Key, Value>::~BST()
{
    makeEmpty();
}

template <class Key, class Value>
const Value &BST<Key, Value>::findMin() const
{
    return elementAt(findMin(root));
}

template <class Key, class Value>
const Value &BST<Key, Value>::findMax() const
{
    return elementAt(findMax(root));
}


template <class Key, class Value>
WordItem<Key, Value>* BST<Key, Value>::findVal(const Key &x) const
{
    WordItem<Key, Value>* result = find(x, root);
    return elementAt(result);
}


template <class Key, class Value>
bool BST<Key, Value>::isEmpty() const
{
    return root == nullptr;
}

//For debugging the AVLTree
template <class Key, class Value>
void BST<Key, Value>::printTree() const
{
    if (isEmpty())
        cout << "Empty tree" << endl;
    else
        printTree(root);
}

template <class Key, class Value>
void BST<Key, Value>::makeEmpty()
{
    makeEmpty(root);
}

//Insert function (public)
template <class Key, class Value>
void BST<Key, Value>::insert(const Key &key, const Value &value)
{
    insert(key, value, root);
}

template <class Key, class Value>
void BST<Key, Value>::remove(const Key &key)
{
    remove(key, root);
}

template <class Key, class Value>
const BST<Key, Value> &BST<Key, Value>::operator=(const BST &rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}


template <class Key, class Value>
WordItem<Key, Value>* BST<Key, Value>::elementAt(WordItem<Key, Value>* t) const
{
    static WordItem<Key, Value>* ITEM_NOT_FOUND = nullptr;
    if (t == nullptr)
        return ITEM_NOT_FOUND;
    return t;
}




template <class Key, class Value>
void BST<Key, Value>::insert(const Key &key, const Value &value, WordItem<Key, Value> *&t)
{
    if (t == nullptr)
    {
        t = new WordItem<Key, Value>(key, value, nullptr, nullptr);
    }
    else if (key < t->key)
    {
        // Key should be inserted to the left tree
        insert(key, value, t->left);

    }
    else if (t->key < key)
    { // Otherwise Key is inserted to the right subtree
        insert(key, value, t->right);
    }
}

//Insert function (private)
template <class Key, class Value>
void BST<Key, Value>::remove(const Key &key, WordItem<Key, Value> *&t)
{
    if (t == nullptr)
        return; // Key not found; do nothing
    if (key < t->key)
        remove(key, t->left);
    else if (t->key < key)
        remove(key, t->right);
    else if (t->left != nullptr && t->right != nullptr) // Two children
    {
        t->key = findMin(t->right)->key;
        t->value = findMin(t->right)->value;
        remove(t->key, t->right);
    }
    else // one or no children
    {
        WordItem<Key, Value> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }

    if (t != nullptr)
        t->height = max(height(t->left), height(t->right)) + 1;
}


template <class Key, class Value>
void BST<Key, Value>::makeEmpty(WordItem<Key, Value> *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <class Key, class Value>
void BST<Key, Value>::printTree(WordItem<Key, Value> *t) const
{
    if (t != nullptr)
    {
        printTree(t->left);
        std::cout << "(" << t->key << ", " << t->value << ") ";
        printTree(t->right);
    }
}

template <class Key, class Value>
WordItem<Key, Value> *BST<Key, Value>::clone(WordItem<Key, Value> *t) const
{
    if (t == nullptr)
        return nullptr;
    return new WordItem<Key, Value>(t->key, t->value, clone(t->left), clone(t->right), t->height);
}



template <class Key, class Value>
WordItem<Key, Value>* BST<Key, Value>::findMin(WordItem<Key, Value>* t) const {
    if (t == nullptr)
        return nullptr;

    while (t->left != nullptr)
        t = t->left;

    return t;
}

template <class Key, class Value>
WordItem<Key, Value>* BST<Key, Value>::findMax(WordItem<Key, Value>* t) const {
    if (t == nullptr)
        return nullptr;

    while (t->right != nullptr)
        t = t->right;

    return t;
}



template <class Key, class Value>
WordItem<Key, Value>* BST<Key, Value>::find(const Key &x, WordItem<Key, Value> *t) const {
    while (t != nullptr) {
        if (x < t->key)
            t = t->left;
        else if (t->key < x)
            t = t->right;
        else
            return t; // Found
        // If not found, move to the appropriate subtree
    }
    return nullptr; // Not found
}




