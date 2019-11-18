
// Philipp & Austin
// 13.11.2019
// Filename: test_graph.cc
// Description: This file tests the Graph class

#include <iostream>
#include "graph.h"
#include <cassert>

using namespace std;

int main() {

  cout << "======== Constructors ========\n\n\n\n";

  cout << "File constructor\n";
  Graph g("sample_graph.txt");

  g.dfs();  // DFS is a void function so cannot make assert

  cout << "Copy constructor\n";
  Graph g2(g);

  g2.dfs();

  cout << "Constructor tests passed\n\n";

  cout << "======== DFS ========\n\n\n\n";

  cout << "First graph DFS output\n";

  g.dfs();  // no cycle in this one

  cout << "Passed\n\nSecond graph DFS output\n";
  Graph g3("graph2.txt"); // there is a cycle in this one
  g3.dfs();
  cout << "Passed\n\n";

  cout << "DFS tests passed\n\n";

  cout << "======== Topological Sort ========\n\n\n\n";

  cout << "Case with cycle\n\n";
 try
 {
    g3.topologicalsort(); // topologicalSort is void so cannot use assert
 }
  catch(CycleError)
  {
    cout << "CYCLE DETECTED\n";
  }

  cout << "Case without cycle\n\n";

  try
  {
    g.topologicalsort();
  }
  catch(CycleError)
  {
    cout << "CYCLE DETECTED\n";
  }

  cout << "Case without cycle 2\n\n";

  Graph g4("graph3.txt");

  try
  {
    g4.topologicalsort();
  }
  catch(CycleError)
  {
    cout << "CYCLE DETECTED\n";
  }


  cout << "Topological sort tests passed\n\n";

  cout << "======== ALL TESTS HAVE BEEN PASSED ========\n\n";
  return 0;
}
