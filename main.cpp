#include "database.h"
#include "DrawGraph.h"
#include "kosaraju.h"
#include <string>

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
  cout<< "Loading database and drawing graph..."<< endl;
  db.getAirportInfo(airportsPath);
  db.getConnections(routesPath);
  DrawGraph *graph = new DrawGraph(db.all_airports, db.connections);

  int choice;

  cout<< "Finished!"<< endl;
  cout<< "Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End): ";

  while(cin>> choice){

    //Shortest Path
    if(choice == 1){

      int src;
      int dest;

      cout<< "Please input source airport ID: ";
      cin>> src;

      cout<< "Please input destination airport ID: ";
      cin>> dest;

      graph->shortestPath(src, dest, db.all_airports);
    }

    //BFS
    else if(choice == 2){

      int src;

      cout<< "Please input starting airport ID: ";
      cin>> src;

      graph->BFS(src, db.all_airports);
    }

    //Strongly Connected
    else if(choice == 3){

      int src;

      cout<< "Please choose airport in graph: ";
      cin>> src;
      if(simpleKosaraju(*graph, src, db.all_airports)) cout<< "Airports are strongly connected."<< endl;
      else cout<< "Airports are not strongly connected." << endl;
    }

    //Find AirportID (CASE SENSITIVE)
    else if(choice == 4){

      std::string name;
      cout<< "Please input airport name: ";
      cin.ignore();
      std::getline(cin, name);
      cout<< name<< endl;
      cout<< "AirportID is: "<< db.getAirportID(name)<< endl;
    }

    //End Program
    else if(choice == 5){
      delete graph;
      graph = NULL;
      break;
    }

    else{

    }

    cout<< "Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End): ";
  }

  return 0;
}
