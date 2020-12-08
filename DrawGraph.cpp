/**
 * @file DrawGraph.cpp
 * CS 225: Data Structures
 */
#define INF 99999999999
#include "DrawGraph.h"
#include "database.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
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

DrawGraph::DrawGraph(const std::vector<Airport> & all_airports, const std::map<int, std::vector<int>> & connections) : g_(true, true) {
    /* Your code goes here! */
    //getAirportinfo? 
    long double long1, long2, lat1, lat2;
//     std::vector<Airport> all_airports;
//     std::map<int, std::vector<int>> connections;
// //     std::string getAiportName(int id);
// //     all_airports = getAirportInfo(filename);
// //     std::map<int, std::vector<int>> getConnections(string filename);
//     std::vector<Airport> getAirportInfo(string filename);
//     std::map<int, std::vector<int>> getConnections(string filename);
    // std::map<int, int> indextoairport;
    int numairports = all_airports.size();
    // std::list<pair<int, int>> *adj;
    adj = new list <airportPair> [numairports];
    // indextoairport.clear();
    // maptoadj.clear();
    startingVertex_ = "Airport " + to_string(all_airports[0].airportID); // the starting airport
    for (unsigned int i = 0; i < all_airports.size(); i++)
    {
      g_.insertVertex("Airport " + to_string(all_airports[i].airportID));  // will this overwrite or make two?
    //   indextoairport.insert(pair<int, int>(i, all_airports[i].airportID));
    }
    // for(auto it: indextoairport){ 

    // }
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
                    adj[i.first].push_back(make_pair(i.second[j], d));  // can i directly do this? 
                    adj[i.second[j]].push_back(make_pair(i.first, d));
                    numairports--;
                }
            }
        }
    }
}

DrawGraph::~DrawGraph(){
    delete[] adj;
    adj = NULL;
}

void DrawGraph::shortestPath(int src, const std::vector<Airport> & all_airports) 
{ 
    // Create a priority queue to store vertices that 
    // are being preprocessed. 
    priority_queue< airportPair, vector <airportPair> , greater<airportPair> > pq; 
  
    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    vector<int> dist(all_airports.size(), INF); 
  
    // Insert source itself in priority queue and initialize 
    // its distance as 0. 
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
  
    /* Looping till priority queue becomes empty (or all 
      distances are not finalized) */
    while (!pq.empty()) 
    { 
        // The first vertex in pair is the minimum distance 
        // vertex, extract it from priority queue. 
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        int u = pq.top().second; 
        pq.pop(); 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            //  If there is shorted path to v through u. 
            if (dist[v] > dist[u] + weight) 
            { 
                // Updating distance of v 
                dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    } 
    printf("Distance from Source to destination"); 
    for (int i = 0; i < all_airports.size(); ++i) 
        printf("%d \t\t %d\n", i, dist[i]); 
} 

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

void DrawGraph::BFS(int start, const std::vector<Airport> & all_airports){
// Mark all the vertices as not visited
    bool *visited = new bool[all_airports.size()];
    for(int i = 0; i < all_airports.size(); i++)
        visited[i] = false;
    // Create a queue for BFS
    list<int> queue;
    // Mark the current node as visited and enqueue it
    visited[start] = true;
    queue.push_back(start);
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list< pair<int, int> >::iterator i; 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        start = queue.front();
        cout << start << " ";
        queue.pop_front();
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited, 
        // then mark it visited and enqueue it
        for (i = adj[start].begin(); i != adj[start].end(); ++i)
        {
            if (!visited[(*i).first])
            {
                visited[(*i).first] = true;
                queue.push_back((*i).first);
            }
        }
    }
}


