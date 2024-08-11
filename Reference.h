#ifndef REFERENCE_H
#define REFERENCE_H

#include <string>
#include <vector>
#include <sstream>
#include "HashSet.h"
#include "CountingHashSet.h"

using namespace std;

template <class T>
class Reference {
public:
    Reference() {
        this->key = new string();
        this->values = new CountingHashSet<T>();
    }

	Reference(const string &key) {
		this->key = new string(key);
		this->values = new CountingHashSet<T>();
	}

	Reference(const string &key, const T &value) {
		this->key = new string(key);
		this->values = new CountingHashSet<T>();
		this->values->insert(value);
	}

	~Reference() {
		delete key;
		delete values;
	}

	Reference(const Reference &rhs) {
		*this = rhs;
	}

	Reference& operator = (const Reference &rhs) {
		if (&rhs != this) {
			delete key;
			delete values;
			key = new string(*rhs.key);
			values = new CountingHashSet<T>();
            (*values).copy(*rhs.values);
		}
		return *this;
	}

	bool operator == (const Reference& rhs) {
		*key == *rhs.key;
	}

	bool operator > (const Reference& rhs) {
		return *key > *rhs.key;
	}
	bool operator < (const Reference& rhs) {
		return *key < *rhs.key;
	}

    friend ostream& operator << (ostream &os, const Reference &obj) {
        os << "[" << *obj.key << *obj.values << "]";
        return os;
    }

    friend istream &operator >> (istream &is, Reference &obj) {
        string s;
        is >> s;
        s = s.substr(1, s.size() - 2);
        string key = s.substr(0, s.find('['));
        string countingHash = s.substr(s.find('['), s.find(']') - 1);
        stringstream buffer(countingHash);
        delete obj.key;
        delete obj.values;
        obj.key = new string(key);
        obj.values = new CountingHashSet<T>();
        buffer >> (*obj.values);
		return is;
    }

	void addValue(T& val) {
		values->insert(val);
	}

	CountingHashSet<T>* getValues() {
		return values;
	}

	int getIndex(T& val) {
        return values->getIndex(val);
    }
private:
    string* key = nullptr;
	CountingHashSet<T>* values = nullptr;
};

#endif //REFERENCE_H
