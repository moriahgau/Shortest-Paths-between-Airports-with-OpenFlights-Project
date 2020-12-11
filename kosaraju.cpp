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
  graph = g.getGraph();

  //BFS code from 'DrawGraph.cpp'
  bool *visited = new bool[all_airports.size()];
  for(unsigned long i = 0; i < all_airports.size(); i++)
      visited[i] = false; //mark all vertices are not visited
  list<int> queue;
  visited[start] = true; //current node as visited and enqueue it
  queue.push_back(start);
  list< pair<int, int> >::iterator i;
  while (!queue.empty()) {
    //start = queue.front();
    //cout << start << " ";
    queue.pop_front(); //dequeue vertex
    for (i = adj[start].begin(); i != adj[start].end(); ++i) {
      if (!visited[(*i).first]) {
        visited[(*i).first] = true;
        queue.push_back((*i).first);
      }
    }
  }
  //end of BFS

  //case: BFS doesn't visit all vertices
  if (find(visited.begin(), visited.end(), false) != visited.end()) return false;

  //reverse all edges
  transpose = graph.getTranspose(graph); //from 'graph.h'

  //reset visited vector
  fill(visited.begin(), visited.end(), false);

  //copied and pasted from above
  //BFS
  list<int> queue;
  visited[start] = true; //current node as visited and enqueue it
  queue.push_back(start);
  list< pair<int, int> >::iterator i;
  while (!queue.empty()) {
    //start = queue.front();
    //cout << start << " ";
    queue.pop_front(); //dequeue vertex
    for (i = adj[start].begin(); i != adj[start].end(); ++i) {
      if (!visited[(*i).first]) {
        visited[(*i).first] = true;
        queue.push_back((*i).first);
      }
    }
  }
  //end of BFS

  //case: BFS doesn't visit all vertices
  if (find(visited.begin(), visited.end(), false) != visited.end()) return false;

  return true;
}
