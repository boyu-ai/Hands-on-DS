// 代码清单6-7至6-12 AVL树的实现
#ifndef CHAPTER6_AVLTREE_H
#define CHAPTER6_AVLTREE_H
#include <iostream>

#include "DynamicSearchTable.h"
using namespace std;
template <class KEY, class OTHER>
class AVLTree : public dynamicSearchTable<KEY, OTHER> {
  struct AVLNode {
    SET<KEY, OTHER> data;
    AVLNode *left;
    AVLNode *right;
    int height;  // 结点的高度

    AVLNode(const SET<KEY, OTHER> &element, AVLNode *lt, AVLNode *rt, int h = 1)
        : data(element), left(lt), right(rt), height(h) {}
  };

  AVLNode *root;

 public:
  AVLTree() { root = nullptr; }
  ~AVLTree() { makeEmpty(root); }
  SET<KEY, OTHER> *find(const KEY &x) const;
  void insert(const SET<KEY, OTHER> &x);
  void remove(const KEY &x);

 private:
  void insert(const SET<KEY, OTHER> &x, AVLNode *&t);
  bool remove(const KEY &x, AVLNode *&t);
  void makeEmpty(AVLNode *t);
  int height(AVLNode *t) const { return t == nullptr ? 0 : t->height; }
  void LL(AVLNode *&t);
  void RR(AVLNode *&t);
  void LR(AVLNode *&t);
  void RL(AVLNode *&t);
  int max(int a, int b) { return (a > b) ? a : b; }
  bool adjust(AVLNode *&t, int subTree);
};

template <class KEY, class OTHER>
SET<KEY, OTHER> *AVLTree<KEY, OTHER>::find(const KEY &x) const {
  AVLNode *t = root;

  while (t != nullptr && t->data.key != x)
    if (t->data.key > x)
      t = t->left;
    else
      t = t->right;

  if (t == nullptr)
    return nullptr;
  else
    return (SET<KEY, OTHER> *)t;
}
template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::LL(AVLNode *&t) {
  AVLNode *t1 = t->left;  // 未来的树根
  t->left = t1->right;
  t1->right = t;
  t->height = max(height(t->left), height(t->right)) + 1;
  t1->height = max(height(t1->left), height(t)) + 1;
  t = t1;
}

template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::RR(AVLNode *&t) {
  AVLNode *t1 = t->right;
  t->right = t1->left;
  t1->left = t;
  t->height = max(height(t->left), height(t->right)) + 1;
  t1->height = max(height(t1->right), height(t)) + 1;
  t = t1;
}
template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::LR(AVLNode *&t) {
  RR(t->left);
  LL(t);
}

template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::RL(AVLNode *&t) {
  LL(t->right);
  RR(t);
}
template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
  insert(x, root);
}

template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, AVLNode *&t) {
  if (t == nullptr)  // 在空树上插入
    t = new AVLNode(x, nullptr, nullptr);
  else if (x.key < t->data.key) {  // 在左子树上插入
    insert(x, t->left);
    if (height(t->left) - height(t->right) == 2)  // t失衡
      if (x.key < t->left->data.key)
        LL(t);  // LL情况
      else
        LR(t);                       // LR情况
  } else if (t->data.key < x.key) {  // 在右子树上插入
    insert(x, t->right);
    if (height(t->right) - height(t->left) == 2)  // t失衡
      if (t->right->data.key < x.key)
        RR(t);  // RR情况
      else
        RL(t);  // RL情况
  }
  // 重新计算t的高度
  t->height = max(height(t->left), height(t->right)) + 1;
}

template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::remove(const KEY &x) {
  remove(x, root);
}

template <class KEY, class OTHER>
bool AVLTree<KEY, OTHER>::remove(const KEY &x, AVLNode *&t) {
  if (t == nullptr) return true;
  if (x == t->data.key) {  // 删除根结点
    if (t->left == nullptr || t->right == nullptr) {
      // 待删除结点是叶结点或只有一个子结点的结点
      AVLNode *oldNode = t;
      t = (t->left != nullptr) ? t->left : t->right;
      delete oldNode;
      return false;
    } else {
      // 待删除结点有两个子结点
      AVLNode *tmp = t->right;
      while (tmp->left != nullptr) tmp = tmp->left;
      t->data = tmp->data;
      if (remove(tmp->data.key, t->right)) return true;  // 删除后右子树没有变矮
      return adjust(t, 1);
    }
  }

  if (x < t->data.key) {                  // 在左子树上删除
    if (remove(x, t->left)) return true;  // 删除后左子树没有变矮
    return adjust(t, 0);
  } else {                                 // 在右子树上删除
    if (remove(x, t->right)) return true;  // 删除后右子树没有变矮
    return adjust(t, 1);
  }
}

template <class KEY, class OTHER>
bool AVLTree<KEY, OTHER>::adjust(AVLNode *&t, int subTree) {
  if (subTree) {  //  在右子树上删除，使右子树变矮
    if (height(t->left) - height(t->right) == 1) return true;  // 情况1
    if (height(t->right) == height(t->left)) {  // 情况2
      --t->height;
      return false;
    }
    if (height(t->left->right) > height(t->left->left)) {  // 情况3.2
      LR(t);
      return false;
    }
    LL(t);
    if (height(t->right) == height(t->left))  // 情况3.1
      return false;
    else	// 情况3.3
      return true;
  } else {
    if (height(t->right) - height(t->left) == 1) return true; 	// 情况1
    if (height(t->right) == height(t->left)) {					// 情况2
      --t->height;
      return false;
    }
    if (height(t->right->left) > height(t->right->right)) {  	// 情况3.2
      RL(t);
      return false;
    }
    RR(t);
    if (height(t->right) == height(t->left))  // 情况3.1
      return false;
    else	// 情况3.3
      return true;
  }
}

template <class KEY, class OTHER>
void AVLTree<KEY, OTHER>::makeEmpty(AVLNode *t) {
  if (t == nullptr) return;
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
}

#endif  // CHAPTER6_AVLTREE_H
