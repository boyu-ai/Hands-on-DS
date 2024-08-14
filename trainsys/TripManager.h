#ifndef TRIP_MANAGER_H_
#define TRIP_MANAGER_H_

#include "Utils.h"
#include "DataStructure/BPlusTree.h"
#include "TripInfo.h"

namespace trainsys {

class TripManager {
private:
    // 数据成员：一个从 UserID 到 [一组 TripInfo]，展现此用户购买了什么票
    BPlusTree<UserID, TripInfo> tripInfo;
public:
    TripManager(const std::string &filename);
    ~TripManager() {}
    void addTrip(const UserID &userID, const TripInfo &trip); 
    seqList<TripInfo> queryTrip(const UserID &userID); // 返回一个用户的多个 TripInfo，输出到 stdout
    void removeTrip(const UserID &userID, const TripInfo &trip);
};

} // namespace trainsys 

#endif