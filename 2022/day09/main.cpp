#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../utils/util.h"

class Point
{
public:
    Point() {
        Point(0, 0);
    }
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    Point(const Point& other) {
        Point(other.x, other.y);
    }
    int x;
    int y;

    void operator=(const Point& other) {
        this->x = other.x;
        this->y = other.y;
    }
};

void move_tail(Point& head, Point& tail)
{
    int x_distance = head.x - tail.x;
    int y_distance = head.y - tail.y;

    if(x_distance > 1) {
        tail.x++;
        if(y_distance > 0) tail.y++;
        if(y_distance < 0) tail.y--;
    }
    else if(y_distance > 1) {
        tail.y++;
        if(x_distance > 0) tail.x++;
        if(x_distance < 0) tail.x--;
    }
    else if(x_distance < -1) {
        tail.x--;
        if(y_distance > 0) tail.y++;
        if(y_distance < 0) tail.y--;
    }
    else if(y_distance < -1) {
        tail.y--;
        if(x_distance > 0) tail.x++;
        if(x_distance < 0) tail.x--;
    }
}

void move_rope(std::vector<Point>& rope) {
    for(size_t i = 0; i < rope.size() - 1; ++i) {
        move_tail(rope.at(i), rope.at(i + 1));
    }
}

size_t part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    
    size_t sum = 0;
    Point head;
    Point tail;
    const size_t gridsize = 600;
    size_t offset = gridsize/2; 
    bool grid[gridsize][gridsize] = {0};

    while(std::getline(file, buffer)) {
        char delimiter = ' ';
        std::vector<std::string> instructions;
        util::tokenize(buffer, delimiter, instructions);
        size_t n_steps = std::stoi(instructions.at(1));
        while(n_steps--) {
            if(instructions.at(0) == "U") {
                head.y++;
                move_tail(head, tail);
            }
            if(instructions.at(0) == "D") {
                head.y--;
                move_tail(head, tail);
            }
            if(instructions.at(0) == "L") {
                head.x--;
                move_tail(head, tail);
            }
            if(instructions.at(0) == "R") {
                head.x++;
                move_tail(head, tail);
            }
            grid[offset + tail.x][offset + tail.y] = true;
        }
    }
    file.close();
    for(size_t x = 0; x < gridsize; ++x) {
        for(size_t y = 0; y < gridsize; ++y) {
            sum += grid[x][y];
        }
    }
    return sum;
}

size_t part2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;

    size_t sum = 0;
    const size_t knots = 10;
    std::vector<Point> rope(knots, Point(0,0));
    const size_t gridsize = 600;
    size_t offset = gridsize/2; 
    bool grid[gridsize][gridsize] = {0};

    while(std::getline(file, buffer)) {
        char delimiter = ' ';
        std::vector<std::string> instructions;
        util::tokenize(buffer, delimiter, instructions);
        size_t n_steps = std::stoi(instructions.at(1));
        while(n_steps--) {
            if(instructions.at(0) == "U") {
                rope.at(0).y++;
                move_rope(rope);
            }
            if(instructions.at(0) == "D") {
                rope.at(0).y--;
                move_rope(rope);
            }
            if(instructions.at(0) == "L") {
                rope.at(0).x--;
                move_rope(rope);
            }
            if(instructions.at(0) == "R") {
                rope.at(0).x++;
                move_rope(rope);
            }
            grid[offset + rope.at(knots-1).x][offset + rope.at(knots-1).y] = true;
        }
    }
    file.close();
    for(size_t x = 0; x < gridsize; ++x) {
        for(size_t y = 0; y < gridsize; ++y) {
            sum += grid[x][y];
        }
    }
    return sum;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
