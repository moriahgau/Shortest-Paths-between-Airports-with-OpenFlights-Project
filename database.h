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

  std::vector<std::pair(int, std::string)> identify_airport; //pairs 'airportID' and 'name'

  std::vector<Airport> getAirportInfo(string filename); //function to read CSV file for airport information
  std::map<int, std::vector<int>> getConnections(string filename); //'airportID' with connected airportIDs
};
