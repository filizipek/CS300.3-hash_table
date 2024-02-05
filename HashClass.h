#ifndef HOMEWORKS_HASHCLASS_H
#define HOMEWORKS_HASHCLASS_H

#include <iostream>
#include <vector>
using namespace std;

template <class Key, class Value>
class HashTable
{
public:
    explicit HashTable(const Value &notFound, int size = 101);
    HashTable(const HashTable &rhs)
            : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
              array(rhs.array), currentSize(rhs.currentSize) {}

    const Value &find(const Key &x) const;

    void makeEmpty();
    void insert(const Key &key, const Value &value);
    void remove(const Key &x);

    const HashTable &operator=(const HashTable &rhs);

    const Value& getItemNotFound() const {
        return ITEM_NOT_FOUND;
    }
    int getCurrSize() const {
        return currentSize;
    }

    int getArraySize() const {
        return array.size();
    }

private:

    enum EntryType { ACTIVE, EMPTY, DELETED };

    struct HashEntry
    {
        Key key;
        Value value;
        EntryType info;

        HashEntry(const Key &k = Key(), const Value &v = Value(),
                  EntryType i = EMPTY)
                : key(k), value(v), info(i) {}
    };

    vector<HashEntry> array;
    int currentSize;

    const Value ITEM_NOT_FOUND;

    bool isActive(int currentPos) const;
    int findPos(const Key &key) const;
    void rehash();
};

#include "HashClass.cpp"
#endif // HOMEWORKS_HASHCLASS_H
