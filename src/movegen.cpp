//
// Created by evcmo on 10/30/2021.
//

#include "movegen.h"

namespace checkers::movegen {
    namespace {

        template<Alliance A, MoveType MT>
        Move* makeKing(Move* moves, Board* const b) {

            if(MT == Promotion) return moves;

            constexpr const Defaults* x = getDefaults<A>();
            constexpr Alliance us = A, them = ~us;
            const uint64_t
                allPieces = b->getAllPieces(),
                ourPieces = b->getPieces<us, King>(),
                enemies = b->getPieces<them, King>();

            if(MT != Passive) {
                // Aggressive king moves here?
            }

            if(MT == Aggressive) return moves;

            uint64_t oursNotOnRight = ourPieces & x->notRightFile,
                     oursNotOnLeft = ourPieces & x->notLeftFile,
                    dr =
                shift<x->downRight>(oursNotOnRight) & ~allPieces,
                    dl =
                shift<x->downLeft>(oursNotOnLeft) & ~allPieces,
                    ur =
                shift<x->upRight>(oursNotOnRight) & ~allPieces,
                    ul =
                shift<x->upLeft>(oursNotOnLeft) & ~allPieces;

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

            constexpr const Defaults* x = getDefaults<A>();
            constexpr Alliance us = A, them = ~us;
            const uint64_t
                allPieces = b->getAllPieces(),
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
                        & ~allPieces,
                         ul =
                    shift<x->upLeft>(ourLowPieces & x->notLeftFile)
                        & ~allPieces;

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
                    & ~allPieces,
                     pl =
                shift<x->upLeft>(ourHighPieces & x->notLeftFile)
                    & ~allPieces;

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
            constexpr const Defaults* x = getDefaults<A>();
            // stubs.
            moves = makeKing<A, MT>(moves, b);
            moves = makePawn<A, MT>(moves, b);
            // stub.
            return moves;
        }
    }

    template<MoveType MT>
    Move* generate(Move* moves, Board* const b) {
        return b->currentPlayer() == White ?
                makeAll<White, MT>(moves, b) :
                makeAll<Black, MT>(moves, b) ;
    }

    template Move* generate<All>(Move*, Board*);
    template Move* generate<Aggressive>(Move*, Board*);
    template Move* generate<Passive>(Move*, Board*);
    template Move* generate<Promotion>(Move*, Board*);
}
