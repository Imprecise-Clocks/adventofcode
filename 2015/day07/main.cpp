#include <iostream>
#include <fstream>
#include <stdint.h>
#include "../../utils/util.h"

class Register {
public:
    Register(const std::string& name, uint16_t value) : name(name), value(value), is_initialized(true) {}
    Register(const std::string& name) : name(name) {}

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

    uint16_t operator &(const uint16_t value) const
    {
        return this->value & value;
    }

    uint16_t operator |(const uint16_t value) const
    {
        return this->value | value;
    }

    uint16_t operator !() const
    {
        return !this->value;
    }

    bool is_initialized = false;
    std::string name;

private:
    uint16_t value;
};

template <typename T>
T parse(std::string& text)
{
    // [0-9]+ -> [a-z]+
    // ([a-z]+|[0-9]+) AND ([a-z]+|[0-9]+) -> [a-z]+
    // ([a-z]+|[0-9]+) OR ([a-z]+|[0-9]+) -> [a-z]+
    // ([a-z]+|[0-9]+) LSHIFT [0-9]+ -> [a-z]+
    // ([a-z]+|[0-9]+) RSHIFT [0-9]+ -> [a-z]+
    // NOT [a-z]+ -> [a-z]+
}

size_t part1()
{  
    return 0;
}

size_t part2()
{    
    return 0;
}

int main() 
{
    std::cout << "The answer to part 1: " << part1() << std::endl;
    std::cout << "The answer to part 2: " << part2() << std::endl;
    return 0;
}