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

int part1()
{
    std::ifstream file;
    file.open("input1.txt");
    std::string buffer;
    size_t score = 0;

    while(std::getline(file, buffer)) {
        RPS opponent = (RPS) (buffer.at(0) - 'A' + 1);
        RPS me = (RPS) (buffer.at(2) - 'X' + 1);

        if(me == opponent) score += Result::Draw + me;
        
        else if(me == RPS::Rock && opponent == RPS::Paper)      score += Result::Loss + me;
        else if(me == RPS::Paper && opponent == RPS::Rock)      score += Result::Win + me;
        else if(me == RPS::Siccor && opponent == RPS::Rock)     score += Result::Loss + me;
        else if(me == RPS::Rock && opponent == RPS::Siccor)     score += Result::Win + me;
        else if(me == RPS::Paper && opponent == RPS::Siccor)    score += Result::Loss + me;
        else if(me == RPS::Siccor && opponent == RPS::Paper)    score += Result::Win + me;
    }

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
        
        if(myResult == Result::Loss) {
            if(opponent == RPS::Rock) score += RPS::Siccor;
            if(opponent == RPS::Paper) score += RPS::Rock;
            if(opponent == RPS::Siccor) score += RPS::Paper;
        }

        if(myResult == Result::Win) {
            if(opponent == RPS::Rock) score += RPS::Paper;
            if(opponent == RPS::Paper) score += RPS::Siccor;
            if(opponent == RPS::Siccor) score += RPS::Rock;
        }
    }

    return score;
}

int main(int argc, char** argv) 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
