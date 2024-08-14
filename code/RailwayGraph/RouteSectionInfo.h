#ifndef ROUTE_SECTION_INFO_H_
#define ROUTE_SECTION_INFO_H_

#include <cstring>

namespace trainsys {

const int MAX_STRING_LENGTH = 50;

struct String {
  char index[MAX_STRING_LENGTH];

  String() = default;

  explicit String(const char *str) { strcpy(index, str); }

  String(const String &other) {
    for (int i = 0; i < MAX_STRING_LENGTH; i++) {
      index[i] = other.index[i];
    }
  }

  String &operator=(const String &other) {
    for (int i = 0; i < MAX_STRING_LENGTH; i++) {
      index[i] = other.index[i];
    }
    return *this;
  }
};

using StationID = int;
using TrainID = String;
using StationName = String;

// 代码清单9-15　RouteSectionInfo 结构体的定义
struct RouteSectionInfo {
  TrainID trainID;
  StationID arrivalStation;
  int price;
  int duration;

  RouteSectionInfo() = default;
  RouteSectionInfo(TrainID trainID, StationID arrivalStation,
      int price, int duration);
  RouteSectionInfo(const RouteSectionInfo &rhs);
  ~RouteSectionInfo() = default;
};

}  // namespace trainsys

#endif  // ROUTE_SECTION_INFO