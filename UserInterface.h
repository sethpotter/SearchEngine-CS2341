#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include "IndexHandler.h"
#include "HashSet.h"
#include "QueryProcessor.h"
#include <experimental/filesystem>
#include <iostream>


using namespace std;
using namespace std::experimental::filesystem;

class UserInterface {
public:
	UserInterface(IndexHandler &indexHandler, HashSet<string> &stopwords, QueryProcessor &queryProcessor, bool hasCorpus) {
        this->indexHandler = &indexHandler;
        this->hasCorpus = hasCorpus;
        this->stopwords = &stopwords;
        this->queryProcessor = &queryProcessor;
		state = main;
		cursorPos = 0;
	}
	void start();
	static void drawLoadingMenu(float percent);
	static void clearScreen();
private:
	enum MenuState { main, search, options };
	MenuState state;
	int cursorPos;
	bool hasCorpus = false;
	string writeBuffer;
	IndexHandler* indexHandler;
	QueryProcessor* queryProcessor;
	HashSet<string>* stopwords;

	void updateMainMenu(bool &stop);
	void updateSearchMenu(bool &stop);
	void updateOptionsMenu(bool &stop);

	void update();

	void drawMainMenu();
	void drawSearchMenu();
	void drawOptionsMenu();
	
	void drawHeader();
	void drawFooter();


};

#endif // USERINTERFACE_H
