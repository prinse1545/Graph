// Philipp & Austin
// 13.11.2019
// Filename: graph.cc
// Description: This file implements a graph as described in graph.h

#include "graph.h"

Graph::Graph(string filename) {

  ifstream f;

  f.open(filename);

  if(f.is_open()) {
    string line;
    getline(f, line);

    int size = int(line[0]) - 48;

    for(int i = 0; i < size; i++) {

      vector<int> edges;

      adjacencyList.insert(pair<int, vector<int> >(i, edges));
    }

    int count = 0;


    while(!f.eof()) {
      getline(f, line);

      vector<int> vec;

      for(int i = 0; i < line.length(); i++) {
        int val = int(line[i]) - 48;
        //Making adjacency list
        if(val > 0) {

          adjacencyList[count].push_back(count);
        }
        //Making matrix
        vec.push_back(val);
        adjacencyMatrix.push_back(vec);
      }

      count ++;
    }
  }

}

void Graph::dfs() {

  vector<bool> coloring;

  for(int i = 0 ; i < adjacencyList.size(); i++) {
    coloring.push_back(false);
  }

  coloring[0] = true;

  stack<int> s;
  s.push(0);



  while(!s.empty()) {
    int u = s.top();
    s.pop();

    for(int i = 0; i < adjacencyList[u].size(); i++) {

      if(coloring[adjacencyList[u][i]] == false) {
        coloring[adjacencyList[u][i]] = true;
        s.push(adjacencyList[u][i]);
      }
    }

    cout << "Visited: " << u << endl;
  }
}
