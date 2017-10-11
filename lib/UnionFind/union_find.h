#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <vector>

struct UnionFind {
  std::vector<int> parent;
  UnionFind (int n) : parent(n, -1) {}

  int root(int x);
  bool merge(int x, int y);
};

#endif /// UNION_FIND_H_
