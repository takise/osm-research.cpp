#include <algorithm>
#include <sstream>
#include <set>

#include "osm_parser.h"
#include "log.h"

namespace graph {

std::string OsmParser::INPUT_FOLDER_PATH = "../data/graph/osm";
std::string OsmParser::OUTPUT_FOLDER_PATH = "../data/graph/processed";

// Get pairs<key, value> from tag <tagname k="v" ... >
std::map<std::string, std::string> OsmParser::GetAttributes(
    XmlInspector &inspector) {
  XmlInspector::SizeType i;
  std::map<std::string, std::string> res;
  for (i = 0; i < inspector.GetAttributesCount(); ++i) {
	res[inspector.GetAttributeAt(i).Name] =
	  inspector.GetAttributeAt(i).Value;
  }
  return res;
}

std::string OsmParser::GetBaseName(const std::string& filename) {
  std::string basename;
  size_t last_slash_pos = filename.find_last_of('/');
  if (last_slash_pos != std::string::npos) {
	basename = filename.substr(last_slash_pos + 1);
  } else {
	basename = filename;
  }
	
  // Get filename without extension
  if ((int)filename.size() < 4 || 
	  filename.substr((int)filename.size() - 4) != ".osm") {
    return ""; /* Error */
  }
  basename = basename.substr(0, (int)basename.size() - 4);
  return basename;
}

// Parse .osm file and
void OsmParser::Parse(const std::string& input_filename,
                      const std::string& output_dirname) {
  // Open input file
  std::ifstream infile(input_filename.c_str());
  if (!infile.good()) {
    base::Log::error("Failed to open file for input: " + input_filename);
    return;
  }

  std::string basename = GetBaseName(input_filename);
  if (basename.empty()) {
    base::Log::error("Invalid filename of  \'" + input_filename +
                     "\'. the filename must end with \'.osm\'");
    return;
  }

  // Open output file.
  // TODO(takise): Check if the output dir exists and writable
  std::string output_filename = output_dirname + '/' + basename + ".txt";
  base::Log::info("finepath to output: " + output_filename);
  std::ofstream outfile(output_filename);
  if (!outfile.good()) {
    base::Log::error("Failed to open file for output: " + output_filename);
    return;
  }

  // First: summarize graph information (node num, edge num, nodes)
  base::Log::progress("Start extracting data from: " + input_filename);
  base::Log::progress("Extracting nodes from: " + input_filename);
  typedef long long ll;
  std::set<ll> nids;
  std::map<ll, std::map<std::string, std::string>> metas;
  Xml::Inspector<Xml::Encoding::Utf8Writer> inspector(input_filename);
  ll id;
  std::map<std::string, std::string> attrs, bounds;
  std::map<ll, int> idtoidx;
  std::vector<ll> ns;
  Graph baseG;
  int baseE = 0;

  // Parsing part
  while (inspector.Inspect()) {
    auto attrs2 = GetAttributes(inspector);
    auto inspected = inspector.GetInspected();
    std::string name = inspector.GetName();
    
    // Start Tag: e.g. <node>
    if (inspected == Xml::Inspected::StartTag) {
      attrs = attrs2;
      if (name == "node") {
        id = stoll(attrs["id"]);
        nids.insert(id);
      }
    }
    
    // End Tag: e.g. </node>
    else if (inspected == Xml::Inspected::EndTag) {
      if (name == "node") {
        metas[id] = attrs;
      } else if (name == "way") {
        if (idtoidx.empty()) {
          int cnt = 0;
          baseG = Graph(nids.size());
          for (ll id : nids) {
            baseG.lat[cnt] = stof(metas[id]["lat"]);
            baseG.lon[cnt] = stof(metas[id]["lon"]);
            idtoidx[id] = cnt;
            cnt++;
          }
          base::Log::progress("Finished extracting nodes");
          base::Log::progress("Extacting edges...");
        }
        for (int i = 0; i < (int)ns.size() - 1; i++) {
          int aidx = idtoidx[ns[i]];
          int bidx = idtoidx[ns[i + 1]];
          double dist = Graph::dist(baseG.lat[aidx], baseG.lon[aidx],
                                    baseG.lat[bidx], baseG.lon[bidx]);
          baseG.es[aidx].push_back(bidx);
          baseG.w[aidx].push_back(dist);
          baseG.es[bidx].push_back(aidx);
          baseG.w[bidx].push_back(dist);
        }
        baseE += (int)ns.size() - 1;
        ns.clear();
      }
    }
    
    // Empty Tag: e.g. <node ... />
    else if (inspected == Xml::Inspected::EmptyElementTag) {
      if (name == "node") {
        id = stoll(attrs2["id"]);
        nids.insert(id);
        metas[id] = attrs2;
      } else if (name == "tag") {
        for (auto kv : attrs2) attrs[kv.first] = kv.second;
      } else if (name == "nd"){
        ns.push_back(stoll(attrs2["ref"]));
      } else if (name == "bounds") {
        bounds = GetAttributes(inspector);
      }
    }
  }

  std::stringstream ss;
  if (inspector.GetErrorCode() != Xml::ErrorCode::None) {
    ss << inspector.GetErrorMessage() << " At row: "
       << inspector.GetRow() << ", column: " << inspector.GetColumn();
    base::Log::error(ss.str());
  }
  ss.clear();
  base::Log::progress("Finished extracting graph");
  ss << "nodes: " << baseG.V << ", edges: " << baseE << '\n';
  base::Log::info(ss.str());

  // Normalizing Part
  // Find the maximum connected component
  UnionFind uf(baseG.V);
  for (int a = 0; a < baseG.V; a++) {
    for (int b : baseG.es[a]) {
      uf.merge(a, b);
    }
  }
  std::map<int, int> mp;
  for (int i = 0; i < baseG.V; i++) mp[uf.root(i)]++;
  int V = 0, root = -1;
  for (auto p : mp) {
    if (p.second > V) {
      V = p.second;
      root = p.first;
    }
  }

  // Build a new graph
  int E = 0;
  Graph g(V);
  std::map<int, int> tonidx;
  int cnt = 0;
  // assign new ids
  for (int i = 0; i < baseG.V; i++) {
    if (uf.root(i) == root) {
      g.lat[cnt] = baseG.lat[i];
      g.lon[cnt] = baseG.lon[i];
      tonidx[i] = cnt++;
    }
  }
  // span edges
  for (int a = 0; a < baseG.V; a++) {
    if (uf.root(a) == root) {
      for (int j = 0; j < baseG.es[a].size(); j++) {
        int b = baseG.es[a][j];
        int from = tonidx[a], to = tonidx[b];
        g.es[from].push_back(to);
        g.w[from].push_back(baseG.w[a][j]);
        E++;
      }
    }
  }

  g.E = E;
  for (int i = 0; i < g.V; i++) {
    g.minlat = std::min(g.minlat, g.lat[i] - 0.001);
    g.maxlat = std::max(g.maxlat, g.lat[i] + 0.001);
    g.minlon = std::min(g.minlon, g.lon[i] - 0.001);
    g.maxlon = std::max(g.maxlon, g.lon[i] + 0.001);
  }

  ss.clear();
  ss << "Finished normalizing graph (nodes: " << V << ", edges: " << E << ")";
  base::Log::progress(ss.str());

  base::Log::progress("Serializing graph");
  g.Serialize(output_filename);

  base::Log::progress("Finished serializing graph");
  // g.visualize();
}

}; // namespace graph
