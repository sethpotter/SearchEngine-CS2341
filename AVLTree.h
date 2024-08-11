#ifndef AVLTREE_H
#define AVLTREE_H

#include "TreeNode.h"
#include <stdexcept>
#include <algorithm>
#include <fstream>

using namespace std;

template <class T>
class AVLTree {
public:
    AVLTree() {}

    ~AVLTree() {
        remove(root);
    }

    void print() {
        cout << "[AVLTree ";
        print(root);
        cout << "]" << endl;
    }

    int size() {
        return size(root, 0) - 1;
    }

    TreeNode<T>* insert(T& value) {
        root = insert(root, value);
		return root;
    }

    TreeNode<T>* insert(T* value) {
        root = insert(root, *value);
		return root;
    }

    /*TreeNode<T>* insert(const TreeNode<T>& node, T& value) {
        root = insert(&node, value);
		return root;
    }*/

    TreeNode<T>* insert(TreeNode<T>* node, T& value) {
        if(node == nullptr) {
            TreeNode<T>* temp = new TreeNode<T>(value);
            if(root == nullptr) {
                root = temp;
                return root;
            } else {
                return temp;
            }
        }

        if(value < *node->getValue()) {
            node->left = insert(node->left, value);
        } else if(value > *node->getValue()) {
            node->right = insert(node->right, value);
        } else {
            return node;
        }

		node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int bal = getBalance(node);

        if(bal > 1 && value < *node->left->getValue()) { // LEFT LEFT
            return rotateRight(node);
        }
        if(bal < -1 && value > *node->right->getValue()) { // RIGHT RIGHT If right heavy, and insert value > right vlaue
            return rotateLeft(node);
        }
        if(bal > 1 && value > *node->left->getValue()) { // LEFT RIGHT
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if(bal < -1 && value < *node->right->getValue()) { // RIGHT LEFT
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    /*
     *       C                       A
     *      / \          (C)       /   \
     *     1   A        Left      C     B
     *        / \     Rotation   / \   / \
     *       2   B       ->     1   2 3   4
     *          / \
     *         3   4
     */
    TreeNode<T>* rotateLeft(TreeNode<T>* node) {
        TreeNode<T>* a = node->right;
        TreeNode<T>* val2 = a->left;

        a->left = node;
        node->right = val2;
		
		node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
		a->height = max(getHeight(a->left), getHeight(a->right)) + 1;

        return a;
    }

    /*
     *         C                    A
     *        / \      (C)        /   \
     *       A   1    Right      B     C
     *      / \      Rotation   / \   / \
     *     B   2        ->     4   3 2   1
     *    / \
     *   4   3
     */
    TreeNode<T>* rotateRight(TreeNode<T>* node) {
        TreeNode<T>* a = node->left;
        TreeNode<T>* val2 = a->right;

        a->right = node;
        node->left = val2;

		node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
		a->height = max(getHeight(a->left), getHeight(a->right)) + 1;

        return a;
    }

	int getBalance(TreeNode<T>* node) {
		if (node == nullptr)
			return 0;
		return getHeight(node->left) - getHeight(node->right);
	}

	int getHeight(TreeNode<T>* node) {
		if(node == nullptr)
			return 0;
		return node->height;
	}

    TreeNode<T>* getNode(T& value) {
        return getNode(root, value);
    }

    bool isEmpty() {
        return (root == nullptr);
    }

    TreeNode<T>* getRoot() {
        return root;
    }

    void saveToFile(string path) {
        ofstream fileOut(path);
        if(fileOut.is_open()) {
            saveToFile(root, fileOut);
            fileOut.close();
        }
    }

    void saveToFile(TreeNode<T>* node, ostream &out) {
        if(node == nullptr) {
            out << "#" << " ";
        } else {
            out << *node << " ";
            saveToFile(node->left, out);
            saveToFile(node->right, out);
        }
    }

    void loadFromFile(string path) {
        ifstream fileIn(path);
        if(fileIn.is_open()) {
            TreeNode<T>* temp = new TreeNode<T>();
            loadFromFile(temp, fileIn);
            root = temp;
        }
        fileIn.close();
    }

    void loadFromFile(TreeNode<T>* &node, istream &in) {
        string serialNode;
        if(!(in >> serialNode))
            return;
        if(serialNode != "#") {
            node = new TreeNode<T>();
            stringstream ss(serialNode);
            ss >> (*node);
            loadFromFile(node->left, in);
            loadFromFile(node->right, in);
        }
    }
private:
    TreeNode<T>* root = nullptr;

    void remove(TreeNode<T>* node) {
        if(node == nullptr)
            return;

        remove(node->left);
        remove(node->right);
        delete node;
    }

    void print(TreeNode<T>* node) {
        if(node == nullptr)
            return;

        print(node->left);
        cout << *node->getValue() << " ";
        print(node->right);
    }

    TreeNode<T>* getNode(TreeNode<T>* node, T& value) {
        TreeNode<T>* temp = node;
        while(temp != nullptr) {
            if(*temp->getValue() > value) {
                temp = temp->left;
            } else if(*temp->getValue() < value) {
                temp = temp->right;
            } else {
                return temp;
            }
        }
        return nullptr;
    }

    int size(TreeNode<T>* node, int amount) {
        if(node == nullptr)
            return ++amount;

        return size(node->left, amount) + size(node->right, amount);
    }
};

#endif //AVLTREE_H
