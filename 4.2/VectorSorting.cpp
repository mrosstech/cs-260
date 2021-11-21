//============================================================================
// Name        : VectorSorting.cpp
// Author      : Your name
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <string.h>

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
 * Prompt user for bid information using console (std::in)
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
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
    // The starting point for the quicksort.   We need to 
    // partition the vector into high and low partitions.

    // Initialize variables.
    // Calculate the starting midpoint index for the partition and get the value
    // of the vector at that index.
    int midpoint = begin + (end - begin)/2;
    Bid pivot = bids.at(midpoint);

    // Create a temporary Bid variable for the swaps
    Bid tempBid;

    // Set the low and high positions to the begin and end to start
    int low = begin;
    int high = end;

    // Create a variable to store the 'doneness' of our partition
    // and initialize to 'false'
    bool done = false;


    // DEBUG: cout << "STARTING PARTITION PASS: " << low << ", " << high << ", " << midpoint << endl;
    // Loop until we're done with the partition
    while (!done) {

        // Check the 'low' partition to see if the value at 'low'
        // is less than or equal to the partition value.   If it 
        // is then the value at low is in the right partition.   Move
        // on to the next one and check that.   If it is larger, we need
        // to check the high side to see if there is a value we can swap.
        while (bids.at(low).title < pivot.title) {
            low++;
        }
        // Check from the far right of the vector to the pivot to find any
        // values which are less than the pivot value.
        while (pivot.title < bids.at(high).title) {
            high--;
        }
        // If we've checked all of the high side and all of the low side
        // and everything is in the right place, we're done with the
        // partitioning.
        if (low >= high) {
            done = true;
        } else {
            // DEBUG: cout << "SWAPPING LOW with HIGH" << endl;
            // We're not done, so we need to swap the values that are on the wrong sides.
            tempBid = bids.at(low);
            bids.at(low) = bids.at(high);
            bids.at(high) = tempBid;
            
            // Decrement high and increment low to move on to the next set of values to be compared
            low++;
            high--;
        }


    }

    // return the value of the highest index of the low partition
    // DEBUG: cout << "DONE WITH THIS PARTITION PASS! RETURNING: " << high << endl;
    return high;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
    // DEBUG: cout << "STARTING NEW QUICKSORT PASS: " << begin << ", " << end << endl;
    // Initialize variables
    // Create a midpoint variable to hold the partition
    // midpoint returned from the partition function.
    int mid = 0;

    // Check to see if we only have one element.   If so
    // the section is already sorted.
    if (begin >= end) {
        // DEBUG: cout << "ENDING QUICKSORT PASS BECAUSE ALREADY SORTED!" << endl;
        return;
    }

    // Otherwise we have some work to do.

    // Get the midpoint from the partition funnction
    mid = partition(bids, begin, end);

    // Quicksort both sides of the vector recursively
    quickSort(bids, begin, mid);
    quickSort(bids, mid+1, end);

    return;
}

// FIXME (1a): Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {
    // Create and initalize a lowIndex integer.
    // This represents the index of the lowest value for the inner loop.
    int lowIndex = 0;

    // We also need a temporary Bid value to store the bid for the swap.
    Bid tempValue;

    // And finally initialize our loop variables.
    int i = 0;
    int j = 0;

    // Outer loop to move from left to right in the bids vector.
    for (i = 0; i < bids.size() - 1; i++) {
        lowIndex = i;
        // Inner loop for comparing the value of the data in the outer loop vector position with the rest of the 
        // vector data to find the next lowest value.
        for (j = i+1; j < bids.size(); j++) {
            if (bids.at(j).title < bids.at(lowIndex).title) {
                lowIndex = j;
            }
        }
        // Swap the lowest value into the outer loop vector position.
        tempValue = bids.at(i);
        bids.at(i) = bids.at(lowIndex);
        bids.at(lowIndex) = tempValue;
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
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;
        
        case 3:
            ticks = clock();
            // Sort using the selection sort algorithm
            selectionSort(bids);

            // FIXME (1b): Invoke the selection sort and report timing results
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;


            break;

        case 4:
            ticks = clock();
            quickSort(bids, 0, bids.size()-1);
        // FIXME (2b): Invoke the quick sort and report timing results
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
