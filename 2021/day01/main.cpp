#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<size_t> get_depths(std::ifstream& file)
{
    std::string depth;
    std::vector<size_t> depth_cont;

    while(std::getline(file, depth)) {
        depth_cont.push_back((size_t) std::stoi(depth));
    }
    return depth_cont;
}

std::vector<size_t> create_moving_sum(const std::vector<size_t>& depths, const size_t window_size)
{
    std::vector<size_t> moving;
    for(size_t i = 0; i + window_size < depths.size(); ++i) {
        size_t sum = 0;
        for(size_t j = 0; j < window_size; ++j) {
            sum += depths.at(i + j);
        }
        moving.push_back(sum);
    }
    return moving;
}

size_t part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t last_depth = 0;
    size_t count = 0;

    while(std::getline(file, buffer, '\n')) {
        size_t current_depth = std::stoi(buffer);
        if(current_depth > last_depth) {
            count++;
        }
        last_depth = current_depth;
    }
    file.close();
    
    return count;
}

size_t part2()
{
    std::ifstream file;
    file.open("input.txt");

    std::vector<size_t> depths = create_moving_sum(get_depths(file), 3);
    file.close();

    size_t count = 0;
    size_t current_depth = depths.at(0);
    for (const auto depth : depths) {
        if(depth > current_depth) {
            count++;
        }
        current_depth = depth;
    }

    return count;
}

int main()
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
}