#pragma once
#include "dsets.h"
#include <string>

class airports{

    public:
    bool isStronglyConnected(std::string pointA, std::string pointB);
    void scHelper();

    private:

    DisjointSets scAirports;

};