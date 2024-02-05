#include "HashClass.h"
#include <functional>
#include <iostream>
using namespace std;

//Most of the functions are retrieved from lecture slides.

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime( int n )
{
    if ( n == 2 || n == 3 )
        return true;

    if ( n == 1 || n % 2 == 0 )
        return false;

    for ( int i = 3; i * i <= n; i += 2 )
        if ( n % i == 0 )
            return false;

    return true;
}

/**
    * Internal method to return a prime number
   * at least as large as n.  Assumes n > 0.
    */
int nextPrime( int n )
{
    if ( n % 2 == 0 )
        n++;

    for ( ; ! isPrime( n ); n += 2 )
        ;

    return n;
}

// HashClass.cpp

template <class Key, class Value>
void HashTable<Key, Value>::makeEmpty()
{
    for (auto &entry : array)
    {
        entry.info = HashTable::EntryType::EMPTY;  // Update the scope
    }
    currentSize = 0;
}

template <class Key, class Value>
HashTable<Key, Value>::HashTable(const Value &notFound, int size)
        : ITEM_NOT_FOUND(notFound), currentSize(0), array(nextPrime(size))
{
    makeEmpty();
}

template <class Key, class Value>
void HashTable<Key, Value>::insert(const Key &key, const Value &value)
{
    // Insert key-value pair as active
    int currentPos = findPos(key);
    if (isActive(currentPos))
        return;
    array[currentPos] = HashTable<Key, Value>::HashEntry(key, value, HashTable<Key, Value>::EntryType::ACTIVE);

    // Enlarge the hash table if necessary
    if (double(++currentSize) / double(array.size()) >= 0.8)
        rehash();
}


template <class Key, class Value>
const Value &HashTable<Key, Value>::find(const Key &key) const
{
    int currentPos = findPos(key);
    if (isActive(currentPos))
        return array[currentPos].value;

    return ITEM_NOT_FOUND;
}

template <class Key, class Value>
void HashTable<Key, Value>::remove(const Key &key)
{
    int currentPos = findPos(key);
    if (isActive(currentPos))
        array[currentPos].info = HashEntry::DELETED;
}

template <class Key, class Value>
bool HashTable<Key, Value>::isActive(int currentPos) const
{
    return array[currentPos].info == HashTable::EntryType::ACTIVE;
}

template <class Key, class Value>
int HashTable<Key, Value>::findPos(const Key &key) const
{
    int collisionNum = 0;
    int currentPos = std::hash<Key>{}(key) % array.size();

    while (array[currentPos].info != HashTable::EntryType::EMPTY &&
           array[currentPos].key != key)
    {
        collisionNum++;
        currentPos += collisionNum * collisionNum;
        currentPos = currentPos % array.size();
    }
    return currentPos;
}

template <class Key, class Value>
void HashTable<Key, Value>::rehash()
{
    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize(nextPrime(2 * oldArray.size()));
    for (int j = 0; j < array.size(); j++)
        array[j].info = HashTable::EntryType::EMPTY;

    // Print rehashing information
    cout << "rehashed..." << endl;
    cout << "previous table size: " << oldArray.size()
         << ", new table size: " << array.size()
         << ", current unique word count: " << currentSize
         << ", current load factor: " << static_cast<double>(currentSize) / array.size() << endl;


    // Copy table over
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == HashTable::EntryType::ACTIVE)
            insert(oldArray[i].key, oldArray[i].value);
}
