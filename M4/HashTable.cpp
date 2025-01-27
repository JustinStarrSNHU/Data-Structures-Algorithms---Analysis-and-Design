//============================================================================
// Name        : HashTable.cpp
// Author      : Justin Starr
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid                 
        // and invoke the default constructor
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key        
        // this invokes prior constructor, which will also invoke the default constructor
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    size_t Size();
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (1): Initialize the structures used to hold bids

    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    this->tableSize = size;
    
    // resize nodes size
    nodes.resize(tableSize);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (2): Implement logic to free storage when class is destroyed

    // erase nodes beginning
    nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (3): Implement logic to calculate a hash value
    
    // return key tableSize
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (4): Implement logic to insert a bid
    // create the key for the given bid
    unsigned key = hash(atoi(bid.bidId.c_str())); // atoi() converts ascii string to integer   c_str converts to a c style string

    // retrieve node using key
    Node* oldNode = &(nodes.at(key));

    // if no entry found for the key
    if (oldNode == nullptr) {
        // assign this node to the key position
        Node* newNode = new Node(bid, key);
        nodes.insert(nodes.begin() + key, (*newNode));
    }
        
    // else if node is not used
    else  {
        // assing old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer
        if (oldNode->key == UINT_MAX) {
            oldNode->key = key;
            oldNode->bid = bid;
            oldNode->next = nullptr;
        } 
        // else find the next open node
        else {
            while (oldNode->next != nullptr) {
                oldNode = oldNode->next;
            }
            // add new newNode to end
            oldNode->next = new Node(bid, key);
        }
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (5): Implement logic to print all bids

    // for node begin to end iterate
    for (unsigned int i = 0; i < nodes.size(); ++i) {
            
        Node* searchNode = &(nodes.at(i));

        //  if key not equal to UINT_MAx
        if (searchNode->key != UINT_MAX) {

            // output key, bidID, title, amount and fund
            cout << searchNode->bid.bidId << ": " << searchNode->bid.title << " | " << searchNode->bid.amount << " | "
                << searchNode->bid.fund << endl;

            // node is equal to next iter
            searchNode = searchNode->next;
                
            // while node not equal to nullptr
            while (searchNode != nullptr) {

                // output key, bidID, title, amount and fund
                cout << searchNode->bid.bidId << ": " << searchNode->bid.title << " | " << searchNode->bid.amount << " | "
                    << searchNode->bid.fund << endl;

                // node is equal to next node
                searchNode = searchNode->next;
            }
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // FIXME (6): Implement logic to remove a bid
    
    // set key equal to hash atoi bidID cstring
    unsigned int tempKey = hash(atoi(bidId.c_str()));

    // erase node begin and key
    nodes.erase(nodes.begin() + tempKey);

}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    // FIXME (7): Implement logic to search for and return a bid

    // create the key for the given bid
    unsigned int tempKey = hash(atoi(bidId.c_str()));

    // try and retrieve node using the key
    Node* node = &(nodes.at(tempKey));

    // if no entry found for the key
    if (node == nullptr || node->key == UINT_MAX) {
        // return bid
        return bid;
    }

    // if entry found for the key
    if (node != nullptr && node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {//if the compare equals 0 then it is a match
        //return node bid
        return node->bid;
    }
    
    // while node not equal to nullptr
    while (node != nullptr) {
        // if the current node matches, return it
        if (node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {
            return node->bid;
        }
        //node is equal to next node
        node = node->next;
    }

    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, searchValue;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        searchValue = "98223";
        break;
    case 3:
        csvPath = argv[1];
        searchValue = argv[2];
        break;
    default:
        //csvPath = "CS 300 eBid_Monthly_Sales.csv";
        csvPath = "CS 300 eBid_Monthly_Sales_Dec_2016.csv";
        searchValue = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(searchValue);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
                cout << "Bid Id " << searchValue << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(searchValue);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}