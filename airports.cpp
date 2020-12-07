#include "airports.h"
#include "dsets.h"
#include <string>
#include <stack>

bool isStronglyConnected (std::string pointA, std::string pointB){

//if airports are in same set,then they are strongly connected
if(scAirports.find(/*pointA id*/) == scAirports.find(/*pointB id*/)) return true;

return false;
}

//call sc helper every time the database is inputted/parsed
//build scAirports based on aiports and their connections
//heavily dependent on how the data is parsed/built
void scHelper(){

//initialize all airports as their own (maybe based on id)
scAirports.addelements(/*size of database*/);

//union all connected airports: airports of the same dset is strongly connected
for(int i = 0; i < /*size of database*/; i++){
    for(int j = 0; j < /*size of list at each entry*/; j++){

        //find some way such that we don't need to go through every entry once it is already set
        if(scAirports.find(/*entry j*/) != -1) break;

        //setunion
        scAirports.setunion(/*entry i*/, /*entry j*/);
    }
}
//perhaps use a dictionary/map with each entry being the ID of the airport,
//and at each entry store an array with all the airports that it is connected to


}

//Kosaraju's algo to find strongly connected components 
void scHelper(){

}

void DFS