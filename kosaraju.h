#pragma once
#include "DrawGraph.h"
#include "graph.h"
#include "edge.h"
#include "database.h"

#include <vector>

/*
** DFS traversal for Kosaraju's.
*/
//void DFS(Graph const &graph, int v, vector<bool> &visited);

/*
** Use Kosaraju’s BFS based simple algorithm that does two BFS traversals of
** graph to find whether a graph is strongly connected or not.
*/
bool simpleKosaraju(DrawGraph g, int start, const vector<Airport> & all_airports);
