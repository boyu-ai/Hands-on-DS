// RailwayGraph 类的测试程序
// 编译命令：g++ RailwayGraph.cpp RailwayGraphTest.cpp RouteSectionInfo.cpp -o code.out
// 样例输出：
// 1 -> 7 is accessible
// 3 -> 7 is not accessible
// route found: 1 2 4 5 7
// shortest path: 2 4 5 7
// shortest path: 2 4 5 7
// 1 -> 7 is accessible
// 3 -> 7 is accessible
// shortest path: 3 4 5 7
// shortest path: 2 4 6 7

#include "RailwayGraph.h"

namespace trainsys {

RailwayGraph *railwayGraph;

void addRoute1(RailwayGraph *graph) {
  graph->addRoute(1, 2, 10, 20, (String) "G1");
  graph->addRoute(2, 4, 10, 20, (String) "G1");
  graph->addRoute(4, 5, 20, 10, (String) "G1");
  graph->addRoute(5, 7, 20, 10, (String) "G1");
}

void addRoute2(RailwayGraph *graph) {
  graph->addRoute(1, 3, 20, 10, (String) "G2");
  graph->addRoute(3, 4, 20, 10, (String) "G2");
  graph->addRoute(4, 6, 10, 20, (String) "G2");
  graph->addRoute(6, 7, 10, 20, (String) "G2");
}

void railwayGraphTest() {
  railwayGraph = new RailwayGraph();
  addRoute1(railwayGraph);
  if (railwayGraph->checkStationAccessibility(1, 7)) {
    std::cout << "1 -> 7 is accessible" << std::endl;
  } else {
    std::cout << "1 -> 7 is not accessible" << std::endl;
  }
  if (railwayGraph->checkStationAccessibility(3, 7)) {
    std::cout << "3 -> 7 is accessible" << std::endl;
  } else {
    std::cout << "3 -> 7 is not accessible" << std::endl;
  }
  railwayGraph->displayRoute(1, 7);
  railwayGraph->shortestPath(1, 7, 0);
  railwayGraph->shortestPath(1, 7, 1);

  addRoute2(railwayGraph);
  if (railwayGraph->checkStationAccessibility(1, 7)) {
    std::cout << "1 -> 7 is accessible" << std::endl;
  } else {
    std::cout << "1 -> 7 is not accessible" << std::endl;
  }
  if (railwayGraph->checkStationAccessibility(3, 7)) {
    std::cout << "3 -> 7 is accessible" << std::endl;
  } else {
    std::cout << "3 -> 7 is not accessible" << std::endl;
  }
  railwayGraph->shortestPath(1, 7, 0);
  railwayGraph->shortestPath(1, 7, 1);
  delete railwayGraph;
}
}  // namespace trainsys

int main() {
  trainsys::railwayGraphTest();
  return 0;
}