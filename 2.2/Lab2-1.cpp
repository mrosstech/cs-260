//============================================================================
// Name        : Lab2-2.cpp
// Author      : Michael Ross
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 2-2 Up to Speed in C++, Part 2
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include "CSVparser.hpp"
#include <ctime>
#include <vector>

// References the CSVParser.hpp header file.

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

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

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter title: ";
    cin.ignore();
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
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
	// Created vector of Bid structs to hold bid data from file.
    vector<Bid> bids;

    // Created a temporary data structure tempBid of type Bid to hold data from each row and add to vector
    Bid tempBid;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

	// loop to read rows of a CSV file
	for (int i = 0; i < file.rowCount(); i++) {
        tempBid.title = file[i][0];
        tempBid.fund = file[i][8];
        tempBid.amount = strToDouble(file[i][4], '$');
        // DEBUG: cout << "Title: " << tempBid.title << " Fund: " << tempBid.fund << " Amount: " << tempBid.amount << endl;
        // Push the temporary bid struct onto the bids vector.
        bids.push_back(tempBid);
    }
    return bids;
}



/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Defined a vector to hold all the bids
    vector<Bid> myBids;

    // Defined a timer variable
    clock_t runtime;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        	cout << "Not currently implemented." << endl;

            break;
        case 2:
            runtime = clock();
            myBids = loadBids(csvPath);
            runtime = clock() - runtime;

            cout << myBids.size() << " bids read" << endl;
            cout << "time: " << runtime << " milliseconds" << endl;
            cout << "time: " << runtime*1.0/CLOCKS_PER_SEC << " seconds" << endl;

            break;
        case 3:
            // Loop and display the bids read
            for (int i = 0; i < myBids.size(); ++i) {
            	displayBid(myBids.at(i));
            }
            cout << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
