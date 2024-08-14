#include "SchedulerManager.h"


namespace trainsys {

    SchedulerManager::SchedulerManager(const std::string &filename) 
        : schedulerInfo(filename) {}

    // 添加一个运行计划
    void SchedulerManager::addScheduler(const TrainID &trainID, int seatNum, 
                int passingStationNumber, const StationID *stations, const int *duration, const int *price) {
        TrainScheduler scheduler;
        scheduler.setTrainID(trainID);
        for (int i = 0; i < passingStationNumber; i++) {
            scheduler.addStation(stations[i]);
        }
        scheduler.setDuration(duration);
        scheduler.setPrice(price);
        scheduler.setSeatNumber(seatNum);
        schedulerInfo.insert(trainID, scheduler);
    }

    // 查询某个ID的运行计划是否存在
    bool SchedulerManager::existScheduler(const TrainID &trainID) {
        return schedulerInfo.contains(trainID);
    }

    // 查询某个ID的运行计划
    TrainScheduler SchedulerManager::getScheduler(const TrainID &trainID) {
        seqList<TrainScheduler> relatedInfo = schedulerInfo.find(trainID);
        // 一个trainID理应只对应一个运行计划，但由于这里的B+树是一对多的B+树，所以需要使用seqList
        return relatedInfo.visit(0);
    }

    // 删除某个ID的运行计划
    void SchedulerManager::removeScheduler(const TrainID &trainID) {
        seqList<TrainScheduler> relatedInfo = schedulerInfo.find(trainID);
        for (int i = 0; i < relatedInfo.length(); ++i) {
            schedulerInfo.remove(trainID, relatedInfo.visit(i));
        }
    }

}
