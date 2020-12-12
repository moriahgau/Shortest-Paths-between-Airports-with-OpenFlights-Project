# genel2-gjiang20-mgau2

--
### legend
*program output*
_example user input_

## How to run the executable
1. Compile the program with 'make airports' in terminal.
2. Execute program by running './airports' in terminal.
3. User prompt to input file paths for 'airports.dat' and 'routes.dat'.
   - *Please input airports file path:* _airports.dat_
   - *Please input routes file path:* _routes.dat_
  The program should work by inputting just the file names for each respective line. If that doesn't work, then try the full path of the files.
4. Program will read data files to populate database and will make a graph of airport data for algorithm functions.
   - *Loading database and drawing graph...*
   - *Finished!*
5. User prompt to pick an algorithm. We recommend inputting an airport name first to get the airport ID.
Shortest Path:
   - *Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):* _1_
   - *Please input source airport ID:* _155_
   - *Please input destination airport ID:* _5_
BFS:
   - *Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):* _2_
   - *Please input starting airport ID:* _155_
Strongly Connected:
   - *Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):* _3_
   - *Please choose airport in graph:* _5_
   - *Airports are not strongly connected.*
      - If graph is not strongly connected, will output above. For this airports graph, it is not strongly connected, so it will always output the above.
   - *Airports are strongly connected.*
      - If graph is strongly connected, will output above.
Find AirportID:
   - *Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):* _4_
   - *Please input airport name:* _San Francisco International Airport_
   - *San Francisco International Airport*
   - *AirportID is:* _3271_

6. Make sure to use end function
   - *Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):* _5_


## Program Outputs
* Shortest path between given airports
* BFS traversal starting from departure airport
* Whether graph is strongly connected (if departure airport can reach all other airports in dataset)
