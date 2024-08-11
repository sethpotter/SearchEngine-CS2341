#include <iostream>
#include "TreeNode.h"
#include "AVLTree.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <document.h>
#include <stringbuffer.h>
#include <writer.h>
#include <experimental/filesystem>
#include "DocumentParser.h"
#include <string>
#include <random>
#include "HashMap.h"
#include "HashSet.h"
#include "CountingHashSet.h"
#include "UserInterface.h"
#include "QueryProcessor.h"

using namespace std;
using namespace std::experimental::filesystem;
using namespace rapidjson;
using namespace std::chrono;

int main(int argc, char** argv) {

    HashSet<string> stopwords;
    stopwords.reserve(635);

    DocumentParser::getStopwords(stopwords);
    IndexHandler indexHandler;
    QueryProcessor queryProcessor(indexHandler, stopwords);

    bool hasCorpus = false;
	if(argc == 2) {
		DocumentParser::parse(argv[1], stopwords, indexHandler, 0);
		hasCorpus = true;
	} else if(argc == 3) {
		DocumentParser::parse(argv[1], stopwords, indexHandler, atoi(argv[2]));
		hasCorpus = true;
	} else if(argc > 3) {
		throw invalid_argument("Error: Invalid Argument Count- SearchEngine.exe {Path} {Search Term}");
	}

	UserInterface ui(indexHandler, stopwords, queryProcessor, hasCorpus);
	ui.start();

	/*char ps = experimental::filesystem::path::preferred_separator;
	string path = DocumentParser::getWorkingPath(argv[0]) + "data" + ps;
	auto start = high_resolution_clock::now();*/



    //int num = DocumentParser::parse(path.c_str(), indexHandler, 1000);



	/*auto end = high_resolution_clock::now();

	auto timeTook = duration_cast<seconds>(end - start);

	cout << "Took: " << timeTook.count() << endl;
    cout << endl;
    cout << "Documents Parsed: " << num << endl;
    cout << "Number of Word Nodes: " << indexHandler.getWordTree()->size() << endl;
    cout << "Number of Author Nodes: " << indexHandler.getAuthorTree()->size() << endl << endl;

    cout << *indexHandler.getWordTree()->getRoot() << endl;
    indexHandler.getWordTree()->getRoot()->getValue()->getValues()->printTable();
    cout << *indexHandler.getAuthorTree()->getRoot() << endl;
    indexHandler.getAuthorTree()->getRoot()->getValue()->getValues()->printTable();

    indexHandler.getWordTree()->saveToFile(DocumentParser::getWorkingPath(argv[0]) + "wordTree.txt");
    indexHandler.getAuthorTree()->saveToFile(DocumentParser::getWorkingPath(argv[0]) + "authorTree.txt");

    cout << "Saved." << endl;

    /*indexHandler.getWordTree()->loadFromFile(DocumentParser::getWorkingPath(argv[0]) + "wordTree.txt");
    indexHandler.getAuthorTree()->loadFromFile(DocumentParser::getWorkingPath(argv[0]) + "authorTree.txt");
    cout << "Loaded!" << endl;

    cout << *indexHandler.getWordTree()->getRoot() << endl;
    indexHandler.getWordTree()->getRoot()->getValue()->getValues()->printTable();
    cout << *indexHandler.getAuthorTree()->getRoot() << endl;
    indexHandler.getAuthorTree()->getRoot()->getValue()->getValues()->printTable();*/
    //indexHandler.basicQuery("coronavirus");*/

    return 0;
}