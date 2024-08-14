// 邻接表实现的拓扑排序的测试程序
// 样例输入（以图9-12为例）：
// 请输入图的顶点个数：8
// 请依次输入有向图的边(-1 -1表示输入完毕)：
// 0 1
// 1 2
// 1 3
// 3 5
// 2 5
// 2 4
// 2 6
// 3 7
// 5 6
// 6 4
// 5 7
// -1 -1
// 样例输出：
// 拓扑排序为：
// 0  1 3 2 5 6 7 4

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
  cout << "请依次输入有向图的边(-1 -1表示输入完毕)：";
  while (true) {
    int u, v;

    cin >> u >> v;
    if (u == -1) {
      break;
    } else {
      adj_list_graph->insert(u, v, 1);
    }
  }

  adj_list_graph->topSort();
  return 0;
}