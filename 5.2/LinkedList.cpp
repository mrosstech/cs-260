#include <algorithm>
#include <iostream>
#include <time.h>
#include <string>

#include "LinkedList.h"

using std::string;
using std::cout;
using std::endl;

struct node;
struct Bid;

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
        cout << "     " << tempNode->dataVal.title << " | " << tempNode->dataVal.amount << " | " << tempNode->dataVal.fund << endl;
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
    // Is the head node being removed?
    if (this->head->dataVal.bidId == bidId) {
        tempNode = this->head->next;
        // Set the head node to the next node
        this->head = tempNode;
        if (tempNode == 0) {
            // we removed the last list item so set the tail to 0
            this->tail = 0;
        }
        // Exit because we're done!
        return;
    }
 
    // Is the next node 0?   (1 node list)
    if (tempNode->next == 0) {
        // return because we've already checked the head
        return;
    }
   // Otherwise it's not the head so loop through all of the other nodes.
    // Loop while the current node is not set to 0 (end of list)
    while (tempNode != 0) {
        // If the next node has the matching bidId
        if (tempNode->next->dataVal.bidId == bidId) {
            // Check to see if the next -> next node is the tail
            if (tempNode->next == this->tail) {
                tempNode->next = 0;
                this->tail = tempNode;
                return;
            }
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