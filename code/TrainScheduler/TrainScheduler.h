// 代码清单2-15　TrainScheduler 类的定义

#ifndef TRAIN_SCHEDULER_H_
#define TRAIN_SCHEDULER_H_

#include "List.h"
#include "Utils.h"

namespace trainsys {

class TrainScheduler {  // 列车运行计划管理类
 private:
  TrainID trainID;              // 车次号
  int seatNum;                  // 额定乘员
  seqList<StationID> stations;  // 途经站点的线性表
  seqList<int> duration;        // 每一段历时的线性表
  seqList<int> price;           // 每一段票价的线性表

 public:
  TrainScheduler();
  ~TrainScheduler();
  void addStation(const StationID &station);
  void insertStation(int i, const StationID &station);
  void removeStation(int i);
  int findStation(const StationID &station);
  void traverseStation();

  void setTrainID(const TrainID &id);
  void setSeatNumber(int seatNum);
  void setPrice(int price[]);
  void setDuration(int duration[]);

  TrainID getTrainID() const;
  int getSeatNum() const;

  void getStations(seqList<StationID> *stations) const;
  void getDuration(seqList<int> *duration) const;
  void getPrice(seqList<int> *price) const;

  StationID getStation(int i) const;
  int getDuration(int i) const;
  int getPrice(int i) const;
};

}  // namespace trainsys

#endif
