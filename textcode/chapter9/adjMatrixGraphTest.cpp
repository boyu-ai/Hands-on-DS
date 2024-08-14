// 基于邻接矩阵的图类的测试程序
// 插入边：insert
// 查询边：exist
// 移除： remove
// 退出：exit
// 样例输入：
// 请输入图的顶点个数：4
// 请输入操作：
// insert 0 1 0.1
// insert 1 2 1
// insert 0 3 0.5
// insert 3 2 0.5
// insert 1 0 0.9
// exist 1 2
// exist 2 3
// remove 1 2
// exist 1 2
// exit

// 样例输出：
//  true
//  false
//  false
#include <iostream>
#include <string.h>

#include "adjMatrixGraph.h"
using namespace std;
int main() {
  cout << "请输入图的顶点个数：";
  int verSize;
  cin >> verSize;
  int *d = new int[verSize];
  for (int i = 0; i < verSize; i++) d[i] = i;
  adjMatrixGraph<int, double> *adj_matrix_graph =
      new adjMatrixGraph<int, double>(verSize, d, -1);
  cout << "\n请输入操作：" << endl;
  int u, v;
  double w;
  while (true) {
    char op[10];
    cin >> op;
    if (strcmp(op, "insert") == 0) {
      cin >> u >> v >> w;
      adj_matrix_graph->insert(u, v, w);
    } else if (strcmp(op, "remove") == 0) {
      cin >> u >> v;
      adj_matrix_graph->remove(u, v);
    } else if (strcmp(op, "exist") == 0) {
      cin >> u >> v;
      cout << (adj_matrix_graph->exist(u, v) ? "true" : "false")
           << endl;
    } else if (strcmp(op, "exit") == 0) {
      break;
    } else {
      cout << "Invalid Operation!" << endl;
    }
  }

  return 0;
}