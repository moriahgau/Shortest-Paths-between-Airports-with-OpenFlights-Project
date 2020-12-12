# genel2-gjiang20-mgau2

--
### Legend
* __program output__
* _example user input_
* ***example program output for example user input***

## How to run the executable
1. Compile the program with 'make airports' in terminal.
2. Execute program by running './airports' in terminal.
3. User prompt to input file paths for 'airports.dat' and 'routes.dat'. The program should work by inputting just the file names for each respective line. If that doesn't work, then try the full path of the files.
   - __Please input airports file path:__ _airports.dat_
   - __Please input routes file path:__ _routes.dat_  

4. Program will read data files to populate database and will make a graph of airport data for algorithm functions.
   - __Loading database and drawing graph...__
   - __Finished!__

5. User prompt to pick an algorithm. We recommend inputting an airport name first to get the airport ID.
   - Shortest Path
     - __Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):__ _1_
     - __Please input source airport ID:__ _155_
     - __Please input destination airport ID:__ _5_
     - If there is a path between source and destination, then program output.
       - __Shortest Distance between 155 and 5 is:__ ***14281 km***
       - __This path is:__
       - ***155->196->49->156->3406->3316->5***
     - If there is not a path, then program output.
       - __Airport is not reachable__

   - BFS
     - __Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):__ _2_
     - __Please input starting airport ID:__ _80_
     - ***80, 111, 154, 161, 202, 146, ...*** (only including first 6 airports in README.md)

   - Strongly Connected
     - __Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):__ _3_
     - __Please choose airport in graph:__ _5_
     - If graph is not strongly connected, then program output. For this airports graph, it is not strongly connected, so it will always output the below.
       - __Airports are not strongly connected__
     - If graph is strongly connected, then program output.
       - __Airports are strongly connected__

   - Find AirportID (airport name needs to be exact including spaces)
     - __Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):__ _4_
     - __Please input airport name:__ _San Francisco International Airport_
     - __AirportID is:__ ***3271***
     - If invalid airport name, then program output.
       - __No AirportID found__

6. Make sure to use end function after running algorithms to avoid memory leaks.
   - __Please choose function (1: Shortest Path; 2: BFS; 3: Strongly Connected; 4: Find AirportID; 5: End):__ _5_
