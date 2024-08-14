#ifndef GRAPH_H_
#define GRAPH_H_

namespace trainsys {

template <class edgeType>
class graph {
public:
    graph() { Vers = 0; Edges = 0;}
    graph(int vers) { Vers = vers; Edges = 0; }
    virtual void insert(int x, int y, const edgeType &w) = 0;
    virtual void remove(int x, int y) = 0;
    virtual bool exist(int x, int y) const = 0;
    int numOfVer() const { return Vers; }
    int numOfEdges() const { return Edges; }

protected:
    int Vers;
    int Edges;
};

// template <class TypeOfVer, class TypeOfEdge>
// class adjMatrixGraph: public graph<TypeOfVer, TypeOfEdge> {
// public:
//     adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge &noEdgeFlag);
//     void insert(const TypeOfVer &x, const TypeOfVer &y, const TypeOfEdge &w);
//     void remove(const TypeOfVer &x, const TypeOfVer &y);
//     bool exist(const TypeOfVer &x, const TypeOfVer &y) const;
//     ~adjMatrixGraph();

// // private:
//     TypeOfEdge **edge;
//     TypeOfVer *ver;
//     TypeOfEdge noEdge;
//     int find(const TypeOfVer &v) const {
//         for (int i = 0; i < Vers; ++i) {
//             if (ver[u] == v) return i;
//         }
//     }
// };

// template <class TypeOfVer, class TypeOfEdge>
// adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge &noEdgeFlag) {
//     Vers = vSize, Edges = 0;
//     noEdge = noEdgeFlag;
    
//     ver = new TypeOfVer[vSize];
//     for (int i = 0; i < vSize; ++i) ver[i] = d[i];

//     edge = new TypeOfEdge*[vSize];
//     for (int i = 0; i < vSize; ++i) {
//         edge[i] = new TypeOfEdge[vSize];
//         for (int j = 0; j < vSize; ++j) edge[i][j] = noEdge;
//     }
// }

// template <class TypeOfVer, class TypeOfEdge>
// adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph() {
//     delete [] ver;
//     for (int i = 0; i < Vers; ++i) delete [] edge[i];
//     delete [] edge;
// }

// template <class TypeOfVer, class TypeOfEdge>
// void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(const TypeOfVer &x, const TypeOfVer &y, const TypeOfEdge &w) {
//     int u = find(x), v = find(y);
//     edge[u][v] = w;
//     Edges++;
// }

// template <class TypeOfVer, class TypeOfEdge>
// void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(const TypeOfVer &x, const TypeOfVer &y) {
//     int u = find(x), v = find(y);
//     edge[u][v] = noEdge;
//     Edges--;
// }

// template <class TypeOfVer, class TypeOfEdge>
// bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(const TypeOfVer &x, const TypeOfVer &y) const {
//     int u = find(x), v = find(y);
//     return edge[u][v] == noEdge;
// }

template <class edgeType> 
class adjListGraph: public graph<edgeType> {
public:
    adjListGraph(int vers);
    void insert(int u, int v, const edgeType &w);
    void remove(int u, int v);
    bool exist(int u, int v) const;
    ~adjListGraph();

    struct edgeNode {
        int end;
        edgeType weight;
        edgeNode *next;
        
        edgeNode(int e, const edgeType &w, edgeNode *n = nullptr): end(e), weight(w), next(n) {}
    };

    edgeNode **verList;
};

template <class edgeType>
adjListGraph<edgeType>::adjListGraph(int vers) : graph<edgeType>(vers) {
    verList = new edgeNode*[vers];
    for (int i = 0; i < vers; ++i) verList[i] = nullptr;
}

template <class edgeType>
adjListGraph<edgeType>::~adjListGraph() {
    for (int i = 0; i < this->Vers; ++i) {
        for (edgeNode *p = verList[i]; p != nullptr; p = verList[i]) {
            verList[i] = p->next;
            delete p;
        }
    }
    delete [] verList;
}

template <class edgeType>
void adjListGraph<edgeType>::insert(int u, int v, const edgeType &w) {
    verList[u] = new edgeNode(v, w, verList[u]);
    this->Edges++;
}

template <class edgeType>
void adjListGraph<edgeType>::remove(int u, int v) {
    edgeNode *p = verList[u], *q;

    if (p != nullptr) return ;
    if (p->end == v) {
        verList[u] = p->next;
        delete p;
        this->Edges--;
        return ;
    }
    while (p->next != nullptr && p->next->end != v) p = p->next;
    if (p->next != nullptr) {
        q = p->next;
        p->next = q->next;
        delete q;
        this->Edges--;
    }
}

template <class edgeType>
bool adjListGraph<edgeType>::exist(int u, int v) const {
    edgeNode *p = verList[u];
    while (p != nullptr && p->end != v) p = p->next;
    return p != nullptr;
}

} // namespace trainsys

#endif // GRAPH_H_