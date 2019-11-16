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

  Graph(const vector<vector<int>> graphMatrix);

  Graph(const Graph &g);

  void dfs();

  int floodFill();

  void topologicalsort();

private:


  map<int, vector<int> > adjacencyList;
  vector<vector<int> > adjacencyMatrix;

  void dfsHelper(int node);
  void floodFillHelper(int node, vector<bool> &coloring, vector<int> &fullGraph);
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

Graph::Graph(const vector<vector<int>> graphMatrix) {

  for(int i = 0; i < graphMatrix.size(); i++) {
    adjacencyMatrix.push_back(graphMatrix[i]);

    vector<int> edges;
    adjacencyList.insert(pair<int,vector<int>>(i, edges));
  }

  for(int i = 0; i < graphMatrix.size(); i++) {

    for(int j = 0; j < graphMatrix[i].size(); j++) {

      if(graphMatrix[i][j] != 0) {
        adjacencyList[i].push_back(j);
      }
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
    cout << "Starting at: " << p.first << endl;
    dfsHelper(p.first, coloring);
    cout << endl;
  }

}

void Graph::dfsHelper(int node, vector<bool> &coloring) {

  if(coloring[node] == true) {
    return;
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

int Graph::floodFill() {

  vector<bool> coloring;
  int count = 0;

  for(pair<int, vector<int>>p : adjacencyList) {
    coloring[p.first] = false;
  }

  for(pair<int, vector<int>>p : adjacencyList) {
    vector<int> fullGraph;
    floodFillHelper(p.first, coloring, fullGraph);

    if(fullGraph.size() > 0) {
      count++;
    }
  }

  return count;

}

void Graph::floodFillHelper(int node, vector<bool> &coloring, vector<int> &fullGraph) {


  if(coloring[node] == true) {
    return;
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

    fullGraph.push_back(u);
  }
}


#endif


int main() {

  string s;
  vector<vector<int>> vec;
  int count = 0;
  int matrixSize = 0;

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

        matrixSize++;
      }
      vec.push_back(temp);
    }
    count++;
  }

  vector<vector<int>> graphMatrix;

  for(int i = 0; i < graphMatrix.size(); i++) {

    for(int j = 0; j < graphMatrix[i].size(); j++) {
      cout << graphMatrix[i][j];
    }

    cout << endl;
  }
  for(int i = 0; i < matrixSize; i++) {

    vector<int> temp;

    for(int j = 0; j < matrixSize; j++) {
      temp.push_back(0);
    }

    graphMatrix.push_back(temp);
  }

  int order = 0;

  for(int i = 0; i < vec.size(); i++) {

    for(int j = 0; j < vec[i].size(); j++) {
      //Checking if lights
      if(vec[i][j] == 1) {
        //Checking adjacency
        if(i > 0 && vec[i - 1][j] == 1) {

          graphMatrix[order][(i - 1) * vec[i].size() + j] = 1;

        }

        if(i != vec.size() - 1 && vec[i + 1][j] == 1) {

          graphMatrix[order][(i + 1) * vec[i].size() + j] = 1;
        }

        if(j > 0 && vec[i][j - 1] == 1) {

          graphMatrix[order][order - 1] = 1;
        }

        if(j != vec[i].size() - 1 && vec[i][j + 1] == 1) {

          graphMatrix[order][order + 1] = 1;
        }
      }

      order++;
    }
  }


  Graph g(graphMatrix);

  cout << g.floodFill() << endl;;




  return 0;
}
