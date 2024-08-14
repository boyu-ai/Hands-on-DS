#ifndef DISJOINTSET_H_
#define DISJOINTSET_H_

namespace trainsys {

class DisjointSet {
private:
    int size;
    int *parent;

public:
    DisjointSet(int n) {
        size = n;
        parent = new int [size];
        for (int i=0; i<size; ++i) parent[i] = -1;
    }
    ~DisjointSet() {
        delete [] parent;
    }
    void join(int root1, int root2) {
        if (root1 == root2) return;
        if (parent[root1] > parent[root2]) {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
        else {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }
    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }
};

}

#endif 