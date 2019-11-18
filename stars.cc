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
#include <sstream>
#include <queue>

using namespace std;

class Graph {
public:

  Graph(string filename);

  Graph(const vector<vector<int>> graphMatrix);

  Graph(const Graph &g);

  vector<vector<int>> dfs();


  void topologicalsort();

private:


  map<int, vector<int> > adjacencyList;
  vector<vector<int> > adjacencyMatrix;

  vector<int> dfsHelper(int node, vector<bool> &coloring);

};

class CycleError
{
	public:
		std::string message = "CYCLE DETECTED";
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

vector<vector<int>> Graph::dfs() {

  vector<bool> coloring;
  vector<vector<int>> visited;

  for(int i = 0 ; i < adjacencyList.size(); i++) {
    coloring.push_back(false);
  }

  for(pair<int, vector<int>>p : adjacencyList) {

    if(coloring[p.first] != true) {
      vector<int> temp;
      temp = dfsHelper(p.first, coloring);
      visited.push_back(temp);
    }

  }

  return visited;

}

vector<int> Graph::dfsHelper(int node, vector<bool> &coloring) {




  coloring[node] = true;

  vector<int> visitedNodes;
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

    visitedNodes.push_back(u);
  }

  return visitedNodes;
}

void Graph::topologicalsort()
{
  stringstream ss;
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
    ss << u << " ";
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

  cout << ss.str() << endl;
}



#endif


int main() {

  string s;

  int count = 0;

  while(cin >> s)
  {

    int inputHeight;
    stringstream num(s);
    num >> inputHeight;

    cin >> s;

    vector<vector<int>> vec;
    int matrixSize = 0;
    int skyCount = 0;

    for(int i = 0; i < inputHeight; i++) {

      cin >> s;
      vector<int> temp;
      for(int i = 0; i < s.length(); i++) {
        if(s[i] == '#') {
          temp.push_back(0);
          skyCount++;
        }
        else {
          temp.push_back(1);

        }

        matrixSize++;
      }
      vec.push_back(temp);
    }

    vector<vector<int>> graphMatrix;

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

    vector<vector<int>> visited = g.dfs();
    count++;
    cout << "Case " << count << ": " << visited.size() - skyCount << endl;


  }







  return 0;
}
