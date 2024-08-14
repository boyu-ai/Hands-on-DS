// 所有顶点对的最短路径（Floyd算法）测试程序
// 样例输入（以图10-8(a)为例）：
// 请输入图的顶点个数：3
// 请依次输入非加权无向图的边(-1 -1 -1表示输入完毕)：
// 0 1 8
// 1 0 3
// 0 2 5
// 2 0 6
// 2 1 2
// -1 -1 -1
// 样例输出：
// 最短路径长度：
// 0    7   5
// 3	0	8
// 5	2	0	
// 最短路径：
// 0	2	0
// 1	1	0
// 1	2	2

#include <iostream>

#include "adjMatrixGraph.h"
using namespace std;
int main() {
  cout << "请输入图的顶点个数：";
  int verSize;
  cin >> verSize;
  int *d = new int[verSize];
  for (int i = 0; i < verSize; i++) d[i] = i;
  adjMatrixGraph<int, double> *adj_matrix_graph =
      new adjMatrixGraph<int, double>(verSize, d, 1e9);
  cout << "请依次输入有向图的边(-1 -1表示输入完毕)：";
  while (true) {
    int u, v;
    double w;
    cin >> u >> v >> w;
    if (u == -1) {
      break;
    } else {
      adj_matrix_graph->insert(u, v, w);
    }
  }
  adj_matrix_graph->floyd();
  return 0;
}