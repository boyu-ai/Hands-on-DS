#include <fstream>
#include <iostream>
#include "StationManager.h"

namespace trainsys {

// 初始化类，从文件中读取车站信息
StationManager::StationManager(const char * filename) {
    std::ifstream fin;
    fin.open(filename, std::ios::in);
    if (!fin.is_open()) {
        puts("station info not found");
        return;
    }
    char stationName[MAX_STATIONNAME_LEN + 1];
    StationID stationID;
    puts("loading station info");
    while (fin >> stationName >> stationID) {
        idToName.insertEntry(stationID, String(stationName));
        nameToID.insertEntry(String(stationName), stationID);
    }
    idToName.sortEntry();
    nameToID.sortEntry();
}

// 根据车站ID获取车站名称
String StationManager::getStationName(const StationID &stationID) {
    return idToName.find(stationID);
}

// 根据车站名称获取车站ID
StationID StationManager::getStationID(const char * stationName) {
    return nameToID.find(String(stationName));
}

}
