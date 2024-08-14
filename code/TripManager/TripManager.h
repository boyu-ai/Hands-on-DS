// 代码清单8-14　TripManager 类的定义
#ifndef TRIP_MANAGER_H_
#define TRIP_MANAGER_H_

#include "TripInfo.h"
#include "Utils.h"
#include "BPlusTree.h"

namespace trainsys {

class TripManager {
 private:
  BPlusTree<UserID, TripInfo> tripInfo;

 public:
  TripManager(const std::string &filename);
  ~TripManager() {}
  void addTrip(const UserID &userID, const TripInfo &trip);
  // 返回一个用户的多个 TripInfo，输出到 stdout
  seqList<TripInfo> queryTrip(const UserID &userID);
  void removeTrip(const UserID &userID, const TripInfo &trip);
};

}  // namespace trainsys

#endif