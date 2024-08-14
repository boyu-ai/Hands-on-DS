// 代码清单4-2　二叉树的抽象类定义
template <class elemType>
class bTree {
 public:
  virtual void clear() = 0;          // 建立一棵空的二叉树
  virtual bool isEmpty() const = 0;  // 判别二叉树是否为空树
  // 返回二叉树的根结点的值，如果根结点不存在，则返回一个特殊值flag
  virtual elemType getRoot(elemType flag) const = 0;
  // 返回结点x的父结点的值，如果x是根结点，则返回一个特殊值flag
  virtual elemType parent(elemType x, elemType flag) const = 0;
  // 返回结点x的左子结点的值，如果x不存在或x的左子结点不存在，则返回一个特殊值flag
  virtual elemType lchild(elemType x, elemType flag) const = 0;
  // 返回结点x的右子结点的值，如果x不存在或x的右子结点不存在，则返回一个特殊值flag
  virtual elemType rchild(elemType x, elemType flag) const = 0;
  virtual void delLeft(elemType x) = 0;   // 删除结点x的左子树
  virtual void delRight(elemType x) = 0;  // 删除结点x的右子树
  virtual void preOrder() const = 0;      // 前序遍历二叉树
  virtual void midOrder() const = 0;      // 中序遍历二叉树
  virtual void postOrder() const = 0;     // 后序遍历二叉树
  virtual void levelOrder() const = 0;    // 层次遍历二叉树
  virtual ~bTree() {}                     // 虚析构函数
};
