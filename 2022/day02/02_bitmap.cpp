#include <iostream>
#include <fstream>

using namespace std;

int main(void) {
    size_t lookup[3] = {1, 2, 3};

    size_t bitmap_win = 0b0;
    size_t bitmap_draw = 0b0;

    for(int i = 0; i < 3; i++) {
        size_t winning_bit = (lookup[i] + lookup[(i + 2) % 3]) * (i + 1);
        size_t draw_bit = (lookup[i] + lookup[i]) * (i + 1);
        bitmap_win |= (1 << (winning_bit));
        bitmap_draw |= (1 << (draw_bit));
    }

    int score = 0;
    int score_two = 0;

    std::ifstream infile("bench.txt");
    char a, b;
    while (infile >> a >> b)
    {   
        int enemy = a - 'A' + 1;
        int res = b - 'X' + 1;
        int shift = (enemy + res) * res;

        score += 6 * ((bitmap_win >> shift) & 1) + 3 * ((bitmap_draw >> shift) & 1) + res;
    }   
    
    cout << score << endl;
}