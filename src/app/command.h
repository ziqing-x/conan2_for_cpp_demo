#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <iostream>
#include <cstdio>
#include <memory>
#include <string>
#include <array>

inline auto exec(const std::string &cmd) -> std::string {
    std::array<char, 2048> buffer;
    std::string output;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        output += buffer.data();
    }
    return output;
}


#endif // __COMMAND_H__