// 代码清单6-2至6-6 二叉查找树类的定义和实现

#ifndef CHAPTER6_BINARYSEARCHTREE_H
#define CHAPTER6_BINARYSEARCHTREE_H

#include <iostream>

#include "dynamicSearchTable.h"
using namespace std;

template <class KEY, class OTHER>
class binarySearchTree : public dynamicSearchTable<KEY, OTHER> {
 private:
  struct binaryNode {
    SET<KEY, OTHER> data;
    binaryNode *left;
    binaryNode *right;

    binaryNode(const SET<KEY, OTHER> &thedata,
        binaryNode *lt = nullptr, binaryNode *rt = nullptr)
        : data(thedata), left(lt), right(rt) {}
  };
  binaryNode *root;

 public:
  binarySearchTree();
  ~binarySearchTree();
  SET<KEY, OTHER> *find(const KEY &x) const;
  void insert(const SET<KEY, OTHER> &x);
  void remove(const KEY &x);

 private:
  // 递归插入，将键值为x的结点插入以t为根结点的子树
  void insert(const SET<KEY, OTHER> &x, binaryNode *&t);
  // 递归删除以t为根结点的子树中的键值为x的结点
  void remove(const KEY &x, binaryNode *&t);
  // 在以t为根结点的子树中递归查找键值为x的结点
  SET<KEY, OTHER> *find(const KEY &x, binaryNode *t) const;
  // 删除以t为根结点的子树上的所有结点
  void makeEmpty(binaryNode *t);
};

template <class KEY, class OTHER>
SET<KEY, OTHER> *binarySearchTree<KEY, OTHER>::find(
    const KEY &x) const {
  return find(x, root);
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *binarySearchTree<KEY, OTHER>::find(
    const KEY &x, binaryNode *t) const {
  if (t == nullptr || t->data.key == x)  //  找到或不存在
    return (SET<KEY, OTHER> *)t;
  if (x < t->data.key)
    return find(x, t->left);  // 继续查找左子树
  else
    return find(x, t->right);  // 继续查找右子树
}
template <class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
  insert(x, root);
}

template <class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::insert(
    const SET<KEY, OTHER> &x, binaryNode *&t) {
  if (t == nullptr)
    t = new binaryNode(x, nullptr, nullptr);
  else if (x.key < t->data.key)
    insert(x, t->left);
  else if (t->data.key < x.key)
    insert(x, t->right);
}
template <class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::remove(const KEY &x) {
  remove(x, root);
}

template <class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::remove(const KEY &x, binaryNode *&t) {
  if (t == nullptr) return;  // 待删除结点不存在
  if (x < t->data.key)
    remove(x, t->left);
  else if (t->data.key < x)
    remove(x, t->right);
  // 上面3种情况还没有定位待删除结点，执行递归查找
  // 下面2种情况是找到了待删除结点，即此时t为待删除结点
  else if (t->left != nullptr && t->right != nullptr) {  
    // 有两个子结点的情况
    binaryNode *tmp = t->right;
    // 循环找左儿子，直到找到没有左儿子的结点，将内存地址保存在tmp中
    while (tmp->left != nullptr) tmp = tmp->left;  
    t->data = tmp->data;  // 用右子树的键值最小的结点替换待删除结点t
    remove(t->data.key, t->right);  // 将结点tmp删除
  } else {  // 待删除结点是叶结点或只有一个儿子
    binaryNode *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }
}
template <class KEY, class OTHER>
binarySearchTree<KEY, OTHER>::binarySearchTree() {
  root = nullptr;
}

template <class KEY, class OTHER>
void binarySearchTree<KEY, OTHER>::makeEmpty(binaryNode *t) {
  if (t == nullptr) return;
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
}

template <class KEY, class OTHER>
binarySearchTree<KEY, OTHER>::~binarySearchTree() {
  makeEmpty(root);
}

#endif  // CHAPTER6_BINARYSEARCHTREE_H
