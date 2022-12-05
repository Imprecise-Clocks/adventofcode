#include "util.h"

template <typename T>
void reverse(std::vector<T> &vec)
{
    std::vector<T> temp;
    for(size_t i = vec.size() - 1; i >= 0; --i) {
        temp.push_back(vec.at(i));
    }
    vec = temp;
}

void tokenize(const std::string &str, const char delim, std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}