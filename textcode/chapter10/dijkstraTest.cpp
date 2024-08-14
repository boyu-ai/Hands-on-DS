// 加权图单源最短路径（Dijkstra算法）测试程序
// 样例输入（以图10-5(a)为例，顶点下标为0-base）：
// 请输入图的顶点个数：5
// 请依次输入非加权无向图的边(-1 -1 -1表示输入完毕)：
// 0 1 4
// 0 2 1
// 0 3 1
// 1 2 2
// 2 1 1
// 2 3 2
// 2 4 1
// 3 4 1
// 4 1 1
// -1 -1 -1
// 样例输出：
// Dijkstra最短路径：
// 从0到0的路径为:
// 0	长度为：0
// 从0到1的路径为:
// 0 - 2 - 1	长度为：2
// 从0到2的路径为:
// 0 - 2	长度为：1
// 从0到3的路径为:
// 0 - 3	长度为：1
// 从0到4的路径为:
// 0 - 2 - 4	长度为：2

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
    double w;
    cin >> u >> v >> w;
    if (u == -1) {
      break;
    } else {
      adj_list_graph->insert(u, v, w);
    }
  }
  cout << "Dijkstra最短路径：" << endl;
  adj_list_graph->dijkstra(0, 1e9);
  return 0;
}