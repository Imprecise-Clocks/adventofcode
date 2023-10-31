#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "../../utils/util.h"

class Monkey
{
public:
    Monkey(const std::vector<int64_t>& items, int multiply, int add, int devisible, int passed, int failed) {
        this->items = items;
        this->multiply = multiply;
        this->add = add;
        this->devisible = devisible;
        this->passed_idx = passed;
        this->failed_idx = failed;
        this->id = monkey_id++;
    };

    static int monkey_id;

    std::vector<int64_t> items;
    int id;
    int inspections = 0;
    bool stressed = false;

private:
    int multiply;
    int add;
    int devisible;
    int passed_idx;
    int failed_idx;

public:
    void inspect(int64_t& item, int& idx) {
        item = this->items.back();
        this->items.pop_back();
        int multiplication = this->multiply == 0 ? item : this->multiply; 
        int reflief_level = stressed ? 1 : 3;

        item = item * multiplication + this->add;
        item /= reflief_level;

        if(item % this->devisible == 0) {
            idx = this->passed_idx;
        }
        else {
            idx = this->failed_idx;
        }
        this->inspections++;
    }

    static Monkey create(std::vector<std::string>& information) {
        std::vector<int64_t> list = std::vector<int64_t>();
        int addition = 0, multiplication = 1, devisible = 1;
        int passed = 0, failed = 0;

        std::vector<std::string> tokens;
        char delim = ':';
        std::string buffer = information.at(1);
        util::tokenize(buffer, delim, tokens);
        delim = ',';
        buffer = tokens.at(1);
        tokens.clear();
        util::tokenize(buffer, delim, tokens);
        for(auto& token : tokens) {
            token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
            list.push_back(std::stoi(token));
        }

        tokens.clear();
        delim = ' ';
        buffer = information.at(2);
        util::tokenize(buffer, delim, tokens);
        if(tokens.at(tokens.size() - 2) == "*") {
            try {
                multiplication = std::stoi(tokens.back());
            }
            catch(...) {
                multiplication = 0;
            }
        }
        else if(tokens.at(tokens.size() - 2) == "+") {
            addition = std::stoi(tokens.back());
        }
        
        tokens.clear();
        delim = 'y';
        buffer = information.at(3);
        util::tokenize(buffer, delim, tokens);
        buffer = tokens.back();
        buffer.erase(std::remove_if(buffer.begin(), buffer.end(), ::isspace), buffer.end());
        devisible = std::stoi(buffer);
        
        tokens.clear();
        delim = 'y';
        buffer = information.at(4);
        util::tokenize(buffer, delim, tokens);
        buffer = tokens.back();
        buffer.erase(std::remove_if(buffer.begin(), buffer.end(), ::isspace), buffer.end());
        passed = std::stoi(buffer);
        
        tokens.clear();
        delim = 'y';
        buffer = information.at(5);
        util::tokenize(buffer, delim, tokens);
        buffer = tokens.back();
        buffer.erase(std::remove_if(buffer.begin(), buffer.end(), ::isspace), buffer.end());
        failed = std::stoi(buffer);

        return Monkey(list, multiplication, addition, devisible, passed, failed);
    } 
};

int Monkey::monkey_id = 0;

int64_t part1()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer; 
    int rounds = 20;
    std::vector<std::string> information;
    std::vector<Monkey> monkey_list;

    while(std::getline(file, buffer)) {
        if(buffer.size() > 0) {
            information.push_back(buffer);
        }
        else {
            monkey_list.push_back(Monkey::create(information));
            information.clear();
        }
    }
    file.close();
    
    monkey_list.push_back(Monkey::create(information));
    Monkey::monkey_id = 0;
    
    while(rounds--) {
        for(std::size_t i = 0; i < monkey_list.size(); ++i) {
            int runs = monkey_list.at(i).items.size();
            int64_t item;
            int idx;
            while(runs--) {
                monkey_list.at(i).inspect(item, idx);
                monkey_list.at(idx).items.push_back(item);
            }
        }
    }
    std::sort(monkey_list.begin(), monkey_list.end(), [](Monkey& a, Monkey& b){
        return a.inspections > b.inspections;
    });

    return monkey_list.at(0).inspections * monkey_list.at(1).inspections;
}

int64_t part2()
{
    std::ifstream file;
    file.open("input.txt");
    std::string buffer; 
    const int64_t rounds = 10000;
    std::vector<std::string> information;
    std::vector<Monkey> monkey_list;

    while(std::getline(file, buffer)) {
        if(buffer.size() > 0) {
            information.push_back(buffer);
        }
        else {
            monkey_list.push_back(Monkey::create(information));
            monkey_list.at(monkey_list.size() - 1).stressed = true;
            information.clear();
        }
    }
    file.close();
    
    monkey_list.push_back(Monkey::create(information));
    monkey_list.at(monkey_list.size() - 1).stressed = true;
    
    int64_t round = 0;
    while(rounds - round) {
        if(round == 20) {
            for(auto& monkey : monkey_list) {
                monkey.stressed = true;
            }
        }
        for(std::size_t i = 0; i < monkey_list.size(); ++i) {
            int runs = monkey_list.at(i).items.size();
            int64_t item;
            int idx;
            while(runs--) {
                monkey_list.at(i).inspect(item, idx);
                monkey_list.at(idx).items.push_back(item);
            }
        }
        round++;
    }
    std::sort(monkey_list.begin(), monkey_list.end(), [](Monkey& a, Monkey& b){
        return a.inspections > b.inspections;
    });

    return monkey_list.at(0).inspections * monkey_list.at(1).inspections;  
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}
