#ifndef     _LINKEDLIST_H_
# define    _LINKEDLIST_H_

#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
using std::string;
using std::cout;

struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

struct node
{
    Bid dataVal;
    node *next;
};



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

#endif /*!_LINKEDLIST_H_*/