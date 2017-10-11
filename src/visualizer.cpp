#include <random>
#include <sstream>

#include "visualizer.h"

namespace graph {

Visualizer::Visualizer(const Graph &_g) : g(_g) {
    pic_w = PIC_SIZE;
    pic_h = pic_w / ((g.maxlon - g.minlon) / 360.0) *
            ((g.maxlat - g.minlat) / 180.0);
  }

void Visualizer::SetPicSize(int sz) {
  PIC_SIZE = sz;
  pic_w = PIC_SIZE;
  pic_h = pic_w / ((g.maxlon - g.minlon) / 360.0) *
          ((g.maxlat - g.minlat) / 180.0);
}

void Visualizer::ShowNodesAndEdges(const std::string& filename,
                                   std::map<int, int> cns,
                                   std::map<Edge, int> _ces) {
  
  std::map<Edge, int> ces;
  for (auto p : _ces) {
    Edge e = p.first;
    if (e.src > e.dst) ces[(Edge){e.dst, e.src, e.weight}] = p.second;
    else ces[(Edge){e.src, e.dst, e.weight}] = p.second;
  }

  std::random_device rnd;
  std::stringstream ss;
  ss << "build/tmp" << rnd() << ".dot";
  std::string dotfilename = ss.str();
  
  std::ofstream ofs(dotfilename);
  ofs << "graph {" << std::endl << "  graph[size=\"" << pic_w << "," << pic_h << "\"];" << std::endl;
  ofs << "  node[fixedsize = true, width = 0.001, height = 0.001];" << std::endl;
  std::cout << "generating .dot file..." << std::endl;
  for (int i = 0; i < g.V; i++) {
    double nlat = (g.lat[i] - g.minlat) / (g.maxlat - g.minlat) * pic_h;
    double nlon = (g.lon[i] - g.minlon) / (g.maxlon - g.minlon) * pic_w;
    if (cns.count(i)) ofs << "  " << i << " [pos=\"" << nlon << "," << nlat << "\", label=\"\", style=filled, height=0.7, width=0.7, fillcolor=\""+COLORS[cns[i]]+"\", color=\""+COLORS[cns[i]]+"\"]" << std::endl;
    else ofs << "  " << i << " [pos=\"" << nlon << "," << nlat << "\", label=\"\"]" << std::endl;
  }
  
  for (int from = 0; from < (int)g.es.size(); from++) {
    for (int i = 0; i < (int)g.es[from].size(); i++) {
      int to = g.es[from][i];
      double w = g.w[from][i];
      Edge e = (Edge){from, to, w};
      if (from < to) {
        if (ces.count(e)) {
          std::string c = COLORS[ces[e]];
          ofs << "  " << from << " -- " << to << " [color=\""+c+"\", penwidth=10];" << std::endl;
        }
        else ofs << "  " << from << " -- " << to << ";" << std::endl;
      }
    }
  }
  
  ofs << "}" << std::endl << std::flush;
  system(("neato -s1 -n1 -Tpng " + dotfilename + " -o build/" + filename).c_str());
  system(("rm " + dotfilename).c_str());
}

};
