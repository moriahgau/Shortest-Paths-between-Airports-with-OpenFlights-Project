#pragma once
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Airport {
public:
  Airport(int id, string airportName, double lat, double long); //constructor

  int airportID; //unique openflight's airport ID
  string name; //name of airport
  double latitude; //Decimal degrees, usually to six significant digits. Negative is South, positive is North.
  double longitude; //Decimal degrees, usually to six significant digits. Negative is South, positive is North.
};

class Database {
public:
  std::vector<Airport> all_airports;
  std::map<int, std::vector<int>> connections;

  //function declarations
  //returns airport name given id
  std::string getAiportName(int id);

  //function to read CSV file and return a vector of all Airport objects
  std::vector<Airport> getAirportInfo(string filename);

  //returns map of 'airportID' with connected airportIDs
  std::map<int, std::vector<int>> getConnections(string filename);


};
