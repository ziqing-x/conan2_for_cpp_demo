#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <yaml-cpp/yaml.h>
#include <string>

struct Config {
    struct Logger {
        std::string log_name;
        std::string log_file_name;
        std::string log_pattern;
        uint64_t log_fize_size;
        uint16_t log_rotation;
        uint16_t log_flush;
    } logger;

    bool load_config(const std::string &filename) {
        try {
            YAML::Node config = YAML::LoadFile(filename);
            logger.log_name = config["logger"]["log_name"].as<std::string>();
            logger.log_file_name = config["logger"]["log_file_name"].as<std::string>();
            logger.log_pattern = config["logger"]["log_pattern"].as<std::string>();
            logger.log_fize_size = config["logger"]["log_fize_size"].as<uint64_t>();
            logger.log_rotation = config["logger"]["log_rotation"].as<uint16_t>();
            logger.log_flush = config["logger"]["log_flush"].as<uint16_t>();
        } catch(...) {
            return false;
        }
        return true;
    }
};

#endif // __CONFIG_H__