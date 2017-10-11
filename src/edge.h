#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>
#include <string>
#include <sstream>

#include "node.h"

namespace graph {

struct Edge {
  //  const Node* src;
  //  const Node* dst;
  int src, dst;
  double weight;
  // double speedLimit;
  // map<string, string> attrs;

  /* std::string toString() const { */
  /*   std::stringstream ss; */
  /*   ss << "(" << src->id << "->" << dst->id << ")"; */
  /*   return ss.str(); */
  /* } */

  Edge(int s, int d, double w);
};

bool operator < (const Edge &x, const Edge &y);

};

#endif /// EDGE_H_
