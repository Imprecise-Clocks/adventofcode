#include <iostream>
#include <fstream>

using namespace std;

int main(void) {
    size_t lookup[3] = {1, 2, 3};
    int score = 0;

    std::ifstream infile("input.txt");
    char a, b;
    while (infile >> a >> b)
    {   
        int enemy = a - 'A' + 1;
        int res = b - 'X' + 1;

        if (enemy == res) { // draw
            score += 3 + res;
        } else if (lookup[(enemy + 1) % 3] == res) { // lose
            score += res;
        } else {
            score += 6 + res;
        }

    }   
    
    cout << score << endl;
}
