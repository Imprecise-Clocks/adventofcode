#include <iostream>
#include <fstream>
#include <string>

enum RPS
{
    Rock = 1,
    Paper = 2,
    Siccor = 3
};

enum Result
{
    Win = 6,
    Draw = 3,
    Loss = 0
};

size_t calculateResult(RPS player1, RPS player2)
{   
    if(player1 == player2) return Result::Draw;
    if(((player2 > player1)*((player2 + player1) % 3) + (player1 > player2)*(player1 - player2)) == 1) return Result::Win;
    return Result::Loss;
}

int part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t score = 0;

    while(std::getline(file, buffer)) {
        RPS opponent = (RPS) (buffer.at(0) - 'A' + 1);
        RPS me = (RPS) (buffer.at(2) - 'X' + 1);

        score += me + calculateResult(me, opponent);
    }
    file.close();

    return score;
}

int part2()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t score = 0;

    while(std::getline(file, buffer)) {
        RPS opponent = (RPS) (buffer.at(0) - 'A' + 1);
        Result myResult = (Result) ((buffer.at(2) - 'X') * 3);

        score += myResult;

        if(myResult == Result::Draw) score += opponent;
        else if(myResult == Result::Loss) score += opponent + 2 > 3 ? (opponent + 2) % 3 : opponent + 2;
        else if(myResult == Result::Win) score += opponent + 1 > 3 ? (opponent + 1) % 3 : opponent + 1;
    }
    file.close();

    return score;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
