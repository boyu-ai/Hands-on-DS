#ifndef WAITING_LIST_H_
#define WAITING_LIST_H_

#include "Utils.h"
#include "PurchaseInfo.h"
#include "DataStructure/Queue.h"

namespace trainsys {

class WaitingList {
private:
    linkQueue<PurchaseInfo> purchaseQueue;
    int listSize;
public:
    WaitingList(): purchaseQueue(), listSize(0) {}
    // PurchaseInfo 是在主逻辑里完成组装的
    void addToWaitingList(const PurchaseInfo &purchaseInfo); 
    void removeHeadFromWaitingList(); 
    const PurchaseInfo getFrontPurchaseInfo() const; 
    bool isEmpty() const;
    bool isBusy() const;
};

class PrioritizedWaitingList {
private:
    priorityQueue<PurchaseInfo> purchaseQueue;
    int listSize;
public:
    PrioritizedWaitingList(): purchaseQueue(), listSize(0) {}
    void addToWaitingList(const PurchaseInfo &purchaseInfo);
    void removeHeadFromWaitingList();
    const PurchaseInfo getFrontPurchaseInfo() const;
    bool isEmpty() const;
    bool isBusy() const;
};

} // namespace trainsys 

#endif // WAITING_LIST_H_