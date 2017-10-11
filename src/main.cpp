#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>

#include "log.h"
#include "osm_parser.h"
#include "visualizer.h"

void extract_graph(int argc, char *argv[], const std::string &cityname) {
  graph::OsmParser::Parse("data/graph/osm/" + cityname + ".osm", 
                          "data/graph/processed");
}

// format:
// 1                   : <hours> <num_trips>
// 2 ~ <num_trips> + 1 : <start_node> <end_node> <start_time>
void generate_trip(int argc, char *argv[], const std::string &cityname) {
  if (argc < 5) {
    base::Log::error("Please specify the number of hours and samples");
    return;
  }
  std::string str_hours(argv[3]);
  std::string str_num_samples(argv[4]);
  int hours = std::stoi(str_hours);
  int num_samples = std::stoi(str_num_samples);

  std::ofstream outfile("data/taxi/processed/taxi_" +
                       cityname + "_s" + str_num_samples + ".txt");

  std::string graph_data_name =
      "data/graph/processed/" + cityname + ".txt";
  graph::Graph g(graph_data_name);
  std::random_device rnd;

  outfile << hours << " " << str_num_samples << std::endl;
  for (int i = 0; i < num_samples; i++) {
    outfile << rnd() % g.V << " " << rnd() % g.V << " "
            << rand() % (hours * 3600LL) << std::endl;
  }
}

void run() {
  
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    base::Log::error("Please specify command to run");
    return 1;
  }
  std::string command(argv[1]);

  if (argc < 3) {
    base::Log::error("Please specify city name");
    return 1;
  }
  std::string cityname(argv[2]);

  if (command == "extract_graph")
    extract_graph(argc, argv, cityname);
   else if (command ==  "generate_trip")
    generate_trip(argc, argv, cityname);
  else if (command ==  "run")
    run();
  else {
    base::Log::error("Invalid command name: " + command);
    return 1;
  }
  return 0;
}
