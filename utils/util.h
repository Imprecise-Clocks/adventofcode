#pragma once

#include <string>
#include <vector>

namespace util
{
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

    template <typename T>
    void reverse(std::vector<T> &vec);

    bool is_unique(const std::string& string);
    bool is_unique_ascii(const char* string, const size_t n);
}