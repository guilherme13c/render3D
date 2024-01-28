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
