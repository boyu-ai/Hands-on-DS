// TripManager类的测试程序
// 编译命令：g++ TripManagerTest.cpp TripManager.cpp DateTime.cpp -o code.out
// 样例输出：
// TripList of User 1:
// TripInfo:
// trainID: G1234
// departureStation: 1
// arrivalStation: 2
// duration: 1
// price: 1
// date: 01-01

// TripInfo:
// trainID: G2345
// departureStation: 2
// arrivalStation: 3
// duration: 4
// price: 10
// date: 01-02

// TripList of User 2:
// TripInfo:
// trainID: G1234
// departureStation: 1
// arrivalStation: 2
// duration: 1
// price: 1
// date: 01-01

// Remove Trip 1 of User 1
// TripList of User 1:
// TripInfo:
// trainID: G2345
// departureStation: 2
// arrivalStation: 3
// duration: 4
// price: 10
// date: 01-02

// TripList of User 1:
// TripInfo:
// trainID: G2345
// departureStation: 2
// arrivalStation: 3
// duration: 4
// price: 10
// date: 01-02

// TripList of User 2:
// TripInfo:
// trainID: G1234
// departureStation: 1
// arrivalStation: 2
// duration: 1
// price: 1
// date: 01-01

#include "TripManager.h"

namespace trainsys {

UserID user1 = 1, user2 = 2;

void testInit() {
  // 旅程信息保存在文件中,如果相同名称的文件已经存在，需要先将文件删掉，以免影响测试
  if (std::ifstream("tripManager_leafFile")) {
    std::remove("tripManager_leafFile");
  }
  if (std::ifstream("tripManager_treeNodeFile")) {
    std::remove("tripManager_treeNodeFile");
  }
}

void testStage1() {
  TripManager tripManager("tripManager");
  TripInfo trip1((TrainID) "G1234", 1, 2, 1, 1, Date(1, 1));
  TripInfo trip2((TrainID) "G2345", 2, 3, 4, 10, Date(1, 2));
  tripManager.addTrip(user1, trip1);
  tripManager.addTrip(user1, trip2);
  tripManager.addTrip(user2, trip1);
  seqList<TripInfo> tripList1 = tripManager.queryTrip(user1);
  seqList<TripInfo> tripList2 = tripManager.queryTrip(user2);
  std::cout << "TripList of User 1:" << std::endl;
  for (int i = 0; i < tripList1.length(); ++i) {
    std::cout << tripList1.visit(i) << std::endl;
  }
  std::cout << "TripList of User 2:" << std::endl;
  for (int i = 0; i < tripList2.length(); ++i) {
    std::cout << tripList2.visit(i) << std::endl;
  }
  std::cout << "Remove Trip 1 of User 1" << std::endl;
  tripManager.removeTrip(user1, trip1);
  seqList<TripInfo> tripList3 = tripManager.queryTrip(user1);
  std::cout << "TripList of User 1:" << std::endl;
  for (int i = 0; i < tripList3.length(); ++i) {
    std::cout << tripList3.visit(i) << std::endl;
  }
}

void testStage2() {
  TripManager tripManager("tripManager");
  seqList<TripInfo> tripList1 = tripManager.queryTrip(user1);
  seqList<TripInfo> tripList2 = tripManager.queryTrip(user2);
  std::cout << "TripList of User 1:" << std::endl;
  for (int i = 0; i < tripList1.length(); ++i) {
    std::cout << tripList1.visit(i) << std::endl;
  }
  std::cout << "TripList of User 2:" << std::endl;
  for (int i = 0; i < tripList2.length(); ++i) {
    std::cout << tripList2.visit(i) << std::endl;
  }
}

void tripManagerTest() {
  testInit();
  testStage1();
  testStage2();
}
}  // namespace trainsys

int main() {
  trainsys::tripManagerTest();
  return 0;
}