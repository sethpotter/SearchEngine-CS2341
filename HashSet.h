#ifndef HASHSET_H
#define HASHSET_H

#include <iostream>

using namespace std;

template <class T>
class HashSet {
public:
    HashSet() {
        root = new T[capacity];
        occupied = new bool[capacity];

        for(int i = 0; i < capacity; i++) {
			root[i] = T();
            occupied[i] = false;
        }
    }

    ~HashSet() {
        delete[] root;
    }

    void insert(T &value) {
        int index = getIndex(value);
        if(index != -1) {
            return;
        }

        int hashVal = getHash(value);
        int count = 0;
        while(occupied[hashVal] && count < capacity) {
            hashVal++;
            hashVal %= capacity;
            count++;
        }

        if(count >= capacity) {
            reserve(capacity * 2);
            insert(value);
            return;
        }
        root[hashVal] = value;
        occupied[hashVal] = true;
    }

	void copy(const HashSet<T>& set) {
		reserve(set.capacity);
		for (int i = 0; i < set.capacity; i++) {
			root[i] = set.root[i];
			occupied[i] = set.occupied[i];
		}
	}

    void remove(T &value) {
        int index = getIndex(value);
        if(index != -1) {
            occupied[index] = false;
        }
    }

    void reserve(int amount) {
        if(amount <= capacity)
            return;
        T* oldRoot = root;
        bool* oldOcc = occupied;
        int oldCapacity = capacity;

        capacity = amount;
        root = new T[capacity];
        occupied = new bool[capacity];

        for(int i = 0; i < capacity; i++) {
			root[i] = T();
            occupied[i] = false;
        }
        for(int i = 0; i < oldCapacity; i++) {
            if(oldOcc[i]) {
                insert(oldRoot[i]);
            }
        }

        delete[] oldRoot;
        delete[] oldOcc;
    }

    bool contains(T &value) {
        return getIndex(value) != -1;
    }

    bool contains(T &value, int limit) {
        return getIndex(value, limit) != -1;
    }

    int getIndex(T &value) {
        return getIndex(value, capacity);
    }

    int getIndex(T &value, int limit) {
        int hashVal = getHash(value);
        int count = 0;
        while(count < limit) {
            if(occupied[hashVal] && root[hashVal] == value) {
                return hashVal;
            }
            count++;
            hashVal++;
            hashVal %= capacity;
        }
        return -1;
    }

    void printTable() {
        cout << "SET: ";
        for(int i = 0; i < capacity; i++) {
            if(occupied[i])
                cout << root[i] << ", ";
            else
                cout << "#, ";
        }
        cout << endl;
    }

    int getHash(T &value) {
		hash<T> t_hash;
		size_t hashVal = t_hash(value);
        return hashVal % capacity;
    }

    T* getRoot() {
        return root;
    }

private:
    size_t capacity = 8;
    T* root = nullptr;
    bool* occupied = nullptr;
};

#endif //HASHSET_H
