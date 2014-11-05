/* file test_Vector.cpp
 * author Nathan Eloe (nwe5g8@mst.edu)
 * brief The unit tests for the Vector class
 */
#include "Vector.h"
#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::log;

TEST(VectorTest, CorrectDefaultSize)
{
  Vector<int> a;
  ASSERT_EQ(0,a.size());
}

TEST(VectorTest, CorrectDefaultMaxSize)
{
  Vector<int> a;
  ASSERT_EQ(0,a.max_size());
}

TEST(VectorTest, PushBackSingle)
{
  Vector<int> a;
  a.push_back(3);
  ASSERT_EQ(3,a[0]);
  ASSERT_EQ(1,a.size());
  ASSERT_EQ(a.max_size(),2);
}

TEST(VectorTest, PushBackMulti)
{
  Vector<int> a;
  for (int i=0; i<1000; i++)
  {
    a.push_back(i);
    ASSERT_EQ(i,a[i]);
    ASSERT_EQ(i+1,a.size());
    ASSERT_LE(log(a.max_size()/a.size())/log(2),1.0);
    for (int j=0; j<a.size(); j++)
      ASSERT_EQ(j,a[j]);
  }
}

TEST(VectorTest, BracketReadNegativeIndex)
{
  Vector<int> a;
  ASSERT_THROW(int test = a[-1], std::out_of_range);
}

TEST(VectorTest, BracketReadIndexLargerThanSize)
{
  Vector<int> a;
  ASSERT_THROW(int test = a[3], std::out_of_range);
}

TEST(VectorTest, BracketReadIndexIsSize)
{
  Vector<int> a;
  ASSERT_THROW(int test = a[0], std::out_of_range);
}

TEST(VectorTest, BracketWriteNegativeIndex)
{
  Vector<int> a;
  ASSERT_THROW(a[-1]=1, std::out_of_range);
}

TEST(VectorTest, BracketWriteIndexLargerThanSize)
{
  Vector<int> a;
  ASSERT_THROW(a[3]=1, std::out_of_range);
}

TEST(VectorTest, BracketWriteIndexIsSize)
{
  Vector<int> a;
  ASSERT_THROW(a[0]=1, std::out_of_range);
}

TEST(VectorTest, PopBackSingle)
{
  Vector<int> a;
  a.push_back(1);
  a.pop_back();
  ASSERT_EQ(0,a.size());
  ASSERT_EQ(0,a.max_size());
}

TEST(VectorTest, PopBackMulti)
{
  Vector<int> a;
  for (int i=0; i<1000; i++)
    a.push_back(i);
  for (int i=0; i<1000; i++)
  {
    ASSERT_EQ(1000-i,a.size());
    a.pop_back();
    if (a.size()>0)
        ASSERT_LE(log(a.max_size()/a.size())/log(2),2.0);
    else
        ASSERT_EQ(0,a.max_size());
    for (int j=0; j<a.size(); j++)
      ASSERT_EQ(j,a[j]);
  }
}

TEST(VectorTest, PopBackEmpty)
{
  Vector<int> a;
  ASSERT_THROW(a.pop_back(), std::length_error);
}

TEST(VectorTest, Clear)
{
  Vector<int> a;
  a.push_back(1);
  a.clear();
  ASSERT_EQ(0,a.size());
  ASSERT_EQ(0,a.max_size());
}

TEST(VectorTest, ClearMulti)
{
  Vector<int> a;
  for (int i=0; i<a.max_size(); i++)
  {
    for (int j=0; j<=i; j++)
      a.push_back(j);
    a.clear();
    ASSERT_EQ(0,a.size());
    ASSERT_EQ(0,a.max_size());
  }
}

TEST(VectorTest, ClearEmpty)
{
  Vector<int> a;
  a.clear();
  ASSERT_EQ(0,a.size());
  ASSERT_EQ(0,a.max_size());
}

TEST(VectorTest, AssignmentEmpty)
{
    Vector<int> a,b;
    a=b;
    ASSERT_EQ(0,a.size());
    ASSERT_EQ(0,b.size());
    ASSERT_EQ(0,a.max_size());
    ASSERT_EQ(0,b.max_size());
}

TEST(VectorTest, AssignmentPopulated)
{
    Vector<int> a,b;
    for (int i=0; i<100; i++)
        a.push_back(i);
    b=a;
    ASSERT_EQ(a.size(),b.size());
    ASSERT_EQ(a.max_size(), b.max_size());
    for (int i=0; i<100; i++)
        ASSERT_EQ(a[i],b[i]);
}

TEST(VectorTest, RemoveEmpty)
{
    Vector<int> a;
    a.remove(42);
    ASSERT_EQ(0,a.size());
    ASSERT_EQ(0,a.max_size());
}

TEST(VectorTest, RemoveFirst)
{
    Vector<int> a;
    for (int i=0; i<5; i++)
        a.push_back(i);
    a.remove(0);
    ASSERT_EQ(4,a.size());
    ASSERT_EQ(1,a[0]);
}

TEST(VectorTest, RemoveLast)
{
    Vector<int> a;
    for (int i=0; i<5; i++)
        a.push_back(i);
    a.remove(4);
    ASSERT_EQ(4,a.size());
    ASSERT_EQ(3,a[3]);
}

TEST(VectorTest, RemoveMiddle)
{
    Vector<int> a;
    for (int i=0; i<3; i++)
        a.push_back(i);
    a.remove(1);
    ASSERT_EQ(2,a.size());
    ASSERT_EQ(0,a[0]);
    ASSERT_EQ(2,a[1]);
}
