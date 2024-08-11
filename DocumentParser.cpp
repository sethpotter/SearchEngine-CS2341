#include "DocumentParser.h"
#include <iostream>

#include "csvparser.hpp"
#include <string>
#include <sstream>
#include <document.h>
#include <stringbuffer.h>
#include "includes/rapidjson/istreamwrapper.h"
#include "HashSet.h"
#include "HashMap.h"
#include <experimental/filesystem>
#include "UserInterface.h"

#include "porter2_stemmer.h"

using namespace std;
using namespace rapidjson;
using namespace aria::csv;
using namespace std::experimental::filesystem;

int DocumentParser::parse(const char* path, HashSet<string>& stopwords, IndexHandler& indexHandler, int limit) {
	vector<string> documentList;

	// Populate Stopwords list, get the document list, and reserve space for the author map.
	getFullTextList(path, documentList);

    // Setup temporary reusable buffers.
	int bufferSize = 262144;
	char* temp = new char[bufferSize];
	istringstream ssBuffer;
	string word;

    int count = 0;
    for(auto& fileName : documentList) {
        if(limit <= 0 || count <= limit - 1) {
            ifstream file(path + fileName + ".json");
            if(!file.good())
                continue;

            // Read all the text in the JSON Document
			int size = file.seekg(0, std::ios::end).tellg();
			if (size > bufferSize) {
				delete[] temp;
				bufferSize = size;
				temp = new char[bufferSize + 1];
			}

			file.seekg(0, ios::beg);
			file.read(temp, size);
			file.close();
			temp[size] = '\0';

			// Construct a JSON Object using RapidJson
            Document doc;
			doc.ParseInsitu(temp);

			// Initialize a String to append all "body_text" to.
			string text = "";
			for (Value& field : doc["body_text"].GetArray()) {
				text.append(field["text"].GetString());
			}

			// Generate a map that correlates authors to documents.
			for(Value& field : doc["metadata"]["authors"].GetArray()) {
			    string authorLastName = field["last"].GetString();
                transform(authorLastName.begin(), authorLastName.end(), authorLastName.begin(), ::tolower);
			    indexHandler.insertAuthor(authorLastName, fileName);
			}

			// Remove characters specified by isDocPunc.
			text.erase(remove_if(text.begin(), text.end(), [](auto &c) {
				return isDocPunc(c);
			}), text.end());
			// Document to lowercase.
			transform(text.begin(), text.end(), text.begin(), ::tolower);

			// Populate stringstream buffer with document text.
			ssBuffer.str(text);
			while(ssBuffer >> word) { // Parse word by word. Stem then insert into AVLTree
				Porter2Stemmer::trim(word);
				Porter2Stemmer::stem(word);
				if (!word.empty() && !stopwords.contains(word, 1)) {
					indexHandler.insertWord(word, fileName);
				}
			}
			// Clear Text buffer.
			ssBuffer.clear();

			// UserInterface misc. (Draw a Loading bar on screen)
            if(count != 0 && count % 250 == 0) {
				if (limit == 0)
					UserInterface::drawLoadingMenu(((float)count / (float)documentList.size()));
				else
					UserInterface::drawLoadingMenu((float) count / (float) limit);
				cout << count << endl;
            }
            count++;
        }
    }
	UserInterface::drawLoadingMenu(1.0f);
    return count;
}

string DocumentParser::getWorkingPath(char* argv) {
	char ps = experimental::filesystem::path::preferred_separator;
	string wp(argv);
	wp = wp.substr(0, wp.find_last_of(ps));
	if(wp[wp.size()] != ps)
	    wp = wp + ps;
	return wp;
}

void DocumentParser::getStopwords(HashSet<string> &set) {
    ifstream stopwordFile("./includes/stopwords/stopwords.txt");
    if(stopwordFile.is_open()) {
        string line;
        while(getline(stopwordFile, line)) {
            line = line.substr(0, line.size());
            set.insert(line);
        }
    }
    stopwordFile.close();
}

void DocumentParser::getFullTextList(const char* path, vector<string> &buffer) {
    string strPath(path);
    ifstream csvFile(strPath + "metadata-cs2341.csv");
    CsvParser parser(csvFile);

    int pdfPos = -1, shaPos = -1;
    int count = 0;
    string sha;

    do {
        string hf = *(parser.next_field().data);
        if(hf == "sha") {
            shaPos = count;
        }
        if(hf == "has_pdf_parse") {
            pdfPos = count;
        }
        count++;
    } while (count < 18);

    for(auto& row : parser) {
        count = 0;
        for(auto& field : row) {
            if(count == shaPos) {
                sha = field;
            }
            if(count == pdfPos) {
                string lower = field;
                transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
                if(lower == "true") {
					buffer.push_back(sha);
                }
            }
            count++;
        }
    }
}

bool DocumentParser::isDocPunc(char c) {
	switch (c) {
	case ',':
	case '.':
	case ';':
	case ':':
	case '?':
	case '!':
	case '-':
	case '(':
	case ')':
	case '\\':
	case '\"':
	case '\'':
	case '*':
		return true;
	default:
		return false;
	}
}