// 代码清单8-13　行程信息TripInfo 结构体的定义
#ifndef TRIPINFO_H_
#define TRIPINFO_H_

#include "Utils.h"

namespace trainsys {

struct TripInfo {
  TrainID trainID;
  StationID departureStation;
  StationID arrivalStation;
  int duration;
  int price;
  Date date;

  TripInfo() = default;
  TripInfo(const TrainID &trainID, const StationID &departureStation,
      const StationID &arrivalStation, int duration, int price,
      const Date &date) {
    this->trainID = trainID;
    this->departureStation = departureStation;
    this->arrivalStation = arrivalStation;
    this->duration = duration;
    this->price = price;
    this->date = date;
  }

  bool operator==(const TripInfo &rhs) const {
    return trainID == rhs.trainID && departureStation == rhs.departureStation &&
           arrivalStation == rhs.arrivalStation && duration == rhs.duration &&
           price == rhs.price && date == rhs.date;
  }

  bool operator!=(const TripInfo &rhs) const { return !(*this == rhs); }

  bool operator<(const TripInfo &rhs) const {
    if (trainID != rhs.trainID) {
      return trainID < rhs.trainID;
    } else if (departureStation != rhs.departureStation) {
      return departureStation < rhs.departureStation;
    } else if (arrivalStation != rhs.arrivalStation) {
      return arrivalStation < rhs.arrivalStation;
    } else if (date != rhs.date) {
      return date < rhs.date;
    } else if (price != rhs.price) {
      return price < rhs.price;
    } else {
      return duration < rhs.duration;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const TripInfo &tripInfo) {
    os << "TripInfo:" << std::endl;
    os << "trainID: " << tripInfo.trainID << std::endl;
    os << "departureStation: " << tripInfo.departureStation << std::endl;
    os << "arrivalStation: " << tripInfo.arrivalStation << std::endl;
    os << "duration: " << tripInfo.duration << std::endl;
    os << "price: " << tripInfo.price << std::endl;
    os << "date: " << tripInfo.date << std::endl;
    return os;
  }
};

}  // namespace trainsys

#endif