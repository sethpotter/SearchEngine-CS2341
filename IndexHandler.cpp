#include "IndexHandler.h"
#include <algorithm>

IndexHandler::IndexHandler() {
    wordTree = new AVLTree<Reference<string>>();
    authorTree = new AVLTree<Reference<string>>();
}

IndexHandler::~IndexHandler() {
    delete wordTree;
}

void IndexHandler::insertWord(string &word, string &document) {
    Reference<string> ref(word);
    TreeNode<Reference<string>>* node = wordTree->getNode(ref);
    if(node == nullptr) {
		ref.addValue(document);
        wordTree->insert(ref);
    } else {
		node->getValue()->addValue(document);
    }
}

void IndexHandler::insertAuthor(string &author, string &document) {
    Reference<string> ref(document);
    TreeNode<Reference<string>>* node = authorTree->getNode(ref);
    if(node == nullptr) {
        ref.addValue(author);
        authorTree->insert(ref);
    } else {
        node->getValue()->addValue(author);
    }
}

void IndexHandler::save(string path) {

}

void IndexHandler::load(string path) {

}

/*void IndexHandler::basicQuery(string query) {
    string lc = query;
    transform(lc.begin(), lc.end(), lc.begin(), ::tolower);

    Reference* ref = new Reference(query);
    TreeNode<Reference>* result = tree->getNode(ref);

    cout << "Search Results for: " << query << endl;
    if(result == nullptr) {
        cout << "0 Results Found." << endl;
    } else {
        cout << "Found across " << result->getValue()->getDocuments()->size() << " document(s)." << endl;
        for(string str : *result->getValue()->getDocuments()) {
            cout << str << ".json" << endl;
        }
    }

    delete ref;
}*/

AVLTree<Reference<string>>* IndexHandler::getWordTree() {
    return wordTree;
}

AVLTree<Reference<string>>* IndexHandler::getAuthorTree() {
    return authorTree;
}