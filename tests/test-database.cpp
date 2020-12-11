#include "../cs225/catch/catch.hpp"

#include "../database.h"
#include "../DrawGraph.h"
#include "../kosaraju.h"
using namespace std;

// make adj public variable
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

TEST_CASE("DrawGraph Ctor", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
  db.getConnections("tests/routestoy.dat");
  
  DrawGraph graph(db.all_airports, db.connections);

  const Graph & g = graph.getGraph();

  // always required edges
  REQUIRE(g.edgeExists("Airport 1", "Airport 2"));
  REQUIRE(g.edgeExists("Airport 5", "Airport 3"));
  REQUIRE(g.edgeExists("Airport 2", "Airport 5"));
  REQUIRE(g.edgeExists("Airport 3", "Airport 2"));
  REQUIRE(g.edgeExists("Airport 5", "Airport 4"));
  REQUIRE(g.edgeExists("Airport 2", "Airport 4"));
  vector<vector<pair<int, int>>> adj = graph.getAdj();
  REQUIRE((adj[1])[0].first == 2);
  // point 1 : lat = -6.081689834590001 long = 145.391998291
  // point 2 : lat = -5.20707988739,long = 145.789001465
  REQUIRE((adj[1])[0].second == 106);
}

TEST_CASE("shortestpath", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
  db.getConnections("tests/routestoy.dat");
  DrawGraph graph(db.all_airports, db.connections);
  graph.shortestPath(1, 4, db.all_airports);
  cout << "Expected: " << "1->2->4" << endl;
}

TEST_CASE("Kosaraju's", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
  db.getConnections("tests/routestoy.dat");
  DrawGraph graph(db.all_airports, db.connections);
  REQUIRE(simpleKosaraju(graph, 1, db.all_airports) == false);
  //REQUIRE(simpleKosaraju(graph, 3, db.all_airports) == false);
}

// TEST_CASE("Shortest Path", "[weight=1]") {
//   Database db;
//   db.getAirportInfo("tests/airportstoy.dat");
//   db.getConnections("tests/routestoy.dat");
//   DrawGraph *graph = new DrawGraph(db.all_airports, db.connections);
//   graph->shortestPath(2, db.all_airports);
//   //REQUIRE(db.getAiportID("Airport 3") == 3);
// }

TEST_CASE("BFS", "[weight=1]") {
  Database db;
  db.getAirportInfo("tests/airportstoy.dat");
  db.getConnections("tests/routestoy.dat");
  DrawGraph *graph = new DrawGraph(db.all_airports, db.connections);
  graph->BFS(2, db.all_airports);
  // cout << "Expectation" << "4 5 2") << endl;
  cout << "Expected: " << "2, 5, 4, 3 " << endl;
}
