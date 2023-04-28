#include <iostream>
#include <fstream>
#include <stdint.h>
#include <regex>
#include <unordered_map>
#include "../../utils/util.h"

class Register {
public:
    Register() {}

    Register(const uint16_t value) {
        this->is_initialized = true;
        this->value = value;
    }

    Register& operator =(const Register& other)
    {
        this->value = other.value;
        this->is_initialized = true;
        return *this;
    }

    Register& operator =(const uint16_t value)
    {
        this->value = value;
        this->is_initialized = true;
        return *this;
    }

    uint16_t operator &(const Register& other) const  
    {
        return this->value & other.value;
    }

    uint16_t operator |(const Register& other) const
    {
        return this->value | other.value;
    }

    uint16_t operator ~() const
    {
        return ~this->value;
    }

    uint16_t operator <<(const Register& other) const
    {
        return this->value << other.value;
    }

    uint16_t operator >>(const Register& other) const
    {
        return this->value >> other.value;
    }

    void execute()
    {
        if(this->is_initialized) {
            return;
        }
        if(left) {
            left->execute();
        }
        if(right) {
            right->execute();
        }
        switch (this->op)
        {
        case Register::OP::AND:
            *this = *(this->left) & *(this->right);
            break;
        case Register::OP::OR:
            *this = *(this->left) | *(this->right);
            break;
        case Register::OP::LSHIFT:
            *this = *(this->left) << *(this->right);
            break;
        case Register::OP::RSHIFT:
            *this = *(this->left) >> *(this->right);
            break;
        case Register::OP::NOT:
            *this = ~*(this->left);
            break;
        case Register::OP::ASSIGN:
            *this = *(this->left);
            break;
        
        default:
            break;
        }
        return;
    }

    void set_left(Register& left) 
    {
        this->left = &left;
        return;
    }

    void set_right(Register& right) 
    {
        this->right = &right;
        return;
    }

    uint16_t value = 0;
    bool is_initialized = false;
    enum class OP
    {
        AND, OR, NOT, LSHIFT, RSHIFT, ASSIGN
    };
    Register::OP op;

    Register* left;
    Register* right;
};

std::vector<Register*> trash_can; // I am not proud!

void empty_trash()
{
    for(auto garbage : trash_can) {
        delete garbage;
    }
    trash_can.clear();
    return;
}

Register& find_or_create(const std::string& identifier, std::unordered_map<std::string, Register>& map)
{
    if(std::regex_match(identifier, std::regex("[0-9]+"), std::regex_constants::match_any)) {
        Register* temp = new Register(std::stoi(identifier));
        trash_can.push_back(temp); // don't laugh
        return *temp;
    }
    if(map.find(identifier) == map.end()) {
        map.insert({identifier, Register()});
    }
    return map.find(identifier)->second;
}

void parse(std::string& text, std::unordered_map<std::string, Register>& map)
{
    // ^[0-9]+ -> [a-z]+
    // ([a-z]+|[0-9]+) AND ([a-z]+|[0-9]+) -> [a-z]+
    // ([a-z]+|[0-9]+) OR ([a-z]+|[0-9]+) -> [a-z]+
    // ([a-z]+|[0-9]+) LSHIFT [0-9]+ -> [a-z]+
    // ([a-z]+|[0-9]+) RSHIFT [0-9]+ -> [a-z]+
    // NOT [a-z]+ -> [a-z]+
    const char delimiter = ' ';
    std::vector<std::string> tokens;
    util::tokenize(text, delimiter, tokens);

    if(std::regex_match(text, std::regex("^([0-9]+|[a-z]+) -> [a-z]+"), std::regex_constants::match_any)) {
        Register& left = find_or_create(tokens.at(0), map);
        Register& assignee = find_or_create(tokens.at(2), map);

        assignee.set_left(left);
        assignee.op = Register::OP::ASSIGN;
    }

    else if(std::regex_match(text, std::regex("([a-z]+|[0-9]+) AND ([a-z]+|[0-9]+) -> [a-z]+"), std::regex_constants::match_any)) {
        Register& left = find_or_create(tokens.at(0), map);
        Register& right = find_or_create(tokens.at(2), map);
        Register& assignee = find_or_create(tokens.at(4), map);
        
        assignee.set_left(left);
        assignee.set_right(right);
        assignee.op = Register::OP::AND;
    }
    else if(std::regex_match(text, std::regex("([a-z]+|[0-9]+) OR ([a-z]+|[0-9]+) -> [a-z]+"), std::regex_constants::match_any)) {
        Register& left = find_or_create(tokens.at(0), map);
        Register& right = find_or_create(tokens.at(2), map);
        Register& assignee = find_or_create(tokens.at(4), map);
        
        assignee.set_left(left);
        assignee.set_right(right);
        assignee.op = Register::OP::OR;
    }
    else if(std::regex_match(text, std::regex("([a-z]+|[0-9]+) LSHIFT [0-9]+ -> [a-z]+"), std::regex_constants::match_any)) {
        Register& left = find_or_create(tokens.at(0), map);
        Register& right = find_or_create(tokens.at(2), map);
        Register& assignee = find_or_create(tokens.at(4), map);
        
        assignee.set_left(left);
        assignee.set_right(right);
        assignee.op = Register::OP::LSHIFT;
    }
    else if(std::regex_match(text, std::regex("([a-z]+|[0-9]+) RSHIFT [0-9]+ -> [a-z]+"), std::regex_constants::match_any)) {
        Register& left = find_or_create(tokens.at(0), map);
        Register& right = find_or_create(tokens.at(2), map);
        Register& assignee = find_or_create(tokens.at(4), map);
        
        assignee.set_left(left);
        assignee.set_right(right);
        assignee.op = Register::OP::RSHIFT;
    }
    else if(std::regex_match(text, std::regex("NOT [a-z]+ -> [a-z]+"), std::regex_constants::match_any)) {
        Register& left = find_or_create(tokens.at(1), map);
        Register& assignee = find_or_create(tokens.at(3), map);

        assignee.set_left(left);
        assignee.op = Register::OP::NOT;
    }

    return;
}

size_t part1()
{  
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    std::unordered_map<std::string, Register> map;

    while(std::getline(file, buffer)) {
        parse(buffer, map);
    }
    file.close();
    
    Register& a = map.find("a")->second;
    a.execute();
    empty_trash();

    return a.value;
}

size_t part2()
{        
    uint16_t previous_result = part1();
    std::ifstream file;
    file.open("input.txt");
    std::string buffer;
    std::unordered_map<std::string, Register> map;

    while(std::getline(file, buffer)) {
        parse(buffer, map);
    }
    file.close();
    
    Register& a = map.find("a")->second;
    Register& b = map.find("b")->second;
    b.left->value = previous_result;

    a.execute();
    empty_trash();

    return a.value;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}