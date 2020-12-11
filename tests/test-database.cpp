#include "../cs225/catch/catch.hpp"

#include "../database.h"

#include "../DrawGraph.h"


TEST_CASE("Reads airport info correctly", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
  REQUIRE(db.all_airports.size() == 5);
  REQUIRE(db.all_airports[0].name == "Airport 1");
  REQUIRE(db.locations[5].first == -9.443380355834961);
}

TEST_CASE("Reads routes info correctly", "[weight=1]") {
  Database db;
  db.getConnections("tests/routestoy.dat");
  REQUIRE(db.connections.size() == 4);
  REQUIRE(db.connections[1].size() == 1);
}

TEST_CASE("Sorting all_airports", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
  db.sortAirportsVector(3, 1);
  REQUIRE(db.all_airports.size() == 5);
  REQUIRE(db.all_airports[0].airportID == 3);
  REQUIRE(db.all_airports[4].airportID == 1); 
}

TEST_CASE("Check getAiportID", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
  REQUIRE(db.getAiportID("Airport 3") == 3);
}

TEST_CASE("shortestpath", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
}

TEST_CASE("BFS Traversal", "[weight=1]") {
}

TEST_CASE("Kosaraju's", "[weight=1]") {
}

