// 代码清单5-6至5-8 不相交集合类的定义和实现

#ifndef CHAPTER5_disjointSet_H
#define CHAPTER5_disjointSet_H
class disjointSet {
 private:
  int size;
  int *parent;

 public:
  disjointSet(int s);
  ~disjointSet() { delete[] parent; }
  void join(int root1, int root2);
  int find(int x);
};

disjointSet::disjointSet(int n) {
  size = n;
  parent = new int[size];
  for (int i = 0; i < size; ++i) parent[i] = -1;
}

int disjointSet::find(int x) {
  if (parent[x] < 0) return x;
  return parent[x] = find(parent[x]);
}

void disjointSet::join(int root1, int root2) {
  if (root1 == root2) return;
  if (parent[root1] > parent[root2]) {
    parent[root2] += parent[root1];
    parent[root1] = root2;
  } else {
    parent[root1] += parent[root2];
    parent[root2] = root1;
  }
}

#endif  // CHAPTER5_disjointSet_H
