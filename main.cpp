#include "database.h"

using namespace std;

int main() {
  Database db;

  vector<Airport> all_airports = db.getAirportInfo("airports.dat");
  map<int, vector<int>> connections = db.getConnections("routes.dat");

  return 0;
}
