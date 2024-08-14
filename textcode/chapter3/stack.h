// 代码清单3-11 栈的抽象类的定义
#ifndef CHAPTER3_STACK_H
#define CHAPTER3_STACK_H

template <class elemType>
class stack {
 public:
  virtual void push(const elemType &x) = 0;  // 进栈
  virtual elemType pop() = 0;                // 出栈
  virtual elemType top() const = 0;          // 读取栈顶元素
  virtual bool isEmpty() const = 0;          // 判栈空
  virtual ~stack() {}                        // 虚析构函数
};

#endif  // CHAPTER3_STACK_H
