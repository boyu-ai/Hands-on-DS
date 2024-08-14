#ifndef RAILWAY_GRAPH_H_
#define RAILWAY_GRAPH_H_

#include "Utils.h"
#include "RouteSectionInfo.h"

#include "DataStructure/Graph.h"
#include "DataStructure/List.h"
#include "DataStructure/DisjointSet.h"

namespace trainsys {

class RailwayGraph {
private:
    using GraphType = adjListGraph<RouteSectionInfo*>;

    GraphType routeGraph;

    DisjointSet stationSet;

    seqList<RouteSectionInfo*> routeSectionPool;

public:

    RailwayGraph();
    ~RailwayGraph();

    void addRoute(StationID departureStationID, StationID arrivalStationID, int duration, int price, TrainID trainID);
    
    bool checkStationAccessibility(StationID departureStationID, StationID arrivalStationID);
    
    void displayRoute(StationID departureStationID, StationID arrivalStationID);
    
    void shortestPath(StationID departureStationID, StationID arrivalStationID, int type);
    
private:
    void routeDfs(int curIdx, int arrivalIdx, seqList<StationID> &prevStations, bool *visited);
};

}

#endif