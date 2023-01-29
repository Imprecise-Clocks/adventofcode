#include <iostream>
#include <fstream>
#include <utility>
#include "../header/board.h"

std::vector<int> convertStringRepresantingNumbers2AContainerHoldingIntegers(std::string& stringRepresantingNumbers) {
    std::stringstream ss(stringRepresantingNumbers);
    std::string number;
    std::vector<int> containerHoldingIntegers;
    while(std::getline(ss, number, ',')){
        containerHoldingIntegers.push_back(stoi(number));
    }
    return containerHoldingIntegers;
}

std::pair<std::vector<int>, std::vector<Board>> get_elements(const char* filename)
{
    std::ifstream ifs(filename);
    if(!ifs.is_open()){
        return {std::vector<int>(), std::vector<Board>()};
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    
    std::string line;
    std::getline(ss, line, '\n');
    std::vector<int> draws = convertStringRepresantingNumbers2AContainerHoldingIntegers(line);
    std::string board;
    std::vector<Board> boards;

    while(std::getline(ss, line, '\n')) {
        if(line.empty() && !board.empty()) {
            boards.push_back(Board(board));
            board = "";
            continue;
        } else if(!line.empty()) {
            board += line + "\n";
        }
    }
    return {draws, boards};
}

int main(int argc, char** argv)
{
    if(argc != 2) {
        return -1;
    }

    auto DrawsAndBoards = get_elements(argv[1]);
    for(auto draw : DrawsAndBoards.first) {
        
        for(int i = 0; i < DrawsAndBoards.second.size(); ++i) {
            if(DrawsAndBoards.second.at(i).checkBingo(draw)) {
                std::cout << DrawsAndBoards.second.at(i).getBoardSum() * draw << std::endl;
                return 0; 
            }
        }

    }
    return 0;
}