// 代码清单3-22　PurchaseInfo 交易信息结构体
#ifndef PURCHASEINFO_H_
#define PURCHASEINFO_H_

#include "DateTime.h"
#include "Utils.h"

namespace trainsys {

struct PurchaseInfo {
  UserID userID;
  TrainID trainID;
  Date date;
  StationID departureStation;
  int type;  // 1表示购票，-1表示退票

  PurchaseInfo() = default;
  PurchaseInfo(const UserID userID, const TrainID &trainID,
      const Date &date, const StationID &departureStation, int type) {
    this->userID = userID;
    this->trainID = trainID;
    this->date = date;
    this->departureStation = departureStation;
    this->type = type;
  }
  ~PurchaseInfo() = default;

  bool isOrdering() const { return type >= 0; }
  bool isRefunding() const { return type < 0; }

  const UserID getUser() const { return userID; }
  const Date getDate() const { return date; }
  const StationID getDepartureStation() const {
    return departureStation;
  }
};

}  // namespace trainsys

#endif