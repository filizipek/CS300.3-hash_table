#ifndef BST_H
#define BST_H
#include <string>

template <class Key, class Value>
class BST;

//Used as an BST Node in this case
template <class Key, class Value>
struct WordItem
{
    Key key;
    Value value;
    WordItem *left;
    WordItem *right;
    int height;

    //WordItem Constructor
    WordItem(const Key &theKey, const Value &theValue,
             WordItem *lt, WordItem *rt, int h = 0)
            : key(theKey), value(theValue), left(lt), right(rt), height(h) {}

    friend class BST<Key, Value>;
};

template <class Key, class Value>
class BST
{
public:
    BST();
    BST(const BST &rhs);
    ~BST();

    const Value &findMin() const;
    const Value &findMax() const;
    WordItem<Key, Value>* findVal(const Key &x) const;
    bool isEmpty() const;
    void printTree() const;

    void makeEmpty();
    void insert(const Key &key, const Value &value);
    void remove(const Key &key);

    const BST &operator=(const BST &rhs);

private:
    WordItem<Key, Value> *root;
    const WordItem<Key, Value> * ITEM_NOT_FOUND;
    //WordItem<Key, Value>* &elementAt(WordItem<Key, Value> *t) const;
    WordItem<Key, Value>* elementAt(WordItem<Key, Value>* t) const;


    void insert(const Key &key, const Value &value, WordItem<Key, Value> *&t);
    void remove(const Key &key, WordItem<Key, Value> *&t);

    WordItem<Key, Value> *findMin(WordItem<Key, Value> *t) const;
    WordItem<Key, Value> *findMax(WordItem<Key, Value> *t) const;
    WordItem<Key, Value> *find(const Key &x, WordItem<Key, Value> *t) const;

    void makeEmpty(WordItem<Key, Value> *&t);
    void printTree(WordItem<Key, Value> *t) const;
    WordItem<Key, Value> *clone(WordItem<Key, Value> *t) const;

};

#include "BST.cpp"
#endif // BST_H
