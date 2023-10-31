#include <iostream>
#include <fstream>

using namespace std;

int main(void) {
    size_t lookup[3] = {1, 2, 3};
    size_t values[18] = {0, 3, 6, 0, 0, 0, 0, 3, 0, 6, 0, 6, 0, 0, 0, 0, 0, 3};
    int score = 0;

    std::ifstream infile("bench.txt");
    char a, b;
    while (infile >> a >> b)
    {   
        int enemy = a - 'A' + 1;
        int res = b - 'X' + 1;
        
        score += values[((enemy + res) * enemy) - 1] + res;
    }   
    
    cout << score << endl;
}