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
#define pi 3.14159265358979323846
using namespace std;
//#include <bits/stdc++.h> 

long double toRadians(const long double degree) 
{ 
    long double one_deg = (M_PI) / 180; 
    return (one_deg * degree); 
} 
  
long double distance(long double lat1, long double long1,  
                     long double lat2, long double long2) 
{ 
    lat1 = toRadians(lat1); 
    long1 = toRadians(long1); 
    lat2 = toRadians(lat2); 
    long2 = toRadians(long2); 
    // Haversine
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1; 
    long double ans = pow(sin(dlat / 2), 2) +  
                          cos(lat1) * cos(lat2) *  
                          pow(sin(dlong / 2), 2); 
  
    ans = 2 * asin(sqrt(ans)); 
    long double R = 6371; 
    ans = ans * R; 
  
    return ans; 
}
/**
 * This function creates a graph, `g_` representing all the airports and their connections
 */

DrawGraph::DrawGraph(const std::vector<Airport> & all_airports, const std::map<int, std::vector<int>> & connections) : g_(true, true) {
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

    startingVertex_ = "Airport " + to_string(all_airports[0].airportID); // the starting airport
    for (unsigned int i = 0; i < all_airports.size(); i++)
    {
      g_.insertVertex("Airport " + to_string(all_airports[i].airportID)); 
    }
    while (numairports > 0) { // until iterates through all airports
        for(auto i : connections){

            bool firstFlag = false;
            bool secondFlag = false;
            for (unsigned long j = 0; j < i.second.size(); j++){
                for(unsigned long check = 0; check < all_airports.size(); check++){
                    if(i.first == all_airports[check].airportID){
                        long1 = all_airports[check].longitude;
                        lat1 =  all_airports[check].latitude;
                        firstFlag = true;
                    }
                    if (i.second[j] == all_airports[check].airportID){
                        long2 = all_airports[check].longitude;
                        lat2 =  all_airports[check].latitude;
                        secondFlag = true;
                    }
                    if(firstFlag && secondFlag){
                        int d = distance(lat1, long1, lat2, long2); // cut it down to int
                        g_.insertEdge("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]));
                        g_.setEdgeWeight("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]), d);
                        adj[i.first].push_back(make_pair(i.second[j], d));  // can i directly do this? 
                        adj[i.second[j]].push_back(make_pair(i.first, d));
                        numairports--;
                        break;
                    }
                        firstFlag = false;
                        secondFlag = false;
            
                    int d = distance(lat1, long1, lat2, long2); // cut it down to int
                    g_.insertEdge("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]));
                    g_.setEdgeWeight("Airport " + to_string(i.first), "Airport " + to_string(i.second[j]), d);
                    adj[i.first].push_back(make_pair(i.second[j], d)); 
                    adj[i.second[j]].push_back(make_pair(i.first, d));
                    numairports--;
                }
                if(firstFlag && secondFlag) break;
            }
        }
    }
}

DrawGraph::~DrawGraph(){
    delete[] adj;
    adj = NULL;
    // delete[] visited;
    // visited = NULL;
}

void DrawGraph::shortestPath(int start, const std::vector<Airport> & all_airports) 
{ 
    // following psuedocode from lecture
    // Create a priority queue and initialize everything to infinity and all parents to 0
    priority_queue< airportPair, vector <airportPair> , greater<airportPair> > pqueue; 
    vector<int> dist(all_airports.size()+1, INF); 
    vector<int> parent(all_airports.size()+1, 0);

    dist[start] = 0; 
    pqueue.push(make_pair(0, start));  

    while (pqueue.empty() == false) 
    { 
        int prior = pqueue.top().second; 
        pqueue.pop();  
        // check in adjacent
        for (std::list< pair<int, int> >::iterator i = adj[prior].begin(); i != adj[prior].end(); ++i) 
        { 
            int id = (*i).first; 
            int distance = (*i).second; 
            if (dist[id] > dist[prior] + distance) 
            { 
                dist[id] = dist[prior] + distance; 
                parent[id] = prior;
                pqueue.push(make_pair(dist[id], id)); 
            } 
        } 
    } 
    cout << "Airport Sequence: " << endl; 
    for (unsigned long i = 0; i < parent.size(); i++) 
        printf("% d ->", parent[i]); 
    // i++;   
    // cout << parent[i] << endl;
}  
// Retrieves the graph
const Graph & DrawGraph::getGraph() const {
  return g_;
}

void DrawGraph::BFS(int start, const std::vector<Airport> & all_airports){
    std::list<int> bfsqueue; // airport id
    // bool visited[all_airports.size()] = {false};
    bool *visited = new bool[all_airports.size()]; // will this cause a mem leak? 
    for(int i = 0; i < all_airports.size(); i++)
         visited[i] = false;
    visited[start] = true;
    bfsqueue.push_back(start);
    // list< pair<int, int> >::iterator i; 
    while(bfsqueue.empty() == false)
    {
        int vertex = bfsqueue.front();
        cout << vertex << " ";
        bfsqueue.pop_front();
        // for (i = adj[vertex].begin(); i != adj[vertex].end(); ++i)
    for(std::list< pair<int, int> >::iterator i = adj[vertex].begin(); i != adj[vertex].end(); ++i)
        {
            if (visited[(*i).first] == false)
            {
                visited[(*i).first] = true;
                bfsqueue.push_back((*i).first);
            }
        }
    }
}


