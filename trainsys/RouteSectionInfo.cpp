#include "RouteSectionInfo.h"

namespace trainsys {

RouteSectionInfo::RouteSectionInfo(TrainID trainID, StationID arrivalStation, int price, int duration) {
    this->trainID = trainID;
    this->arrivalStation = arrivalStation;
    this->price = price;
    this->duration = duration;
}

RouteSectionInfo::RouteSectionInfo(const RouteSectionInfo &rhs) {
    this->trainID = rhs.trainID;
    this->arrivalStation = rhs.arrivalStation;
    this->price = rhs.price;
    this->duration = rhs.duration;
}

}