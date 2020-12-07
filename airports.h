#pragma once
#include "dsets.h"
#include "graph.h"
#include <string>
#include <list>

class airports{

    public:
    bool isStronglyConnected(std::string pointA, std::string pointB);
    void scHelper();
    void DFS(int vertex);
    void DFSHelper(int vertex);

    private:

    DisjointSets scAirports;

};