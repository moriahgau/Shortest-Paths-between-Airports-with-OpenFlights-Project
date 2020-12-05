#include <vector>
#include <string>
#include "database.h"

using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::map;
using namespace std;

/*
** Constructor for Airport object.
*/
Airport::Airport(int id, string airportName, double lat, double long) {
  airportID = id;
  name = airportName;
  latitude = lat;
  longitude = long;
}

/*
** Return name of airport given airportID.
*/
string Database::getAiportName(int id) {
  for (auto& plane : all_airports) {
    if (plane.airportID == id) return plane.name;
  }
  return "name not found";
}


/*
** Read airport info from file (airports.dat) and create Airport vector.
**
*/
vector<Airport> Database::getAirportInfo(string filename) { //airports.dat
  ifstream file(filename); // Object to read from file
  file.open(filename, ios::in); // Opening file in input mode

  string temp;
  vector<string> row;
  //vector<Airport> all_airports;
  all_airports.clear(); //clear all_airports data just in case

  while (file) {
    row.clear();
    stringstream s(line);

    while (getline(s, temp, ',')) {
      row.push_back(temp); //put all the column data of a row in 'temp'
    }

    // store data in airport variables
    int identifier = stoi(row[0]); //convert string to integer
    string airportName = row[1];
    double lat = stod(row[6]);
    double long = stod(row[7]);

    // add new Airport to airport vector
    all_airports.push_back(Airport(identifier, airportName, lat, long));
  }

  file.close();
  return all_airports;
}


/*
** Read connections info from file (routes.dat) and create 'connections'.
**
*/
map<int, vector<int>> Database::getConnections(string filename) { //routes.dat
  ifstream file(filename); // Object to read from file
  file.open(filename, ios::in); // Opening file in input mode

  string temp;
  vector<string> row;
  //map<int, vector<int>> connections;
  connections.clear(); //clear connections data just in case

  while (file) {
    row.clear();
    stringstream s(line);

    while (getline(s, temp, ',')) {
      row.push_back(temp); //put all the column data of a row in 'temp'
    }

    //convert string to integer
    int sourceID = stoi(row[3]);
    int destID = stoid(row[5]);

    // if sourceID in map, add destID to vector
    if (connections.count(sourceID) > 0) {
      connections.at(sourceID).push_back(destID); // add destID
    }
    else {     // if sourceID not in map, create new element
      vector<int> dest;
      dest.push_back(destID);
      connections[sourceID] = dest; // create new entry
    }

    // if destID in map, add sourceID to vector
    if (connections.count(destID) > 0) {
      connections.at(destID).push_back(sourceID); // add sourceID
    }
    else {    // if destID not in map, create new element
      vector<int> dest;
      dest.push_back(sourceID);
      connections[destID] = dest;
    }
  }

  file.close();
  return connections;
}
