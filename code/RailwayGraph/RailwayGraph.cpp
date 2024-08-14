// RailwayGraph 类的实现
// 包括：代码清单5-10、9-17、9-18和10-6
#include "RailwayGraph.h"

#include <iostream>

#include "List.h"
#include "Queue.h"

namespace trainsys {

const int MAX_STATIONID = 1000;

RailwayGraph::RailwayGraph()
    : routeGraph(MAX_STATIONID), stationSet(MAX_STATIONID) {}

RailwayGraph::~RailwayGraph() {}

void RailwayGraph::connectStation(
    StationID departureStationID, StationID arrivalStationID) {
  int x = stationSet.find(departureStationID);
  int y = stationSet.find(arrivalStationID);
  if (x != y) stationSet.join(x, y);
}

bool RailwayGraph::checkStationAccessibility(
    StationID departureStationID, StationID arrivalStationID) {
  return stationSet.find(departureStationID) ==
         stationSet.find(arrivalStationID);
}

void RailwayGraph::addRoute(StationID departureStationID,
    StationID arrivalStationID, int duration, int price,
    TrainID trainID) {
  RouteSectionInfo section(trainID, arrivalStationID, price, duration);
  routeGraph.insert(departureStationID, arrivalStationID, section);
  connectStation(departureStationID, arrivalStationID);
}

void RailwayGraph::displayRoute(
    StationID departureStationID, StationID arrivalStationID) {
  bool *visited = new bool[routeGraph.numOfVer()];
  seqList<StationID> prev;
  routeDfs(departureStationID, arrivalStationID, prev, visited);
  delete[] visited;
}

void RailwayGraph::routeDfs(
    int x, int t, seqList<StationID> &prev, bool *visited) {
  prev.insert(prev.length(), x);

  // 已找到一条路径，输出它
  if (x == t) {
    std::cout << "route found: ";
    for (int i = 0; i < prev.length(); ++i) {
      std::cout << prev.visit(i) << " ";
    }
    std::cout << std::endl;
    return;
  }

  visited[x] = true;
  for (GraphType::edgeNode *p = routeGraph.verList[x]; p != nullptr;
       p = p->next) {
    if (!visited[p->end]) routeDfs(p->end, t, prev, visited);
  }
}

void RailwayGraph::shortestPath(StationID departureStationID,
    StationID arrivalStationID, int type) {
  int numOfVer = routeGraph.numOfVer();

  // 使用朴素迪杰斯特拉算法求解最短路径
  int *prev = new int[numOfVer];
  bool *known = new bool[numOfVer];
  long long *distance = new long long[numOfVer];
  long long min;

  for (int i = 0; i < numOfVer; ++i) {
    prev[i] = i;
    known[i] = false;
    distance[i] = (1ll << 32);
  }

  distance[departureStationID] = 0;
  prev[departureStationID] = departureStationID;

  for (int i = 1; i < numOfVer; ++i) {
    int u;
    min = (1ll << 32);
    for (int j = 0; j < numOfVer; ++j) {
      if (!known[j] && distance[j] < min) {
        min = distance[j];
        u = j;
      }
    }
    known[u] = true;
    for (GraphType::edgeNode *p = routeGraph.verList[u]; p != nullptr;
         p = p->next) {
      int weight = 0;
      if (type == 1)
        weight = p->weight.duration;
      else
        weight = p->weight.price;
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
  } while (u != departureStationID);

  // 输出最短路径
  std::cout << "shortest path: ";
  for (int i = path.length() - 1; i >= 0; --i) {
    std::cout << path.visit(i) << " ";
  }
  std::cout << std::endl;

  delete[] prev;
  delete[] known;
  delete[] distance;
}

}  // namespace trainsys