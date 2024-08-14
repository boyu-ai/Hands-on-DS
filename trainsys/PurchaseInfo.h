#ifndef PURCHASEINFO_H_
#define PURCHASEINFO_H_

#include "Utils.h"

namespace trainsys {

struct PurchaseInfo {
    UserID userID;
    TrainID trainID;
    Date date;
    StationID departureStation;
    int type;  // 1表示购票，-1表示退票

    PurchaseInfo() = default;
    PurchaseInfo(const UserID userID, const TrainID &trainID, const Date &date, const StationID &departureStation, int type) {
        this->userID = userID;
        this->trainID = trainID;
        this->date = date;
        this->departureStation = departureStation;
        this->type = type;
    }
    ~PurchaseInfo() = default;
    bool operator < (const PurchaseInfo &rhs) const {
        if (userID != rhs.userID) return userID < rhs.userID;
        if (trainID != rhs.trainID) return trainID < rhs.trainID;
        if (date != rhs.date) return date < rhs.date;
        if (departureStation != rhs.departureStation) return departureStation < rhs.departureStation;
        return type < rhs.type;
    }

    bool isOrdering() const { return type >= 0; }
    bool isRefunding() const { return type < 0; }
};

}

#endif 