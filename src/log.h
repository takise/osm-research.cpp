#ifndef LOG_H_
#define LOG_H_

#include <string>

namespace base {

class Log {
public:
  static void printMessage(const std::string& kind, const std::string& color,
                           const std::string& message);

  static void info(const std::string& message);
  static void progress(const std::string& message);
  static void warning(const std::string& message);
  static void error(const std::string& message);

  static void progressBar(int progress);
  static void progressBarEnd();
};

}; // namespace base

#endif
