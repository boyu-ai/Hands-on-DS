// PrioritizedWaitingList 类的测试程序
// 编译命令：g++ PrioritizedWaitingList.cpp PrioritizedWaitingListTest.cpp DateTime.cpp -o code.out
// 样例输出：
// User: User2 with priviledge: 6
// Date: 02-02
// DepartureStation: 470
// Type: Ordering

// User: User3 with priviledge: 4
// Date: 03-03
// DepartureStation: 626
// Type: Ordering

// User: User4 with priviledge: 2
// Date: 04-04
// DepartureStation: 1318
// Type: Ordering

// User: User4 with priviledge: 2
// Date: 05-04
// DepartureStation: 1318
// Type: Ordering

// User: User4 with priviledge: 2
// Date: 05-04
// DepartureStation: 1318
// Type: Refunding

// User: User1 with priviledge: 0
// Date: 01-01
// DepartureStation: 295
// Type: Ordering

#include "PrioritizedWaitingList.h"

int main() {
    trainsys::PrioritizedWaitingList wl;
    wl.addToPrioritizedWaitingList(
        trainsys::PurchaseInfo(trainsys::User("User1", "Psd1", "Mail1", 0),
            trainsys::TrainID("1462"), trainsys::Date(1, 1), 295, 1));
    wl.addToPrioritizedWaitingList(
        trainsys::PurchaseInfo(trainsys::User("User2", "Psd2", "Mail2", 6), 
            trainsys::TrainID("G8"), trainsys::Date(2, 2), 470, 1));
    wl.addToPrioritizedWaitingList(
        trainsys::PurchaseInfo(trainsys::User("User3", "Psd3", "Mail3", 4),
            trainsys::TrainID("T110"), trainsys::Date(3, 3), 626, 1));
    wl.addToPrioritizedWaitingList(
        trainsys::PurchaseInfo(trainsys::User("User4", "Psd4", "Mail4", 2),
            trainsys::TrainID("G18"), trainsys::Date(5, 4), 1318, 1));
    wl.addToPrioritizedWaitingList(
        trainsys::PurchaseInfo(trainsys::User("User4", "Psd4", "Mail4", 2),
            trainsys::TrainID("G18"), trainsys::Date(5, 4), 1318, -1));
    wl.addToPrioritizedWaitingList(
        trainsys::PurchaseInfo(trainsys::User("User4", "Psd4", "Mail4", 2),
            trainsys::TrainID("G18"), trainsys::Date(4, 4), 1318, 1));
    while (!wl.isEmpty()) {
        std::cout << "User: " << wl.getFrontPurchaseInfo().getUser().getName()
                  << " with priviledge: " << wl.getFrontPurchaseInfo().getUser().getPrivilege()
                  << std::endl;
        std::cout << "Date: " << wl.getFrontPurchaseInfo().getDate() << std::endl;
        std::cout << "DepartureStation: " << wl.getFrontPurchaseInfo().getDepartureStation()
                  << std::endl;
        std::cout << "Type: " << (wl.getFrontPurchaseInfo().isOrdering() ? "Ordering" : "Refunding")
                  << std::endl << std::endl;
        wl.removeHeadFromPrioritizedWaitingList();
    }
    return 0;
}