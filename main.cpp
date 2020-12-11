#include "database.h"
#include "DrawGraph.h"

using namespace std;

int main() {
  Database db; // initialize database
  // read data files and store info
  db.getAirportInfo("airports.dat");
  db.getConnections("routes.dat");
  
  /*// ask user for departure airport (source) and arrival airport (dest)
  string source;
  bool depFlag = false;
  cout << "Departure Airport Name (e.g ): ";
  getline(cin, source); // get user input from the keyboard
  for (auto plane : db.all_airports) {

    if (source == plane.name){
      depFlag = true;
      break;
    } 
  }
  if(!depFlag) cout << "Invalid airport name"<< endl; // check if valid airport name

  string dest;
  bool destFlag = false;
  cout << "Arrival Airport Name: ";
  getline(cin, dest);
  for (auto plane : db.all_airports) {
    if (source == plane.name){
      destFlag = true;
      break;
    } 
  }
  if(!destFlag) cout << "Invalid airport name"<< endl; // check if valid airport name*/

  //db.sortAirportsVector(db.getAiportID(source), db.getAiportID(dest)); // rearrange 'all_airports'

  DrawGraph *graph = new DrawGraph(db.all_airports, db.connections);

  graph->shortestPath(2, 18, db.all_airports);

  graph->BFS(2, db.all_airports);

  return 0;
}
