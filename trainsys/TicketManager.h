#ifndef TICKET_MANAGER_H_
#define TICKET_MANAGER_H_

#include "Utils.h"
#include "TicketInfo.h"
#include "TrainScheduler.h"
#include "DataStructure/BPlusTree.h"

namespace trainsys {
    
class TicketManager {
private:
    // 数据成员：一个从 trainID 到 [一组 TicketInfo] 的 B+ 树索引
    BPlusTree<TrainID, TicketInfo> ticketInfo;
public:
    TicketManager(const std::string &filename);
    ~TicketManager();
    // 功能：给定车次号、乘车日期、始发站（由于分段购票原则，始发站确定即终点站确定），查询余票数量
    // 由于 B+ 树索引只能从 TrainID 到 该车次号 所有日期、所有区间段的余票信息
    // 在拿到 TicketInfo 数组后，需要暴力枚举日期与始发站，才能查到票数
    int querySeat(const TrainID &trainID, const Date &date, const StationID &stationID);
    
    // 功能：给定车次号、乘车日期、始发站、购票或退票，修改余票数量，索引方式同上
    // 参数：delta == 1，购票；delta == -1，退票
    // 返回：票价
    int updateSeat(const TrainID &trainID, const Date &date, const StationID &stationID, int delta);
    
    // 功能：给定列车运行计划，开售列车运行计划分段、逐日的车票，导入车票管理系统
    // 在此处new TicketInfo的空间，构建 B+ 树等，TicketInfo 从 TrainScheduler 拷信息
    void releaseTicket(const TrainScheduler &scheduler, const Date &date);

    // 功能：给定车次与日期，停售该列车运行计划分段、逐日的车票
    void expireTicket(const TrainID &trainID, const Date &date);

    
};


}

#endif // TICKET_MANAGER_H_