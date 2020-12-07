/**
 * @file DrawGraph.cpp
 * CS 225: Data Structures
 */

#include "DrawGraph.h"
#include "database.h"
#include <iostream>
#include <cmath>
#include <ctime>
#define pi 3.14159265358979323846
using namespace std;
#include <bits/stdc++.h> 
  
// Utility function for  
// converting degrees to radians 
long double toRadians(const long double degree) 
{ 
    // cmath library in C++  
    // defines the constant 
    // M_PI as the value of 
    // pi accurate to 1e-30 
    long double one_deg = (M_PI) / 180; 
    return (one_deg * degree); 
} 
  
long double distance(long double lat1, long double long1,  
                     long double lat2, long double long2) 
{ 
    // Convert the latitudes  
    // and longitudes 
    // from degree to radians. 
    lat1 = toRadians(lat1); 
    long1 = toRadians(long1); 
    lat2 = toRadians(lat2); 
    long2 = toRadians(long2); 
      
    // Haversine Formula 
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1; 
  
    long double ans = pow(sin(dlat / 2), 2) +  
                          cos(lat1) * cos(lat2) *  
                          pow(sin(dlong / 2), 2); 
  
    ans = 2 * asin(sqrt(ans)); 
  
    // Radius of Earth in  
    // Kilometers, R = 6371 
    // Use R = 3956 for miles 
    long double R = 6371; 
      
    // Calculate the result 
    ans = ans * R; 
  
    return ans; 
}
/**
 * Constructor to create a game of Nim with `numairports` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param numairports The number of starting tokens in the game of Nim.
 */

DrawGraph::DrawGraph(string filename) : g_(true, true) {
    /* Your code goes here! */
    //getAirportinfo? 
    long double long1, long2, lat1, lat2;
    std::vector<Airport> all_airports;
    std::map<int, std::vector<int>> connections;
//     std::string getAiportName(int id);
//     all_airports = getAirportInfo(filename);
//     std::map<int, std::vector<int>> getConnections(string filename);
    std::vector<Airport> getAirportInfo(string filename);
    std::map<int, std::vector<int>> getConnections(string filename);
    airports = all_airports;
    connects = connections;
    startingVertex_ = "Airport " + to_string(all_airports[0].airportID); // the starting airport
    int numairports = all_airports.size();
    for (unsigned i = 0; i < all_airports.size(); i++)
    {
      g_.insertVertex("Airport " + to_string(all_airports[i].airportID));  // will this overwrite or make two?
    }
    while (numairports > 0) { // until iterates through all airports
        for(auto i : connections){
            for (int j = 0; j < i.second.size(); j++){
                for(int check; check < all_airports.size(); check++){
                    if(i.first == all_airports[check].airportID){
                        long1 = all_airports[check].longitude;
                        lat1 =  all_airports[check].latitude;
                    }
                    if (i.second[j] == all_airports[check].airportID){
                        long2 = all_airports[check].longitude;
                        lat2 =  all_airports[check].latitude;
                    }
                    int d = distance(lat1, long1, lat2, long2); // cut it down to int
                    g_.insertEdge("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]));
                    g_.setEdgeWeight("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]), d);
                    numairports--;
                }
            }
        }
    }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
//don't think need this function either
// std::vector<Edge> DrawGraph::drawsConnections() const {
//   vector<Edge> path;
//  /* Your code goes here! */
//  Vertex vertex = startingVertex_;
//  Vertex temp = startingVertex_;
//  int i = 0;
//  while(temp != "Airport " + to_string(airports.back().airportID) && i < airports.size()){
//     vertex = "Airport " + to_string(airports[i].airportID);
//     path.push_back(g_.getEdge(temp, vertex));
//     temp = vertex;
//     i++;
//  }
//   return path;
// }


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
// i don't think we need this? 
// void DrawGraph::updateEdgeWeights(const std::vector<Edge> & path) {
//  /* Your code goes here! */
//  // if player 1 wins
//  if (path.back().dest == "Airport " + vector.back()){   // end of the path
//   for(size_t i = 0; i < path.size(); i++){
//    if (i%2 == 0){
//      g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest)+1);
//    }
//    else
//     g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest)-1);
//   }
//  }
//  // if player 2 wins
//  else if (path.back().dest == "p1-0"){
//    for(size_t i = 0; i < path.size(); i++){
//      if (i%2 == 0){
//        g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest)-1); // -1 for player 1
//      }
//      else
//       g_.setEdgeWeight(path[i].source, path[i].dest, g_.getEdgeWeight(path[i].source, path[i].dest)+1); // +1 for player 2
//    }
//  }
// }
// 

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
// I don't think we need this? 
// void DrawGraph::labelEdgesFromThreshold(int threshold) {
//   for (const Vertex & v : g_.getVertices()) {
//     for (const Vertex & w : g_.getAdjacent(v)) {
//       int weight = g_.getEdgeWeight(v, w);

//       // Label all edges with positve weights as "WINPATH"
//       g_.setEdgeLabel(v, w, "weight");
//     //   if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
//     //   else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
//     }
//   }
// }

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & DrawGraph::getGraph() const {
  return g_;
}
