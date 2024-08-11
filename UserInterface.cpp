#include "UserInterface.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <vector>
#include "DocumentParser.h"
#include <experimental/filesystem>

using namespace std;
using namespace std::experimental::filesystem;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

void UserInterface::start() {
	while (true) {
		update();
	}
}

void UserInterface::update() {
	bool stop = false;
	while (!stop) {
		switch (state) {
		case main:
			drawMainMenu();
			updateMainMenu(stop);
			break;
		case search:
			drawSearchMenu();
			updateSearchMenu(stop);
			break;
		case options:
			drawOptionsMenu();
			updateOptionsMenu(stop);
			break;
		default:
			break;
		}
	}
}

void UserInterface::updateMainMenu(bool &stop) {
	char key = 0;
	cin >> key;
	switch(key) {
	    case '1':
	        state = search;
	        break;
	    /*case '2':
	        state = options;
	        break;*/
	    case '21':
	        exit(EXIT_SUCCESS);
	        break;
	    default:
	        break;
	}
}

void UserInterface::updateSearchMenu(bool &stop) {
	if (!hasCorpus) {
	    string path;
	    cin >> path;
	    DocumentParser::parse(path.c_str(), *stopwords, *indexHandler, 0);
	    hasCorpus = true;
    } else {
	    string query;
	    cin >> query;

	}
}

void UserInterface::updateOptionsMenu(bool& stop) {
    int key = 0;
    cin >> key;
    switch (key) {
    case KEY_UP:
        if (cursorPos > main)
            cursorPos--;
        break;
    case KEY_DOWN:
        if (cursorPos < 2)
            cursorPos++;
        break;
    case KEY_ENTER:
        stop = true;
        switch (cursorPos) {
        case 0: // Open Persistance File.
            break;
        case 1: // Clear Index.
            break;
        case 2: // Back
            state = main;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void UserInterface::drawMainMenu() {
    clearScreen();
    drawHeader();

    vector<string> menus;
    menus.push_back("1) Search Menu");
    //menus.push_back("2) Options");
    menus.push_back("2) Exit");

	for(int i = 0; i < menus.size(); i++) {
        string grouped("|  " + menus[i]);
        cout << left << setw(50) << grouped << "|" << endl;
	}

	drawFooter();
}

void UserInterface::drawSearchMenu() {
	clearScreen();
	drawHeader();

	if (!hasCorpus) {
		cout << " -=- Search Menu -=-" << endl;
		cout << " No Corpus Found! Please Enter a path to the database directory." << endl;
		cout << " > ";
	} else {
        cout << " -=- Search Menu -=-" << endl;
        cout << " Enter a Query -> (AND term1 term2 ...) (OR term1 term2 ...) AUTHOR (lastName)";
        cout << " > ";
	}
}

void UserInterface::drawOptionsMenu() {
	clearScreen();
	drawHeader();

	vector<string> menus;
	menus.push_back("Open Save File");
	menus.push_back("Clear Index");
	menus.push_back("Back");

	for (int i = 0; i < menus.size(); i++) {
		if (cursorPos == i) {
			string grouped("| > " + menus[i]);
			cout << left << setw(50) << grouped << "|" << endl;
		}
		else {
			string grouped("|   " + menus[i]);
			cout << left << setw(50) << grouped << "|" << endl;
		}
	}

	drawFooter();
}

void UserInterface::drawLoadingMenu(float percent) {
    clearScreen();

	int toDraw = (int) round(percent * 45.0f);

	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
	cout << "|                                                 |" << endl;
	cout << "| Loading...                                      |" << endl;
	cout << "| >";

	for (int i = 0; i < toDraw; i++) {
		cout << "#";
	}
	for (int i = 0; i < 45 - toDraw; i++) {
		cout << "-";
	}
	cout << "< |" << endl;

	cout << "|                                                 |" << endl;
	cout << "|                                                 |" << endl;
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

void UserInterface::drawHeader() {
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
	cout << "|                                                 |" << endl;
	cout << "| CS2341-Search-Engine (Project 4)                |" << endl;
	cout << "| By Seth Potter                                  |" << endl;
	cout << "| ----------------------------------------------- |" << endl;
}

void UserInterface::drawFooter() {
	cout << "|                                                 |" << endl;
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
}

void UserInterface::clearScreen() {
    #ifdef linux
        for(int i = 0; i < 10; i++) {
            printf("\n\n\n\n\n\n\n\n\n\n");
        }
    #endif
    #ifdef _WIN32
        system("cls");
    #endif
}