// 代码清单3-23　WaitingList 类的定义
#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include "DateTime.h"
#include "PurchaseInfo.h"
#include "Queue.h"
#include "Utils.h"

namespace trainsys {

class WaitingList {  // 排队交易类
 private:
  linkQueue<PurchaseInfo> purchaseQueue;

 public:
  WaitingList();
  ~WaitingList();
  // 将订单加入队列
  void addToWaitingList(const PurchaseInfo &purchaseInfo);
  // 将队头的订单移出队列
  void removeHeadFromWaitingList();
  // 获取队列头部的订单
  const PurchaseInfo getFrontPurchaseInfo() const;
  // 判断队列是否为空
  bool isEmpty() const;
};

}  // namespace trainsys

#endif  // WAITINGLIST_H