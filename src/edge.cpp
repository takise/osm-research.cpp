#include "edge.h"

namespace graph {

bool operator < (const Edge &x, const Edge &y) {
  return x.src == y.src ? x.dst < y.dst : x.src < y.src;
}

Edge::Edge(int s, int d, double w) : src(s), dst(d), weight(w) {}

};
