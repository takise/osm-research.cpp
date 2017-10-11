#include <cstdlib>
#include <cstdio>
#include <sstream>

#include "log.h"
#include "commandline.h"

namespace base {
namespace commandline {

std::string exec_with_result(const std::string& command) {
  FILE *fp;
  char buffer[1024];
  if ((fp = popen(command.c_str(), "r")) == NULL) {
    // TODO(takise): しっかりエラー処理
    return "error";
  }
  std::stringstream stream;
  while(fgets(buffer, 1024, fp) != NULL) {
    stream << buffer;
  }
  (void) pclose(fp);
  return stream.str();
}

int count_line(const std::string& filepath) {
  std::string result = exec_with_result("wc -l " + filepath);
  if (result == "error") return -1;
  std::istringstream stream(result);
  int num_line;
  stream >> num_line;
  return num_line;
}

}; // namespace commandline
}; // namespace base
