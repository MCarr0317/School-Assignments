/*  linkedList.h
    Definition of a class for a doubly linked list
    Nathan Eloe & Jennifer Leopold
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include <stdexcept>

template <class T>
class LinkedList
{
  private:
    unsigned int m_size;         // # of nodes in list
    Node<T> *m_head, *m_tail;    // ptrs to first and last nodes in list
    
  public:
    // Purpose: default constructor
    // Postconditions: current size set to 0, head and tail
    // pointers set to NULL
    LinkedList(): m_size(0), m_head(NULL), m_tail(NULL) {}
    
    // Purpose: copy constructor
    // Parameters: cpy is LinkedList that is to be copied
    // Postconditions: this list contains same data values (in same order) as
    // in cpy
    LinkedList(const LinkedList<T>& cpy): 
        m_head(NULL), m_tail(NULL) { *this = cpy; }
    
    // Purpose: destructor
    // Postconditions: current size is now 0, list contains no data,
    // and all memory deallocated (via clear())
    ~LinkedList() { clear(); }

    // Purpose: effectively "empties" the list
    // Postconditions: current size set to 0, head and tail ptrs set to NULL,
    // and all dynamically allocated memory for nodes deallocated
    void clear();
    
    // Purpose: accessor function for head of the list
    // Returns: pointer to the first node in the list; returns NULL if empty
    Node<T>* getHeadPtr() { return m_head; }
    
    // Purpose: accessor function for tail of the list
    // Returns: pointer to the last node in the list; returns NULL if empty
    Node<T>* getTailPtr() { return m_tail; }
    
    // Purpose: accessor function for the current # data values in the list
    // Returns: current size of the list
    unsigned int size() const {return m_size;}
    
    // Purpose: determines whether the list is empty
    // Returns: true if list is empty; otherwise, false
    bool isEmpty() const { return m_size==0; }
    
    // Purpose: determines whether x is in the list
    // Parameters: x is data value to be found
    // Returns: true if x is in the list; otherwise, false
    bool find(const T& x) const;
    
    // Purpose: puts the data value x at the beginning of the list
    // Parameters: x is data value to inserted
    // Postconditions: current size of list incremented by 1, head pointer
    // now points to a node with data value x, the new node's next ptr points 
    // to what was previously the first in the list, and its prev ptr points
    // to NULL; if x is the only value in the list, tail pointer also points 
    // to the new node
    void insertAtHead(const T& x);
    
    // Purpose: puts the data value x at the end of the list
    // Parameters: x is data value to inserted
    // Postconditions: current size of list incremented by 1, tail pointer
    // now points to a node with data value x, the new node's prev ptr points 
    // to what was previously the last in the list, and its next ptr points
    // to NULL; if x is the only value in the list, head pointer also points 
    // to the new node
    void insertAtTail(const T& x);
    
    // Purpose: removes the data value at the beginning of the list
    // Postconditions: current size of list decremented by 1, head pointer
    // now points to whatever the removed node's next ptr was pointing at, and
    // that node's prev ptr is NULL; if list is now empty, tail pointer 
    // is set to NULL
    // Exceptions: if the list is empty, then throw std::length_error
    void removeAtHead();
    
    // Purpose: removes the data value at the end of the list
    // Postconditions: current size of list decremented by 1, tail pointer
    // now points to whatever the removed node's prev ptr was pointing at, and
    // that node's next ptr is NULL; if list is now empty, head pointer 
    // is set to NULL
    // Exceptions: if the list is empty, then throw std::length_error
    void removeAtTail();
    
    // Purpose: starting from the head of the list, removes the first node
    // with data value x
    // Parameters: x is data value whose first occurrence is to be removed
    // Returns: true if an occurrence of x successfully removed; otherwise,
    // false
    // Postconditions: if x was in the list, current size of list decremented 
    // by 1, and the (formerly) first occurrence of x has been removed
    bool removeFirstOccurrence(const T& x);
    
    // Purpose: removes all nodes with data value x
    // Parameters: x is data value to be removed
    // Returns: # of occurrences of x that were removed (0 if none)
    // Postconditions: all occurrence of x have been removed and current size
    // of list updated accordingly
    unsigned int removeAllOccurrences(const T& x);
    
    // Purpose: performs a deep copy of the data from rhs into this linked list
    // Parameters: rhs is linked list to be copied
    // Returns: *this
    // Postconditions: this list contains same data values (in the same order)
    // as are in rhs; any memory previously used by this list has been
    // deallocated
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    
    // Purpose: determines whether this list is identical to rhs list in
    // terms of data values and their order in the list
    // Parameters: rhs is list to be compared to this list
    // Returns: true if lists are identical; otherwise, false
    bool operator==(const LinkedList<T>& rhs) const;
};

#include "linkedList.hpp"

#endif
