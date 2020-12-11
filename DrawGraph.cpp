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
            
                }
                if(firstFlag && secondFlag) break;
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
    priority_queue< airportPair, vector <airportPair> , greater<airportPair> > pq; 
    vector<int> dist(all_airports.size(), INF); 
    vector<int> parent(all_airports.size(), 0);
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 

    while (!pq.empty()) 
    { 
        int u = pq.top().second; 
        pq.pop(); 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            int v = (*i).first; 
            int weight = (*i).second; 
            if (dist[v] > dist[u] + weight) 
            { 
                dist[v] = dist[u] + weight; 
                parent[v] = u;
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    } 
    printf("Airport Sequence: "); 
    unsigned long i;
    for (i = 0; i < parent.size()-1; ++i) 
        printf("%d->", parent[i]); 
    i++;   
    printf("%d\n", parent[i]);
}  
// Retrieves the graph
const Graph & DrawGraph::getGraph() const {
  return g_;
}

void DrawGraph::BFS(int start, const std::vector<Airport> & all_airports){
    bool *visited = new bool[all_airports.size()];
    for(unsigned long i = 0; i < all_airports.size(); i++)
        visited[i] = false;
    list<int> queue;
    visited[start] = true;
    queue.push_back(start);
    list< pair<int, int> >::iterator i; 
    while(!queue.empty())
    {
        start = queue.front();
        cout << start << " ";
        queue.pop_front();
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


