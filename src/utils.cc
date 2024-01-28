#include "utils.h"

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");

    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }

    return str.substr(first, last - first + 1);
}
