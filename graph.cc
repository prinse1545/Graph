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

      vector<pair<int, int>> edges;

      adjacencyList.insert({ i, edges });
    }

    int count = 0;


    while(!f.eof()) {
      getline(f, line);

      vector<int> vec;

      for(int i = 0; i < line.length(); i++) {
        int val = int(line[i]) - 48;
        //Making adjacency list
        if(val > 0) {
          pair<int, int> edge;

          edge.first = i;
          edge.second = count;

          adjacencyList[count].push_back(edge);
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
    int u;
    u = s.pop();

    for(int i = 0; i < adjacencyList[u].size(); i++) {

      if(coloring[adjacencyList[u][i].second] == false) {
        coloring[adjacencyList[u][i].second] = true;
        s.push(adjacencyList[u][i].second);
      }
    }

    cout << "Visited: " << u << endl;
  }
}
