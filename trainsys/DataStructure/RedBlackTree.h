#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include "SearchTable.h"

namespace trainsys {

template <class KeyType, class ValueType>
class RedBlackTree : public DynamicSearchTable<KeyType, ValueType> {
   private:
    enum Color { RED, BLACK };

    class RedBlackNode {
       public:
        Color color;           // 颜色 (红色或黑色)
        RedBlackNode *parent;  // 父亲结点
        RedBlackNode *left;    // 左儿子
        RedBlackNode *right;   // 右儿子

        DataType<KeyType, ValueType> data;

        RedBlackNode() = default;
        RedBlackNode(Color color, const DataType<KeyType, ValueType> &element, RedBlackNode *pt = nullptr,
            RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr)
            : data(element) {
            this->color = color;
            parent = pt, left = lt, right = rt;
        }
        ~RedBlackNode() = default;
    };

   private:
    RedBlackNode *root;

   public:
    RedBlackTree();
    ~RedBlackTree();

   private:
    /**
     * @brief 工具函数, 用于递归析构
     *
     * @param u 当前子树的根
     */
    void makeEmpty(RedBlackNode *u);

    void LL(RedBlackNode *t);
    void RR(RedBlackNode *t);
    void LR(RedBlackNode *t);
    void RL(RedBlackNode *t);

    /**
     * @brief 结点u与其父亲结点可能均为红色, 此函数将调整树结构使其重新平衡
     *
     * @param u
     */
    void insertionRebalance(RedBlackNode *u);

    /**
     * @brief 以结点u为根的子树恰缺少一个黑色结点, 此函数将调整红黑树结构使其重新平衡
     *
     * @param u 子树的根结点
     */
    void removalRebalance(RedBlackNode *u);

   public:
    DataType<KeyType, ValueType> *find(const KeyType &x) const;
    void insert(const DataType<KeyType, ValueType> &x);
    void remove(const KeyType &x);

   private:
    void insert(const DataType<KeyType, ValueType> &x, RedBlackNode *p, RedBlackNode *&t);
    void remove(const KeyType &x, RedBlackNode *&t);
};

template <class KeyType, class ValueType>
RedBlackTree<KeyType, ValueType>::RedBlackTree() {
    root = nullptr;
}

template <class KeyType, class ValueType>
RedBlackTree<KeyType, ValueType>::~RedBlackTree() {
    if (root != nullptr) makeEmpty(root);
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::makeEmpty(RedBlackNode *u) {
    if (u->left) makeEmpty(u->left);
    if (u->right) makeEmpty(u->right);
    delete u;
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::LL(RedBlackNode *t) {
    RedBlackNode *tmp = t->left;
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
    t = tmp;
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::RR(RedBlackNode *t) {
    RedBlackNode *tmp = t->right;
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
    t = tmp;
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::LR(RedBlackNode *t) {
    RR(t->left);
    LL(t);
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::RL(RedBlackNode *t) {
    LL(t->right);
    RR(t);
}

template <class KeyType, class ValueType>
DataType<KeyType, ValueType> *RedBlackTree<KeyType, ValueType>::find(const KeyType &x) const {
    RedBlackNode *t = root;
    while (t != nullptr) {
        if (x == t->data.key) return &t->data;
        if (x < t->data.key)
            t = t->left;
        else
            t = t->right;
    }
    return nullptr;
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::insertionRebalance(RedBlackNode *u) {
    if (u == nullptr) return;

    while (u != root) {
        RedBlackNode *p = u->parent;   // 父亲结点p
        if (p->color == BLACK) break;  // 如果不再出现相邻的红色结点, 可以结束调整

        RedBlackNode *g = p->parent;                            // 祖父结点g
        RedBlackNode *s = (p == g->left) ? g->right : g->left;  // 父亲结点p的兄弟结点s

        // 情况1: 结点s为红色, 重新着色并递归向上调整
        if (s != nullptr && s->color == RED) {
            p->color = BLACK;
            s->color = BLACK;
            g->color = RED;
            u = g;
        }
        // 情况2: 结点s为黑色(或不存在), 旋转与重新着色
        else {
            // 仔细分析情况2.1和2.2, 可以发现它们的处理方式等价于
            // 分类讨论后染色并进行 LL,LR,RL,RR 旋转
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

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::insert(const DataType<KeyType, ValueType> &x) {
    insert(x, nullptr, root);
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::insert(const DataType<KeyType, ValueType> &x, RedBlackNode *p, RedBlackNode *&t) {
    if (t == nullptr) {
        t = new RedBlackNode(RED, x, p);
        insertionRebalance(t);
    } else if (x.key < t->data.key) {
        insert(x, t, t->left);
    } else if (x.key > t->data.key) {
        insert(x, t, t->right);
    }
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::removalRebalance(RedBlackNode *u) {
    if (u == nullptr) return;
    while (u != root) {
        RedBlackNode *p = u->parent;                            // 结点u的父亲结点p
        RedBlackNode *s = (u == p->left) ? p->right : p->left;  // 结点u的兄弟结点s

        // 情况1: 结点s为红色
        if (s->color == RED) {
            p->color = RED;
            s->color = BLACK;
            if (s == p->left)
                LL(p);
            else
                RR(p);
        } else {
            // 关注结点s的子结点的颜色
            bool leftBlackOrNil = s->left == nullptr || s->left->color == BLACK;
            bool rightBlackOrNil = s->right == nullptr || s->right->color == BLACK;

            // 情况2: 结点s为黑色(或不存在), 它的子结点都是黑色(或不存在)
            if (leftBlackOrNil && rightBlackOrNil) {
                // 情况2.1: 父结点p是红色, 可以通过重新染色完成调整
                if (p->color == RED) {
                    s->color = RED;
                    p->color = BLACK;
                    break;
                }
                // 情况2.2: 父结点是黑色, 仍需递归向上调整
                else {
                    s->color = RED;
                    u = p;
                }
            } else {
                // 先处理u是p的左孩子的情况
                if (u == p->left) {
                    // 情况3: 结点s为黑色(或不存在), 它特定的一侧结点也是黑色的(或不存在)
                    if (rightBlackOrNil) {
                        s->left->color = BLACK;
                        s->color = RED;
                        LL(s);
                    }
                    // 情况4: 结点s为黑色(或不存在), 它特定的一侧结点是红色的
                    else {
                        s->color = p->color;
                        p->color = BLACK;
                        s->right->color = BLACK;
                        RR(p);
                        break;  // 可以完成调整
                    }
                }
                // 再处理u是p的右孩子的情况
                else {
                    if (leftBlackOrNil) {
                        s->right->color = BLACK;
                        s->color = RED;
                        RR(s);
                    } else {
                        s->color = p->color;
                        p->color = BLACK;
                        s->left->color = BLACK;
                        LL(p);
                        break;
                    }
                }
            }
        }
    }
    root->color = BLACK;
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::remove(const KeyType &x) {
    remove(x, root);
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::remove(const KeyType &x, RedBlackNode *&t) {
    if (!t) return;

    // 步骤1: 找到需要删除的结点t
    if (x == t->data.key) {
        // 步骤2: 确定替换结点v
        if (t->left != nullptr && t->right != nullptr) {
            // 类似于二叉搜索树的删除, 用后继结点替换
            RedBlackNode *tmp = t->right;
            while (tmp->left != nullptr) tmp = tmp->left;
            t->data = tmp->data;
            remove(tmp->data.key, t->right);
        } else {
            RedBlackNode *v = nullptr;  // 结点v用于替换被删除的结点t
            if (t->left) v = t->left;
            if (t->right) v = t->right;

            // 步骤3: 调整红黑树, 使删除结点t后树仍然平衡
            if (t->color == BLACK) {
                if (v && v->color == RED)
                    v->color = BLACK;
                else
                    removalRebalance(t);
            }

            // 步骤4: 删除结点tf
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

}  // namespace trainsys

#endif  // REB_BLACK_TREE_H_
