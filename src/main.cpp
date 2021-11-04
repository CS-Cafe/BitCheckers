#include <iostream>
#include "board.h"
#include "move.h"
#include "movegen.h"

using namespace checkers;

int main() {
    State s;
    Board b = Board::Builder(s).build();
    Move m[256];
    Move* u = movegen::generate<All>(m, &b);
    for(Move* x = m; x < u; ++x)
        std::cout << *x << '\n';
    std::cout << b;
}
