// 代码清单4-20　PrioritizedWaitingList 类的实现
#include "PrioritizedWaitingList.h"
#include <string.h>
#include <iostream>
#include "DateTime.h"

namespace trainsys {

PrioritizedWaitingList::PrioritizedWaitingList() {}

PrioritizedWaitingList::~PrioritizedWaitingList() {}

void PrioritizedWaitingList::addToPrioritizedWaitingList(
    const PurchaseInfo &purchaseInfo) {
  purchaseQueue.enQueue(purchaseInfo);
}

void PrioritizedWaitingList::removeHeadFromPrioritizedWaitingList() {
  purchaseQueue.deQueue();
}

const PurchaseInfo PrioritizedWaitingList::getFrontPurchaseInfo() const {
  return purchaseQueue.getHead();
}

bool PrioritizedWaitingList::isEmpty() const {
  return purchaseQueue.isEmpty();
}

};  // namespace trainsys
