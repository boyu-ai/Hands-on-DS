#include "TrainSystem.h"

#include <iostream>
#include <cstring>

namespace trainsys {

UserInfo currentUser;
UserManager *userManager;
RailwayGraph *railwayGraph;
SchedulerManager *schedulerManager;
TicketManager *ticketManager;
PrioritizedWaitingList *waitingList;
TripManager *tripManager;
StationManager *stationManager;
RedBlackTree<String, StationID> stationNameToIDMapping;

/*
 * part1 运行计划管理子系统（需要系统管理员权限）
 */

void addTrainScheduler(const TrainID &trainID, int seatNum, int passingStationNumber, 
                       const StationID *stations, const int *duration, const int *price) {
    if (currentUser.userID == -1 || currentUser.privilege < ADMIN_PRIVILEGE) {
        std::cout << "Permission denied." << std::endl;
        return ;
    }
    if (schedulerManager->existScheduler(trainID)) {
        std::cout << "TrainID existed." << std::endl;
        return ;
    }
    schedulerManager->addScheduler(trainID, seatNum, passingStationNumber, stations, duration, price);
    for (int i = 0; i + 1 < passingStationNumber; i++) {
        railwayGraph->addRoute(stations[i], stations[i + 1], duration[i], price[i], trainID);
    }
    std::cout << "Train added." << std::endl;
}

void queryTrainScheduler(const TrainID &trainID) {
    if (currentUser.userID == -1 || currentUser.privilege < ADMIN_PRIVILEGE) {
        std::cout << "Permission denied." << std::endl;
        return ;
    }
    if (!schedulerManager->existScheduler(trainID)) {
        std::cout << "Train not found." << std::endl;
        return ;
    }
    TrainScheduler relatedInfo = schedulerManager->getScheduler(trainID);
    std::cout << "TrainID: " << relatedInfo.getTrainID() << std::endl;
    std::cout << "SeatNum: " << relatedInfo.getSeatNum() << std::endl;
    std::cout << "PassingStationNum: " << relatedInfo.getPassingStationNum() << std::endl;
    std::cout << "Stations: ";
    for (int i = 0; i < relatedInfo.getPassingStationNum(); i++) {
        std::cout << relatedInfo.getStation(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Duration: ";
    for (int i = 0; i + 1 < relatedInfo.getPassingStationNum(); i++) {
        std::cout << relatedInfo.getDuration(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Price: ";
    for (int i = 0; i + 1 < relatedInfo.getPassingStationNum(); i++) {
        std::cout << relatedInfo.getPrice(i) << " ";
    }
    std::cout << std::endl;
}

/*
 * part2 票务管理子系统（需要系统管理员权限）
 */

void releaseTicket(const TrainScheduler &scheduler, const Date &date) {
    if (currentUser.userID != -1 && currentUser.privilege >= ADMIN_PRIVILEGE) {
        ticketManager->releaseTicket(scheduler, date);
        std::cout << "Ticket released." << std::endl;
    } else {
        std::cout << "Permission denied." << std::endl;
    }
}

void expireTicket(const TrainID &trainID, const Date &date) {
    if (currentUser.userID != -1 && currentUser.privilege >= ADMIN_PRIVILEGE) {
        ticketManager->expireTicket(trainID, date);
        std::cout << "Ticket expired." << std::endl;
    } else {
        std::cout << "Permission denied." << std::endl;
    }
}

/*
 * part3 车票交易子系统
 */

int queryRemainingTicket(const TrainID &trainID, const Date &date, const StationID &departureStation) {
    return ticketManager->querySeat(trainID, date, departureStation);
}

bool trySatisfyOrder() {
    PurchaseInfo purchaseInfo = waitingList->getFrontPurchaseInfo();
    waitingList->removeHeadFromWaitingList();

    std::cout << "Processing request from User " << purchaseInfo.userID << std::endl;

    if (purchaseInfo.isOrdering()) {
        // 购票信息
        int remainingTickets = queryRemainingTicket(purchaseInfo.trainID, purchaseInfo.date, purchaseInfo.departureStation);
        if (remainingTickets < purchaseInfo.type) {
            std::cout << "No enough tickets or scheduler not exists. Order failed." << std::endl;
            return false;
        } else {
            ticketManager->updateSeat(purchaseInfo.trainID, purchaseInfo.date, purchaseInfo.departureStation, -purchaseInfo.type);
            
            TrainScheduler schedule = schedulerManager->getScheduler(purchaseInfo.trainID);
            int id = schedule.findStation(purchaseInfo.departureStation);
            int duration = schedule.getDuration(id);
            int price = schedule.getPrice(id);
            StationID arrivalStation = schedule.getStation(id + 1);
            
            tripManager->addTrip(purchaseInfo.userID, TripInfo(
                purchaseInfo.trainID, purchaseInfo.departureStation, arrivalStation, purchaseInfo.type, duration, price, purchaseInfo.date
            ));

            std::cout << "Order succeeded." << std::endl;
            return true;
        }
    } 
    else {
        // 退票信息
        ticketManager->updateSeat(purchaseInfo.trainID, purchaseInfo.date, purchaseInfo.departureStation, -purchaseInfo.type);
        
        TrainScheduler schedule = schedulerManager->getScheduler(purchaseInfo.trainID);
        int id = schedule.findStation(purchaseInfo.departureStation);
        int duration = schedule.getDuration(id);
        int price = schedule.getPrice(id);
        StationID arrivalStation = schedule.getStation(id + 1);

        tripManager->removeTrip(purchaseInfo.userID, TripInfo(
            purchaseInfo.trainID, purchaseInfo.departureStation, arrivalStation, -purchaseInfo.type, duration, price, purchaseInfo.date
        ));
        std::cout << "Refund succeeded." << std::endl;
        return true;
    }
}

void queryMyTicket() {
    while (waitingList->isBusy()) trySatisfyOrder();

    seqList<TripInfo> tripInfo = tripManager->queryTrip(currentUser.userID);

    for (int i = 0; i < tripInfo.length(); i++) {
        std::cout << tripInfo.visit(i) << std::endl;
    }
}

void orderTicket(const TrainID &trainID, const Date &date, const StationID &departureStation) {
    while (waitingList->isBusy()) trySatisfyOrder();

    waitingList->addToWaitingList(PurchaseInfo(currentUser.userID, trainID, date, departureStation, +1));
    std::cout << "Ordering request has added to waiting list." << std::endl;
}

void refundTicket(const TrainID &trainID, const Date &date, const StationID &departureStation) {
    while (waitingList->isBusy()) trySatisfyOrder();
    
    waitingList->addToWaitingList(PurchaseInfo(currentUser.userID, trainID, date, departureStation, -1));
    std::cout << "Refunding request has added to waiting list." << std::endl;
}

/*
 * part4 路线查询子系统
 */

void findAllRoute(const StationID departureID, const StationID arrivalID) {
    if (!railwayGraph->checkStationAccessibility(departureID, arrivalID)) {
        std::cout << "Disconnected. No route found." << std::endl;
        return ;
    }

    railwayGraph->displayRoute(departureID, arrivalID);
}

void findBestRoute(const StationID departureID, const StationID arrivalID, int preference) {
    if (!railwayGraph->checkStationAccessibility(departureID, arrivalID)) {
        std::cout << "Disconnected. No route found." << std::endl;
        return ;
    }
    
    railwayGraph->shortestPath(departureID, arrivalID, preference);
}

/*
 * part5 用户管理子系统
 */

void login(const UserID userID, const char* password) {
    if (currentUser.userID != -1) {
        std::cout << "Only one user can login in at the same time." << std::endl;
        return ;
    }

    if (!userManager->existUser(userID)) {
        std::cout << "User not found. Login failed." << std::endl;
        return ; 
    }

    UserInfo userInfo = userManager->findUser(userID);
    if (strncmp(userInfo.password, password, MAX_PASSWORD_LEN) != 0) {
        std::cout << "Wrong password. Login failed." << std::endl;
        return ;
    }

    currentUser = userInfo;
    std::cout << "Login succeeded." << std::endl;
}

void logout() {
    if (currentUser.userID == -1) {
        std::cout << "No user logined." << std::endl;
        return ;
    }
    currentUser.userID = -1;
}

void addUser(const UserID userID, const char *username, const char* password) {
    if (userManager->existUser(userID)) {
        std::cout << "User ID existed." << std::endl;
        return ;
    }
    if (currentUser.userID == -1) {
        std::cout << "Permission denied." << std::endl;
        return ;
    }
    
    userManager->insertUser(userID, username, password, 0);
    std::cout << "User added." << std::endl;
}

void findUserInfoByUserID(const UserID userID) {
    if (!userManager->existUser(userID)) {
        std::cout << "User not found." << std::endl;
        return ;
    }

    UserInfo userInfo = userManager->findUser(userID);
    if (currentUser.userID == -1 || currentUser.privilege <= userInfo.privilege) {
        std::cout << "Permission denied." << std::endl;
        return ;
    }

    std::cout << "UserID: " << userInfo.userID << std::endl;
    std::cout << "UserName: " << userInfo.username << std::endl;
    std::cout << "Password: " << userInfo.password << std::endl;
    std::cout << "Privilege: " << userInfo.privilege << std::endl;
}

void modifyUserPassword(const UserID userID, const char* newPassword) {
    if (!userManager->existUser(userID)) {
        std::cout << "User not found." << std::endl;
        return ;
    }
    UserInfo userInfo = userManager->findUser(userID);
    if (currentUser.userID == -1 || currentUser.privilege <= userInfo.privilege) {
        std::cout << "Modification forbidden." << std::endl;
        return ;
    }

    userManager->modifyUserPassword(userID, newPassword);
    std::cout << "Modification succeeded." << std::endl;
}

void modifyUserPrivilege(const UserID userID, int newPrivilege) {
    if (!userManager->existUser(userID)) {
        std::cout << "User not found." << std::endl;
        return ;
    }

    UserInfo userInfo = userManager->findUser(userID);
    if (currentUser.userID == -1 || currentUser.privilege <= userInfo.privilege) {
        std::cout << "Modification forbidden." << std::endl;
        return ;
    }

    //* here `userID != currentUser.userID` should hold
    userManager->modifyUserPrivilege(userID, newPrivilege);
    std::cout << "Modifiaction succeeded." << std::endl;
}

} // namespace trainsys 