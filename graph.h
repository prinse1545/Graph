// Philipp & Austin
// 13.11.2019
// Filename: graph.h
// Description: This file implements a graph using an adjacency list
// to store th graph and an adjacency matrix to store its weights

#ifndef _Graph_h
#define _Graph_h

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <utility>

using namespace std;

class Graph {
public:

  Graph(string filename);

  void dfs();

  void bfs();

  void topologicalsort();

private:


  map<int, vector< pair<int, int> > > adjacencyList;
  vector<vector<int>> adjacencyMatrix;
};
#endif
