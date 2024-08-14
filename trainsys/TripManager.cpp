#include "TripManager.h"
#include "DataStructure/List.h"

namespace trainsys {

TripManager::TripManager(const std::string &filename)
    : tripInfo(filename) {}

void TripManager::addTrip(const UserID &userID, const TripInfo &trip) {
    tripInfo.insert(userID, trip);
}

seqList<TripInfo> TripManager::queryTrip(const UserID &userID) {
    return tripInfo.find(userID);
}

void TripManager::removeTrip(const UserID &userID, const TripInfo &trip) {
    tripInfo.remove(userID, trip);
}

}