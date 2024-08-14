// 在第九章基于邻接矩阵的图类基础上，添加了代码清单10-5
// Floyd算法的实现
#ifndef CHAPTER10_ADJMATRIXGRAPH_H
#define CHAPTER10_ADJMATRIXGRAPH_H
#include <iostream>

#include "../chapter9/graph.h"
using namespace std;
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph : public graph<TypeOfVer, TypeOfEdge> {
 public:
  adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
  void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
  void remove(TypeOfVer x, TypeOfVer y);
  bool exist(TypeOfVer x, TypeOfVer y) const;
  void floyd() const;
  ~adjMatrixGraph();

 private:
  TypeOfEdge **edge;  // 保存邻接矩阵
  TypeOfVer *ver;     // 保存顶点值
  TypeOfEdge noEdge;  // 邻接矩阵中没有边的表示值
  int find(TypeOfVer v) const {
    for (int i = 0; i < this->Vers; ++i)
      if (ver[i] == v) return i;
  }
};

template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(
    int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag) {
  int i, j;
  this->Vers = vSize;
  this->Edges = 0;
  noEdge = noEdgeFlag;
  // 存储顶点的数组的初始化
  ver = new TypeOfVer[vSize];
  for (i = 0; i < vSize; ++i) ver[i] = d[i];
  // 邻接矩阵的初始化
  edge = new TypeOfEdge *[vSize];
  for (i = 0; i < vSize; ++i) {
    edge[i] = new TypeOfEdge[vSize];
    for (j = 0; j < vSize; ++j) edge[i][j] = noEdge;
    edge[i][i] = 0;
  }
}
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph() {
  delete[] ver;
  for (int i = 0; i < this->Vers; ++i)
    delete[] edge[i];  // 释放邻接矩阵中的每一行
  delete[] edge;
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(
    TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
  int u = find(x), v = find(y);
  edge[u][v] = w;
  ++this->Edges;
}
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
  int u = find(x), v = find(y);
  edge[u][v] = noEdge;
  --this->Edges;
}
template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(
    TypeOfVer x, TypeOfVer y) const {
  int u = find(x), v = find(y);
  if (edge[u][v] == noEdge)
    return false;
  else
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::floyd() const {
  TypeOfEdge **dist = new TypeOfEdge *[this->Vers];  // 保存矩阵D每行的首地址
  int **prev = new int *[this->Vers];  // 保存数组prev每行的首地址
  int i, j, k;
  // 初始化
  for (i = 0; i < this->Vers; ++i) {
    dist[i] = new TypeOfEdge[this->Vers];  // 为矩阵D的第i行分配空间
    prev[i] = new int[this->Vers];      // 为数组prev的第i行分配空间
    for (j = 0; j < this->Vers; ++j) {  // 为矩阵D和数组prev赋初值
      dist[i][j] = edge[i][j];
      prev[i][j] = (edge[i][j] != noEdge) ? i : -1;
    }
  }
  // 迭代过程
  for (k = 0; k < this->Vers; ++k)
    for (i = 0; i < this->Vers; ++i)
      for (j = 0; j < this->Vers; ++j)
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          prev[i][j] = prev[k][j];
        }
  // 输出过程
  cout << "最短路径长度：" << endl;
  for (i = 0; i < this->Vers; ++i) {
    for (j = 0; j < this->Vers; ++j) cout << dist[i][j] << '\t';
    cout << endl;
  }
  cout << "最短路径：" << endl;
  for (i = 0; i < this->Vers; ++i) {
    for (j = 0; j < this->Vers; ++j) cout << prev[i][j] << '\t';
    cout << endl;
  }
  for (i = 0; i < this->Vers; ++i) {
    delete prev[i];
    delete dist[i];
  }
  delete[] prev;
  delete[] dist;
}
#endif  // CHAPTER10_ADJMATRIXGRAPH_H
