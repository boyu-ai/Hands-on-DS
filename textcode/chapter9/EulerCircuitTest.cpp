// 邻接表实现的欧拉回路的测试程序
// 样例输入（以图9-11为例）：
// 请输入图的顶点个数：6
// 请依次输入无向图的边(-1 -1表示输入完毕)：
// 0 1
// 0 2
// 1 2
// 1 3
// 1 4
// 2 3
// 2 4
// 3 4
// 3 5
// 4 5
// -1 -1
// 请输入查询欧拉回路的起点编号：5
// 样例输出：
// 欧拉回路是：
// 5  4 2	1	0	2	3	1	4 3	5

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
  cout << "请依次输入无向图的边(-1 -1表示输入完毕)：";
  while (true) {
    int u, v;

    cin >> u >> v;
    if (u == -1) {
      break;
    } else {
      adj_list_graph->insert(u, v, 1);
      adj_list_graph->insert(v, u, 1);
    }
  }
  cout << "请输入查询欧拉回路的起点编号：";
  int start;
  cin >> start;
  EulerNode *beg, *end;
  adj_list_graph->EulerCircuit(start);
  return 0;
}