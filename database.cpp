#include <vector>
#include <string>
#include <sstream>
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
Airport::Airport() {
  airportID = 0;
  name = "";
  latitude = 0;
  longitude = 0;
}

Airport::Airport(int id, string airportName, long double lat, long double longi) {
  airportID = id;
  name = airportName;
  latitude = lat;
  longitude = longi;
}

/*
** Return airportID given airport name.
*/
int Database::getAiportID(string airportname) {
  for (auto plane : all_airports) {
    if (plane.name == airportname) return plane.airportID;
  }
  return -1; // invalid
}


/*
** Sorts 'all_airports' so that all_airports[0] is the starting point, and all_airports.back() is the ending point.
*/
void Database::sortAirportsVector(int startingID, int endingID) {
  Airport new_start;
  Airport new_end;
  for (unsigned i = 0; i < all_airports.size(); i++) {
    if (all_airports[i].airportID == startingID) {
      // create a copy Airport object of starting airport and remove from vector
      new_start.airportID = all_airports[i].airportID;
      new_start.name = all_airports[i].name;
      new_start.latitude = all_airports[i].latitude;
      new_start.longitude =  all_airports[i].longitude;
      all_airports.erase(all_airports.begin()+i);
      break;
    }
  }
  for (unsigned i = 0; i < all_airports.size(); i++) {
    if (all_airports[i].airportID == endingID) {
      new_end.airportID = all_airports[i].airportID;
      new_end.name = all_airports[i].name;
      new_end.latitude = all_airports[i].latitude;
      new_end.longitude =  all_airports[i].longitude;
      all_airports.erase(all_airports.begin()+i);
      break;
    }
  }

  all_airports.insert(all_airports.begin(),new_start); // inserts starting Airport to front of vector
  all_airports.push_back(new_end); // puts ending Airport to end of vector
}


/*
** Read airport info from file (airports.dat) and create Airport vector.
**
*/
vector<Airport> Database::getAirportInfo(string filename) { //airports.dat
  ifstream file(filename); // Object to read from file
  file.open(filename, ios::in); // Opening file in input mode

  string temp, line;
  vector<string> row;
  //vector<Airport> all_airports;
  all_airports.clear(); //clear all_airports data just in case
  locations.clear();

  while (getline(file, line)) {
    row.clear();
    stringstream ss(line);

    while (getline(ss, temp, ',')) {
      row.push_back(temp); //put all the column data of a row in 'temp'
    }

    // store data in airport variables
    int identifier = stoi(row[0]); //convert string to integer
    string airportName = row[1];
    long double lat = stod(row[6]);
    long double longi = stod(row[7]);

    // add new Airport to airport vector
    Airport new_obj;
    new_obj.airportID = identifier;
    new_obj.name = airportName;
    new_obj.latitude = lat;
    new_obj.longitude = longi;

    all_airports.push_back(new_obj);

    // add location info to locations map
    pair<long double, long double> loc;
    loc.first = lat;
    loc.second = longi;
    locations[identifier] = loc;
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

  string temp, line;
  vector<string> row;
  //map<int, vector<int>> connections;
  connections.clear(); //clear connections data just in case

  while (getline(file, line)) {
    row.clear();
    stringstream ss(line);

    while (getline(ss, temp, ',')) {
      row.push_back(temp); //put all the column data of a row in 'temp'
    }

    //convert string to integer
    int sourceID = stoi(row[3]);
    int destID = stoi(row[5]);

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
    // if (connections.count(destID) > 0) {
    //   connections.at(destID).push_back(sourceID); // add sourceID
    // }
    // else {    // if destID not in map, create new element
    //   vector<int> dest;
    //   dest.push_back(sourceID);
    //   connections[destID] = dest;
    // }
  }

  file.close();
  return connections;
}
