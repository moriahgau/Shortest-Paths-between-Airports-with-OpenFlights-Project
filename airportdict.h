#pragma once
#include <iostream>
#include <fstream>

#include <map>
#include <vector>

#include "database.h"

class AirportDict{
public:
  std::map<int, std::vector<int>> connections; //airportID with connected airportIDs

  AirportDict();

  int getConnectionsDict(string filename);

};
