#include "kosaraju.h"

#include <vector>
#include <algorithm>

/*
** DFS function for Kosaraju algorithm.
*/
// void DFS(Graph const &graph, int v, vector<bool> &visited)
// {
//   // mark current node as visited
//   visited[v] = true;
//
//   for (int u : graph.adjList[v]) {
//     if (!visited[u]) DFS(graph, u, visited);
//   }
// }

/*
** Use Kosaraju’s BFS based simple algorithm that does two BFS traversals of
** graph to find whether a graph is strongly connected or not.
*/
bool simpleKosaraju(DrawGraph g, int start, const vector<Airport> & all_airports) {
  Graph graph = g.getGraph();

  //BFS code from 'DrawGraph.cpp'
  vector<bool> visited;
  vector<vector<pair<int, int>>> adj = g.getAdj();

  for(unsigned long i = 0; i < all_airports.size(); i++)
      visited.push_back(false); //mark all vertices are not visited
  list<int> queue1;
  visited[start] = true; //current node as visited and enqueue it
  queue1.push_back(start);
  list< pair<int, int> >::iterator i;
  while (!queue1.empty()) {
    //start = queue.front();
    //cout << start << " ";
    queue1.pop_front(); //dequeue vertex
    for (auto i = adj[start].begin(); i != adj[start].end(); ++i) {
      if (!visited[(*i).first]) {
        visited[(*i).first] = true;
        queue1.push_back((*i).first);
      }
    }
  }
  //end of BFS

  //case: BFS doesn't visit all vertices
  if (find(visited.begin(), visited.end(), false) != visited.end()){
    cout<< "first"<< endl;
    return false;
  } 
  

  //reverse all edges in adj directly
  vector<vector<pair<int, int>>> transposeAdj;

  transposeAdj.resize(all_airports.size());

  for(unsigned long initSrc = 0; initSrc < adj.size(); initSrc++){
    for(auto initDest = adj[initSrc].begin(); initDest != adj[initSrc].end(); initDest++){
      transposeAdj[initDest->first].push_back(make_pair(initSrc, initDest->second));
    }
  }


  //reset visited vector
  fill(visited.begin(), visited.end(), false);

  //copied and pasted from above
  //BFS
  list<int> queue2;
  visited[start] = true; //current node as visited and enqueue it
  queue2.push_back(start);
  while (!queue2.empty()) {

    queue2.pop_front(); //dequeue vertex
    for (auto i = transposeAdj[start].begin(); i != transposeAdj[start].end(); ++i) {
      if (!visited[(*i).first]) {
        visited[(*i).first] = true;
        queue2.push_back((*i).first);
      }
    }
  }
  //end of BFS

  //case: BFS doesn't visit all vertices
  if (find(visited.begin(), visited.end(), false) != visited.end()) return false;

  return true;
}
