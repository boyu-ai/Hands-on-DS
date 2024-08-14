#ifndef STATION_MANAGER_H_
#define STATION_MANAGER_H_

#include "Utils.h"
#include "DataStructure/BinarySearchTable.h"

namespace trainsys {

class StationManager {

private:
    BinarySearchTable<StationID, String> idToName;
    BinarySearchTable<String, StationID> nameToID;

public:
    StationManager(const char * filename);
    ~StationManager() {}
    String getStationName(const StationID &stationID);
    StationID getStationID(const char * stationName);
};

}

#endif // STATION_MANAGER_H_