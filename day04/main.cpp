#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

bool is_full_sub_section(int startid1, int endid1, int startid2, int endid2)
{
    return (startid1 <= startid2 && endid1 >= endid2) || (startid1 >= startid2 && endid1 <= endid2);
}

bool is_sub_section(int startid1, int endid1, int startid2, int endid2)
{
    return ! ((startid1 < startid2 && endid1 < startid2) || (startid1 > endid2 && endid1 > endid2));
}

std::vector<int> get_section_ids(const std::string& buffer)
{
        char delimiter = ',';
        std::vector<std::string> sections;
        std::vector<std::string> sectionIDs;
        std::vector<int> ids;
        
        tokenize(buffer, delimiter, sections);
        
        for(auto& section : sections) {
            delimiter = '-';
            tokenize(section, delimiter, sectionIDs);
        }
        for(auto& id : sectionIDs) {
            ids.push_back(std::stoi(id));
        }
        return ids;
}

int part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t sum = 0;

    while(std::getline(file, buffer)) {
        std::vector<int> sectionID = get_section_ids(buffer);
        
        sum += is_full_sub_section(sectionID.at(0), sectionID.at(1), sectionID.at(2), sectionID.at(3));
    }
    return sum;
}

int part2()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t sum = 0;

    while(std::getline(file, buffer)) {
        std::vector<int> sectionID = get_section_ids(buffer);

        sum += is_sub_section(sectionID.at(0), sectionID.at(1), sectionID.at(2), sectionID.at(3));
    }
    return sum;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
