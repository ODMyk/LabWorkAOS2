#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

namespace Utils {
	void parse(std::string &line, std::string &command, std::vector<std::string> &args);
	void getUserLine(std::string& line);
}

#endif
