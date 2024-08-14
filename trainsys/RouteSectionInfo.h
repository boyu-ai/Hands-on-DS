#ifndef ROUTE_SECTION_INFO_H_
#define ROUTE_SECTION_INFO_H_

#include "Utils.h"

namespace trainsys {

struct RouteSectionInfo { 
    TrainID trainID;
    StationID arrivalStation;
    int price;
    int duration;

    RouteSectionInfo() = default;
    RouteSectionInfo(TrainID trainID, StationID arrivalStation, int price, int duration);
    RouteSectionInfo(const RouteSectionInfo &rhs);
    ~RouteSectionInfo() = default;
};

}

#endif // ROUTE_SECTION_INFO