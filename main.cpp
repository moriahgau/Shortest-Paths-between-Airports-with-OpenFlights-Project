#include "database.h"

using namespace std;

int main() {
  Database db; // initialize database
  // read data files and store info
  vector<Airport> all_airports = db.getAirportInfo("airports.dat");
  map<int, vector<int>> connections = db.getConnections("routes.dat");

  // ask user for departure airport (source) and arrival airport (dest)
  string source;
  cout << "Departure Airport Name (e.g ): ";
  getline(cin, source); // get user input from the keyboard
  for (auto plane : all_airports) {
    if (source != plane.name) cout << "Invalid airport name"; // check if valid airport name
    break;
  }

  string dest;
  cout << "Arrival Airport Name: ";
  getline(cin, dest);
  for (auto plane : all_airports) {
    if (dest != plane.name) cout << "Invalid airport name"; // check if valid airport name
    break;
  }

  db.sortAirportsVector(db.getAiportID(source), db.getAiportID(dest)); // rearrange 'all_airports'


  return 0;
}
