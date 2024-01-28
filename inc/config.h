#pragma once

#include "utils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

typedef std::map<std::string, std::string> Env;

void newConfig(Env &cfg);
