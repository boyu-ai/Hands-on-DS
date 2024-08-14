// 代码清单4-20　PrioritizedWaitingList 类的定义
#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include "Utils.h"
#include "PurchaseInfo.h"
#include "Queue.h"
#include "DateTime.h"

namespace trainsys {

class PrioritizedWaitingList {  // 带优先级的排队交易类
   private:
    priorityQueue<PurchaseInfo> purchaseQueue;

   public:
    PrioritizedWaitingList();
    ~PrioritizedWaitingList();
    // 将订单按照优先级插入队列的合适位置
    void addToPrioritizedWaitingList(const PurchaseInfo &purchaseInfo);       
    // 将队头的订单移出队列
    void removeHeadFromPrioritizedWaitingList(); 
    // 获取队头的订单 
    const PurchaseInfo getFrontPurchaseInfo() const; 
    // 判断队列是否为空 
    bool isEmpty() const;        
};

}  // namespace trainsys

#endif  // PRORITIZEDWAITINGLIST_H