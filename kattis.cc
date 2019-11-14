// Philipp & Austin
// 13.11.2019
// Filename: kattis.h
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

  Graph(const Graph &g);

  void dfs();

  void bfs();

  void topologicalsort();

private:


  map<int, vector<int> > adjacencyList;
  vector<vector<int> > adjacencyMatrix;

  void dfsHelper(int node);
};


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

  for(pair<int, vector<int>>p : adjacencyList) {
    cout << "Starting at: " << p.first << endl;
    dfsHelper(p.first);
    cout << endl;
  }

}

void Graph::dfsHelper(int node) {
  vector<bool> coloring;

  for(int i = 0 ; i < adjacencyList.size(); i++) {
    coloring.push_back(false);
  }

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

#endif


int main() {

  string s;
  vector<vector<int>> vec;
  int count = 0;
  int graphSize = 0;

  while(cin >> s)
  {
    if(count > 1) {
      vector<int> temp;
      for(int i = 0; i < s.length(); i++) {
        if(s[i] == '#') {
          temp.push_back(0);
        }
        else {
          temp.push_back(1);
        }

        graphSize++;
      }
      vec.push_back(temp);
    }
    count++;
  }

  cout << graphSize << endl;


  return 0;
}
