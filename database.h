#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>

#include "dsets.h"

using namespace std;

class Airport {
public:
  Airport(); //default constructor
  Airport(int id, string airportName, long double lat, long double longi); //constructor

  int airportID; //unique openflight's airport ID
  string name; //name of airport
  long double latitude; //Decimal degrees, usually to six significant digits. Negative is South, positive is North.
  long double longitude; //Decimal degrees, usually to six significant digits. Negative is South, positive is North.
};

class Database {
public:
  vector<Airport> all_airports; //vector of all Airport objects in database
  map<int, pair<long double, long double>> locations; //map of locations of all Airports, locations[20].first = latitude, locations[20].second = longitude
  map<int, vector<int>> connections; //map of < airportID, vector of connected airport IDs >

  DisjointSets scAirports; //disjoint set to keep track of all strongly connected airports with O(1) lookup

  //function declarations

  /*
  ** Returns int airportID of Airport object given name.
  */
  int getAiportID(string airportname);

  /*
  ** Sorts 'all_airports' so that all_airports[0] is the starting point, and all_airports.back() is the ending point.
  */
  void sortAirportsVector(int startingID, int endingID);

  /*
  ** Read CSV file and store info in 'all_airports'.
  ** 'all_airports' has all the Airports in database
  **
  ** example: can iterate through vector
  ** for (auto i : all_airports) {
  **  // 'i.airportID' to get airportID
  ** }
  */
  std::vector<Airport> getAirportInfo(string filename);

  /*
  ** Read CSV file and store info in 'connections'.
  ** 'connections' has all the connected airport info in database
  **
  ** example: can iterate through map
  ** for (auto i : connections) {
  **  // 'i.first' to get the airportID (example: 20)
  **  // 'i.second' to get the vector of airportIDs (example: <5,30,60>) connected to original airportID (example: 20)
  ** }
  */
  std::map<int, std::vector<int>> getConnections(string filename);

  bool isStronglyConnected(int idA, int idB);
  void scHelper();
  void DFS(int vertex);
  void DFSHelper(int vertex);


};
