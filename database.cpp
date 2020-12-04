#include "database.h"

Airport::Airport(int identifier, string airport, double lat, double long) {
  airportID = identifier;
  name = airport;
  latitude = lat;
  longitude = long;
}
