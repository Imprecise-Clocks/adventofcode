#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool is_highest_going_up_until_edge(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    for(int y = row - 1; y >= 0; --y) {
        if(trees.at(y).at(col) >= tree) {
            return false;
        }
    }
    return true;
}

bool is_highest_going_down_until_edge(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    for(size_t y = row + 1; y < trees.size(); ++y) {
        if(trees.at(y).at(col) >= tree) {
            return false;
        }
    }
    return true;
}

bool is_highest_going_left_until_edge(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    for(int x = col - 1; x >= 0; --x) {
        if(trees.at(row).at(x) >= tree) {
            return false;
        }
    }
    return true;
}

bool is_highest_going_right_until_edge(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    for(size_t x = col + 1; x < trees.at(row).size(); ++x) {
        if(trees.at(row).at(x) >= tree) {
            return false;
        }
    }
    return true;
}

size_t trees_up(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    int y;
    for(y = 1; row - y >= 0; ++y) {
        if(trees.at(row - y).at(col) >= tree) {
            return y;
        }
    }
    return --y;
}

size_t trees_down(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    size_t y;
    for(y = 1; row + y < trees.size(); ++y) {
        if(trees.at(row + y).at(col) >= tree) {
            return y;
        }
    }
    return --y;
}

size_t trees_left(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    int x;
    for(x = 1; col - x >= 0; ++x) {
        if(trees.at(row).at(col - x) >= tree) {
            return x;
        }
    }
    return --x;
}

size_t trees_right(size_t tree, std::vector<std::vector<size_t>> trees, int row, int col) {
    size_t x;
    for(x = 1; col + x < trees.at(row).size(); ++x) {
        if(trees.at(row).at(col + x) >= tree) {
            return x;
        }
    }
    return --x;
}

size_t part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t visible_trees = 0;
    std::vector<std::vector<size_t>> trees;

    while(std::getline(file, buffer)) {
        std::vector<size_t> treerow;
        for(char tree : buffer) {
            treerow.push_back(tree - '0');
        }
        trees.push_back(treerow);
    }
    file.close();

    size_t rows = trees.size();
    size_t columns = trees.at(0).size();

    bool tree_map[rows * columns];
    std::fill_n(tree_map, rows*columns, true);

    for(int row = 1; row < rows - 1; ++row) {
        for(int col = 1; col < columns - 1; ++col) {
            size_t tree = trees.at(row).at(col);
            tree_map[(row*columns) + col] = is_highest_going_up_until_edge(tree, trees, row, col) |
                                            is_highest_going_down_until_edge(tree, trees, row, col) |
                                            is_highest_going_left_until_edge(tree, trees, row, col) |
                                            is_highest_going_right_until_edge(tree, trees, row, col);
            
        }
    }

    for(auto tree : tree_map) {
        visible_trees += tree;
    }

    return visible_trees;
}

size_t part2()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t scenic_tree_score = 0;
    std::vector<std::vector<size_t>> trees;

    while(std::getline(file, buffer)) {
        std::vector<size_t> treerow;
        for(char tree : buffer) {
            treerow.push_back(tree - '0');
        }
        trees.push_back(treerow);
    }
    file.close();

    size_t rows = trees.size();
    size_t columns = trees.at(0).size();

    size_t tree_map[rows * columns] = {0};

    for(int row = 1; row < rows - 1; ++row) {
        for(int col = 1; col < columns - 1; ++col) {
            size_t tree = trees.at(row).at(col);
            tree_map[(row*columns) + col] = trees_up(tree, trees, row, col) *
                                            trees_down(tree, trees, row, col) *
                                            trees_left(tree, trees, row, col) *
                                            trees_right(tree, trees, row, col);
        }
    }

    for(auto score : tree_map) {
        if(scenic_tree_score < score) {
            scenic_tree_score = score;
        }
    }

    return scenic_tree_score;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
