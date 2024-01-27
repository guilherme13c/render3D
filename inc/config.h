#pragma once

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

typedef std::map<std::string, std::string> Env;

void newConfig(Env &cfg);
std::string trim(const std::string &str);
