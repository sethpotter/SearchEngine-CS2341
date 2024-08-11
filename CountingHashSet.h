#ifndef COUNTINGHASHSET_H
#define COUNTINGHASHSET_H

#include <iostream>
#include <stdlib.h>

using namespace std;

template <class T>
class CountingHashSet {
public:
	CountingHashSet() {
		root = new T[capacity];
		occupied = new bool[capacity];
		instances = new int[capacity];

		for (int i = 0; i < capacity; i++) {
			root[i] = T();
			occupied[i] = false;
			instances[i] = 0;
		}
	}

	~CountingHashSet() {
		delete[] root;
	}

	friend ostream &operator << (ostream &os, const CountingHashSet &obj) {
	    os << "[";
	    for(int i = 0; i < obj.capacity; i++) {
	        if(obj.occupied[i])
                os << obj.root[i] << "|||" << obj.instances[i] << "|||";
	        else
	            os << "NULL" << "|||0|||";
	    }
	    os << "]";
	    return os;
	};

	friend istream &operator >> (istream &is, CountingHashSet &obj) {
        string s, delimiter = "|||";
        is >> s;
        s = s.substr(1, s.size() - 2);
        size_t pos = 0;
        string token;
        int count = 0, num = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            if(count % 2 == 1) {
                num = atoi(s.substr(0, pos).c_str());
                int i = (count - 1) / 2;
                obj.root[i] = token;
                obj.instances[i] = num;
                obj.occupied[i] = !(token == "NULL");
            }
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            count++;
        }
		return is;
	}

	void insert(T& value) {
		insert(value, 0);
	}

	void insert(T& value, int ints) {
		int index = getIndex(value);
		if (index != -1) {
			instances[index]++;
			return;
		}

		int hashVal = getHash(value);
		int count = 0;
		while (occupied[hashVal] && count < capacity) {
			hashVal++;
			hashVal %= capacity;
			count++;
		}

		if (count >= capacity) {
			reserve(capacity * 2);
			insert(value);
			return;
		}
		root[hashVal] = value;
		occupied[hashVal] = true;
		if (ints > 0) {
			instances[hashVal] = ints;
		}
	}

	void copy(const CountingHashSet<T>& set) {
		reserve(set.capacity);
		for (int i = 0; i < set.capacity; i++) {
			root[i] = set.root[i];
			occupied[i] = set.occupied[i];
			instances[i] = set.instances[i];
		}
	}

	void remove(T& value) {
		int index = getIndex(value);
		if (index != -1) {
			occupied[index] = false;
		}
	}

	void reserve(int amount) {
		if (amount <= capacity)
			return;
		T * oldRoot = root;
		bool* oldOcc = occupied;
		int* oldInst = instances;
		int oldCapacity = capacity;

		capacity = amount;
		root = new T[capacity];
		occupied = new bool[capacity];
		instances = new int[capacity];

		for (int i = 0; i < capacity; i++) {
			root[i] = T();
			occupied[i] = false;
			instances[i] = 0;
		}
		for (int i = 0; i < oldCapacity; i++) {
			if (oldOcc[i]) {
				insert(oldRoot[i], oldInst[i]);
			}
		}

		delete[] oldRoot;
		delete[] oldOcc;
		delete[] oldInst;
	}

	bool contains(T& value) {
		return getIndex(value) != -1;
	}

	bool contains(T& value, int limit) {
		return getIndex(value, limit) != -1;
	}

	int getIndex(T& value) {
		return getIndex(value, capacity);
	}

	int getIndex(T& value, int limit) {
		int hashVal = getHash(value);
		int count = 0;
		while (count < limit) {
			if (occupied[hashVal] && root[hashVal] == value) {
				return hashVal;
			}
			count++;
			hashVal++;
			hashVal %= capacity;
		}
		return -1;
	}

	vector<T> getValues() {
	    vector<T> values;
	    for(int i = 0; i < capacity; i++) {
	        if(occupied[i])
	            values.push_back(root[i]);
	    }
	    return values;
	}

	void printTable() {
		cout << "SET: ";
		for (int i = 0; i < capacity; i++) {
			if (occupied[i])
				cout << root[i] << " (" << instances[i] << "), ";
			else
				cout << "#, ";
		}
		cout << endl;
	}

	int getHash(T& value) {
		size_t hashVal = hash<T>()(value);
		return hashVal % capacity;
	}

	T* getRoot() {
		return root;
	}

private:
	size_t capacity = 8;
	T* root = nullptr;
	bool* occupied = nullptr;
	int* instances = nullptr;
};

#endif //HASHSET_H
