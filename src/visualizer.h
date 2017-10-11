#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <vector>
#include <map>

#include "graph.h"

namespace graph {

class Visualizer {
public:
  int PIC_SIZE = 5000;
  std::vector<std::string> COLORS = {
    "#c0392b", "#2980b9", "#16a085", "#8e44ad", "#f39c12", "#2c3e50", "#f1c40f", "#3498db", "#2ecc71", "#7f8c8d"
  };
  int pic_w, pic_h;
  Graph g;
  
  Visualizer(const Graph &_g);

  void SetPicSize(int sz);
  
  void ShowNodesAndEdges(const std::string& filename,
                         std::map<int, int> cns = {},
                         std::map<Edge, int> _ces = {});
};

} // namespace graph
