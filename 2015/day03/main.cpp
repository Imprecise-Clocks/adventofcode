#include <iostream>
#include <fstream>
#include <array>

#define UP '^'
#define DOWN 'v'
#define LEFT '<'
#define RIGHT '>'

#define GRID_SIZE 143 // This is the smallest grid size possible for the provided input

void update_grid(std::array<std::array<bool, GRID_SIZE>, GRID_SIZE>& grid, char direction, int& x, int& y) {
    if(direction == UP) {
        if(++y == GRID_SIZE) y = 0;
        grid.at(y).at(x) = true;
    }
    if(direction == DOWN) {
        if(--y < 0) y = GRID_SIZE - 1;
        grid.at(y).at(x) = true;
    }
    if(direction == LEFT) {
        if(++x == GRID_SIZE) x = 0;
        grid.at(y).at(x) = true;
    }
    if(direction == RIGHT) {
        if(--x < 0) x = GRID_SIZE - 1;
        grid.at(y).at(x) = true;
    }
    return;
}

int part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t visited_houses = 0;

    std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> grid = {0};
    int current_x = 0;
    int current_y = 0;
    grid.at(current_y).at(current_x) = true;
    
    std::getline(file, buffer);
    for(char direction : buffer) {
        update_grid(grid, direction, current_x, current_y);
    }

    for(size_t i = 0; i < grid.size(); ++i) {
        for(size_t j = 0; j < grid.at(i).size(); ++j) {
            visited_houses += grid.at(i).at(j);
        }
    }
    
    return visited_houses;
}

int part2()
{    
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t visited_houses = 0;

    std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> grid = {0};
    int current_x = 0;
    int current_y = 0;
    int robo_x = 0;
    int robo_y = 0;
    grid.at(current_y).at(current_x) = true;
    
    std::getline(file, buffer);
    for(size_t i = 0; i < buffer.size(); ++i) {
        if(i % 2 == 0) {
            update_grid(grid, buffer.at(i), current_x, current_y);
        }
        else {
            update_grid(grid, buffer.at(i), robo_x, robo_y);
        }
    }

    for(size_t i = 0; i < grid.size(); ++i) {
        for(size_t j = 0; j < grid.at(i).size(); ++j) {
            visited_houses += grid.at(i).at(j);
        }
    }
    
    return visited_houses;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}