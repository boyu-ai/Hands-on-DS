// 代码清单4-1 树的抽象类定义
template <class elemType>
class tree {
 public:
  virtual void clear() = 0;          // 清空树
  virtual bool isEmpty() const = 0;  // 判断树是否为空树
  // 返回树的根结点的值，如果根结点不存在，则返回一个特殊值flag
  virtual elemType getRoot(elemType flag) const = 0;
  // 返回结点x的父结点的值，如果x是根结点，则返回一个特殊值flag
  virtual elemType parent(elemType x, elemType fl ag) const = 0;
  // 返回结点x的第i个子结点的值，如果x不存在或x的第i个子结点不存在，则返回一个特殊值fl
  // ag
  virtual elemType child(elemType x, int i, elemType fl ag) const = 0;
  // 删除结点x的第i棵子树
  virtual void remove(elemType x, int i) = 0;
  virtual void traverse() const = 0;  // 访问树的每个结点
  virtual ~tree() {}
};
