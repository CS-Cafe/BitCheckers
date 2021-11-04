#include <iostream>
#include "board.h"

using namespace checkers;

int main() {
    State s;
    Board b = Board::Builder(s).build();
    std::cout << b;
}
