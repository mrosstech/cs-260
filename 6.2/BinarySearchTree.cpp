//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : JYour name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================




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


// forward declarations
double strToDouble(string str, char ch);
void displayBid(Bid bid);

// FIXME (1): Internal structure for tree node
struct Node {
    Node* left = 0;
    Node* right = 0;
    Bid dataVal;

    Node() {
        left = 0;
        right = 0;
    }

    Node(Bid myBid) : Node() {
        this->dataVal = myBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    int size(Node* node);
    Node* removeNode(Node* node, string bidId);
    // Added method to search for a node by BidId and return that node.  This will help with 
    // the recursive remove algorithm.
    Node* nodeSearch(string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    int size();
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = 0;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    this->inOrder(this->root);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree
    
    // temporary node variable for traversing the tree
    if (root == 0) {
        root = new Node(bid);
    } else {
        this->addNode(root, bid);
    }
    
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree
    Node* cur;
    Node* par = 0;
    Node* suc;

    cur = this->root;
    while (cur != 0) { // Search for node
        if (cur->dataVal.bidId == bidId) { // Node found 
            if (cur->left == 0 && cur->right == 0) {         // Remove leaf
                if (par == 0) { // Node is root
                    this->root = 0;
                }
                else if (par->left == cur) {
                    par->left = 0;
                }
                else {
                    par->right = 0;
                }
            }
            else if (cur->left != 0 && cur->right == 0) {    // Remove node with only left child
                if (par == 0) { // Node is root
                    this->root = cur->left;
                }
                else if (par->left == cur) {
                    par->left = cur->left;
                }
                else {
                    par->right = cur->left;
                }
            }
            else if (cur->left == 0 && cur->right != 0) {    // Remove node with only right child
                if (par == 0) { // Node is root
                    this->root = cur->right;
                }
                else if (par->left == cur) {
                    par->left = cur->right;
                }
                else {
                    par->right = cur->right;
                }
            }
            else {                                  // Remove node with two children
                // Find successor (leftmost child of right subtree)
                suc = cur->right;
                while (suc->left != 0) {
                    suc = suc->left;
                    cur = suc;                     // Copy successor to current node
                    this->Remove(cur->right, bidId);     // Remove successor from right subtree
                }
            }
            return; // Node found and removed
        }
        else if (cur->key < key) {// Search right
            par = cur;
            cur = cur->right;
        }
        else {                     // Search left
            par = cur;
            cur = cur->left;
        }
    }
    return; // Node not found
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid
	// Temp node for traversing the tree
    Node* cur;
    // Create an empty bid to return in case we don't find the right one.
    Bid bid;
    cur = this->root;
    while (cur != 0) {
        if (bidId == cur->dataVal.bidId) {
            // Return the bid value at cur because we found the right bid.
            return cur->dataVal;
        } else if (bidId < cur->dataVal.bidId) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    // Return empty bid because we didn't find anything
    return bid;
}

Node* BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid
	// Temp node for traversing the tree
    Node* cur;
    // Create an empty bid to return in case we don't find the right one.
    Bid bid;
    cur = this->root;
    while (cur != 0) {
        if (bidId == cur->dataVal.bidId) {
            // Return the bid value at cur because we found the right bid.
            return cur;
        } else if (bidId < cur->dataVal.bidId) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    // Return empty bid because we didn't find anything
    return 0;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree
    if (bid.bidId < node->dataVal.bidId) {
        if (node->left == 0) {
            node->left = new Node(bid);
            return;
        } else {
            this->addNode(node->left, bid);
        }
    } else {
        if (node->right == 0) {
            node->right = new Node(bid);
            return;
        } else {
            this->addNode(node->right, bid);
        }
    }

}

void BinarySearchTree::inOrder(Node* node) {
    if (node == 0) {
        return;
    }

    this->inOrder(node->left);
    displayBid(node->dataVal);
    this->inOrder(node->right);
}


int BinarySearchTree::size(Node* node) {
    if (node == 0) {
        return 0;
    }
    return 1 + this->size(node->left) + size(node->right);
}
int BinarySearchTree::size() {
    return this->size(root);
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
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    /* Doesn't work properly
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;
    */
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
            bst->Insert(bid);
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
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

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
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            cout << bst->size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
