// TicketManager类的测试程序
// 编译命令：g++ ./TicketManager.cpp TicketManagerTest.cpp TrainScheduler.cpp DateTime.cpp -o code.out
// 样例输出：
// Release Tickets of G1234, Jan 1st
// Release Tickets of G1234, Jan 2nd
// Release Tickets of G1234, Jan 3rd
// Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: 10
// Remaining Tickets of G1234 from Station 2 to Station 3, Jan 1st: 10
// Buying 1 Ticket of G1234 from Station 1 to Station 2, Jan 1st
// Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: 9
// Remaining Tickets of G1234 from Station 2 to Station 3, Jan 4th: -1
// Expire Tickets of G1234, Jan 1st
// Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: -1
// Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: -1
// Remaining Tickets of G1234 from Station 2 to Station 3, Jan 2nd: 10
// Buying One Ticket of G1234 from Station 1 to Station 2, Jan 3rd
// Remaining Tickets of G1234 from Station 1 to Station 2, Jan 3rd: 9
// Refounding Tickets of G1234 from Station 1 to Station 2, Jan 3rd
// Remaining Tickets of G1234 from Station 1 to Station 2, Jan 3rd: 10
// Release Tickets of G5678, Jan 1st
// Remaining Tickets of G5678 from Station 1 to Station 2, Jan 1st: 10
// Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: -1

#include "TicketManager.h"

namespace trainsys {

TrainScheduler scheduler1, scheduler2;
Date date1(1, 1), date2(1, 2), date3(1, 3), date4(1, 4), date5(1, 5);

void testInit() {
  scheduler1.addStation(1);
  scheduler1.addStation(2);
  scheduler1.addStation(3);
  scheduler1.addStation(4);
  scheduler1.addStation(5);
  scheduler1.setDuration(new int[4]{1, 2, 3, 4});
  scheduler1.setPrice(new int[4]{1, 2, 3, 4});
  scheduler1.setSeatNumber(10);
  scheduler1.setTrainID((TrainID) "G1234");
  scheduler2.addStation(1);
  scheduler2.addStation(2);
  scheduler2.addStation(3);
  scheduler2.setDuration(new int[2]{1, 2});
  scheduler2.setPrice(new int[2]{1, 2});
  scheduler2.setSeatNumber(10);
  scheduler2.setTrainID((TrainID) "G5678");
  // 车票信息保存在文件。如果相同名称的文件已经存在，需要先将文件删掉，以免影响测试
  if (std::ifstream("ticketManager_leafFile")) {
    std::remove("ticketManager_leafFile");
  }
  if (std::ifstream("ticketManager_treeNodeFile")) {
    std::remove("ticketManager_treeNodeFile");
  }
}

void testStage1() {
  // 构造一个TicketManager对象，参数是车票信息保存的文件名
  TicketManager *ticketManager = new TicketManager("ticketManager");
  std::cout << "Release Tickets of G1234, Jan 1st" << std::endl;
  ticketManager->releaseTicket(scheduler1, date1);
  std::cout << "Release Tickets of G1234, Jan 2nd" << std::endl;
  ticketManager->releaseTicket(scheduler1, date2);
  std::cout << "Release Tickets of G1234, Jan 3rd" << std::endl;
  ticketManager->releaseTicket(scheduler1, date3);
  std::cout
      << "Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: "
      << ticketManager->querySeat((TrainID) "G1234", date1, 1) << std::endl;
  std::cout
      << "Remaining Tickets of G1234 from Station 2 to Station 3, Jan 1st: "
      << ticketManager->querySeat((TrainID) "G1234", date1, 2) << std::endl;
  std::cout << "Buying 1 Ticket of G1234 from Station 1 to Station 2, Jan 1st"
            << std::endl;
  ticketManager->updateSeat((TrainID) "G1234", date1, 1, -1);
  std::cout
      << "Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: "
      << ticketManager->querySeat((TrainID) "G1234", date1, 1) << std::endl;
  std::cout
      << "Remaining Tickets of G1234 from Station 2 to Station 3, Jan 4th: "
      << ticketManager->querySeat((TrainID) "G1234", date4, 2) << std::endl;
  // 这里输出的是-1，因为我们约定，如果没有找到符合条件的车票，就返回-1
  std::cout << "Expire Tickets of G1234, Jan 1st" << std::endl;
  ticketManager->expireTicket((TrainID) "G1234", date1);
  std::cout
      << "Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: "
      << ticketManager->querySeat((TrainID) "G1234", date1, 1) << std::endl;
  // 析构TicketManager对象
  delete ticketManager;
}

void testStage2() {
  // 重新构造一个TicketManager对象。他会从文件中读取车票信息
  TicketManager *ticketManager = new TicketManager("ticketManager");
  std::cout
      << "Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: "
      << ticketManager->querySeat((TrainID) "G1234", date1, 1) << std::endl;
  ticketManager->querySeat((TrainID) "G1234", date1, 1);
  std::cout
      << "Remaining Tickets of G1234 from Station 2 to Station 3, Jan 2nd: "
      << ticketManager->querySeat((TrainID) "G1234", date2, 2) << std::endl;
  std::cout << "Buying One Ticket of G1234 from Station 1 to Station 2, Jan 3rd"
            << std::endl;
  ticketManager->updateSeat((TrainID) "G1234", date3, 1, -1);
  std::cout
      << "Remaining Tickets of G1234 from Station 1 to Station 2, Jan 3rd: "
      << ticketManager->querySeat((TrainID) "G1234", date3, 1) << std::endl;
  std::cout
      << "Refounding Tickets of G1234 from Station 1 to Station 2, Jan 3rd"
      << std::endl;
  ticketManager->updateSeat((TrainID) "G1234", date3, 1, 1);
  std::cout
      << "Remaining Tickets of G1234 from Station 1 to Station 2, Jan 3rd: "
      << ticketManager->querySeat((TrainID) "G1234", date3, 1) << std::endl;
  std::cout << "Release Tickets of G5678, Jan 1st" << std::endl;
  ticketManager->releaseTicket(scheduler2, date1);
  std::cout
      << "Remaining Tickets of G5678 from Station 1 to Station 2, Jan 1st: "
      << ticketManager->querySeat((TrainID) "G5678", date1, 1) << std::endl;
  std::cout
      << "Remaining Tickets of G1234 from Station 1 to Station 2, Jan 1st: "
      << ticketManager->querySeat((TrainID) "G1234", date1, 1) << std::endl;
  delete ticketManager;
}

void TicketManagerTest() {
  testInit();
  testStage1();
  testStage2();
}
}  // namespace trainsys

int main() {
  trainsys::TicketManagerTest();
  return 0;
}