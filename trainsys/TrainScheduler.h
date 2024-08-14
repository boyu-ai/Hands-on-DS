#ifndef TRAIN_SCHEDULER_H_
#define TRAIN_SCHEDULER_H_

#include "Utils.h"
#include "DataStructure/List.h"

namespace trainsys {

class TrainScheduler {
private:
    TrainID trainID;	                             // 车次号
    int seatNum;					                 // 额定乘员
    int passingStationNum;                           // 途径站点数
    StationID stations[MAX_PASSING_STATION_NUMBER];	 // 途径站点的线性表
    int duration[MAX_PASSING_STATION_NUMBER];	     // 每一段历时的线性表
    int price[MAX_PASSING_STATION_NUMBER];           // 每一段票价的线性表

public:
    TrainScheduler();
    ~TrainScheduler();

    void addStation(const StationID &station);
    void insertStation(int i, const StationID &station);
    void removeStation(int i);
    int findStation(const StationID &station);
    void traverseStation();

    void setTrainID(const TrainID &id);
    void setPrice(const int price[]);
    void setDuration(const int duration[]);
    void setSeatNumber(int seatNum);

    TrainID getTrainID() const;
    int getSeatNum() const;
    int getPassingStationNum() const;

    // 功能：因为要返回指针，所以参数作为返回了
    void getStations(StationID *stations) const;
    void getDuration(int* duration) const;
    void getPrice(int* price) const;

    StationID getStation(int i) const;
    int getDuration(int i) const;
    int getPrice(int i) const;

    bool operator == (const TrainScheduler &rhs) const;

    bool operator != (const TrainScheduler &rhs) const;

    bool operator < (const TrainScheduler &rhs) const;

    friend std::ostream &operator << (std::ostream &os, const TrainScheduler &trainScheduler);

};

}

#endif 