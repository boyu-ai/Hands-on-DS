// 代码清单8-9 TicketManager类的定义
#ifndef TICKET_MANAGER_H_
#define TICKET_MANAGER_H_

#include "TicketInfo.h"
#include "TrainScheduler.h"
#include "Utils.h"
#include "BPlusTree.h"

namespace trainsys {

class TicketManager {
 public:
  // 从 trainID 到 [一组 TicketInfo] 的 B+ 树索引
  BPlusTree<TrainID, TicketInfo> ticketInfo;

 public:
  TicketManager(const std::string &filename);
  ~TicketManager();
  // 余票查询
  int querySeat(
      const TrainID &trainID, const Date &date, const StationID &stationID);

  // 余票更新（购票、退票）
  // 给定车次号、乘车日期、始发站、购票或退票，修改余票数量
  // delta == 1，购票；delta == -1，退票
  // 返回：票价
  int updateSeat(const TrainID &trainID, const Date &date,
      const StationID &stationID, int delta);

  // 车票发售
  void releaseTicket(const TrainScheduler &scheduler, const Date &date);

  // 车票停售
  void expireTicket(const TrainID &trainID, const Date &date);
};

}  // namespace trainsys

#endif  // TICKET_MANAGER_H_