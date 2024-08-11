#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashNode.h"

template <class K, class V>
class HashMap {
public:
    HashMap() {
        root = new HashNode<K,V>*[capacity];
        for(int i = 0; i < capacity; i++) {
            root[i] = nullptr;
        }
    }

    ~HashMap() {
        for(int i = 0; i < capacity; i++) {
            if(root[i] == nullptr)
                continue;
            HashNode<K, V>* parent = root[i];
            HashNode<K, V>* next = parent->next;
            while (next != nullptr) {
                delete parent;
                parent = next;
                next = parent->next;
            }
            delete parent;
        }
        delete root;
    }

    void insert(K &key, V &value) {
        int hashVal = getHash(key);
        int count = 0;
        while(root[hashVal] != nullptr && *root[hashVal]->getKey() != key && count < capacity) {
            hashVal++;
            hashVal %= capacity;
            count++;
        }

        if(count >= capacity) {
            reserve(capacity * 2);
            insert(key, value);
            return;
        }

        HashNode<K,V>* temp = new HashNode<K,V>(key, value);
        if(root[hashVal] != nullptr) {
            HashNode<K,V>* currNode = root[hashVal];
            while(currNode->next != nullptr) {
                currNode = currNode->next;
            }
            currNode->next = temp;
        } else {
            root[hashVal] = temp;
        }
    }

    void remove(K &key) {
        int index = getIndex(key);
        if(index != -1) {
            HashNode<K,V>* parent = root[index];
            HashNode<K,V>* next = parent->next;
            while(next != nullptr) {
                delete parent;
                parent = next;
                next = parent->next;
            }
            delete parent;
            root[index] = nullptr;
        }
    }

    void reserve(int amount) {
        if(amount <= capacity)
            return;
        HashNode<K,V>** oldRoot = root;
        int oldCapacity = capacity;
        capacity = amount;
        root = new HashNode<K,V>*[capacity];
        for(int i = 0; i < capacity; i++) {
            root[i] = nullptr;
        }
        for(int i = 0; i < oldCapacity; i++) {
            if(oldRoot[i] != nullptr) {
                insert(*oldRoot[i]->getKey(), *oldRoot[i]->getValue());
                HashNode<K, V> *parent = oldRoot[i];
                HashNode<K, V> *next = parent->next;
                while (next != nullptr) {
                    delete parent;
                    parent = next;
                    next = parent->next;
                }
                delete parent;
            }
        }
        delete oldRoot;
    }

    V getValue(K &key) {
        return getValues(key)[0];
    }

    vector<V> getValues(K &key) {
        vector<V> values;
        int index = getIndex(key);
        if(index != -1) {
            HashNode<K,V>* currNode = root[index];
            while(currNode != nullptr) {
                values.push_back(*currNode->getValue());
                currNode = currNode->next;
            }
        }
        return values;
    }

    int getIndex(K &key) {
        int hashVal = getHash(key);
        int count = 0;
        while(count < capacity) {
            if(root[hashVal] != nullptr && *root[hashVal]->getKey() == key) {
                return hashVal;
            }
            count++;
            hashVal++;
            hashVal %= capacity;
        }
        return -1;
    }

    void printTable() {
        cout << "TABLE: ";
        for(int i = 0; i < capacity; i++) {
            if(root[i] != nullptr)
                cout << *root[i]->getKey() << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }

    int getHash(K &key) {
        size_t hash = std::hash<K>()(key);
        return hash % capacity;
    }
private:
    int capacity = 8;
    HashNode<K,V>** root = nullptr;
};

#endif //HASHMAP_H
