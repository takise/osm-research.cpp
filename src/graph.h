#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include <memory>

#include "edge.h"

namespace graph {

class Graph {
public:

  Graph();
  Graph(int _V);
  Graph(const std::string &graph_data_path);

  void importGraph(const std::string& filename);
  int randomNode() const;
  void Serialize(const std::string& filename);
  
  static double dist(double lata, double lona, double latb, double lonb);
  
  int V, E;
  double minlat = 1000, maxlat = -1000, minlon = 1000, maxlon = -1000;

  std::vector<double> lat;
  std::vector<double> lon;
  std::vector<std::vector<int> > es;
  std::vector<std::vector<double> > w;
};

};

#endif /// GRAPH_H_
