#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Airport {
public:
  Airport(int identifier, string airport, double lat, double long); //constructor

  int airportID; //unique openflight's identifier
  string name; //name of airport

  double latitude; //Decimal degrees, usually to six significant digits. Negative is South, positive is North.
  double longitude; //Decimal degrees, usually to six significant digits. Negative is South, positive is North.

  int getAirportData(); //function to read CSV file for airport information
};
