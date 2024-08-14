#ifndef TRAIN_SYSTEM_H_
#define TRAIN_SYSTEM_H_

#include "Utils.h"
#include "UserManager.h"
#include "TripManager.h"
#include "TicketManager.h"
#include "TrainScheduler.h"
#include "RailwayGraph.h"
#include "SchedulerManager.h"
#include "StationManager.h"
#include "WaitingList.h"
#include "DataStructure/RedBlackTree.h"

namespace trainsys {
    
/*
 * part1 运行计划管理子系统（需要系统管理员权限）
 */

void addTrainScheduler(const TrainID &trainID, int seatNum, int passingStationNumber, 
                       const StationID *stations, const int *duration, const int *price);
                       
void queryTrainScheduler(const TrainID &trainID);

/*
 * part2 票务管理子系统（需要系统管理员权限）
 */

void releaseTicket(const TrainScheduler &scheduler, const Date &date);

void expireTicket(const TrainID &trainID, const Date &date);

/*
 * part3 车票交易子系统
 */

int queryRemainingTicket(const TrainID &trainID, const Date &date, const StationID &departureStation);

void queryMyTicket();

void orderTicket(const TrainID &trainID, const Date &date, const StationID &departureStation);

void refundTicket(const TrainID &trainID, const Date &date, const StationID &departureStation);

/*
 * part4 路线查询子系统
 */

void findAllRoute(const StationID departureID, const StationID arrivalID);

void findBestRoute(const StationID departureID, const StationID arrivalID, int preference);

/*
 * part5 用户管理子系统
 */

void login(const UserID userID, const char* password);

void logout();

void addUser(const UserID userID, const char *username, const char* password);

void findUserInfoByUserID(const UserID userID);

void modifyUserPassword(const UserID userID, const char* password);

void modifyUserPrivilege(const UserID userID, int newPrivilege);

}

#endif 