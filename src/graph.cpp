#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <random>

#include "graph.h"
#include "log.h"

namespace graph {

Graph::Graph() {}

Graph::Graph(int V) : V(V) {
  lat = std::vector<double>(V);
  lon = std::vector<double>(V);
  es = std::vector<std::vector<int> >(V, std::vector<int>());
  w = std::vector<std::vector<double> >(V, std::vector<double>());
}

void Graph::importGraph(const std::string& filename) {
  base::Log::progress("Extracting nodes from " + filename);
  std::ifstream ifs(filename);
  ifs >> V >> E;
  ifs >> minlat >> maxlat >> minlon >> maxlon;

  lat = std::vector<double>(V);
  lon = std::vector<double>(V);
  for (int i = 0; i < V; i++) {
    ifs >> lat[i] >> lon[i];
    base::Log::progressBar((double)i / V * 100);
  }
  base::Log::progressBarEnd();

  es = std::vector<std::vector<int> >(V, std::vector<int>());
  w = std::vector<std::vector<double> >(V, std::vector<double>());
  base::Log::progress("Extracting edges from " + filename);
  for (int i = 0; i < E; i++) {
    int s, t;
    double weight;
    ifs >> s >> t >> weight;
    es[s].push_back(t);
    w[s].push_back(weight);
    base::Log::progressBar((double)i / E * 100);
  }
  base::Log::progressBarEnd();
}

Graph::Graph(const std::string& graph_data_path) {
  importGraph(graph_data_path);
}

int Graph::randomNode() const {
  std::random_device rnd;
  return rnd() % V;
}

void Graph::Serialize(const std::string& filename) {
  std::ofstream ofs(filename);
  ofs << std::setprecision(10) << std::fixed;
  ofs << V << " " << E << std::endl;
  ofs << minlat << " " << maxlat << " "
      << minlon << " " << maxlon << std::endl;
  base::Log::progress("Serializing nodes to " + filename);
  for (int i = 0; i < V; i++)
    ofs << lat[i] << " " << lon[i] << std::endl;
  base::Log::progress("Serializing edges to " + filename);
  for (int a = 0; a < V; a++) {
    for (int j = 0; j < (int)es[a].size(); j++) {
      ofs << a << " " << es[a][j] << " " << w[a][j] << std::endl;
    }
  }
}

double Graph::dist(double lata, double lona, double latb, double lonb) {
  
  double PI = 3.141592653589793;
  double P = ( lata + latb ) / 2 * PI / 180;
  double dP = ( lata - latb ) * PI / 180;
  double dR = ( lona-lonb ) * PI / 180;
  double M = 6334834 / sqrt( ( 1-0.006674 * sin( P ) * sin( P ) ) *
                             ( 1-0.006674 * sin( P ) * sin( P ) ) *
                             ( 1-0.006674 * sin( P ) * sin( P ) ) );
  double N = 6377397 / sqrt( 1-0.006674 * sin( P ) * sin( P ) );
  double D = sqrt( ( M * dP ) * ( M * dP ) + ( N * cos( P ) * dR ) *
                   ( N * cos( P ) * dR ) );
  return D;
}

}; // namespace graph
