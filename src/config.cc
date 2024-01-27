#include "config.h"

void newConfig(Env &cfg) {
    std::ifstream dotenv(".env");

    if (!dotenv.is_open()) {
        std::cerr << "Error: Unable to open .env file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(dotenv, line)) {
        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            cfg[trim(key)] = trim(value);
        } else {
            std::cerr << "Warning: Malformed line in config file: " << line
                      << std::endl;
        }
    }

    dotenv.close();
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");

    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }

    return str.substr(first, last - first + 1);
}
