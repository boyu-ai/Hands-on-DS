// 代码清单6-13至6-16 红黑树类的实现

#ifndef CHAPTER6_REDBLACKTREE_H
#define CHAPTER6_REDBLACKTREE_H

#include <iostream>

#include "../chapter5/set.h"
#include "dynamicSearchTable.h"
using namespace std;

template <class KEY, class OTHER>
class redBlackTree : public dynamicSearchTable<KEY, OTHER> {
 private:
  enum Color { RED, BLACK };  // 结点颜色的枚举类型

  class redBlackNode {
   public:
    Color color;
    redBlackNode *parent;        // 父结点
    redBlackNode *left, *right;  // 左、右子结点

    SET<KEY, OTHER> data;

    redBlackNode() = default;
    redBlackNode(Color color, const SET<KEY, OTHER> &element,
        redBlackNode *pt = nullptr, redBlackNode *lt = nullptr,
        redBlackNode *rt = nullptr)
        : data(element) {
      this->color = color;
      parent = pt, left = lt, right = rt;
    }
    ~redBlackNode() = default;
  };

 private:
  redBlackNode *root;

 public:
  redBlackTree() { root = nullptr; }
  ~redBlackTree() {
    if (root) makeEmpty(root);
  }
  SET<KEY, OTHER> *find(const KEY &x) const;
  void insert(const SET<KEY, OTHER> &x);
  void remove(const KEY &x);

 private:
  /**
   * @brief 工具函数, 用于递归析构
   *
   * @param t 当前子树的根
   */
  void makeEmpty(redBlackNode *t);

  void LL(redBlackNode *t);
  void RR(redBlackNode *t);
  void LR(redBlackNode *t);
  void RL(redBlackNode *t);

  /**
   * @brief 结点u与其父亲结点可能均为红色, 此函数将调整树结构使其重新平衡
   *
   * @param u
   */
  void insertionRebalance(redBlackNode *u);

  /**
   * @brief 以结点u为根的子树恰缺少一个黑色结点,
   * 此函数将调整红黑树结构使其重新平衡
   *
   * @param u 子树的根结点
   */
  void removalRebalance(redBlackNode *u);
  void insert(const SET<KEY, OTHER> &x, redBlackNode *p, redBlackNode *&t);
  void remove(const KEY &x, redBlackNode *&t);
};

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::makeEmpty(redBlackNode *t) {
  if (t->left) makeEmpty(t->left);
  if (t->right) makeEmpty(t->right);
  delete t;
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::LL(redBlackNode *t) {
  redBlackNode *tmp = t->left;
  t->left = tmp->right;
  if (tmp->right) tmp->right->parent = t;
  tmp->right = t;
  tmp->parent = t->parent;
  if (t->parent != nullptr) {
    if (t->parent->left == t)
      t->parent->left = tmp;
    else
      t->parent->right = tmp;
  } else
    root = tmp;
  t->parent = tmp;
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::RR(redBlackNode *t) {
  redBlackNode *tmp = t->right;
  t->right = tmp->left;
  if (tmp->left) tmp->left->parent = t;
  tmp->left = t;
  tmp->parent = t->parent;
  if (t->parent != nullptr) {
    if (t->parent->left == t)
      t->parent->left = tmp;
    else
      t->parent->right = tmp;
  } else
    root = tmp;
  t->parent = tmp;
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::LR(redBlackNode *t) {
  RR(t->left);
  LL(t);
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::RL(redBlackNode *t) {
  LL(t->right);
  RR(t);
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *redBlackTree<KEY, OTHER>::find(const KEY &x) const {
  redBlackNode *t = root;
  while (t != nullptr) {
    if (x == t->data.key) return &t->data;
    if (x < t->data.key)
      t = t->left;
    else
      t = t->right;
  }
  return nullptr;
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::insertionRebalance(redBlackNode *u) {
  if (u == nullptr) return;

  while (u != root) {
    redBlackNode *p = u->parent;  // 父结点p
    if (p->color == BLACK)
      break;  // 如果父结点为黑色结点，则说明不再出现相邻的红色结点，可以结束调整
    redBlackNode *g = p->parent;                            // 祖父结点g
    redBlackNode *s = (p == g->left) ? g->right : g->left;  // 叔结点s

    // 情况2: 结点s为黑色结点(或不存在)，旋转与重新着色
    if (s != nullptr && s->color == RED) {
      p->color = BLACK;
      s->color = BLACK;
      g->color = RED;
      u = g;
    }
    // 情况2: 结点s为黑色(或不存在), 旋转与重新着色
    else {
      // 仔细分析情况2.1和情况2.2，可以发现它们的处理方式等价于
      // 分类讨论后染色并执行LR（RL）单旋转或LL（RR）单旋转
      if (p == g->left && u == p->left) {
        p->color = BLACK;
        g->color = RED;
        LL(g);
      } else if (p == g->left && u == p->right) {
        u->color = BLACK;
        g->color = RED;
        LR(g);
      } else if (p == g->right && u == p->left) {
        u->color = BLACK;
        g->color = RED;
        RL(g);
      } else if (p == g->right && u == p->right) {
        p->color = BLACK;
        g->color = RED;
        RR(g);
      }
      break;  // 无论哪种情况都可以完成调整
    }
  }
  root->color = BLACK;
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
  insert(x, nullptr, root);
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::insert(
    const SET<KEY, OTHER> &x, redBlackNode *p, redBlackNode *&t) {
  if (t == nullptr) {
    t = new redBlackNode(RED, x, p);
    insertionRebalance(t);
  } else if (x.key < t->data.key) {
    insert(x, t, t->left);
  } else if (x.key > t->data.key) {
    insert(x, t, t->right);
  }
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::removalRebalance(redBlackNode *u) {
  if (u == nullptr) return;
  while (u != root) {
    redBlackNode *p = u->parent;  // 结点u的父结点p
    redBlackNode *s = (u == p->left) ? p->right : p->left;  // 结点u的兄弟结点s

    // 情况1: 结点s为红色结点
    if (s->color == RED) {
      p->color = RED;
      s->color = BLACK;
      if (s == p->left)
        LL(p);
      else
        RR(p);
    } else {
      // 关注结点s的子结点的颜色
      bool leftIsRed = s->left != nullptr && s->left->color == RED;
      bool rightIsRed = s->right != nullptr && s->right->color == RED;

      // 情况2.1:结点s是黑色结点，它的子结点都是黑色结点（或不存在）
      if (!leftIsRed && !rightIsRed) {
        // 情况2.1.1:父结点p是红色结点，可以通过重新染色完成调整
        if (p->color == RED) {
          s->color = RED;
          p->color = BLACK;
          break;
        }
        // 情况2.1.2:父结点p是黑色结点，仍需要递归向上调整
        else {
          s->color = RED;
          u = p;
        }
      }
      // 情况2.2:
      // 结点s为黑色结点，s的内侧子结点是红色结点（s是p的右子结点）
      else if (s == p->right && leftIsRed) {
        s->left->color = BLACK;
        s->color = RED;
        LL(s);
      }
      // 情况2.2:
      // 结点s为黑色结点，s的内侧子结点是红色结点（s是p的左子结点）
      else if (s == p->left && rightIsRed) {
        s->right->color = BLACK;
        s->color = RED;
        RR(s);
      }
      // 情况2.3:
      // 结点s为黑色结点，s的外侧子结点是红色结点（s是p的右子结点）
      else if (s == p->right && rightIsRed) {
        s->color = p->color;
        p->color = BLACK;
        s->right->color = BLACK;
        RR(p);
        break;
      }
      // 情况2.3:
      // 结点s为黑色结点，s的外侧子结点是红色结点（s是p的左子结点）
      else if (s == p->left && leftIsRed) {
        s->color = p->color;
        p->color = BLACK;
        s->left->color = BLACK;
        LL(p);
        break;
      }
    }
  }
  root->color = BLACK;
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::remove(const KEY &x) {
  remove(x, root);
}

template <class KEY, class OTHER>
void redBlackTree<KEY, OTHER>::remove(const KEY &x, redBlackNode *&t) {
  if (!t) return;

  // 步骤1：找到需要删除的结点t
  if (x == t->data.key) {
    // 步骤2：确定替换结点v
    if (t->left != nullptr && t->right != nullptr) {
      // 类似于二叉搜索树的删除,用后继结点替换
      redBlackNode *tmp = t->right;
      while (tmp->left != nullptr) tmp = tmp->left;
      t->data = tmp->data;
      remove(tmp->data.key, t->right);
    } else {
      redBlackNode *v = nullptr;  // 结点v用于替换待删除结点t
      if (t->left) v = t->left;
      if (t->right) v = t->right;

      // 步骤3：调整红黑树, 使删除结点t后的树仍然平衡
      if (t->color == BLACK) {
        if (v && v->color == RED)
          v->color = BLACK;
        else
          removalRebalance(t);
      }

      // 步骤4: 删除结点t
      if (v) v->parent = t->parent;
      delete t;
      t = v;
    }
  } else if (x < t->data.key) {
    remove(x, t->left);
  } else {
    remove(x, t->right);
  }
}

#endif  // CHAPTER6_REDBLACKTREE_H
