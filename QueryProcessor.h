#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <string>
#include "HashSet.h"
#include "IndexHandler.h"

using namespace std;

class QueryProcessor {
public:
    QueryProcessor(IndexHandler &indexHandler, HashSet<string> &stopwords) {
        this->stopwords = &stopwords;
        this->indexHandler = &indexHandler;
    }
    void termQuery(string query);
private:
    HashSet<string>* stopwords = nullptr;
    IndexHandler* indexHandler = nullptr;
};

#endif //QUERYPROCESSOR_H
