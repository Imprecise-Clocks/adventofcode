#include <iostream>
#include <fstream>
#include <string>
#include "../../utils/util.h"

#define GRID_SIZE 1000

void toggle(bool grid[][GRID_SIZE], size_t from_x, size_t from_y, size_t to_x, size_t to_y)
{
    if(from_x > to_x) {
        util::swap<size_t>(&from_x, &to_x);
    }
    if(from_y > to_y) {
        util::swap<size_t>(&from_y, &to_y);
    }
    for(size_t i = from_x; i <= to_x; ++i) {
        for(size_t j = from_y; j <= to_y; ++j) {
            grid[i][j] = !grid[i][j];
        }
    }
    return;
}

void turn_on(bool grid[][GRID_SIZE], size_t from_x, size_t from_y, size_t to_x, size_t to_y)
{
    if(from_x > to_x) {
        util::swap<size_t>(&from_x, &to_x);
    }
    if(from_y > to_y) {
        util::swap<size_t>(&from_y, &to_y);
    }
    for(size_t i = from_x; i <= to_x; ++i) {
        for(size_t j = from_y; j <= to_y; ++j) {
            grid[i][j] = true;
        }
    }
    return;
}

void turn_off(bool grid[][GRID_SIZE], size_t from_x, size_t from_y, size_t to_x, size_t to_y)
{
    if(from_x > to_x) {
        util::swap<size_t>(&from_x, &to_x);
    }
    if(from_y > to_y) {
        util::swap<size_t>(&from_y, &to_y);
    }
    for(size_t i = from_x; i <= to_x; ++i) {
        for(size_t j = from_y; j <= to_y; ++j) {
            grid[i][j] = false;
        }
    }
    return;
}

void change(int grid[][GRID_SIZE], size_t from_x, size_t from_y, size_t to_x, size_t to_y, int value)
{
    if(from_x > to_x) {
        util::swap<size_t>(&from_x, &to_x);
    }
    if(from_y > to_y) {
        util::swap<size_t>(&from_y, &to_y);
    }
    for(size_t i = from_x; i <= to_x; ++i) {
        for(size_t j = from_y; j <= to_y; ++j) {
            grid[i][j] = grid[i][j] + value >= 0 ? grid[i][j] + value : 0;
        }
    }
    return;
}

size_t part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    size_t lights = 0;
    bool grid[GRID_SIZE][GRID_SIZE] = {false};

    while(std::getline(file, buffer)) {
        char delimiter = ' ';
        std::vector<std::string> instructions;
        util::tokenize(buffer, delimiter, instructions);
        std::vector<std::string> coordinates;
        delimiter = ',';
        if(instructions.at(0) == "toggle") {
            util::tokenize(instructions.at(1), delimiter, coordinates);
            size_t from_x = std::stoi(coordinates.at(0));
            size_t from_y = std::stoi(coordinates.at(1));

            coordinates.clear();
            util::tokenize(instructions.at(3), delimiter, coordinates);
            size_t to_x = std::stoi(coordinates.at(0));
            size_t to_y = std::stoi(coordinates.at(1));
            
            toggle(grid, from_x, from_y, to_x, to_y);
        }
        else {
            util::tokenize(instructions.at(2), delimiter, coordinates);
            size_t from_x = std::stoi(coordinates.at(0));
            size_t from_y = std::stoi(coordinates.at(1));

            coordinates.clear();
            util::tokenize(instructions.at(4), delimiter, coordinates);
            size_t to_x = std::stoi(coordinates.at(0));
            size_t to_y = std::stoi(coordinates.at(1));

            if(instructions.at(1) == "on") {
                turn_on(grid, from_x, from_y, to_x, to_y);
            }
            else {
                turn_off(grid, from_x, from_y, to_x, to_y);
            }
        }
    }
    file.close();

    for(size_t i = 0; i < GRID_SIZE; ++i) {
        for(size_t j = 0; j < GRID_SIZE; ++j) {
            lights += grid[i][j];
        }
    }
    return lights;
}

size_t part2()
{    
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    int lights = 0;
    int grid[GRID_SIZE][GRID_SIZE] = {0};

    while(std::getline(file, buffer)) {
        char delimiter = ' ';
        std::vector<std::string> instructions;
        std::vector<std::string> coordinates;
        util::tokenize(buffer, delimiter, instructions);
        delimiter = ',';
        if(instructions.at(0) == "toggle") {
            util::tokenize(instructions.at(1), delimiter, coordinates);
            size_t from_x = std::stoi(coordinates.at(0));
            size_t from_y = std::stoi(coordinates.at(1));

            coordinates.clear();
            util::tokenize(instructions.at(3), delimiter, coordinates);
            size_t to_x = std::stoi(coordinates.at(0));
            size_t to_y = std::stoi(coordinates.at(1));
            
            change(grid, from_x, from_y, to_x, to_y, 2);
        }
        else {
            util::tokenize(instructions.at(2), delimiter, coordinates);
            size_t from_x = std::stoi(coordinates.at(0));
            size_t from_y = std::stoi(coordinates.at(1));

            coordinates.clear();
            util::tokenize(instructions.at(4), delimiter, coordinates);
            size_t to_x = std::stoi(coordinates.at(0));
            size_t to_y = std::stoi(coordinates.at(1));

            if(instructions.at(1) == "on") {
                change(grid, from_x, from_y, to_x, to_y, 1);
            }
            else {
                change(grid, from_x, from_y, to_x, to_y, -1);
            }
        }
    }
    file.close();

    for(size_t i = 0; i < GRID_SIZE; ++i) {
        for(size_t j = 0; j < GRID_SIZE; ++j) {
            lights += grid[i][j];
        }
    }
    return (size_t) lights;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}