#ifndef QUEUE_H_
#define QUEUE_H_

namespace trainsys {

template <class elemType>
class queue {
 public:
  virtual void enQueue(const elemType &x) = 0;  // 入队
  virtual elemType deQueue() = 0;               // 出队
  virtual elemType getHead() const = 0;         // 读取队头元素
  virtual bool isEmpty() const = 0;             // 判队列空
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

template <class elemType>
linkQueue<elemType>::~linkQueue() {
  node *tmp;
  while (front != nullptr) {
    tmp = front;
    front = front->next;
    delete tmp;
  }
}

template <class elemType>
bool linkQueue<elemType>::isEmpty() const {
  return front == nullptr;
}

template <class elemType>
elemType linkQueue<elemType>::getHead() const {
  return front->data;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
  if (rear == nullptr)  // 入队前为空队列
    front = rear = new node(x);
  else
    rear = rear->next = new node(x);
}

template <class elemType>
elemType linkQueue<elemType>::deQueue() {
  node *tmp = front;
  elemType value = front->data;
  front = front->next;
  if (front == nullptr) rear = nullptr;  // 出队后为空队列
  delete tmp;
  return value;
}

template <class Type>
class priorityQueue : public queue<Type> {
 public:
  priorityQueue(int capacity = 100);
  priorityQueue(const Type data[], int size) {}
  ~priorityQueue();
  bool isEmpty() const;
  void enQueue(const Type &x);
  Type deQueue();
  Type getHead() const;

 private:
  int currentSize;
  Type *array;
  int maxSize;

  void doubleSpace();
  void percolateDown(int hole);
};

template <class Type>
priorityQueue<Type>::priorityQueue(int capacity) {
  array = new Type[capacity];
  maxSize = capacity;
  currentSize = 0;
}

template <class Type>
priorityQueue<Type>::~priorityQueue() {
  delete[] array;
}

template <class Type>
bool priorityQueue<Type>::isEmpty() const {
  return currentSize == 0;
}

template <class Type>
Type priorityQueue<Type>::getHead() const {
  return array[1];
}
template <class Type>
void priorityQueue<Type>::doubleSpace() {
  Type *tmp = array;

  maxSize *= 2;
  array = new Type[maxSize];
  for (int i = 0; i <= currentSize; ++i) array[i] = tmp[i];
  delete[] tmp;
}

template <class Type>
void priorityQueue<Type>::enQueue(const Type &x) {
  if (currentSize == maxSize - 1) doubleSpace();

  // 向上过滤
  int hole = ++currentSize;
  for (; hole > 1 && x < array[hole / 2]; hole /= 2)
    array[hole] = array[hole / 2];
  array[hole] = x;
}

template <class Type>
Type priorityQueue<Type>::deQueue() {
  Type minItem;
  minItem = array[1];  // 根结点保存的是二叉堆的最小值
  array[1] =
      array[currentSize--];  // 将二叉堆的最后一个元素移到根结点
  percolateDown(1);  // 将根结点的元素向下过滤
  return minItem;
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole) {
  int child;
  // 将待过滤结点的值保存在tmp中
  Type tmp = array[hole];

  // 向下过滤
  // hole中保存了空结点的位置
  for (; hole * 2 <= currentSize; hole = child) {
    child = hole * 2;  // 找到结点的左儿子
    if (child != currentSize && array[child + 1] < array[child])
      child++;  // child变量保存左、右子结点中值较小的子结点
    // child变量保存了左右儿子中较小的儿子，并继续向下过滤
    // 如果tmp比child大，那么由child代替空结点，空结点则向下过滤了一层
    if (array[child] < tmp)
      array[hole] = array[child];
    else
      break;  // 当前的空结点是一个符合规定的位置，向下过滤结束
  }
  array[hole] = tmp;  // 将待过滤结点的值写入空结点
}

}  // namespace trainsys

#endif