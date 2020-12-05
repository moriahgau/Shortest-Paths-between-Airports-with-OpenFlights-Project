#include "airportdict.h"



int AirportDict::getConnectionsDict(string filename) { //airports.dat
  ifstream myFile(filename); // Object to read from file
  //myFile.open(filename, ios::in); // Opening file in input mode

  if (myFile.is_open()) {
    while (getline(myFile, line)) {
      stringstream ss(line);

      //Airport(airportID, name, latitude, longitude);

      /*
      ifstream wordsFile(filename);
      string word;
      if (wordsFile.is_open()) {
      // Reads a line from `wordsFile` into `word` until the file ends.
        while (getline(wordsFile, word)) {
          string temp = word;
          std::sort(temp.begin(), temp.end());
          dict[temp].push_back(word); //dict[word].push_back(line);
        }
      }
      */

    }
  }

  myFile.close();

  return 0;
}
