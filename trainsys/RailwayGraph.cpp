#include "RailwayGraph.h"
#include "DataStructure/Queue.h"
#include "DataStructure/List.h"

#include <iostream>

namespace trainsys {

RailwayGraph::RailwayGraph()
    : routeGraph(MAX_STATIONID), stationSet(MAX_STATIONID), routeSectionPool() {}

RailwayGraph::~RailwayGraph() {
    for (int i = 0; i < routeSectionPool.length(); ++i) {
        delete routeSectionPool.visit(i);
    }
}

// 向运行图中加入一条边
void RailwayGraph::addRoute(StationID departureStationID, StationID arrivalStationID, int duration, int price, TrainID trainID) {
    // 新建一条 SectionInfo 并将其放入内存池
    RouteSectionInfo *section = new RouteSectionInfo(trainID, arrivalStationID, price, duration);
    routeSectionPool.insert(routeSectionPool.length(), section); // 内存池
    // 向图中插入一条边
    routeGraph.insert(departureStationID, arrivalStationID, section);
    // 用不相交集将节点标记为连通
    int x = stationSet.find(departureStationID);
    int y = stationSet.find(arrivalStationID);
    stationSet.join(x, y);
}

bool RailwayGraph::checkStationAccessibility(StationID departureStationID, StationID arrivalStationID) {
    // 利用并查集判断连通性
    return stationSet.find(departureStationID) == stationSet.find(arrivalStationID);
}

// 
void RailwayGraph::routeDfs(int x, int t, seqList<StationID> &prev, bool *visited) {
    prev.insert(prev.length(), x);
    
    // 已找到一条路径，输出它
    if (x == t) {
        std::cout << "route found: ";
        for (int i = 0; i < prev.length(); ++i) {
            std::cout << prev.visit(i) << " ";
        }
        std::cout << std::endl;
        return ;
    }
    
    visited[x] = true;
    for (GraphType::edgeNode *p = routeGraph.verList[x]; p != nullptr; p = p->next) {
        if (!visited[p->end])
            routeDfs(p->end, t, prev, visited);
    }
}

void RailwayGraph::displayRoute(StationID departureStationID, StationID arrivalStationID) {
    bool *visited = new bool[routeGraph.numOfVer()];
    seqList<StationID> prev;
    routeDfs(departureStationID, arrivalStationID, prev, visited);
    delete [] visited;
}

void RailwayGraph::shortestPath(StationID departureStationID, StationID arrivalStationID, int type) {
    int numOfVer = routeGraph.numOfVer();

    // 使用朴素 Dijkstra 算法求解最短路
    int *prev = new int [numOfVer];
    bool *known = new bool[numOfVer];
    long long *distance = new long long [numOfVer];
    long long min;
    
    for (int i = 0; i < numOfVer; ++i) {
        prev[i] = i;
        known[i] = false;
        distance[i] = (1ll << 50);
    }

    distance[departureStationID] = 0;
    prev[departureStationID] = departureStationID;

    for (int i = 1; i < numOfVer; ++i) {
        int u;
        min = (1ll << 50);
        for (int j = 0; j < numOfVer; ++j) {
            if (!known[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }
        known[u] = true;
        for (GraphType::edgeNode *p = routeGraph.verList[u]; p != nullptr; p = p->next) {
            int weight = 0;
            // 根据 type 信息选择边权 weight
            if (type == 1) weight = p->weight->duration;
            else weight = p->weight->price;
            if (!known[p->end] && distance[p->end] > min + weight) {
                distance[p->end] = min + weight;
                prev[p->end] = u;
            }
        }
    }

    // 反向寻路，找到一条最短路径
    seqList<StationID> path;
    int u = arrivalStationID;
    do {
        path.insert(path.length(), u);
        u = prev[u];
    } 
    while (u != departureStationID);
    
    // 输出最短路
    std::cout << "shortest path: ";
    for (int i = path.length() - 1; i >= 0; --i) {
        std::cout << path.visit(i) << " ";
    }  
    std::cout << std::endl;

    delete [] prev;
    delete [] known;
    delete [] distance;
}





}