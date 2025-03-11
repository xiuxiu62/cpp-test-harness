#pragma once

#include <sstream>
#include <string>

template <typename T> std::string to_string(const T &val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

template <> inline std::string to_string(const std::string &val) {
    return "\"" + val + "\"";
}

template <> inline std::string to_string(const char *const &val) {
    return val ? ('"' + std::string(val) + '"') : "nullptr";
}
