#include "database.h"
#include "DrawGraph.h"
#include "kosaraju.h"
#include "string"

using namespace std;

int main() {
  Database db; // initialize database
  // read data files and store info

  std::string airportsPath;
  std::string routesPath;
  cout<< "Please input airports file path: ";
  cin>> airportsPath;
  cout<< "Please input routes file path: ";
  cin>> routesPath;
  db.getAirportInfo(airportsPath);
  db.getConnections(routesPath);
  DrawGraph *graph = new DrawGraph(db.all_airports, db.connections);

  int choice;

  cout<< "Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: End): ";
  
  while(cin>> choice){

    if(choice == 1){

      int src;
      int dest;

      cout<< "Please input source airport ID: ";
      cin>> src;

      cout<< "Please input destination airport ID: ";
      cin>> dest;

      graph->shortestPath(src, dest, db.all_airports);
    }

    else if(choice == 2){
      
      int src;

      cout<< "Please input starting airport ID: ";
      cin>> src;

      graph->BFS(src, db.all_airports);
    }

    else if(choice == 3){

      int src;

      cout<< "Please choose airport in graph: ";
      cin>> src;
      if(simpleKosaraju(*graph, src, db.all_airports)) cout<< "Airports are strongly connected."<< endl;
      else cout<< "Airports are not strongly connected." << endl;
    }

    else if(choice == 4){
      break;
    }

    cout<< "Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected): ";
  }
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

  /*graph->shortestPath(2, 5522, db.all_airports);

  graph->BFS(2, db.all_airports);

  if(simpleKosaraju(*graph, 2, db.all_airports)) cout<< "Is strongly connected."<< endl;
  else cout<< "Is not strongly connected." << endl;*/

  return 0;
}
