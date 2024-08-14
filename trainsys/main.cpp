#include "TrainSystem.h"
#include "CommandParser.h"
#include "Utils.h"

namespace trainsys {

extern UserInfo currentUser;
extern UserManager *userManager;
extern RailwayGraph *railwayGraph;
extern SchedulerManager *schedulerManager;
extern TicketManager *ticketManager;
extern PrioritizedWaitingList *waitingList;
extern TripManager *tripManager;
extern StationManager *stationManager;

// 初始化系统
void init() {
    stationManager = new StationManager("station.txt");
    userManager = new UserManager("user.dat");
    schedulerManager = new SchedulerManager("scheduler.dat");
    ticketManager = new TicketManager("ticket.dat");
    waitingList = new PrioritizedWaitingList();
    tripManager = new TripManager("trip.dat");
    railwayGraph = new RailwayGraph();

    // 开启系统时，自动登录管理员。默认管理员账号ID为0
    puts("admin login");
    if (userManager->existUser(0)) {
        currentUser = userManager->findUser(0);
    } else {
        currentUser = UserInfo(0, "admin", "admin", 100);
        userManager->insertUser(0, "admin", "admin", 100);
    }
}

}

int main() {
    trainsys::init();
    char command[30000];
    // 读入指令
    while (std::cin.getline(command, 30000)) {
        printf("get command: %s\n", command);
        if (trainsys::parseCommand(command) == 1) { // 读入到exit指令
            break;
        }
    }
    delete trainsys::userManager;
    delete trainsys::railwayGraph;
    delete trainsys::schedulerManager;
    delete trainsys::ticketManager;
    delete trainsys::waitingList;
    delete trainsys::tripManager;
    return 0;
}