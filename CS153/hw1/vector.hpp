#include "vector.h"
#include <stdexcept>
#include <cmath>


template <class T>
void Vector<T>::clear()
{
  delete [] m_data;
  m_data = NULL;
  m_size = 0;
  m_max_size = 0;

  m_data = NULL;

  delete [] m_data;
}

template <class T>
void Vector<T>::push_back(const T& x)
{ 
  int NewSize;
  bool Resize = false;
  if(m_max_size == 0 || m_data == NULL) //if the size is zero, we need to change the max to 2
  { 
    Resize = true;
    NewSize = 2;
  }
  if (m_size + 1 == m_max_size) //if we are about to run out of space, we double the memory
  {
    Resize = true;
    NewSize = m_max_size * 2;
  }

  if (Resize == true)  //resize the vector to NewSize
  {
    this->Resize(NewSize); //Resize the vector
  }

   m_data[m_size] = x; //assign x to the position
   m_size++;  //increase the size
}


template <class T>
void Vector<T>::remove(const T& x)
{
  if (m_data != NULL) //if the array actually has something in it
  {
    int Counter = 1;  //counter so that it only removes the leftmost element
    for (int i = 0;i < Counter;++i) 
    {
      if (m_data[i] == x)
      {
        m_data[i] = m_data[i + 1]; //move everything down
        m_size--; //decrease the size
      }
      else
        Counter++; //if we dont find it once, try again
    }
  }
  if (m_size <= m_max_size / 4)
  {
    this->Resize(ceil(m_max_size / 2)); //Resize the vector
  }
}

template <class T>
void Vector<T>::pop_back()
{
  if (m_data == NULL || m_size == 0)
    throw std::length_error("Size is zero");

  m_size--;

  if(float(m_size)/m_max_size <= 0.25)//
  {
    this->Resize(ceil(m_max_size / 2)); //resizing the vector
  }

}

template <class T>
T& Vector<T>::operator[](unsigned int i)
{
  if (i < 0 || i >= m_size)
  {
    throw std::out_of_range("i<0 or i>=m_size");
  }
  else
    return m_data[i];
}

template <class T>
const T& Vector<T>::operator[](unsigned int i) const
{
  if (i < 0 || i >= m_size)
  {
    throw std::out_of_range("i<0 or i>=m_size");
  }
  else
  {
    T Data_copy;
    Data_copy = m_data[i];

    return Data_copy;
  }
}

template <class T>
void Vector<T>::Resize(int NewSize)
{
  T* temp_data;
  temp_data = new T [NewSize];

  for(int i = 0;i < m_size;++i)
  {
    temp_data[i]= m_data[i];
  }

  m_max_size = NewSize;

  if(m_max_size == 1)
    m_max_size=0;

  delete [] m_data;

  m_data = temp_data;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
  m_size = rhs.m_size;
  m_max_size = rhs.m_max_size;

  m_data = new T[m_max_size];

  //resizing to the same size as rhs so it doesn't segfault
  
  this->Resize(m_max_size);  //resizing the vector

 //then copying over the contents
  for (int i = 0;i < m_size;++i)
  {
    m_data[i] = rhs.m_data[i];
  }

  return *this;
}
