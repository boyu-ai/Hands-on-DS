// TrainScheduler 类的测试程序
// 编译命令：g++ TrainScheduler.cpp TrainSchedulerTest.cpp -o code.out
// 样例输出：
// 0 295 470 626 912 1318
// 0 295 626 912 1318
// 0 295 626 912 1196 1318
// 4
// -1

#include <cstdio>
#include <iostream>

#include "TrainScheduler.h"
#include "Utils.h"

int main() {
  trainsys::TrainScheduler scheduler;
  trainsys::StationID stationID[6] = {0, 295, 470, 626, 912, 1318};
  for (int i = 0; i < 6; i++) { scheduler.addStation(stationID[i]); }
  scheduler.traverseStation();

  scheduler.removeStation(2);
  scheduler.traverseStation();

  trainsys::StationID newStation = 1196;
  scheduler.insertStation(4, newStation);
  scheduler.traverseStation();

  std::cout << scheduler.findStation(1196) << std::endl;
  std::cout << scheduler.findStation(1462) << std::endl;

  return 0;
}