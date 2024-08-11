#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <sstream>

using namespace std;

template <class T>
class TreeNode {
public:
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
	int height = 1;

    TreeNode() {}

    TreeNode(const T& value, TreeNode<T>& left, TreeNode<T>& right) : TreeNode(value, &left, &right) {}
    TreeNode(T* value, TreeNode<T>& left, TreeNode<T>& right) : TreeNode(value, &left, &right) {}

    TreeNode(const T& value, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr) {
        this->value = new T(value);
        this->left = left;
        this->right = right;
    }

    TreeNode(T* value, TreeNode<T>* left = nullptr, TreeNode<T>* right = nullptr) {
        this->value = value;
        this->left = left;
        this->right = right;
    }

    TreeNode(const TreeNode<T>& rhs) {
        *this = rhs;
    }

    ~TreeNode() {
        delete value;
    }

    TreeNode& operator = (const TreeNode& rhs) {
        if(&rhs != this) {
            delete value;
            value = new T(*rhs.value);
            left = rhs.left;
            right = rhs.right;
        }
        return *this;
    }

    bool operator > (const TreeNode& rhs) {
        return (rhs.value != nullptr) ? value > rhs.value : false;
    }

    bool operator < (const TreeNode& rhs) {
        return (rhs.value != nullptr) ? value < rhs.value : false;
    }

    bool operator == (const TreeNode& rhs) {
        return value == rhs.value;
    }

    friend ostream &operator << (ostream &os, const TreeNode &obj) {
        os << *obj.value;
        return os;
    }

    friend istream &operator >> (istream &is, TreeNode &obj) {
        string str;
        is >> str;
        stringstream buffer(str);
        delete obj.value;
        obj.value = new T();
        buffer >> (*obj.value);
		return is;
    }

    T* getValue() {
        return value;
    }
private:
    T* value = nullptr;
};

#endif //TREENODE_H
