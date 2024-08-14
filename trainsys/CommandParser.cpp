#include "CommandParser.h"
#include "TrainSystem.h"
#include "DataStructure/List.h"
#include "DataStructure/RedBlackTree.h"

namespace trainsys {

extern UserInfo currentUser;
extern UserManager *userManager;
extern RailwayGraph *railwayGraph;
extern SchedulerManager *schedulerManager;
extern TicketManager *ticketManager;
extern PrioritizedWaitingList *waitingList;
extern TripManager *tripManager;
extern StationManager *stationManager;

// 存放参数，例如 argMap['u'] 存放的是 -u 后面的参数
static char* argMap[200];
extern RedBlackTree<String, StationID> stationNameToIDMapping;

bool isStringEnding(char ch) {
    return ch == '\0' || ch == '\n' || ch == '\r';
}

// 将字符串按照分隔符分割
seqList<char*> splitTokens(const char *command, char separator) {
    seqList<char*> tokens;
    int i = 0;
    while (true) {
        int j = i;
        while (!isStringEnding(command[j]) && command[j] != separator) {
            ++j;
        }
        char *token = new char[j - i + 1];
        for (int k = i; k < j; ++k) {
            token[k - i] = command[k];
        }
        token[j - i] = '\0';
        tokens.insert(tokens.length(), token);
        i = j + 1;
        if (isStringEnding(command[j])) {
            break;
        }
    }
    return tokens;
}

// 将字符串转换为数字
long long stringToNumber(const char * str) {
    long long number = 0;
    int i = 0;
    while (str[i] != '\0') {
        number = number * 10 + str[i] - '0';
        ++i;
    }
    return number;
}

// 在这个简单的火车票系统中，我们没有对输入数据进行严格的检查，例如检查输入的参数个数等，读者可以自行添加以加强代码的鲁棒性
int parseCommand(const char * command) {
    int exitCode = 0;
    seqList<char*> tokens = splitTokens(command, ' ');
    for (int i = 1; i < tokens.length(); i += 2) {
        if (tokens.visit(i)[0] == '-') {
            argMap[(int)tokens.visit(i)[1]] = tokens.visit(i + 1);
        } else {
            exitCode = -1;
        }
    }
    char* commandName = tokens.visit(0);
    if (exitCode != -1) {
        if (strcmp(commandName, "register") == 0) {
            addUser(stringToNumber(argMap['i']), argMap['u'], argMap['p']);
        } else if (strcmp(commandName, "login") == 0) {
            login(stringToNumber(argMap['i']), argMap['p']);
        } else if (strcmp(commandName, "logout") == 0) {
            logout();
        } else if (strcmp(commandName, "modify_password") == 0) {
            modifyUserPassword(stringToNumber(argMap['i']), argMap['p']);
        } else if (strcmp(commandName, "modify_privilege") == 0) {
            modifyUserPrivilege(stringToNumber(argMap['i']), stringToNumber(argMap['g']));
        } else if (strcmp(commandName, "query_profile") == 0) {
            findUserInfoByUserID(stringToNumber(argMap['i']));
        } else if (strcmp(commandName, "add_train") == 0) {
            seqList<char *> stationsString = splitTokens(argMap['s'], '|');
            seqList<char *> pricesString = splitTokens(argMap['p'], '|');
            seqList<char *> durationsString = splitTokens(argMap['t'], '|');
            StationID *stations = new StationID[stationsString.length()];
            int *prices = new int[pricesString.length()];
            int *durations = new int[durationsString.length()];
            for (int i = 0; i < stationsString.length(); ++i) {
                stations[i] = stationManager->getStationID(stationsString.visit(i));
                delete [](stationsString.visit(i));
            }
            for (int i = 0; i < pricesString.length(); ++i) {
                prices[i] = stringToNumber(pricesString.visit(i));
                delete [](pricesString.visit(i));
            }
            for (int i = 0; i < durationsString.length(); ++i) {
                durations[i] = stringToNumber(durationsString.visit(i));
                delete [](durationsString.visit(i));
            }
            // 结构体Date和String(TrainID是结构体String的别名)中有一个构造函数，可以将字符串转换为Date/String类型
            addTrainScheduler(TrainID(argMap['i']), stringToNumber(argMap['m']),
                              stringToNumber(argMap['n']), stations, durations, prices);
            delete []stations;
            delete []prices;
            delete []durations;
        } else if (strcmp(commandName, "query_train") == 0) {
            queryTrainScheduler(TrainID(argMap['i']));
        } else if (strcmp(commandName, "release_ticket") == 0) {
            releaseTicket(schedulerManager->getScheduler(TrainID(argMap['i'])), Date(argMap['d']));
        } else if (strcmp(commandName, "expire_ticket") == 0) {
            expireTicket(TrainID(argMap['i']), Date(argMap['d']));
        } else if (strcmp(commandName, "display_route") == 0) {
            findAllRoute(stationManager->getStationID(argMap['s']), stationManager->getStationID(argMap['t']));
        } else if (strcmp(commandName, "query_best_path") == 0) {
            int preference = -1;
            if (strcmp(argMap['p'], "time") == 0) {
                preference = 1;
            } else if (strcmp(argMap['p'], "price") == 0) {
                preference = 0;
            } else {
                std::cout << "Invalid preference: " << argMap['p'] << std::endl;
            }
            if (preference != -1) {
                findBestRoute(stationManager->getStationID(argMap['s']), stationManager->getStationID(argMap['t']), preference);
            }
        } else if (strcmp(commandName, "query_remaining") == 0) {
            int remaining = queryRemainingTicket(TrainID(argMap['i']), Date(argMap['d']), stationManager->getStationID(argMap['f']));
            std::cout << "Remaining ticket:" << remaining << std::endl;
        } else if (strcmp(commandName, "buy_ticket") == 0) {
            orderTicket(TrainID(argMap['i']), Date(argMap['d']), stationManager->getStationID(argMap['f']));
        } else if (strcmp(commandName, "query_order") == 0) {
            queryMyTicket();
        } else if (strcmp(commandName, "refund_ticket") == 0) {
            refundTicket(TrainID(argMap['i']), Date(argMap['d']), stationManager->getStationID(argMap['f']));
        } else if (strcmp(commandName, "query_accessibility") == 0) {
            bool result = railwayGraph->checkStationAccessibility(stationManager->getStationID(argMap['s']), stationManager->getStationID(argMap['t']));
            if (result) {
                std::cout << "Accessible." << std::endl;
            } else {
                std::cout << "Not accessible." << std::endl;
            }
        } else if (strcmp(commandName, "exit") == 0) {
            exitCode = 1;
        } else {
            std::cout << "Invalid command: " << commandName << std::endl;
            exitCode = -1;
        }
    }
    for (int i = 0; i < tokens.length(); ++i) {
        delete [](tokens.visit(i));
    }
    return exitCode;
}

}