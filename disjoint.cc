#include "disjoint.h"

template <class T>

Disjoint<T>::Disjoint(T item) {

  Node* to_add = new Node;

  to_add->parent = to_add;
  to_add->item = item;
  to_add->rank = 0;

  container.insert({item, to_add});
}

template <class T>

void Disjoint<T>::makeSet(T item) {

  Node* to_add = new Node;

  to_add->parent = to_add;
  to_add->item = item;
  to_add->rank = 0;

  container.insert({item, to_add});
}

template <class T>

T findSet(T item) {
  Node* ret = findSetHelper(item);

  return ret->item;
}

template <class T>

void union(T x, T y) {

  x = findSet(x);
  y = findSet(y);

  if(container[x]->rank > container[y]->rank) {
    container[y]->parent = container[x];
  }
  else {
    container[x]->parent = container[y]

    if(container[x]->rank == container[y]->rank) {
      container[y]->rank++;
    }
  }

}

template <class T>

Node* findSetHelper(T item) {

  Node* curr = container[item];

  while(curr->parent != curr) {
    curr = curr->parent;
  }

  return curr;
}
