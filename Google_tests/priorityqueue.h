//
//  Priorityqueue with BST
//
//  priorityqueue.h
//
//	This header file implements a priority queue using a binary search tree that can accept duplicates.
//  Each node in the binary search tree has a priority assigned to it and carries a value based on the context it is
//  implemented in. The smaller the priority integer, the greater the priority. Regardless of the order in which items
//  are added/enqueued, when you remove/dequeue them, the one with the lowest priority number comes out
//  first, then second-lowest, and so on, with the highest-numbered (i.e. lowest priority) item coming
//  out last. If two or more elements in the queue have the same priority, the element that was placed in the queue
//  first has a greater priority. This implementation supports values of different variable types.
//
#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template <typename T>
class priorityqueue
{
private:
    struct NODE
    {
        int priority; // used to build BST
        T value;      // stored data for the p-queue
        bool dup;     // marked true when there are duplicate priorities
        NODE *parent; // links back to parent
        NODE *link;   // links to linked list of NODES with duplicate priorities
        NODE *left;   // links to left child
        NODE *right;  // links to right child
    };
    NODE *root; // pointer to root node of the BST
    int size;   // # of elements in the pqueue
    NODE *curr; // pointer to next item in pqueue (see begin and next)

    //
    // Recursive function called in toString()
    // Inorder traversal through the BST
    // If duplicates exist, output all values with the same priority
    // before moving on to the next node with higher priority.
    // Parameters: root of the tree and type of output stream
    //
    void _pqStream(NODE *current, ostream &output)
    {
        if (current == nullptr) { // base case
            return;
        }
        else
        {
            _pqStream(current->left, output); // recursive call on left subtree
            output << current->priority << " value: " << current->value << endl;
            // Check if there are nodes with the same priority
            if (current->dup) {
                NODE *duplicate = current->link;
                while (duplicate != nullptr) {
                    output << duplicate->priority << " value: " << duplicate->value << endl;
                    duplicate = duplicate->link;
                }
            }
            _pqStream(current->right, output); // recursive call on right subtree
        }
    }

    //
    // Recursive function called in clear()
    // Postorder traversal through the BST
    // If nodes with same priority exist, delete all of them
    // before moving on to the next node with different priority.
    // Parameter: root of the tree
    //
    void _deleteTree(NODE* &current)
    {
        if (current == nullptr) { // base case
            return;
        }

        _deleteTree(current->left);     // recursive call on left subtree
        _deleteTree(current->right);    // recursive call on right subtree

        // Check if there are nodes with the same priority
        // Iterate through the list and delete current node on each iteration
        if (current->link) {
            NODE* nextDup = current->link;
            while (nextDup) {
                delete current;
                current = nextDup;
                nextDup = nextDup->link;
            }
        }
        delete current;
        current = nullptr;
        size = 0;
    }

    //
    // Recursive function called in equality operator
    // Preorder traversal through the BST
    // If nodes with same priority exist, enqueue all of them (going away from the tree)
    // before moving on to the next node with different priority.
    // Parameters: root of tree copying from and the tree(by reference) being copied into
    //
    void _copyTree(NODE* current, priorityqueue<T> &newTree)
    {
        if (current == nullptr) { // base case
            return;
        }
        else {
            newTree.enqueue(current->value, current->priority);
            // Check if there are nodes with the same priority
            // Iterate through the list until the end
            if (current->dup) {
                NODE *duplicate = current->link;
                while (duplicate) {
                    // Enqueue each node during each iteration
                    newTree.enqueue(duplicate->value, duplicate->priority);
                    duplicate = duplicate->link;
                }
            }
            _copyTree(current->left, newTree);      // recursive call on left subtree
            _copyTree(current->right, newTree);     // recursive call on right subtree
        }
    }

    //
    // Recursive function called in (==) operator
    // Preorder traversal through the BST
    // If duplicates exist, call _duplicatesEqual() which returns true if the duplicate lists are equal
    // Return true if the BSTs match exactly (including values, priorities, size, shape, order, duplicates)
    // Parameters: Both trees that are being compared
    // Starter code for this function adapted from UIC 251 Data Structures 2022, Professor Adam Koehler
    //
    bool _equality(NODE* myCurrent, NODE* otherCurrent) const
    {
        if (myCurrent == nullptr && otherCurrent == nullptr) { // both empty
            return true;
        }
        else if (myCurrent == nullptr) { // left empty but not right
            return false;
        }
        else if (otherCurrent == nullptr) { // right empty but not left
            return false;
        }
        else {
            // 1. Check if value and priority match for the current node
            // 2. If duplicates exists, check if the whole duplicate list matches for the current node
            // 3. Recursive call on left subtree
            // 4. Recursive call on right subtree
            if ((myCurrent->value == otherCurrent->value) &&
                (myCurrent->priority == otherCurrent->priority) &&
                (_duplicatesEqual(myCurrent, otherCurrent)) &&
                (_equality(myCurrent->left, otherCurrent->left)) &&
                (_equality(myCurrent->right, otherCurrent->right))) {
                return true;
            }
            else {
                return false; // if any part of the tree does not match
            }
        }
    }

    //
    // Called in the recursive _equality() function
    // If nodes with the same priority exist, checks if the list of duplicates are the same for both trees
    // Return true if the list matches exactly (including values, priorities, size, order)
    // Parameters: Both trees that are being compared
    //
    bool _duplicatesEqual(NODE* thisNode, NODE* otherNode) const
    {
        // First 3 if statements, compares if list is same size-wise
        while (true) {
            // Neither has duplicates OR reached the end of duplicate list and size of the list matches
            if (thisNode->link == nullptr && otherNode->link == nullptr) {
                return true;
            }
            else if (thisNode->link == nullptr) { // one has duplicate(s) and other does not
                return false;
            }
            else if (otherNode->link == nullptr) { // one has duplicate(s) and other does not
                return false;
            }
            // If either value or priority do not match while iterating through the list, end loop and return
            else if ((thisNode->value != otherNode->value) || (thisNode->priority != otherNode->priority)) {
                return false;
            }
            // Progress to the next node in the list for both trees
            thisNode = thisNode->link;
            otherNode = otherNode->link;
        }
    }

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue()
    {
        size = 0;
        root = nullptr;
        curr = nullptr;
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue &operator=(const priorityqueue &other)
    {
        if (this != &other) {   // if not assigning to itself
            this->clear();
            _copyTree(other.root, *this);
        }
        return *this;
    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear()
    {
        _deleteTree(root);
    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue()
    {
        clear();
    }

    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    // Parameters: value and priority to be inserted
    // Starter code for this function adapted from UIC 251 Data Structures 2022, Professor Adam Koehler
    //
    void enqueue(T value, int priority)
    {
        NODE *current = root;
        NODE *previous = nullptr;

        // Search for the correct location of insertion
        // Keep track of previous node to make links with parent and left/right child pointer
        while (current != nullptr)
        {
            previous = current;
            if (priority == current->priority) // priority exists
            {
                current = current->link;
            }
            else if (priority < current->priority) // go left
            {
                current = current->left;
            }
            else { // go right
                current = current->right;
            }
        }

        // Initialize a new node to be inserted
        NODE *newNode = new NODE();
        newNode->value = value;
        newNode->priority = priority;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->link = nullptr;
        newNode->dup = false;

        // If priority exists, make a linked list with duplicate priority
        // else set the new node to be either the left or right child of a leaf
        if (previous == nullptr)                    // Tree is empty
        {
            root = newNode;
            newNode->parent = nullptr;
        }
        else if (priority == previous->priority)    // Connect in linked list of duplicates
        {
            previous->dup = true;
            newNode->dup = true;
            previous->link = newNode;
            newNode->parent = previous;
        }
        else if (priority < previous->priority)     // Insert as left child
        {
            previous->left = newNode;
            newNode->parent = previous;
        }
        else                                        // Insert as right child
        {
            previous->right = newNode;
            newNode->parent = previous;
        }
        size++;
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    // Returns the value that was dequeued
    //
    T dequeue()
    {
        T valueOut{};
        // If queue is empty, return 0 equivalent for all variable types
        if (root == nullptr) {
            return valueOut;
        }
        begin();
        valueOut = curr->value; // Store value before deleting

        // Check for duplicates
        if (curr->link) {
            if (curr == root) {                         // Root has duplicates
                root = curr->link;
                root->right = curr->right;              // Set new root's right child (if exists) OR assign nullptr
                if (curr->right) {                      // If there is a right subtree, set the parent
                    root->right->parent = curr->link;   // of the first right node to be the next duplicate at root
                }
            } else {
                curr->link->parent = curr->parent;
                if (curr == curr->parent->left) {
                    curr->parent->left = curr->link;    // Set the next duplicate to be left child
                } else {
                    curr->parent->right = curr->link;   // Set the next duplicate to be right child
                }
            }
            delete curr;
            begin(); // Allow peek on first element in queue
            size--;
            return valueOut;
        }

        // For nodes with no duplicates OR no duplicates left
        if (curr == root) { // No left subtree, root is next in queue
            root = curr->right;
            if (root) {
                root->parent = nullptr;
            }
        }
        else {  // Remove node if right subtree does not exist
            if (curr->right == nullptr) {
                curr->parent->left = nullptr;
            }
            else { // Right subtree exists, link right subtree's root to the parent of the current node
                curr->parent->left = curr->right;
                curr->right->parent = curr->parent;
            }
        }
        delete curr;
        begin(); // Allow peek on first element in queue
        size--;
        return valueOut;
    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size()
    {
        return size;
    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    void begin()
    {
        if (root) {
            // Set curr to node with the lowest priority number (highest priority)
            NODE *min = root;
            while (min->left != nullptr) {
                min = min->left;
            }
            this->curr = min;
        }
    }

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    // Parameters: value and priority (by reference) to set before assigning new successor
    //
    bool next(T &value, int &priority) {
        if (curr == nullptr) { // all elements accounted for, requires resetting with begin()
            return false;
        }

        // Store value and priority before setting curr to the next successor
        value = curr->value;
        priority = curr->priority;

        // Check for duplicates
        // Assign successor left to right
        if (curr->dup) {
            if (curr->link != nullptr) // Duplicate priorities still exist
            {
                curr = curr->link;
                return true;
            }
            else {  // Reached end of the duplicate list
                // Reset curr to the duplicate node in the BST
                // The rest of the code will further set curr to the next successor
                while ((curr->parent != nullptr) && (curr->priority == curr->parent->priority)) // get back to BST
                {
                    curr = curr->parent;
                }
            }
        }

        // Move curr to the next inorder node in anticipation of future calls to next()
        if (curr->right != nullptr) {           // if there is a right subtree
            curr = curr->right;                 // move to the right subtree's root
            while (curr->left != nullptr) {     // go to the left most child in the subtree
                curr = curr->left;
            }
        }
        else if (curr->parent == nullptr) {     // At the root with no right tree
            curr = nullptr;
        }
        else {
            // For comparing priorities when traversing up the queue
            NODE *tempNode = curr;
            // Move up the tree until you see a node that is a left child
            while ((curr->parent != nullptr) && (curr == curr->parent->right)) {
                curr = curr->parent;
            }
            // If curr traversed up from a right child until it found a left child
            // OR it didn't traverse up because it is a left child itself
            if ((tempNode->priority >= curr->priority) && (curr->parent != nullptr)) {
                curr = curr->parent;
            }
            else { // curr traversed up to the root from the last node in queue
                curr = nullptr;
            }
        }
        return true;
    }

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString()
    {
        stringstream ss;
        _pqStream(root, ss);
        return ss.str();
    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    // Return the value at the top of the priority queue
    //
    T peek()
    {
        T valueOut{};
        if (root != nullptr) {
            begin();
            valueOut = curr->value;
        }
        return valueOut;
    }

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    // Returns true if 2 BSTs are exactly the same
    //
    bool operator==(const priorityqueue &other) const
    {
        return _equality(this->root, other.root);
    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void *getRoot()
    {
        return root;
    }
};