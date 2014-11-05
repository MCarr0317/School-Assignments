/* Vector.h
   Definition of a templated Vector class
   Nathan Eloe (nwe5g8@mst.edu) & Jennifer Leopold (leopoldj@mst.edu)
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>

template <class T>
class Vector
{
  private:  
    unsigned int m_size;      // current # of elements (i.e., data items)
    unsigned int m_max_size;  // current maximum size of vector
    T* m_data;                // data
    
  public:
    // Purpose: default constructor
    // Postconditions: current size and maximum size set to 0, 
    // and data set to NULL
    Vector(): m_size(0), m_max_size(0), m_data(NULL) {}

    // Purpose: copy constructor
    // Parameters: cpy is Vector that is to be copied
    // Postconditions: current size, maximum size, and data set to those of cpy
    Vector(const Vector<T>& cpy) { *this = cpy; }

    // Purpose: destructor
    // Postconditions: current size and maximum size set to 0, 
    // and data set to NULL (via clear())
    ~Vector() { clear(); }

    // Purpose: effectively "empties" the vector
    // Postconditions: current size and maximum size set to 0, 
    // data set to NULL, and all dynamically allocated memory for data is
    // deallocated
    void clear();
    
    // Purpose: puts the value x at the "leftmost available" index in vector
    // Parameters: x is value to be added to vector
    // Postconditions: if current size + 1 == maximum size BEFORE the insertion
    // of x, memory for data is doubled; x now at the formerly "leftmost 
    // available" position in the vector, and current size incremented by 1
    void push_back(const T& x);

    // Purpose: Removes one instance of the value x from the vector if it exists
    // Parameters: x is the value to be removed from the vector
    // Postconditions: if x is in the vector, m_size is decremented and the
    //     first instance of x is removed from the vector. If x is not in the
    //     vector, do nothing.
    //     If m_size <= m_max_size/4, halve the amount of memory available
    void remove(const T& x);

    // Purpose: removes the "last" element in the vector
    // Postconditions: current size decremented by 1, and memory for data is
    // halved if current size / maximum size <= 0.25 AFTER the removal of x
    // Exceptions: if the vector is empty, then throw std::length_error
    void pop_back();

    // Purpose: accessor function for the current # data values in the vector
    // Returns: current size of the vector 
    unsigned int size() const {return m_size;}

    // Purpose: accessor function for the maximum size of the vector
    // Returns: current maximum size of the vector 
    unsigned int max_size() const { return m_max_size; }

    // Purpose: return a read-and-write reference to the element at 
    // the specified position
    // Parameters: i is 0-based index into the vector
    // Returns: the element at position i in the vector
    // Exceptions: if i < 0 or i >= current size, throw 
    // std::out_of_range("i<0 or i>=m_size")
    T& operator[](unsigned int i);

    // Purpose: return a read-only reference to the element at 
    // the specified position
    // Parameters: i is 0-based index into the vector
    // Returns: the element at position i in the vector
    // Exceptions: if i < 0 or i >= current size, throw 
    // std::out_of_range("i<0 or i>=m_size")
    const T& operator[](unsigned int i) const;

    // Purpose: performs a deep copy of the data from rhs into this vector
    // Parameters: rhs is vector to be copied
    // Returns: *this
    // Postconditions: current size, maximum size, and data set to those of
    // rhs
    Vector<T>& operator=(const Vector<T>& rhs);

    //Purpose: Resizes the vector to a max size of NewSize
    //Parameters: NewSize is the desired MAX size of the vector
    //Postconditions: m_data is a vector of size NewSize
    void Resize(int NewSize);
};

#include "Vector.hpp"
#endif

