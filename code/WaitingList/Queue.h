#ifndef QUEUE_H_
#define QUEUE_H_

namespace trainsys {

template <class elemType>
class queue {
 public:
  virtual bool isEmpty() const = 0;             // 判队空
  virtual void enQueue(const elemType &x) = 0;  // 进队
  virtual elemType deQueue() = 0;               // 出队
  virtual elemType getHead() const = 0;         // 读队头元素
  virtual ~queue() {}                           // 虚析构函数
};

template <class elemType>
class linkQueue : public queue<elemType> {
 private:
  struct node {
    elemType data;
    node *next;
    node(const elemType &x, node *N = nullptr) {
      data = x;
      next = N;
    }
    node() : next(nullptr) {}
    ~node() {}
  };
  node *front, *rear;

 public:
  linkQueue();
  ~linkQueue();
  bool isEmpty() const;
  void enQueue(const elemType &x);
  elemType deQueue();
  elemType getHead() const;
};

template <class elemType>
linkQueue<elemType>::linkQueue() {
  front = rear = nullptr;
}

// linkQueue类的析构函数
template <class elemType>
linkQueue<elemType>::~linkQueue() {
  node *tmp;
  while (front != nullptr) {
    tmp = front;
    front = front->next;
    delete tmp;
  }
}

// 判断队列是否为空
template <class elemType>
bool linkQueue<elemType>::isEmpty() const {
  return front == nullptr;
}

// 读队头元素
template <class elemType>
elemType linkQueue<elemType>::getHead() const {
  return front->data;
}

// 进队
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
  if (rear == nullptr)  // 入队前为空队列
    front = rear = new node(x);
  else
    rear = rear->next = new node(x);
}

// 出队
template <class elemType>
elemType linkQueue<elemType>::deQueue() {
  node *tmp = front;
  elemType value = front->data;
  front = front->next;
  if (front == nullptr) rear = nullptr;  // 出队后为空队列
  delete tmp;
  return value;
}

}  // namespace trainsys

#endif