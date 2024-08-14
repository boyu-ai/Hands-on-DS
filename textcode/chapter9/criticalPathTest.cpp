// 邻接表实现的关键路径的测试程序
// 样例输入（以图9-14为例）：
// 请输入图的顶点个数：7
// 请依次输入有向图的边(-1 -1 -1表示输入完毕)：
//  0 1 1
//  1 2 2
//  1 3 3
//  2 4 4
//  3 4 2
//  3 5 3
//  5 6 2
//  4 6 1
//  -1 -1 -1
//  样例输出：
//  当前图的关键路径是：(0,  0)  (1,  1)  (3,  4)  (5,  7)  (6,  9)

#include <iostream>

#include "adjListGraph.h"
using namespace std;
int main() {
  cout << "请输入图的顶点个数：";
  int verSize;
  cin >> verSize;
  int *d = new int[verSize];
  for (int i = 0; i < verSize; i++) d[i] = i;
  adjListGraph<int, double> *adj_list_graph =
      new adjListGraph<int, double>(verSize, d);
  cout << "请依次输入有向图的边(-1 -1 -1表示输入完毕)：";
  while (true) {
    int u, v;
    double w;
    cin >> u >> v >> w;
    if (u == -1) {
      break;
    } else {
      adj_list_graph->insert(u, v, w);
    }
  }

  adj_list_graph->criticalPath();
  return 0;
}