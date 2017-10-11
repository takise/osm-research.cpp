#include <iostream>
#include <map>

#include "log.h"

namespace base {

namespace LogConst {
std::map<std::string, std::string> esc = {
	{"black", "\u001b[30m"},
	{"red", "\u001b[31m"},
	{"green", "\u001b[32m"},
	{"yellow", "\u001b[33m"},
	{"blue", "\u001b[34m"},
	{"magenta", "\u001b[35m"},
	{"cyan", "\u001b[36m"},
	{"white", "\u001b[37m"},
	{"reset", "\u001b[0m"},
	{"bold", "\u001b[1m"},
	{"underline", "\u001b[4m"}
  };
}

void Log::progressBar(int progress) {
  std::string sharps(progress, '#');
  std::cerr << '\r' << sharps << " " << progress << "%" << std::flush;
}

void Log::progressBarEnd() {
  progressBar(100);
  std::cerr << std::endl;
}

void Log::printMessage(const std::string& kind, const std::string& color,
                       const std::string& message) {
  std::cerr << LogConst::esc["bold"] << LogConst::esc["underline"]
            << LogConst::esc[color] << kind << LogConst::esc["reset"]
            << ": " << message << std::endl;
}

void Log::info(const std::string& message) {
  std::cerr << LogConst::esc["underline"]
            << LogConst::esc["blue"] << "Info" << LogConst::esc["reset"]
            << ": " << message << std::endl;
}

void Log::warning(const std::string& message) {
  std::cerr << LogConst::esc["bold"] << LogConst::esc["underline"]
            << LogConst::esc["yellow"] << "Warning" << LogConst::esc["reset"]
            << ": " << message << std::endl;
}

void Log::progress(const std::string& message) {
  std::cerr << LogConst::esc["blue"] << "==> " << LogConst::esc["reset"]
            << LogConst::esc["bold"] << message << std::endl
            << LogConst::esc["reset"] << std::flush;
}

void Log::error(const std::string& message) {
  std::cerr << LogConst::esc["bold"] << LogConst::esc["underline"]
            << LogConst::esc["red"] << "Error" << LogConst::esc["reset"]
            << ": " << message << std::endl;
}

}; // namespace base
