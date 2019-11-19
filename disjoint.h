// Philipp & Austin
// Filename: disjoint.h
// Description: A header file for the disjonint set class
// 19.11.2019

#ifndef _Disjoint_h
#define _Disjoint_h

#include <iostream>
#include <string>
#include <map>

using namespace std;

template <class T>
class Disjoint {
public:

  Disjoint(T item);

  void makeSet(T item);

  void union(T x, T y);

  T findSet(T item);

private:

  struct Node {
    Node* parent;
    int rank;
    T item;
  };

  map<T, Node*> container;

  Node* findSetHelper(T item);
};



#endif
