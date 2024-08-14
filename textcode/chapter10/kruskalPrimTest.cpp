// 最小生成树：kruskal算法及prim算法的测试程序
// 样例输入（以图10-1为例，顶点下标改为0-base）：
// 请输入图的顶点个数：6
// 请依次输入无向图的加权边(-1 -1 -1表示输入完毕)：
// 0 1 6
// 0 2 1
// 0 3 5
// 1 2 5
// 1 4 3
// 2 4 6
// 2 5 4
// 3 5 2
// 4 5 6
// -1 -1 -1
// 样例输出：
// Kruskal:(0,2)	(3,5)	(1,4)	(2,5)	(1,2)
// Prim:(0,2)	(2,5)	(5,3)	(2,1)	(1,4)

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
    double w;
    cin >> u >> v >> w;
    if (u == -1) {
      break;
    } else {
      adj_list_graph->insert(u, v, w);
      adj_list_graph->insert(v, u, w);
    }
  }
  cout << "Kruskal:";
  adj_list_graph->kruskal();
  cout << endl;
  cout << "Prim:";
  adj_list_graph->prim(1e9);
  cout << endl;
  return 0;
}