#include <iostream>
#include <fstream>
#include <stdint.h>
#include "../../utils/util.h"

class Register {
public:
    Register(const std::string& name, uint16_t value) : name(name), value(value) {}

    Register& operator =(const Register& other)
    {
        this->value = other.value;
        return this;
    }

    Register& operator =(const uint16_t value)
    {
        this->value = value;
        return this;
    }

    Register operator &(const Register& other) const
    {

    }

private:
    std::string name;
    uint16_t value;
};

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