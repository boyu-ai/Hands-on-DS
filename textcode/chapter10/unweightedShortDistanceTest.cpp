// 非加权图的单源最短路径测试程序
// 样例输入（以图10-4为例，顶点下标改为0-base）：
// 请输入图的顶点个数：4
// 请依次输入非加权无向图的边(-1 -1表示输入完毕)：
// 0 1
// 1 0
// 0 3
// 1 2
// 3 2
// -1 -1
// 样例输出：
// 非加权图的单源最短路径：从1到0的路径为:
// 1 - 0
// 从1到1的路径为:
// 1
// 从1到2的路径为:
// 1 - 2
// 从1到3的路径为:
// 1 - 0 - 3

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
    cin >> u >> v;
    if (u == -1) {
      break;
    } else {
      adj_list_graph->insert(u, v, 1);
    }
  }
  cout << "非加权图的单源最短路径：" << endl;
  adj_list_graph->unweightedShortDistance(1, 1e9);
  return 0;
}