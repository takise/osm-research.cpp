#include "union_find.h"

int UnionFind::root(int x) {
  return parent[x] < 0 ? x : parent[x] = root(parent[x]);
}

bool UnionFind::merge(int x, int y) {
  x = root(x); y = root(y);
  if (x == y) return false;
  if (parent[y] < parent[x]) std::swap(x, y);
  if (parent[x] == parent[y]) --parent[x];
  parent[y] = x;
  return true;
}
