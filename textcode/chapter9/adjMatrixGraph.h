// 代码清单9-2至9-4 基于邻接矩阵的图类

#ifndef CHAPTER9_ADJMATRIXGRAPH_H
#define CHAPTER9_ADJMATRIXGRAPH_H
#include "graph.h"
template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph : public graph<TypeOfVer, TypeOfEdge> {
 public:
  adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
  void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
  void remove(TypeOfVer x, TypeOfVer y);
  bool exist(TypeOfVer x, TypeOfVer y) const;
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
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(
    TypeOfVer x, TypeOfVer y) {
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

#endif  // CHAPTER9_ADJMATRIXGRAPH_H
