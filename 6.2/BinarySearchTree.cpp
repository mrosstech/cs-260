//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Michael Ross
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Binary Search Tree Assignment
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

    // Added default constructor to Node()
    Node() {
        left = 0;
        right = 0;
    }

    // Added overloaded constructor to Node() for 
    // initializing with a bid given.
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
    Node* removeNode(Node* node, string bidId);
    // Helper function to find the minimum value node on a particular tree
    // Used in the removeNode recursive function
    // Found at:  https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
    Node* minValueNode(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    // Added a size function to get the number of entries read to
    // display properly
    int size(Node* node);
    int size();
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    // Setting the root to 0 on initialization.
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
    // Call the recursive inOrder method to print the tree
    // in order from the root.
    this->inOrder(this->root);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree
    
    // If the root is zero we're inserting the first bid so
    // just set the root to the new Node with the bid as
    // data value.
    if (root == 0) {
        root = new Node(bid);
    } else {
        // Otherwise recursively call the addNode method to insert
        // the bid in the right location.
        this->addNode(root, bid);
    }
    
}

/**
 * Remove a node
 * 
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // If we're given an empty node, just return that node back.
    if (node == 0) {
        return node;
    }

    // bidId is less than the bidId of the node, so it must be to the left
    // run a recursive delete on the left branch.
    if (bidId < node->dataVal.bidId) {
        node->left = removeNode(node->left, bidId);
    } else if (bidId > node->dataVal.bidId) {
        // bidId is greater than the node bidId so it must be to the right
        // run a recursive delete on the right branch
        node->right = removeNode(node->right, bidId);
    } else {
        // if the bidId searched and the bidId of this node are equal then remove the 
        // node

        // First search for the various possible combinations of children:
        // No children
        if (node->left == 0 and node->right == 0) {
            return 0;
        } else if (node->left == 0) {
            // Only right node
            Node* tempNode = node->right;
            free(node);
            return tempNode;
        } else if (node->right == 0) {
            // Only left node
            Node* tempNode = node->left;
            free(node);
            return tempNode;
        }
        // Two children

        // Get the minimum value node on the right subtree.
        Node* tempNode = minValueNode(node->right);
        // Set the value of this node to the minimum value returned from 
        // the method above.
        node->dataVal = tempNode->dataVal;

        // run the recursive removeNode on the right subtree to remove the node we just 
        // replaced this node with.
        node->right = removeNode(node->right, tempNode->dataVal.bidId);
    }
    return node;

}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree
    // Call the recursive removeNode method starting at the root of the tree.
    this->removeNode(this->root, bidId);
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

// Helper function to find the inorder successor in the given node tree.
Node* BinarySearchTree::minValueNode(Node* node) {
    Node* cur = node;
    while (cur and cur->left != 0) {
        cur = cur->left;
    }
    return cur;
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
