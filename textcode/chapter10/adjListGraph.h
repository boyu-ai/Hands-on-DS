// 在第九章邻接表实现的基础上，新增代码清单10-1至
// 包含 代码清单9-8 dfs的实现，代码清单9-9
// bfs的实现，代码清单9-10欧拉回路，代码清单9-12 拓扑排序，代码清单9-13 关键路径
#ifndef CHAPTER10_ADJLISTGRAPH_H
#define CHAPTER10_ADJLISTGRAPH_H
#include <iostream>

#include "../chapter3/linkQueue.h"
#include "../chapter4/priorityQueue.h"
#include "../chapter5/disjointSet.h"
#include "../chapter9/graph.h"
using namespace std;
struct EulerNode {
  int NodeNum;
  EulerNode *next;
  EulerNode(int ver) {
    NodeNum = ver;
    next = nullptr;
  }
};

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph : public graph<TypeOfVer, TypeOfEdge> {
 public:
  adjListGraph(int vSize, const TypeOfVer d[]);
  void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
  void remove(TypeOfVer x, TypeOfVer y);
  bool exist(TypeOfVer x, TypeOfVer y) const;
  void dfs() const;
  void bfs() const;
  void EulerCircuit(TypeOfVer start);
  void topSort() const;
  void criticalPath() const;
  void kruskal() const;
  void prim(TypeOfEdge noEdge) const;
  void unweightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const;
  void dijkstra(TypeOfVer start, TypeOfEdge noEdge) const;
  ~adjListGraph();

 private:
  struct edgeNode {     // 邻接表中存储边的结点类
    int end;            // 终点编号
    TypeOfEdge weight;  // 边的权值
    edgeNode *next;
    edgeNode(int e, TypeOfEdge w, edgeNode *n = nullptr) {
      end = e;
      weight = w;
      next = n;
    }
  };
  struct verNode {   // 保存顶点的数据类型
    TypeOfVer ver;   // 顶点值
    edgeNode *head;  // 对应的单链表的头指针
    verNode(edgeNode *h = nullptr) { head = h; }
  };
  verNode *verList;
  int find(TypeOfVer v) const {
    for (int i = 0; i < this->Vers; ++i)
      if (verList[i].ver == v) return i;
  }
  void dfs(int start, bool visited[]) const;
  verNode *clone() const;
  void printPath(int start, int end, int prev[]) const;
  void EulerCircuit(int start, EulerNode *&beg, EulerNode *&end);

  // edge类用于kruskal算法
  struct edge {
    int beg, end;
    TypeOfEdge w;
    bool operator<(const edge &rp) const { return w < rp.w; }
  };
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(
    int vSize, const TypeOfVer d[]) {
  this->Vers = vSize;
  this->Edges = 0;
  verList = new verNode[vSize];
  for (int i = 0; i < this->Vers; ++i) verList[i].ver = d[i];
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
  edgeNode *p;
  for (int i = 0; i < this->Vers; ++i)  // 释放第i个顶点的单链表
    while ((p = verList[i].head) != nullptr) {
      verList[i].head = p->next;
      delete p;
    }
  delete[] verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
  int u = find(x), v = find(y);
  verList[u].head = new edgeNode(v, w, verList[u].head);
  ++this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(
    TypeOfVer x, TypeOfVer y) {
  int u = find(x), v = find(y);
  edgeNode *p = verList[u].head, *q;
  if (p == nullptr) return;  // 顶点u没有相连的边
  if (p->end == v) {  // 单链表中的第一个结点就是被删除的边
    verList[u].head = p->next;
    delete p;
    --this->Edges;
    return;
  }
  while (p->next != nullptr && p->next->end != v)
    p = p->next;             // 查找被删除的边
  if (p->next != nullptr) {  // 删除
    q = p->next;
    p->next = q->next;
    delete q;
    --this->Edges;
  }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
  int u = find(x), v = find(y);
  edgeNode *p = verList[u].head;
  while (p != nullptr && p->end != v) p = p->next;
  if (p == nullptr)
    return false;
  else
    return true;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const {
  bool *visited = new bool[this->Vers];  // 记录每个顶点是否已被访问
  for (int i = 0; i < this->Vers; ++i) visited[i] = false;
  cout << "当前图的DFS遍历序列为：" << endl;
  for (int i = 0; i < this->Vers; ++i) {
    if (visited[i] == true) continue;
    dfs(i, visited);
    cout << endl;
  }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const {
  edgeNode *p = verList[start].head;
  cout << verList[start].ver << '\t';  // 访问顶点
  visited[start] = true;
  while (p != nullptr) {  // 对start的后继顶点进行dfs
    if (visited[p->end] == false) 
      dfs(p->end, visited);
    p = p->next;
  }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const {
  bool *visited = new bool[this->Vers];
  int currentNode;
  linkQueue<int> q;
  edgeNode *p;
  for (int i = 0; i < this->Vers; ++i)
    visited[i] = false;  // 初始化所有元素为未访问
  cout << "当前图的BFS序列为：" << endl;
  for (int i = 0; i < this->Vers; ++i) {
    if (visited[i] == true) continue;
    q.enQueue(i);
    while (!q.isEmpty()) {
      currentNode = q.deQueue();
      if (visited[currentNode] == true) continue;
      cout << verList[currentNode].ver << '\t';
      visited[currentNode] = true;
      p = verList[currentNode].head;
      while (p != nullptr) {  // 将currentNode的后继顶点入队
        if (visited[p->end] == false) q.enQueue(p->end);
        p = p->next;
      }
    }
    cout << endl;
  }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(
    int start, EulerNode *&beg, EulerNode *&end) {
  int nextNode;
  beg = end = new EulerNode(start);  // 将起始顶点放入欧拉回路
  while (verList[start].head != nullptr) {  // start顶点尚有边未被访问
    nextNode = verList[start].head->end;
    remove(start, nextNode);
    remove(nextNode, start);
    start = nextNode;
    end->next = new EulerNode(start);
    end = end->next;
  }
}

template <class TypeOfVer, class TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::verNode *
adjListGraph<TypeOfVer, TypeOfEdge>::clone() const {
  verNode *tmp = new verNode[this->Vers];
  edgeNode *p;
  for (int i = 0; i < this->Vers; ++i) { // 复制每个顶点在邻接表中的信息
    tmp[i].ver = verList[i].ver;  // 复制下标为i的顶点
    p = verList[i].head;
    while (p != nullptr) {  // 复制下标为i的顶点对应的边的信息
      tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
      p = p->next;
    }
  }
  return tmp;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(
    TypeOfVer start) {
  // beg和end分别为欧拉回路的起点和终点
  EulerNode *beg, *end, *p, *q, *tb, *te;  
  int numOfDegree;
  edgeNode *r;
  verNode *tmp;
  // 检查是否存在欧拉回路
  if (this->Edges == 0) {
    cout << "不存在欧拉回路" << endl;
    return;
  }
  for (int i = 0; i < this->Vers; ++i) {
    numOfDegree = 0;
    r = verList[i].head;
    while (r != 0) {
      ++numOfDegree;
      r = r->next;
    }
    if (numOfDegree % 2) {
      cout << "不存在欧拉回路" << endl;
      return;
    }
  }
  // 寻找起始顶点的编号
  int i = find(start);
  tmp = clone();  // 创建一份邻接表的备份
  // 寻找从i出发的路径，路径的起点和终点地址分别是beg和end
  EulerCircuit(i, beg, end);
  while (true) {
    p = beg;
    while (p->next != nullptr)  // 检查p的后继顶点是否有边尚未被访问
      if (verList[p->next->NodeNum].head != nullptr)
        break;
      else
        p = p->next;
    if (p->next == nullptr) break;  // 所有边都已被访问
    q = p->next;                    // 尚有未被访问边的顶点
    EulerCircuit(q->NodeNum, tb, te);  // 从此顶点开始寻找一段路径
    te->next = q->next;  // 将搜索到的路径拼接到原来的路径上
    p->next = tb;
    delete q;
  }
  // 恢复原图
  delete[] verList;
  verList = tmp;
  // 显示得到的欧拉回路
  cout << "欧拉回路是：" << endl;
  while (beg != nullptr) {
    cout << verList[beg->NodeNum].ver << '\t';
    p = beg;
    beg = beg->next;
    delete p;
  }
  cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const {
  linkQueue<int> q;
  edgeNode *p;
  int current;
  int *inDegree = new int[this->Vers];
  for (int i = 0; i < this->Vers; ++i) { inDegree[i] = 0; }
  for (int i = 0; i < this->Vers; ++i) {  // 计算每个顶点的入度
    for (p = verList[i].head; p != nullptr; p = p->next)
      ++inDegree[p->end];
  }
  for (int i = 0; i < this->Vers; ++i)  // 将入度为0的顶点入队
    if (inDegree[i] == 0) q.enQueue(i);
  cout << "拓扑排序为：" << endl;
  while (!q.isEmpty()) {
    current = q.deQueue();
    cout << verList[current].ver << '\t';
    for (p = verList[current].head; p != nullptr; p = p->next)
      if (--inDegree[p->end] == 0) q.enQueue(p->end);
  }
  cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::criticalPath() const {
  TypeOfEdge *ee = new TypeOfEdge[this->Vers],
             *le = new TypeOfEdge[this->Vers];
  // top 保存拓扑序列
  int *top = new int[this->Vers], *inDegree = new int[this->Vers];  
  linkQueue<int> q;
  int i;
  edgeNode *p;
  // 找出拓扑序列，放入数组top
  for (i = 0; i < this->Vers; ++i) {  // 计算每个顶点的入度
    inDegree[i] = 0;
  }
  for (int i = 0; i < this->Vers; ++i) {
    for (p = verList[i].head; p != nullptr; p = p->next)
      ++inDegree[p->end];
  }

  for (i = 0; i < this->Vers; ++i)  // 将入度为0的顶点入队
    if (inDegree[i] == 0) q.enQueue(i);
  i = 0;
  while (!q.isEmpty()) {
    top[i] = q.deQueue();
    for (p = verList[top[i]].head; p != nullptr; p = p->next)
      if (--inDegree[p->end] == 0)
        q.enQueue(p->end);
    ++i;
  }
  // 找最早发生时间
  for (i = 0; i < this->Vers; ++i) ee[i] = 0;
  for (i = 0; i < this->Vers; ++i) {  // 找出最早发生时间并保存于数组ee中
    for (p = verList[top[i]].head; p != nullptr; p = p->next)
      if (ee[p->end] < ee[top[i]] + p->weight)
        ee[p->end] = ee[top[i]] + p->weight;
  }
  // 找最迟发生时间
  for (i = 0; i < this->Vers; ++i) le[i] = ee[this->Vers - 1];
  for (i = this->Vers - 1; i >= 0; --i)  // 找出最迟发生时间并保存于数组le中
    for (p = verList[top[i]].head; p != nullptr; p = p->next)
      if (le[p->end] - p->weight < le[top[i]])
        le[top[i]] = le[p->end] - p->weight;

  cout << "当前图的关键路径是：";
  for (i = 0; i < this->Vers; ++i)  // 找出关键路径
    if (le[top[i]] == ee[top[i]])
      cout << "(" << verList[top[i]].ver << ", " << ee[top[i]] << ") ";
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal() const {
  int edgesAccepted = 0, u, v;
  edgeNode *p;
  edge e;
  disjointSet ds(this->Vers);
  priorityQueue<edge> pq;
  // 生成优先级队列
  for (int i = 0; i < this->Vers; ++i) {
    for (p = verList[i].head; p != NULL; p = p->next)
      if (i < p->end) {
        e.beg = i;
        e.end = p->end;
        e.w = p->weight;
        pq.enQueue(e);
      }
  }
  // 开始归并
  while (edgesAccepted < this->Vers - 1) {
    e = pq.deQueue();  // 取出权值最小的边
    u = ds.find(e.beg);
    v = ds.find(e.end);
    if (u != v) {  // 加入（u，v）不会形成回路
      edgesAccepted++;
      ds.join(u, v);
      cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
    }
  }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge) const {
  bool *flag = new bool[this->Vers];
  TypeOfEdge *lowCost = new TypeOfEdge[this->Vers];
  int *startNode = new int[this->Vers];
  edgeNode *p;
  TypeOfEdge min;
  int start, i, j;
  for (i = 0; i < this->Vers; ++i) {  // 初始化，所有顶点都不在生成树中
    flag[i] = false;
    lowCost[i] = noEdge;
  }
  start = 0;  // 将0作为第一个加入生成树的顶点
  for (i = 1; i < this->Vers; ++i) {
    for (p = verList[start].head; p != NULL; p = p->next)  // 检查start的边
      if (!flag[p->end] && lowCost[p->end] > p->weight) {  // 更新距离信息
        lowCost[p->end] = p->weight;
        startNode[p->end] = start;
      }
    flag[start] = true;  // 将start标记为已在U中
    min = noEdge;
    for (j = 0; j < this->Vers; ++j) {  
      // 寻找U到V−U的权值最小的边，把权值最小的边的终点加入U中
      if (lowCost[j] < min) {
        min = lowCost[j];
        start = j;
      }
    }
    cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver
         << ")\t";
    lowCost[start] = noEdge;
  }
  delete[] flag;
  delete[] startNode;
  delete[] lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(
    int start, int end, int prev[]) const {
  if (start == end) {
    cout << verList[start].ver;
    return;
  }
  printPath(start, prev[end], prev);
  cout << " - " << verList[end].ver;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::unweightedShortDistance(
    TypeOfVer start, TypeOfEdge noEdge) const {
  linkQueue<int> q;
  TypeOfEdge *dist = new TypeOfEdge[this->Vers];
  int *prev = new int[this->Vers];
  int u, sNo;
  edgeNode *p;
  for (int i = 0; i < this->Vers; ++i) dist[i] = noEdge;  // 初始化
  // 寻找起始顶点的编号
  sNo = find(start);
  // 寻找最短路径
  dist[sNo] = 0;
  prev[sNo] = sNo;
  q.enQueue(sNo);
  while (!q.isEmpty()) {
    u = q.deQueue();
    for (p = verList[u].head; p != NULL; p = p->next)
      if (dist[p->end] == noEdge) {
        dist[p->end] = dist[u] + 1;
        prev[p->end] = u;
        q.enQueue(p->end);
      }
  }
  // 输出最短路径
  for (int i = 0; i < this->Vers; ++i) {
    cout << "从" << start << "到" << verList[i].ver << "的路径为:" << endl;
    printPath(sNo, i, prev);
    cout << endl;
  }
  delete[] dist;
  delete[] prev;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra(
    TypeOfVer start, TypeOfEdge noEdge) const {
  TypeOfEdge *dist = new TypeOfEdge[this->Vers];
  int *prev = new int[this->Vers];
  bool *known = new bool[this->Vers];
  int u, sNo, i, j;
  edgeNode *p;
  TypeOfEdge min;
  for (i = 0; i < this->Vers; ++i) {  // 初始化
    known[i] = false;
    dist[i] = noEdge;
  }
  sNo = find(start);
  dist[sNo] = 0;
  prev[sNo] = sNo;
  for (i = 1; i < this->Vers; ++i) {
    min = noEdge;
    for (j = 0; j < this->Vers; ++j)  // 寻找具有最短距离的顶点
      if (!known[j] && dist[j] < min) {
        min = dist[j];
        u = j;
      }
    known[u] = true;  // 将u放入S
    for (p = verList[u].head; p != NULL; p = p->next)
      if (!known[p->end] && dist[p->end] > min + p->weight) {
        dist[p->end] = min + p->weight;  // 更新u的邻接顶点的距离
        prev[p->end] = u;
      }
  }
  for (i = 0; i < this->Vers; ++i) {  // 输出所有路径信息
    cout << "从" << start << "到" << verList[i].ver << "的路径为:" << endl;
    printPath(sNo, i, prev);
    cout << "\t长度为：" << dist[i] << endl;
  }
  delete[] prev;
  delete[] known;
  delete[] dist;
}
#endif  // CHAPTER10_ADJMATRIXGRAPH_H