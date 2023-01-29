#pragma once

#include <string>
#include <vector>

namespace util
{
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

    /* This function checks if all values within this string are occuring only once.
    * const std::string& string: string to be checked on uniqueness.
    * return: True if all characters in string occur only once.
    */
    bool is_unique(const std::string& string);
    bool is_unique_ascii(const char* string, const size_t n);
}