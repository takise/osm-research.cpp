#ifndef SHORTEST_PATH_H_
#define SHORTEST_PATH_H_

#include "graph.h"

namespace graph {

  class ShortestPath {
 public:
    // Get Shortest Path from s to t with Dijkstra
    static std::pair<double, std::vector<Edge>> dijkstra(const Graph& g,
                                                         int s, int t);
  };
  
}; // namespace graph

#endif
