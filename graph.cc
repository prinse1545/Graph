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

          adjacencyList[count].push_back(i);
        }
        //Making matrix
        vec.push_back(val);
      }

      adjacencyMatrix.push_back(vec);

      count ++;
    }
  }


}

Graph::Graph(const Graph &g) {
  adjacencyList = g.adjacencyList;
  adjacencyMatrix = g.adjacencyMatrix;
}

void Graph::dfs() {

  vector<bool> coloring;

  for(int i = 0 ; i < adjacencyList.size(); i++) {
    coloring.push_back(false);
  }

  for(pair<int, vector<int>>p : adjacencyList) {

    if(coloring[p.first] != true) {
      cout << "Starting at: " << p.first << endl;
      dfsHelper(p.first, coloring);
    }

    cout << endl;
  }

}

void Graph::dfsHelper(int node, vector<bool> &coloring) {




  coloring[node] = true;

  stack<int> s;
  s.push(node);



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

void Graph::topologicalsort()
{

  queue<int> Q;

  map<int, int> inDegrees;

  for (auto const& x : adjacencyList)
  {
    int inDegree = 0;
    for (auto const& y : adjacencyList)
    {
      for (int i = 0; i < y.second.size(); i++)
      {
        if (y.second[i] == x.first)
        {
          inDegree++;
        }
      }
    }

    inDegrees[x.first] = inDegree;

    if (inDegree == 0)
    {
      Q.push(x.first);
    }
  }

  if (Q.size() == 0) throw CycleError();

  while (Q.size() != 0)
  {
    bool outputHappened = false;
    int u = Q.front();
    Q.pop();
    cout << u << " ";
    outputHappened = true;

    for (int i = 0; i < adjacencyList[u].size(); i++)
    {
      inDegrees[adjacencyList[u][i]] = inDegrees[adjacencyList[u][i]] - 1;

      if (inDegrees[adjacencyList[u][i]] == 0)
      {
        Q.push(adjacencyList[u][i]);
      }
    }
  }

}
