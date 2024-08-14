#ifndef SCHEDULER_MANAGER_H
#define SCHEDULER_MANAGER_H

#include "Utils.h"
#include "TrainScheduler.h"
#include "DataStructure/BPlusTree.h"


namespace trainsys {

class SchedulerManager {
private:
    BPlusTree<TrainID, TrainScheduler> schedulerInfo;

public:
    SchedulerManager(const std::string &filename);
    ~SchedulerManager() {}

    void addScheduler(const TrainID &trainID, int seatNum, 
                int passingStationNumber, const StationID *stations, const int *duration, const int *price);

    bool existScheduler(const TrainID &trainID);

    TrainScheduler getScheduler(const TrainID &trainID);

    void removeScheduler(const TrainID &trainID);
};

}

#endif // SCHEDULER_MANAGER_H