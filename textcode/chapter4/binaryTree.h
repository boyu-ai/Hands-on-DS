// 代码清单4-3至4-8 采用链接存储的二叉树类的实现

#ifndef CHAPTER4_BINARYTREE_H
#define CHAPTER4_BINARYTREE_H
#include <iostream>

#include "../chapter3/linkQueue.h"
#include "btree.h"
using namespace std;

template <class elemType>
class binaryTree : public bTree<elemType> {
 private:
  struct Node {          // 二叉树的结点类
    Node *left, *right;  // 结点的左、右儿子的地址
    elemType data;       // 结点的数据
    Node() : left(nullptr), right(nullptr) {}
    Node(elemType item, Node *L = nullptr, Node *R = nullptr)
        : data(item), left(L), right(R) {}
    ~Node() {}
  };
  Node *root;  // 二叉树的根结点指针
 public:
  binaryTree() : root(nullptr) {}
  binaryTree(elemType x) { root = new Node(x); }
  ~binaryTree();
  void clear();
  void createTree(elemType flag);
  bool isEmpty() const;
  elemType getRoot(elemType flag) const;
  elemType lchild(elemType x, elemType flag) const;
  elemType rchild(elemType x, elemType flag) const;
  void delLeft(elemType x);
  void delRight(elemType x);
  void preOrder() const;
  void midOrder() const;
  void postOrder() const;
  void levelOrder() const;
  // 一般不在二叉链表中找父结点，因此标准操作中的找父结点的操作直接返回空值，不做额外的查找
  elemType parent(elemType x, elemType flag) const { return flag; }

 private:
  Node *find(elemType x, Node *t) const;
  void clear(Node *&t);
  void preOrder(Node *t) const;
  void midOrder(Node *t) const;
  void postOrder(Node *t) const;
};

template <class elemType>
bool binaryTree<elemType>::isEmpty() const {
  return root == nullptr;
}

template <class elemType>
elemType binaryTree<elemType>::getRoot(elemType flag) const {
  if (root == nullptr)
    return flag;
  else
    return root->data;
}

template <class elemType>
void binaryTree<elemType>::clear(binaryTree<elemType>::Node *&t) {
  if (t == nullptr) return;
  // 递归删除左、右子树
  clear(t->left);
  clear(t->right);
  delete t;
  t = nullptr;
}

template <class elemType>
void binaryTree<elemType>::clear() {
  clear(root);
}

template <class elemType>
binaryTree<elemType>::~binaryTree() {
  clear(root);
}

template <class elemType>
void binaryTree<elemType>::preOrder(binaryTree<elemType>::Node *t) const {
  if (t == nullptr) return;
  cout << t->data << ' ';
  preOrder(t->left);
  preOrder(t->right);
}

template <class elemType>
void binaryTree<elemType>::preOrder() const {
  cout << "\n前序遍历：";
  preOrder(root);
}

template <class elemType>
void binaryTree<elemType>::midOrder(binaryTree<elemType>::Node *t) const {
  if (t == nullptr) return;
  midOrder(t->left);
  cout << t->data << ' ';
  midOrder(t->right);
}

template <class elemType>
void binaryTree<elemType>::midOrder() const {
  cout << "\n中序遍历：";
  midOrder(root);
}

template <class elemType>
void binaryTree<elemType>::postOrder(binaryTree<elemType>::Node *t) const {
  if (t == nullptr) return;
  postOrder(t->left);
  postOrder(t->right);
  cout << t->data << ' ';
}

template <class elemType>
void binaryTree<elemType>::postOrder() const {
  cout << "\n后序遍历：";
  postOrder(root);
}

template <class elemType>
void binaryTree<elemType>::levelOrder() const {
  linkQueue<Node *> que;
  Node *tmp;

  cout << "\n层次遍历：";
  if (root == nullptr) return;
  que.enQueue(root);

  while (!que.isEmpty()) {
    tmp = que.deQueue();
    cout << tmp->data << ' ';
    if (tmp->left) que.enQueue(tmp->left);
    if (tmp->right) que.enQueue(tmp->right);
  }
}

template <class elemType>
typename binaryTree<elemType>::Node *binaryTree<elemType>::find(
    elemType x, binaryTree<elemType>::Node *t) const {
  Node *tmp;
  if (t == nullptr) return nullptr;
  if (t->data == x) return t;
  if (tmp = find(x, t->left))
    return tmp;
  else
    return find(x, t->right);
}

template <class elemType>
void binaryTree<elemType>::delLeft(elemType x) {
  Node *tmp = find(x, root);
  if (tmp == nullptr) return;
  clear(tmp->left);
}

template <class elemType>
void binaryTree<elemType>::delRight(elemType x) {
  Node *tmp = find(x, root);
  if (tmp == nullptr) return;
  clear(tmp->right);
}

template <class elemType>
elemType binaryTree<elemType>::lchild(elemType x, elemType flag) const {
  Node *tmp = find(x, root);
  if (tmp == nullptr || tmp->left == nullptr) return flag;

  return tmp->left->data;
}

template <class elemType>
elemType binaryTree<elemType>::rchild(elemType x, elemType flag) const {
  Node *tmp = find(x, root);
  if (tmp == nullptr || tmp->right == nullptr) return flag;

  return tmp->right->data;
}

template <class elemType>
void binaryTree<elemType>::createTree(elemType flag) {
  linkQueue<Node *> que;
  Node *tmp;
  elemType x, ldata, rdata;

  // 创建树，输入flag表示空
  cout << "\n输入根结点：";
  cin >> x;
  root = new Node(x);
  que.enQueue(root);

  while (!que.isEmpty()) {
    tmp = que.deQueue();
    cout << "\n输入" << tmp->data << "的两个子结点(" << flag << "表示空结点)：";
    cin >> ldata >> rdata;
    if (ldata != flag) que.enQueue(tmp->left = new Node(ldata));
    if (rdata != flag) que.enQueue(tmp->right = new Node(rdata));
  }

  cout << "create completed!\n";
}

#endif  // CHAPTER4_BINARYTREE_H
