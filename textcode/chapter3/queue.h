// 代码清单3-1 队列抽象类的定义
#ifndef CHAPTER3_QUEUE_H
#define CHAPTER3_QUEUE_H

template <class elemType>
class queue {
 public:
  virtual void enQueue(const elemType &x) = 0;  // 入队
  virtual elemType deQueue() = 0;               // 出队
  virtual elemType getHead() const = 0;         // 读取队头元素
  virtual bool isEmpty() const = 0;             // 判队列空
  virtual ~queue() {}                           // 虚析构函数
};
#endif  // CHAPTER3_QUEUE_H
