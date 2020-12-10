/**
 * @file DrawGraph.cpp
 */

#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include "graph.h"
#include "edge.h"
#include "database.h"
using namespace std;

typedef pair<int, int> airportPair;
class DrawGraph {

  public:
    DrawGraph(const std::vector<Airport> & all_airports, const std::map<int, std::vector<int>> & connections);
    ~DrawGraph();
    const Graph & getGraph() const;
    void shortestPath(int src, const std::vector<Airport> & all_airports);
    void BFS(int start, const std::vector<Airport> & all_airports);
  private:
    Graph g_;
    Vertex startingVertex_;
    std::list<pair<int, int>> *adj;
};
