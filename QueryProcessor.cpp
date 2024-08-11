#include "QueryProcessor.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "DocumentParser.h"
#include "Reference.h"
#include "TreeNode.h"

using namespace std;

void QueryProcessor::termQuery(string query) {
    string buffer;
    stringstream ss(query);

    string operation;
    string author;

    vector<string> terms;

    int count = 0;
    while(ss >> buffer) {
        transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
        if(buffer == "author"){
            ss >> buffer;
            author = buffer;
            break;
        } else if(count == 0) {
            operation = buffer;
        } else {
            terms.push_back(buffer);
        }
        count++;
    }

    vector<string> docs;

    for(string &s : terms) {
        Reference<string> ref(s);
        TreeNode<Reference<string>>* result = indexHandler->getWordTree()->getNode(ref); // Get node containing word.
        if(result != nullptr) {
            CountingHashSet<string>* set = result->getValue()->getValues();
            for(string &doc : set->getValues()) {
                docs.push_back(doc);
            }
        }
    }

    if(operation == "and") {

    } else if(operation == "or") {

    } else {
        // ID
    }
}