#pragma once

#include <string>
#include <vector>

namespace util
{
    /*
    Splits a string by a delimiter and fill an output vector with the string tokens.
    Delimiter elements are not included.
    */
    void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
    void tokenize(std::string const &str, const char delim, std::vector<int> &out);
    void tokenize(std::string const &str, const std::string &delim, std::vector<std::string> & out);
    void tokenize(std::string const &str, const std::string &delim, std::vector<int> & out);
    
    /* 
    * This function checks if all values within this string are occuring only once.
    * Returns true if all characters in string occur only once.
    */
    bool is_unique(const std::string& string);

    /* 
    * This function checks if all values within this string are occuring only once.
    * Returns true if all characters in string occur only once.
    */
    bool is_unique_ascii(const char* string, const size_t n);

    /*
    *This function swaps the values in the provided pointers
    */
    template<typename T>
    void swap(T* a, T* b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
        return;
    }
}
