/**
 * @file DrawGraph.cpp
 * CS 225: Data Structures
 */
#define INF 999999999
#include "DrawGraph.h"
#include "database.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#define pi 3.14159265358979323846
using namespace std;
//#include <bits/stdc++.h> 
// helper function for distance calculation to convert to radians from degrees
long double toRadians(const long double degree) 
{ 
    long double deg = (M_PI) / 180; 
    deg = (deg * degree); 
    return deg;
} 
  
// helper function to calculate distance using Haversine
long double distance(long double lat1, long double long1,  
                     long double lat2, long double long2) 
{ 
    //conversions from degrees to radians
    lat1 = toRadians(lat1);
    long1 = toRadians(long1); 
    lat2 = toRadians(lat2); 
    long2 = toRadians(long2); 
    // Haversine formula to find distance between two locations
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1; 
    long double distance = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2); 
    distance = 2 * asin(sqrt(distance)); 

    long double radiusofearth = 6371; 
    return distance * radiusofearth; //return the found distance between the two points
} 
/**
 * This function creates a graph, `g_` representing all the airports and their connections
 */

DrawGraph::DrawGraph(const std::vector<Airport> & all_airports, const std::map<int, std::vector<int>> & connections) : g_(true, true) {
    long double long1, long2, lat1, lat2;

    int numAirports = all_airports.size();

    //init adj
    adj.resize(numAirports + 1); 

    startingVertex_ = "Airport " + to_string(all_airports[0].airportID); // the starting airport
    for (unsigned int i = 0; i < all_airports.size(); i++)
    {
      g_.insertVertex("Airport " + to_string(all_airports[i].airportID)); 
    }
    while (numAirports > 0) { // until iterates through all airports
        for(auto i : connections){
            
            //flag to skip invalid airportIDs as passed in from database 
            bool firstFlag = false;
            //find long/lat data for first
            for(unsigned long firstCheck = 0;  firstCheck < all_airports.size(); firstCheck++){
                if(i.first == all_airports[firstCheck].airportID){
                    if(i.first == -1) break;
                    long1 = all_airports[firstCheck].longitude;
                    lat1 =  all_airports[firstCheck].latitude;
                    firstFlag = true;
                }
            }

            //find long/lat data for second
            if(firstFlag){
                for (unsigned long j = 0; j < i.second.size(); j++){
                    for(unsigned long secondCheck = 0; secondCheck < all_airports.size(); secondCheck++){
                        if (i.second[j] == all_airports[secondCheck].airportID){
                            if(i.second[j] == -1) break;
                            long2 = all_airports[secondCheck].longitude;
                            lat2 =  all_airports[secondCheck].latitude;
                        
                            //add connection to graph (first data is already ready)
                            int d = distance(lat1, long1, lat2, long2); // cut it down to int
                            g_.insertEdge("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]));    // create corresponding edge and its weight
                            g_.setEdgeWeight("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]), d);
                            adj[i.first].push_back(make_pair(i.second[j], d)); // add connected airport and distance to adjacency
                            numAirports--;
                        }
                    }
                }
            }



        }
    }
}
/**
 * Destructor for the airport graph
 */
DrawGraph::~DrawGraph(){
    adj.clear();
}
/**
 * Shortest path function by using Dijkstra's Algorithm
 */
void DrawGraph::shortestPath(int start, int dest, const std::vector<Airport> & all_airports) 
{ 
    // following psuedocode from lecture
    // Create a priority queue and initialize everything to infinity and all parents to 0
    priority_queue< airportPair, vector <airportPair> , greater<airportPair> > pqueue; 
    vector<int> dist(all_airports.size()+1, INF); 
    vector<int> parent(all_airports.size()+1, 0);   // initialize all distances to infinity and parent to 0

    dist[start] = 0; 
    pqueue.push(make_pair(0, start));  

    while (pqueue.empty() == false) 
    { 
        int prior = pqueue.top().second; 
        pqueue.pop();  
        // check in adjacent
        for (auto i = adj[prior].begin(); i != adj[prior].end(); ++i) //iterate through adj
        { 
            int id = (*i).first; 
            int distance = (*i).second; 
            if (dist[id] > dist[prior] + distance) // check to see if the distance is smaller
            { 
                dist[id] = dist[prior] + distance; // add to the total distance
                parent[id] = prior;  // track where it came from
                pqueue.push(make_pair(dist[id], id)); 
            } 
        }
    } 
    if(dist[dest] == 999999999){
        cout<< "Airport is not reachable"<< endl;
        return;
    }
    cout<< "Shortest Distance between "<< start<< " and "<< dest<< " is: "<< dist[dest]<< endl;
    cout<< "This path is: "<< endl;
    
    int back = dest;
    std::stack<int> path;
    // Backtracking to print the correct sequence
    while(back != start){
        path.push(parent[back]);
        back = parent[back];
    } 
    
    while(!path.empty()){
        cout<< path.top()<< "->";
        path.pop();
    }

    cout<< dest<< endl;
}  
// Retrieves the graph
const Graph & DrawGraph::getGraph() const {
  return g_;
}
// Retrieves adj
const vector<vector<pair<int, int>>> DrawGraph::getAdj() const{
    return adj;
}
/**
 * BFS traversal through the entire airport graph
 */
void DrawGraph::BFS(int start, const std::vector<Airport> & all_airports){
    std::list<int> bfsqueue; // airport id
    vector<int> path;
    bool *visited = new bool[all_airports.size()+1]; // will this cause a mem leak? 
    for(unsigned long i = 0; i < all_airports.size()+1; i++)
         visited[i] = false;    // set everything as initially unvisited
    visited[start] = true;  // initialize only the starting airport to be visited
    bfsqueue.push_back(start);
    
    while(bfsqueue.empty() == false)
    {
        int vertex = bfsqueue.front();
        path.push_back(vertex); // push visited airport to the path vector
        bfsqueue.pop_front();
    for(auto i = adj[vertex].begin(); i != adj[vertex].end(); ++i)   // iterate through adjacent airports
        {
            if (visited[(*i).first] == false)   // confirm the airport has not yet been visited
            {
                visited[(*i).first] = true; // set as visited
                bfsqueue.push_back((*i).first); // push the airport index to the queue
            }
        }
    }
    unsigned long index;
    for (index = 0; index < path.size() - 1; index++){  // iterate to printout path sequence
        cout << path[index] <<", ";
    }

    cout<< path[index]<< endl;

    delete[] visited;   //destroy to remove mem leak possibilities
    visited = NULL;
}



