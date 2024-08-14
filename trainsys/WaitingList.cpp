#include "WaitingList.h"

namespace trainsys {

void WaitingList::addToWaitingList(const PurchaseInfo &purchaseInfo) {
    purchaseQueue.enQueue(purchaseInfo);
    listSize++;
}

void WaitingList::removeHeadFromWaitingList() {
    if (!purchaseQueue.isEmpty()) {
        purchaseQueue.deQueue();
        listSize--;
    }
}

const PurchaseInfo WaitingList::getFrontPurchaseInfo() const {
    return purchaseQueue.getHead();
}

bool WaitingList::isEmpty() const {
    return purchaseQueue.isEmpty();
}

bool WaitingList::isBusy() const {
    return listSize >= BUSY_STATE_TRESHOLD;
}

void PrioritizedWaitingList::addToWaitingList(const PurchaseInfo &purchaseInfo) {
    purchaseQueue.enQueue(purchaseInfo);
    listSize++;
}

void PrioritizedWaitingList::removeHeadFromWaitingList() {
    if (!purchaseQueue.isEmpty()) {
        purchaseQueue.deQueue();
        listSize--;
    }
}

const PurchaseInfo PrioritizedWaitingList::getFrontPurchaseInfo() const {
    return purchaseQueue.getHead();
}

bool PrioritizedWaitingList::isEmpty() const {
    return purchaseQueue.isEmpty();
}
    
bool PrioritizedWaitingList::isBusy() const {
    return listSize >= BUSY_STATE_TRESHOLD;
} 

} // namespace trainsys