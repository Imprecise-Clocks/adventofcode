#pragma once

#include <string>
#include <vector>

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);

template <typename T>
void reverse(std::vector<T> &vec);
