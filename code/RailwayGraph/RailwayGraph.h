// RailwayGraph 类的定义
// 包括：代码清单5-9与9-16
#ifndef RAILWAY_GRAPH_H_
#define RAILWAY_GRAPH_H_

#include "DisjointSet.h"
#include "Graph.h"
#include "List.h"
#include "RouteSectionInfo.h"

namespace trainsys {

class RailwayGraph {
 private:
  using GraphType = adjListGraph<RouteSectionInfo>;
  GraphType routeGraph;
  DisjointSet stationSet;

 public:
  RailwayGraph();
  ~RailwayGraph();
  // 把两个站点所属的并查集子集合并
  void connectStation(
      StationID departureStationID, StationID arrivalStationID);

  // 查询两站点之间是否可达
  bool checkStationAccessibility(
      StationID departureStationID, StationID arrivalStationID);

  // 向列车运行图添加一条边
  void addRoute(StationID departureStationID,
      StationID arrivalStationID, int duration, int price,
      TrainID trainID);

  void displayRoute(
      StationID departureStationID, StationID arrivalStationID);

  void shortestPath(StationID departureStationID,
      StationID arrivalStationID, int type);

 private:
  void routeDfs(int curIdx, int arrivalIdx,
      seqList<StationID> &prevStations, bool *visited);
};

}  // namespace trainsys

#endif