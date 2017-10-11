#include <cmath>
#include <queue>

#include "shortest_path.h"

namespace graph {

// Get Shortest Path from s to t with Dijkstra
std::pair<double, std::vector<Edge>> ShortestPath::dijkstra(const Graph& g, int s,
                                                   int t) {
  std::vector<double> d(g.V, 1e18);
  d[s] = 0;
  typedef std::pair<double, int> P;
  std::priority_queue<P, std::vector<P>, std::greater<P> > que;
  que.push(P(0, s));
  while (!que.empty()) {
	double dist = que.top().first;
	int v = que.top().second;
	que.pop();
	if (d[v] < dist) continue;
        for (int i = 0; i < g.es[v].size(); i++) {
          int dst = g.es[v][i];
          double w = g.w[v][i];
	  if (d[dst] > d[v] + w) {
		d[dst] = d[v] + w;
		que.push(P(d[dst], dst));
	  }
	}
  }
  std::vector<Edge> path;
  int now = t;
  while(now != s) {
    for (int i = 0; i < g.es[now].size(); i++) {
      int dst = g.es[now][i];
      double w = g.w[now][i];
      if (fabs(w + d[dst] - d[now]) < 1e-8) {
        path.push_back((Edge){now, dst, w});
        now = dst;
      }
    }
  }
  reverse(path.begin(), path.end());
  for (auto &e : path) std::swap(e.src, e.dst);
  return std::pair<int, std::vector<Edge>>(d[t], path);
}

};
