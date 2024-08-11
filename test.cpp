#include "catch.hpp"
#include "TreeNode.h"
#include "AVLTree.h"
#include <iostream>

using namespace std;

TEST_CASE("TreeNode", "[TreeNode]") {

    TreeNode<int> left;
    TreeNode<int> right(2);
    TreeNode<int> root(5, left, right);

    SECTION("Basic") {
        cout << left << endl;
        cout << right << endl;
        cout << root << endl;
    }

}

TEST_CASE("AVLTree", "[AVLTree]") {

    /*AVLTree<int> tree;

    // 10 Random Integers
    int amount = 10;
    for(int i = 0; i < amount; i++) {
        int val = rand() % amount + 1;
        tree.insert(val);
    }

    SECTION("Printing a random tree") {
        tree.print();
        cout << *tree.getRoot() << endl;
        cout << tree.size() << endl;
    }*/

    AVLTree<string> wordTree;

    string car("carrot");
    string ham("hamburger");
    string par("parrot");
    string boo("book");

    string mec("mechanical");
    string key("keyboard");
    string bit("bitcoin");
    string cry("crystals");

    string inv("investing");
    string run("running");
    string out("outta");
    string wor("words");

    string lau("laughing");
    string ott("otters");
    string zeb("zebras");
    string won("wonder");

    wordTree.insert(car);
    wordTree.insert(ham);
    wordTree.insert(par);
    wordTree.insert(boo);
    wordTree.insert(mec);
    wordTree.insert(key);
    wordTree.insert(bit);
    wordTree.insert(cry);
    wordTree.insert(inv);
    wordTree.insert(run);
    wordTree.insert(out);
    wordTree.insert(wor);
    wordTree.insert(lau);
    wordTree.insert(ott);
    wordTree.insert(zeb);
    wordTree.insert(won);

    SECTION("Printing a word tree") {
        wordTree.print();
        cout << *wordTree.getRoot() << endl;
        cout << wordTree.size() << endl;
    }
}