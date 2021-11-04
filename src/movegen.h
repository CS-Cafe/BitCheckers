//
// Created by evcmo on 10/30/2021.
//

#ifndef BITCHECKERS_MOVEGEN_H
#define BITCHECKERS_MOVEGEN_H
#include "utility.h"
#include "move.h"
#include "board.h"

namespace checkers::movegen {
    using namespace utility;
    using namespace board;

    template<MoveType MT>
    Move* generate(Move*, Board*);
}


#endif //BITCHECKERS_MOVEGEN_H
