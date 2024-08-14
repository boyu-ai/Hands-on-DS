// 采用链接存储的二叉树类的测试程序
// 首先，根据createTree函数的流程，构建二叉树
// 例如：
// 输入根结点：4
// 输入4的两个儿子(-1表示空结点)：1 2
// 输入1的两个儿子(-1表示空结点)：-1 5
// 输入2的两个儿子(-1表示空结点)：3 -1
// 输入5的两个儿子(-1表示空结点)：-1 -1
// 输入3的两个儿子(-1表示空结点)：-1 -1
// create completed!
// 现在的树的形状输出如下：
// 层次遍历：4 1 2 5 3
// 前序遍历：4 1 5 2 3
// 中序遍历：1 5 4 3 2
// 前序遍历：4 1 5 2 3
// 这时可以开始调用成员函数
// 输入： getRoot 输出：二叉树根的值为：4
// 输入：lchild 2 输出：The left child of node 2 is 3
// 输入：rchild 1 输出：The right child of node 1 is 5
// 输入：
// delLeft 2
// delRight 1
// print
// 输出：
// 现在的树的形状输出如下：
// 层次遍历：4 1 2
// 前序遍历：4 1 2
// 中序遍历：1 4 2
// 前序遍历：4 1 2
// exit

#include <cassert>
#include <cstring>
#include <iostream>

#include "binaryTree.h"
using namespace std;
const int N = 50, M = 10, W = 50;

void print_tree(binaryTree<int> *binary_tree) {
  // 测试输出整棵树
  cout << "现在的树的形状输出如下：";
  binary_tree->levelOrder();
  binary_tree->preOrder();
  binary_tree->midOrder();
  binary_tree->preOrder();
  cout << endl;
}
int main() {
  binaryTree<int> *binary_tree = new binaryTree<int>;
  binary_tree->createTree(-1);
  print_tree(binary_tree);
  assert(!binary_tree->isEmpty());
  while (true) {
    char op[30];
    cin >> op;
    if (strcmp(op, "delLeft") == 0) {
      int x;
      cin >> x;
      binary_tree->delLeft(x);
    } else if (strcmp(op, "delRight") == 0) {
      int x;
      cin >> x;
      binary_tree->delRight(x);
    } else if (strcmp(op, "getRoot") == 0) {
      cout << "二叉树根的值为：" << binary_tree->getRoot(-1) << endl;
    } else if (strcmp(op, "print") == 0) {
      print_tree(binary_tree);
    } else if (strcmp(op, "lchild") == 0) {
      int x;
      cin >> x;
      cout << "The left child of node " << x << " is "
           << binary_tree->lchild(x, -1) << endl;
    } else if (strcmp(op, "rchild") == 0) {
      int x;
      cin >> x;
      cout << "The right child of node " << x << " is "
           << binary_tree->rchild(x, -1) << endl;
    } else if (strcmp(op, "exit") == 0) {
      break;
    } else {
      cout << "Invalid operation!" << endl;
    }
  }
  return 0;
}