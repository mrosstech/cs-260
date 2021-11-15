//============================================================================
// Name        : LinkedList.cpp
// Author      : Michael Ross
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
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

// Needed another structure to hold the data value and the pointer to the next node.
struct node
{
    Bid dataVal;
    node *next;
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
    // Internal structure for list entries, housekeeping variables
    // We only need the *head and *tail pointer structures to allow us to function.
    node *head;
    node *tail;
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
    // Configure the head and tail with the value of 0 to allow for append / prepend logic.
    this->head = 0;
    this->tail = 0;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // Assign bid data to temp node.
    node *tempNode = new node;

    // Assign the bid data to the dataVal struct member.
    tempNode->dataVal = bid;

    // Since this will be the last object in the list, assign the next node as 0
    tempNode->next = 0;

    // Check if this is the first node being added:
    if (this->head == 0) {
        // It is the first node so change the head and tail node to point to the incoming node.
        this->head = tempNode;
        this->tail = tempNode;
    } else {
        // It is not the first node, so change the tail node to point to this one.
        this->tail->next = tempNode;
        // The new tail is the new tempNode being appended.
        this->tail = tempNode;
    }

}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // Initialize the temporary node
    node *tempNode = new node;
    tempNode->dataVal = bid;
    tempNode->next = 0;

    // If this is the first node, set the head and tail to the new node.
    if (this->head == 0) {
        this->head = tempNode;
        this->tail = tempNode;
    // If it is not the first node, point the incoming node to the existing head
    // and then set the incoming node as the new head.
    } else {
        tempNode->next = this->head;
        this->head = tempNode;
    }
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // Initialize the temporary node.
    node *tempNode = new node;
    // Set the temporary node to the head.
    tempNode = this->head;
    // Loop while the current node is not set to 0 (end of list)
    while (tempNode != 0) {
        // Output the relevant data.
        cout << tempNode->dataVal.title << " | " << tempNode->dataVal.amount << " | " << tempNode->dataVal.fund << endl;
        // Navigate to the next list node.
        tempNode = tempNode->next;
    }
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // Initialize temporary node
    node *tempNode = new node;
    // Set the temporary node to the head.
    tempNode = this->head;
    // Loop while the current node is not set to 0 (end of list)
    while (tempNode != 0) {
        // If the next node has the matching bidId
        if (tempNode->next->dataVal.bidId == bidId) {
            // Change the current node to point to the next->next node to skip the next one.
            tempNode->next = tempNode->next->next;
            // Found the bid, so return.
            return;
        }
        tempNode = tempNode->next;
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // Initialize temporary variables
    Bid matchedBid;
    node *tempNode = new node;

    // Set tempNode to the head
    tempNode = this->head;
    while (tempNode->next != 0) {
        // If the bidId of the current node data value is equal to the search term then return the data value
        if (tempNode->dataVal.bidId == bidId) {
            return tempNode->dataVal;
        }
        tempNode = tempNode->next;
    }
    // No matched bid id so return the empty bid.
    return matchedBid;
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    int size = 0;
    node *tempNode = new node;
    tempNode = this->head;
    while (tempNode != 0) {
        size++;
        tempNode = tempNode->next;
    }
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
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

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
    } catch (csv::Error &e) {
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
        csvPath = "./eBid_Monthly_Sales_Dec_2016.csv";
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
            bid = getBid();
            bidList.Prepend(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
