// WaitingList 类的测试程序
// 编译命令：g++ WaitingList.cpp WaitingListTest.cpp DateTime.cpp -o code.out
// 样例输出：
// User: 1
// Date: 01-01
// DepartureStation: 295
// Type: Ordering

// User: 2
// Date: 02-02
// DepartureStation: 470
// Type: Ordering

// User: 3
// Date: 03-03
// DepartureStation: 626
// Type: Ordering

// User: 4
// Date: 04-04
// DepartureStation: 1318
// Type: Ordering

// User: 4
// Date: 04-04
// DepartureStation: 1318
// Type: Refunding

#include "WaitingList.h"
int main() {
  trainsys::WaitingList wl;
  wl.addToWaitingList(trainsys::PurchaseInfo(
      1, trainsys::TrainID("1462"), trainsys::Date(1, 1), 295, 1));
  wl.addToWaitingList(trainsys::PurchaseInfo(
      2, trainsys::TrainID("G8"), trainsys::Date(2, 2), 470, 1));
  wl.addToWaitingList(trainsys::PurchaseInfo(
      3, trainsys::TrainID("T110"), trainsys::Date(3, 3), 626, 1));
  wl.addToWaitingList(trainsys::PurchaseInfo(
      4, trainsys::TrainID("G18"), trainsys::Date(4, 4), 1318, 1));
  wl.addToWaitingList(trainsys::PurchaseInfo(
      4, trainsys::TrainID("G18"), trainsys::Date(4, 4), 1318, -1));
  while (!wl.isEmpty()) {
    std::cout << "User: " << wl.getFrontPurchaseInfo().getUser() << std::endl;
    std::cout << "Date: " << wl.getFrontPurchaseInfo().getDate() << std::endl;
    std::cout << "DepartureStation: "
              << wl.getFrontPurchaseInfo().getDepartureStation() << std::endl;
    std::cout << "Type: "
              << (wl.getFrontPurchaseInfo().isOrdering() ? "Ordering" : "Refunding")
              << std::endl << std::endl;
    wl.removeHeadFromWaitingList();
  }
  return 0;
}