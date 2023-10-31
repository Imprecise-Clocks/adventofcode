#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int data;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(int value) : data(value) {}
};

int main(void) {
    // Create nodes directly in the lookup table
    Node lookup[3] = {Node(1), Node(2), Node(3)};
    // link nodes
    for(size_t i = 0; i < 3; i++) {
        lookup[i].next = &lookup[(i + 1) % 3];
        lookup[i].prev = &lookup[(i + 2) % 3];
    }

    int score = 0;

    std::ifstream infile("input.txt");
    char a, b;
    while (infile >> a >> b)
    {   
        int enemy = a - 'A' + 1;
        int res = b - 'X' + 1;

        // draw
        if (enemy == res)
            score += 3 + res;

        // win
        else if(lookup[enemy - 1].next->data == res)
            score += 6 + res;

        else 
            score += 0 + res;

    }   
    
    cout << score << endl;
}
