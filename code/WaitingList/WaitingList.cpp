// 代码清单3-23　WaitingList 类的实现
#include "WaitingList.h"
#include <string.h>
#include <iostream>
#include "DateTime.h"
#include "PurchaseInfo.h"
#include "Queue.h"

namespace trainsys {

WaitingList::WaitingList() {}

WaitingList::~WaitingList() {}

void WaitingList::addToWaitingList(const PurchaseInfo &purchaseInfo) {
  purchaseQueue.enQueue(purchaseInfo);
}

void WaitingList::removeHeadFromWaitingList() {
  purchaseQueue.deQueue();
}

const PurchaseInfo WaitingList::getFrontPurchaseInfo() const {
  return purchaseQueue.getHead();
}

bool WaitingList::isEmpty() const { return purchaseQueue.isEmpty(); }

}  // namespace trainsys
