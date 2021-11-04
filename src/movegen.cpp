//
// Created by evcmo on 10/30/2021.
//

#include "movegen.h"

namespace checkers::movegen {
    namespace {

        template<Alliance A, MoveType MT>
        Move* makeKing(Move* moves, Board* const b) {

            constexpr Defaults* x = getDefaults<A>();
            constexpr Alliance us = A, them = ~us;
            constexpr uint64_t
                ourPieces = b->getPieces<us, King>(),
                enemies = b->getPieces<them, King>();

            if(MT == Promotion) return moves;

            if(MT != Passive) {
                // Aggressive king moves here?
            }

            if(MT == Aggressive) return moves;

            uint64_t dr =
                shift<x->downRight>(ourPieces & x->notRightFile)
                    & ~enemies,
                    dl =
                shift<x->downLeft>(ourPieces & x->notLeftFile)
                    & ~enemies,
                    ur =
                shift<x->upRight>(ourPieces & x->notRightFile)
                    & ~enemies,
                    ul =
                shift<x->upLeft>(ourPieces & x->notLeftFile)
                    & ~enemies;

            for (int d; dr; dr &= dr - 1) {
                d = bitScanFwd(dr);
                *moves++ =
                        Move::make(d + x->upLeft, d);
            }

            for (int d; dl; dl &= dl - 1) {
                d = bitScanFwd(dl);
                *moves++ =
                        Move::make(d + x->upRight, d);
            }

            for (int d; ur; ur &= ur - 1) {
                d = bitScanFwd(ur);
                *moves++ =
                        Move::make(d + x->downLeft, d);
            }

            for (int d; ul; ul &= ul - 1) {
                d = bitScanFwd(ul);
                *moves++ =
                        Move::make(d + x->downRight, d);
            }

            return moves;
        }

        template<Alliance A, MoveType MT>
        Move* makePawn(Move* moves, Board* const b) {

            constexpr Defaults* x = getDefaults<A>();
            constexpr Alliance us = A, them = ~us;
            constexpr uint64_t
                ourPieces = b->getPieces<us, Pawn>(),
                enemies = b->getPieces<them, Pawn>(),
                ourLowPieces = ourPieces & ~x->promotionMask,
                ourMidPieces = ourPieces & x->midPromotionMask,
                ourHighPieces = ourPieces & x->highPromotionMask;



            if(MT != Passive) {
                // Aggressive "jump" moves here?
                if(MT != Promotion) {
                    //Aggressive non-promotion moves here?
                }
                // Aggressive promotion moves here?
            }

            if(MT == Aggressive) return moves;

            if(MT != Promotion) {

                uint64_t ur =
                    shift<x->upRight>(ourLowPieces & x->notRightFile)
                        & ~enemies,
                         ul =
                    shift<x->upLeft>(ourLowPieces & x->notLeftFile)
                        & ~enemies;

                for (int d; ur; ur &= ur - 1) {
                    d = bitScanFwd(ur);
                    *moves++ =
                            Move::make(d + x->downLeft, d);
                }

                for (int d; ul; ul &= ul - 1) {
                    d = bitScanFwd(ul);
                    *moves++ =
                            Move::make(d + x->downRight, d);
                }
            }

            uint64_t pr =
                shift<x->upRight>(ourHighPieces & x->notRightFile)
                    & ~enemies,
                     pl =
                shift<x->upLeft>(ourHighPieces & x->notLeftFile)
                    & ~enemies;

            for(int d; pr; pr &= pr - 1) {
                d = bitScanFwd(pr);
                *moves++ =
                        Move::make<Promotion>(d + x->downLeft, d);
            }

            for(int d; pl; pl &= pl - 1) {
                d = bitScanFwd(pl);
                *moves++ =
                        Move::make<Promotion>(d + x->downRight, d);
            }

            return moves;
        }

        template<Alliance A, MoveType MT>
        Move* makeAll(Move* moves, Board* const b) {
            constexpr Defaults* x = getDefaults<A>();
            //stub
        }
    }

    template<MoveType MT>
    Move* generate(Move* moves, Board* const b) {
        return b->currentPlayer() == White ?
                makeAll<White, MT>() :
                makeAll<Black, MT>() ;
    }
}
