//============================================================================
// Name        : Justin Starr.cpp
// Author      : Your Name
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 3-2 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

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
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        Bid bid;
        Node* next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // FIXME (1): Initialize housekeeping variables
    //set head and tail equal to nullptr
    head = nullptr;
    tail = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // FIXME (2): Implement append logic

    //Create new node
    Node* temp = new Node();
    temp->bid = bid;
    temp->next = nullptr;

    //if there is nothing at the head...
    if (head == nullptr) {
        // new node becomes the head and the tail
        head = temp;
        tail = temp;
    }

    //else 
    else {
        // make current tail node point to the new node
        tail->next = temp;

        // and tail becomes the new node
        tail = temp;
    }

    //increase size count
    size += 1;
    
   
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIXME (3): Implement prepend logic

    // create a temporary node and assign it with the passed in bid
    Node* temp = new Node();
    temp->bid = bid;

    // case 1
    // if there is nothing at the head
    if (head == nullptr) {
        // set the heads next node to point to the nullptr
        head = temp;
        tail = temp;
        head->next = nullptr;
    }

    // case 2 
    // else there is already something at the head...
    else {
        // new node points to current head as its next node
        temp->next = head;

        // head now becomes the new node
        head = temp;
    }

    //increase size count
    size += 1;

}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (4): Implement print logic

    // start at the head
    Node* current = head;

    // while loop over each node looking for a match
    while (current != nullptr) {

        //output current bidID, title, amount and fund
        cout << current->bid.bidId << ": " << current->bid.title << " | " << current->bid.amount << " | " << current->bid.fund << endl;

        //set current equal to next
        current = current->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (5): Implement remove logic
    // 
    //   ******************* NOTE *****************
    // 
    // I was unable to code the way the comments describe this method
    //
    // special case if matching node is the head
        // make head point to the next node in the list
        //decrease size count
        //return

    // start at the head
    // while loop over each node looking for a match
        // if the next node bidID is equal to the current bidID
            // hold onto the next node temporarily
         // make current node point beyond the next node
         // now free up memory held by temp
         // decrease size count
         //return

    // current node is equal to next node

    // I coded for two cases, the first covers if the head node is the node we want to remove
    // The second case covers if the matching bid is anywhere after the head node including the tail node

    // special case if matching node is the head
    if (bidId == head->bid.bidId) {
        // create a temporary node to store the current head in
        Node* temp = head;

        // make head point to the next node in the list
        head = head->next;

        // free up memory
        delete(temp);

        //decrease size count
        size -= 1;

        //return
        return;
    }

    // case 2 is if the node we are searching for after the head node including the tail node
    // start at the head
    Node* current = head->next;;
    Node* prev = head;

    // while loop over each node looking for a match
    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            //found the node to remove and do not need to keep searching
            break;
        }

        // when a match is not found, set the previous node to the current node 
        // and the current node to the next node to be checked
        prev = current;
        current = current->next;
    }

    // if a match was never found, return.
    if (current == nullptr) {
        return;
    }

    // a match is found
    else {
        // special case if the current node is the tail node
        if (current == tail) {
            tail = prev;
        }
        // point current nodes previous node to current nodes next node
        prev->next = current->next;

        // delete the current node that was found
        delete(current);

        // decrease size count
        size -= 1;
    }

}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (6): Implement search logic
    
    
    // start at the head of the list
    Node* current = head;

    // if the head is the nullptr there are no bids so we must check that the head is not nullptr
    if (head != nullptr) {
        // special case if matching bid is the head
        if (bidId == head->bid.bidId) {
            return head->bid;
        }

        // keep searching until end reached with while loop (current != nullptr)
        while (current != nullptr) {
            // if the current node matches, return current bid
            if (current->bid.bidId == bidId) {
                return current->bid;
            }

            // else current node is equal to next node
            else {
                current = current->next;
            }
        }
    }

    //(the next two statements will only execute if search item is not found)
    if (current == nullptr) {
        //create new empty bid
        Bid newEmptyBid;

        //return empty bid 
        return newEmptyBid;
    }
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
        << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList* list) {
    cout << endl << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        //csvPath = "eBid_Monthly_Sales.csv";
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << endl;
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);
            cout << endl;

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            break;

        case 3:
            bidList.PrintList();
            cout << endl;

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                cout << endl;
                displayBid(bid);
            }
            else {
                cout << endl << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;

            break;

        case 5:
            bidList.Remove(bidKey);
            cout << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
