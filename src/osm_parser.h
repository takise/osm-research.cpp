#include <map>

#include "graph.h"

#include "../lib/XMLInspector/XmlInspector.hpp"
#include "../lib/UnionFind/union_find.h"

namespace graph {

class OsmParser {

  static std::string INPUT_FOLDER_PATH;
  static std::string OUTPUT_FOLDER_PATH;

  typedef Xml::Inspector<Xml::Encoding::Utf8Writer> XmlInspector;
  // Get pairs<key, value> from tag <tagname k="v" ... >
  static std::map<std::string, std::string> GetAttributes(
      XmlInspector &inspector);
  
  static std::string GetBaseName(const std::string& filename);

public:

  /* Parse .osm file in data/osm and Save converted one onto data/preprocessed.
	 input_filename must be a relative path from project home dir. output_dir
	 must not end with '/'.
   */
  static void Parse(const std::string &input_filename,
                    const std::string &output_dirname);
};

}; // namespace graph
