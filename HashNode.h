#ifndef HASHNODE_H
#define HASHNODE_H

template <class K, class V> // Generic Pair.
class HashNode {
public:
    HashNode* next = nullptr;

    HashNode() {}

    HashNode(const K& key, const V& value, HashNode* next = nullptr) {
        this->key = new K(key);
        this->value = new V(value);
        this->next = next;
    }

    HashNode(const K& key) {
        this->key = new K(key);
    }

    HashNode(const HashNode& rhs) {
        *this = rhs;
    }

    ~HashNode() {
        delete key;
        delete value;
    }

    HashNode& operator = (const HashNode& rhs) {
        if(&rhs != this) {
            delete key;
            delete value;
            if(rhs.key != nullptr)
                key = new K(*rhs.key);
            if(rhs.value != nullptr)
                value = new V(*rhs.value);
            next = rhs.next;
        }
        return *this;
    }

    bool operator == (const HashNode& rhs) {
        return key == rhs.key && value == rhs.value;
    }

    K* getKey() {
        return key;
    }

    V* getValue() {
        return value;
    }
private:
    K* key = nullptr;
    V* value = nullptr;
};

#endif //HASHNODE_H
