#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "Reference.h"
#include "AVLTree.h"
#include "HashMap.h"

using namespace std;

class IndexHandler {
public:
    IndexHandler();
    ~IndexHandler();
    void insertWord(string &word, string &document);
    void insertAuthor(string &author, string &document);
    void save(string path);
    void load(string path);
    AVLTree<Reference<string>>* getWordTree();
    AVLTree<Reference<string>>* getAuthorTree();
private:
    AVLTree<Reference<string>>* wordTree = nullptr;
    AVLTree<Reference<string>>* authorTree = nullptr;
};

#endif //INDEXHANDLER_H