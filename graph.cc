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
