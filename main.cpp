#include <iostream>
#include <vector>
#include "BST.h"
#include "HashClass.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <chrono>

using namespace std;

// Struct for storing the document info
struct DocumentItem {
    string documentName;
    int count = 1; // Assigning the word count 1 as default
};

// Function to preprocess the input file
void preprocessed(ifstream &input, const string &openFile, vector<string> &temp) {
    input.open(openFile.c_str()); // Opening the file
    string word;

    while (input >> word) {
        string alphabeticChars;

        for (char c : word) {
            if (isalpha(c)) {
                alphabeticChars += tolower(c);
            } else {
                // Non-alphabetic character acts as a separator
                if (!alphabeticChars.empty()) {
                    temp.push_back(alphabeticChars);
                    alphabeticChars = ""; // Reset for the next word
                }
            }
        }

        // Add the remaining alphabetic characters
        if (!alphabeticChars.empty()) {
            temp.push_back(alphabeticChars);
        }
    }

    input.close(); // Close the file after reading
}

// Function to preprocess the query
void preprocessQuery(const string &inputLine, vector<string> &wordList) {
    istringstream iss(inputLine);
    string word;

    while (iss >> word) {
        string alphabeticChars;

        for (char c : word) {
            if (isalpha(c)) {
                alphabeticChars += tolower(c);
            } else {
                // Non-alphabetic character acts as a separator
                if (!alphabeticChars.empty()) {
                    wordList.push_back(alphabeticChars);
                    alphabeticChars = ""; // Reset for the next word
                }
            }
        }

        // Add the remaining alphabetic characters
        if (!alphabeticChars.empty()) {
            wordList.push_back(alphabeticChars);
        }
    }
}

// Function to store words in the BST and HashTable
void storing(vector<string> &fileName, vector<string> &temp, BST<string, WordItem<string, vector<DocumentItem>>*> &myTree, HashTable<string, WordItem<string, vector<DocumentItem>>*> &myHashTable) {
    for (int j = 0; j < fileName.size(); j++) {
        ifstream input;
        const string openFile = fileName[j];
        temp = {};
        preprocessed(input, openFile, temp);
        int vecSize = temp.size(), index = 0;
        while (index < vecSize) {
            string word = temp[index];
            //---Storing into the BST---
            if (myTree.findVal(word) != nullptr) {
                bool newDoc = true;
                for (int k = 0; k < myTree.findVal(word)->value->value.size(); k++) {
                    if (myTree.findVal(word)->value->value[k].documentName == fileName[j]) {
                        myTree.findVal(word)->value->value[k].count++;
                        newDoc = false;
                        break;
                    }
                }
                if (newDoc) {
                    DocumentItem doc;
                    doc.documentName = fileName[j];
                    myTree.findVal(word)->value->value.push_back(doc);
                }
            } else if (myTree.findVal(word) == nullptr) {
                // If the word is not in the BST, add it
                vector<DocumentItem> docVec;
                DocumentItem doc;
                doc.documentName = fileName[j];
                docVec.push_back(doc);
                auto *ptr = new WordItem<string, vector<DocumentItem>>(word, docVec, nullptr, nullptr, 0);
                myTree.insert(word, ptr);
            }

            //---Storing into the HashTable---
            if (auto *entry = myHashTable.find(word)) {
                // Word found in HashTable
                bool newDoc = true;
                for (DocumentItem &doc : entry->value) {
                    if (doc.documentName == fileName[j]) {
                        doc.count++;
                        newDoc = false;
                        break;
                    }
                }
                if (newDoc) {
                    DocumentItem doc;
                    doc.documentName = fileName[j];
                    entry->value.push_back(doc);
                }
            } else {
                // If the word is not in the HashTable, add it
                vector<DocumentItem> docVec{DocumentItem{fileName[j]}};
                auto *ptr = new WordItem<string, vector<DocumentItem>>(word, docVec, nullptr, nullptr, 0);
                myHashTable.insert(word, ptr);
            }
            index++;
        }
    }
}

int main() {
    int fileNum = 0;
    vector<string> fileName;

    // Getting input of files
    cout << "Enter number of input files: ";
    cin >> fileNum;

    // Storing the filenames in a vector
    for (int i = 0; i < fileNum; i++) {
        string file;
        cout << "Enter " << i + 1 << ". file name: ";
        cin >> file;
        fileName.push_back(file);
    }

    // Creating the BST
    BST<string, WordItem<string, vector<DocumentItem>>*> myTree;
    HashTable<string, WordItem<string, vector<DocumentItem>>*> myHashTable(nullptr);

    vector<string> temp;
    storing(fileName, temp, myTree, myHashTable);

    double loadFac = double(myHashTable.getCurrSize()) / double(myHashTable.getArraySize());
    cout << "\nAfter preprocessing, the unique word count is " << myHashTable.getCurrSize() << ". Current load ratio is\n"
         << loadFac;

    string inputLine;
    bool queryExistsInAnyDocument = false;

    cout << "\nEnter queried words in one line: ";
    cin.ignore();
    getline(cin, inputLine);

    vector<string> queryWordList;
    preprocessQuery(inputLine, queryWordList);

    int k = 100;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++) {
        // QueryDocuments (with BST);

        // For each file, check if all words in the query exist
        for (int h = 0; h < fileName.size(); h++) {
            bool allWordsFoundInDocument = true;

            for (int p = 0; p < queryWordList.size(); p++) {
                string temp = queryWordList[p];

                // Check if the word is in the AVL tree
                if (myTree.findVal(temp) != nullptr) {
                    bool wordFoundInDocument = false;

                    // Check if the word is in the document
                    for (int j = 0; j < myTree.findVal(temp)->value->value.size(); j++) {
                        if (myTree.findVal(temp)->value->value[j].documentName == fileName[h]) {
                            wordFoundInDocument = true;
                            break;
                        }
                    }

                    if (!wordFoundInDocument) {
                        allWordsFoundInDocument = false;
                        break;
                    }
                } else {
                    allWordsFoundInDocument = false;
                    break;
                }
            }

            if (allWordsFoundInDocument && i == 0) {
                queryExistsInAnyDocument = true;

                cout << "in Document " << fileName[h] << ", ";
                bool first = true;

                // Output the result for each word in the query
                for (int y = 0; y < queryWordList.size(); y++) {
                    string newestWord = queryWordList[y];

                    // Check if the word is in the BST tree
                    if (myTree.findVal(newestWord) != nullptr) {
                        int count = myTree.findVal(newestWord)->value->value[h].count;

                        if (count > 0) {
                            if (!first) {
                                cout << ", ";
                            }

                            cout << newestWord << " found " << count << " times";
                            first = false;
                        }
                    }
                }
                cout << "." << endl;
            }
        }

        // If the query doesn't exist in any document
        if (!queryExistsInAnyDocument && i == 0) {
            cout << "No document contains the given query\n";
        }
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start);

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++) {
        // QueryDocuments (with hashtable);
        // For each file, check if all words in the query exist
        for (int h = 0; h < fileName.size(); h++) {
            bool allWordsFoundInDocument = true;

            for (int p = 0; p < queryWordList.size(); p++) {
                string temp = queryWordList[p];

                // Check if the word is in the hash table
                const auto& wordData = myHashTable.find(temp);
                if (wordData != myHashTable.getItemNotFound()) {
                    bool wordFoundInDocument = false;

                    // Check if the word is in the document
                    for (const auto& documentItem : wordData->value) {
                        if (documentItem.documentName == fileName[h]) {
                            wordFoundInDocument = true;
                            break;
                        }
                    }

                    if (!wordFoundInDocument) {
                        allWordsFoundInDocument = false;
                        break;
                    }
                } else {
                    allWordsFoundInDocument = false;
                    break;
                }
            }

            if (allWordsFoundInDocument && i == 0) {
                queryExistsInAnyDocument = true;

                cout << "in Document " << fileName[h] << ", ";
                bool first = true;

                // Output the result for each word in the query using BST
                for (int y = 0; y < queryWordList.size(); y++) {
                    string newestWord = queryWordList[y];

                    // Check if the word is in the BST tree
                    if (myTree.findVal(newestWord) != nullptr) {
                        int count = myTree.findVal(newestWord)->value->value[h].count;

                        if (count > 0) {
                            if (!first) {
                                cout << ", ";
                            }
                            cout << newestWord << " found " << count << " times";
                            first = false;
                        }
                    }
                }
                cout << "." << endl;
            }
        }

        // If the query doesn't exist in any document
        if (!queryExistsInAnyDocument && i == 0) {
            cout << "No document contains the given query\n";
        }
    }
    cout << "\nTime: " << BSTTime.count() / k << endl;

    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - start);
    cout << "\nTime : " << HTTime.count() / k << endl;

    cout << "Speed Up: "<< double(BSTTime.count() / k) / double(HTTime.count() / k)<< endl;

    return 0;
}
