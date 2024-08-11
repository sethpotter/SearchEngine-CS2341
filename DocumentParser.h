#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <string>
#include <vector>
#include "IndexHandler.h"
#include "HashSet.h"

using namespace std;

class DocumentParser {
public:
    static int parse(const char* path, HashSet<string> &stopwords, IndexHandler &indexHandler, int limit);
	static string getWorkingPath(char* argv);
    static void getStopwords(HashSet<string> &set);
private:
	static void getFullTextList(const char* path, vector<string> &buffer);
	static bool isDocPunc(char c);
};

#endif //DOCUMENTPARSER_H
