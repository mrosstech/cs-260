//============================================================================
// Name        : Lab1-3.cpp
// Author      : Michael Ross
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 1-3 Up to Speed in C++
//============================================================================

#include <algorithm>
#include <iostream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Use a struct object to contain all of the relevant fields from the bid CSV files.
struct bidItem {
    string articleTitle;
    int articleID;
    string department;
    string closeDate;
    double winningBid;
    string inventoryID;
    string vehicleID;
    string receiptNumber;
    string fund;
};


/**
 * Display the bid information
 *
 * @param bidItem data structure containing the bid info
 */
void displayBid(bidItem myBidItem) {
    cout << "Title: " << myBidItem.articleTitle << endl;
    cout << "Fund: " << myBidItem.fund << endl;
    cout << "Vehicle: " << myBidItem.vehicleID << endl;
    cout << "Bid Amount: " << myBidItem.winningBid << endl;

    return;
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
 * Prompt user for bid information
 *
 * @return data structure containing the bid info
 */
bidItem getBid() {
    bidItem readBidItem;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, readBidItem.articleTitle);

    cout << "Enter fund: ";
    cin >> readBidItem.fund;

    cout << "Enter vehicle: ";
    cin.ignore();
    getline(cin, readBidItem.vehicleID);

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    readBidItem.winningBid = strToDouble(strAmount, '$');

    return readBidItem;
}



/**
 * The one and only main() method
 */
int main() {

    // Declare bidItem type to store bid item details
	bidItem myBidItem;

    // loop to display menu until exit chosen
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter Bid" << endl;
        cout << "  2. Display Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            	myBidItem = getBid();
                break;
            case 2:
                displayBid(myBidItem);
                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
