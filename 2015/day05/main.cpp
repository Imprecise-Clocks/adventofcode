#include <iostream>
#include <fstream>
#include <string>

bool contains_three_vowels(const std::string& string)
{
    size_t vowels_counter = 0;
    for(char character : string) {
        if(character == 'a' ||
           character == 'e' ||
           character == 'i' ||
           character == 'o' ||
           character == 'u') {
            ++vowels_counter;
        }
        if(vowels_counter == 3) {
            return true;
        }
    }
    return false;
}

bool contains_conjugated_duplicates(const std::string& string)
{
    int value = 0;
    for(char character : string) {
        if(value == 0) {
            value += character;
        }
        else {
            value -= character;
            if(value == 0) {
                return true;
            }
            value = character;
        }
    }
    return false;
}

bool contains_substring(const std::string& string)
{
    static const std::string ab = "ab";
    static const std::string cd = "cd";
    static const std::string pq = "pq";
    static const std::string xy = "xy";
    static const size_t pair_size = 2;

    for(size_t i = 0; i < string.size() - 1; ++i) {
        if(string.substr(i, pair_size) == ab ||
           string.substr(i, pair_size) == cd ||
           string.substr(i, pair_size) == pq ||
           string.substr(i, pair_size) == xy) {
            return true;
        }
    }
    return false;
}

bool contains_duplicate_pairs(const std::string& string)
{
    static const size_t pair_size = 2;
    std::string pair;

    for(size_t i = 0; i < string.size() - 1; ++i) {
        pair = string.substr(i, pair_size);
        for(size_t j = i + pair_size; j < string.size(); ++j) {
            if(pair == string.substr(j, pair_size)) {
                return true;
            }
        }
    }
    return false;
}

bool contains_palindrom(const std::string& string)
{
    static const size_t palindrom_distance = 2;
    
    for(size_t i = 0; i < string.size() - palindrom_distance; ++i) {
        if(string.at(i) == string.at(i + palindrom_distance)) {
            return true;
        }
    }
    return false;
}

size_t part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t nice = 0;

    while(std::getline(file, buffer)) {
        if(contains_conjugated_duplicates(buffer) && contains_three_vowels(buffer) && ! contains_substring(buffer)) {
            ++nice;
        }
    }
    file.close();

    return nice;
}

size_t part2()
{    
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t nice = 0;

    while(std::getline(file, buffer)) {
        if(contains_duplicate_pairs(buffer) && contains_palindrom(buffer)) {
            ++nice;
        }
    }
    file.close();

    return nice;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}