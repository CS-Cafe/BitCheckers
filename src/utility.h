//
// Created by evcmo on 10/30/2021.
//

#ifndef BITCHECKERS_UTILITY_H
#define BITCHECKERS_UTILITY_H

#include <ostream>
#include <cassert>

namespace checkers::utility {

    constexpr uint8_t BoardLength = 64;

    /** The alliances, enumerated. */
    enum Alliance : uint8_t { White, Black };

    /** The piece types, enumerated. */
    enum PieceType : uint8_t { Pawn, King, NullPT };

    /** The move types, enumerated. */
    enum MoveType : uint8_t
    { Passive, Aggressive, Promotion, All };

    /** A table to convert a move type to a string. */
    constexpr const char* MoveTypeToString[] =
    { "Passive", "Aggressive" };

    /** A table to convert a piece type to a string. */
    constexpr const char* PieceTypeToString[] =
    { "Pawn", "King", "NullPT" };

    /**
     * An operator overload to apply the not operator
     * to an Alliance.
     *
     * @param a the alliance to negate
     * @return the complement of the given alliance,
     * if { White, Black } is the universal set
     */
    constexpr Alliance operator~(const Alliance& a) {
        assert(a == White || a == Black);
        return Alliance(a ^ White ^ Black);
    }

    /** The board directions, enumerated. */
    enum Direction : int8_t
    {
        North =  8,
        South = -North,
        East  =  1,
        West  = -East,
        NorthEast = North + East,
        NorthWest = North + West,
        SouthEast = South + East,
        SouthWest = South + West
    };

    /** The board squares, enumerated */
    enum Square : uint8_t
    {
        H1, G1, F1, E1, D1, C1, B1, A1,
        H2, G2, F2, E2, D2, C2, B2, A2,
        H3, G3, F3, E3, D3, C3, B3, A3,
        H4, G4, F4, E4, D4, C4, B4, A4,
        H5, G5, F5, E5, D5, C5, B5, A5,
        H6, G6, F6, E6, D6, C6, B6, A6,
        H7, G7, F7, E7, D7, C7, B7, A7,
        H8, G8, F8, E8, D8, C8, B8, A8,
        NullSQ
    };

    constexpr uint64_t WhiteStartingPosition =
            0x55AA550000000000L;
    constexpr uint64_t BlackStartingPosition =
            0x0000000000AA55AAL;
    constexpr uint64_t NotWestFile
            = 0x7F7F7F7F7F7F7F7FL;
    constexpr uint64_t NotEastFile
            = 0xFEFEFEFEFEFEFEFEL;
    constexpr uint64_t NotEdges
            = 0x007E7E7E7E7E7E00L;
    constexpr uint64_t NotEdgeFiles
            = 0x7E7E7E7E7E7E7E7EL;
    constexpr uint64_t NotEdgeRanks
            = 0x00FFFFFFFFFFFF00L;
    constexpr uint64_t FullBoard
            = 0xFFFFFFFFFFFFFFFFL;
    constexpr uint64_t WhiteHighPromotionMask
            = 0x00000000000000FFL;
    constexpr uint64_t BlackHighPromotionMask
            = 0xFF00000000000000L;
    constexpr uint64_t WhiteMidPromotionMask
            = 0x000000000000FF00L;
    constexpr uint64_t BlackMidPromotionMask
            = 0x00FF000000000000L;
    constexpr uint64_t WhitePromotionMask
            = 0x000000000000FFFFL;
    constexpr uint64_t BlackPromotionMask
            = 0xFFFF000000000000L;

    struct Defaults final {
        const Direction up;
        const Direction Down;
        const Direction left;
        const Direction right;
        const Direction upLeft;
        const Direction upRight;
        const Direction downLeft;
        const Direction downRight;
        const uint64_t notLeftFile;
        const uint64_t notRightFile;
        const uint64_t promotionMask;
        const uint64_t midPromotionMask;
        const uint64_t highPromotionMask;
    };

    constexpr Defaults WhiteDefaults {
            South,
            North,
            East,
            West,
            SouthEast,
            SouthWest,
            NorthEast,
            NorthWest,
            NotEastFile,
            NotWestFile,
            WhitePromotionMask,
            WhiteMidPromotionMask,
            WhiteHighPromotionMask
    };

    constexpr Defaults BlackDefaults {
            North,
            South,
            West,
            East,
            NorthWest,
            NorthEast,
            SouthWest,
            SouthEast,
            NotWestFile,
            NotEastFile,
            BlackPromotionMask,
            BlackMidPromotionMask,
            BlackHighPromotionMask
    };

    template<Alliance A>
    constexpr const Defaults* getDefaults()
    { return A == White? &WhiteDefaults: &BlackDefaults; }

    /** A map from squares to bit boards. */
    constexpr uint64_t SquareToBitBoard[] = {
            0x0000000000000001L, 0x0000000000000002L,
            0x0000000000000004L, 0x0000000000000008L,
            0x0000000000000010L, 0x0000000000000020L,
            0x0000000000000040L, 0x0000000000000080L,
            0x0000000000000100L, 0x0000000000000200L,
            0x0000000000000400L, 0x0000000000000800L,
            0x0000000000001000L, 0x0000000000002000L,
            0x0000000000004000L, 0x0000000000008000L,
            0x0000000000010000L, 0x0000000000020000L,
            0x0000000000040000L, 0x0000000000080000L,
            0x0000000000100000L, 0x0000000000200000L,
            0x0000000000400000L, 0x0000000000800000L,
            0x0000000001000000L, 0x0000000002000000L,
            0x0000000004000000L, 0x0000000008000000L,
            0x0000000010000000L, 0x0000000020000000L,
            0x0000000040000000L, 0x0000000080000000L,
            0x0000000100000000L, 0x0000000200000000L,
            0x0000000400000000L, 0x0000000800000000L,
            0x0000001000000000L, 0x0000002000000000L,
            0x0000004000000000L, 0x0000008000000000L,
            0x0000010000000000L, 0x0000020000000000L,
            0x0000040000000000L, 0x0000080000000000L,
            0x0000100000000000L, 0x0000200000000000L,
            0x0000400000000000L, 0x0000800000000000L,
            0x0001000000000000L, 0x0002000000000000L,
            0x0004000000000000L, 0x0008000000000000L,
            0x0010000000000000L, 0x0020000000000000L,
            0x0040000000000000L, 0x0080000000000000L,
            0x0100000000000000L, 0x0200000000000000L,
            0x0400000000000000L, 0x0800000000000000L,
            0x1000000000000000L, 0x2000000000000000L,
            0x4000000000000000L, 0x8000000000000000L
    };

    /**
     * The eight files of the board.
     */
    constexpr uint64_t Files[] = {
            0x0101010101010101L, 0x0202020202020202L,
            0x0404040404040404L, 0x0808080808080808L,
            0x1010101010101010L, 0x2020202020202020L,
            0x4040404040404040L, 0x8080808080808080L
    };

    /**
     * The eight ranks of the board.
     */
    constexpr uint64_t Ranks[] = {
            0x00000000000000FFL, 0x000000000000FF00L,
            0x0000000000FF0000L, 0x00000000FF000000L,
            0x000000FF00000000L, 0x0000FF0000000000L,
            0x00FF000000000000L, 0xFF00000000000000L
    };

    /**
     * The DeBruijn constant.
     */
    constexpr uint64_t DeBruijn64 = 0x03F79D71B4CB0A89L;

    /**
     * The DeBruijn map from hash key to integer
     * square index.
     */
    constexpr uint8_t DeBruijnTable[] = {
            0,   1, 48,  2, 57, 49, 28,  3,
            61, 58, 50, 42, 38, 29, 17,  4,
            62, 55, 59, 36, 53, 51, 43, 22,
            45, 39, 33, 30, 24, 18, 12,  5,
            63, 47, 56, 27, 60, 41, 37, 16,
            54, 35, 52, 21, 44, 32, 23, 11,
            46, 26, 40, 15, 34, 20, 31, 10,
            25, 14, 19,  9, 13,  8,  7,  6
    };

    /**
     * A method to shift the given bitboard left or
     * right by the absolute value of the direction,
     * according to its sign.
     *
     * @param b The board to shift
     * @tparam D The direction and amount to shift with
     */
    template<Direction D>
    constexpr uint64_t shift(const uint64_t b) {
        static_assert(
                D == North     || D == South     ||
                D == East      || D == West      ||
                D == NorthEast || D == NorthWest ||
                D == SouthEast || D == SouthWest
        );
        return D > 0 ? b << D : b >> -D;
    }

    /**
     * A method to getPieces the file of the current square
     * (square mod 8).
     *
     * @param square the square to calculate the file of
     * @return the file of the given square
     */
    constexpr int fileOf(unsigned int square)
    { return (int)(square & 7U); }

    /**
     * A method to getPieces the rank of the current square
     * (square div 8).
     *
     * @param the square to calculate the rank of
     * @return the rank of the given square
     */
    constexpr int rankOf(unsigned int square)
    { return (int)(square >> 3U); }

    /**
     * A method to check if a king move in the given
     * direction is within the boundaries of the board.
     *
     * @param origin the origin of the move
     * @param direction the direction in which to move
     * @return whether or not a move in the specified
     * direction will be within the bounds of the board.
     */
    constexpr bool withinBounds(const int origin,
                                const int direction) {
        const int x = origin + direction;
        return x >= H1 && x <= A8 && (
                abs(fileOf(x) - fileOf(origin)) < 2 ||
                abs(direction) == North
        );
    }

    /**
     * A method to compute the absolute value of an
     * integer, without branching.
     *
     * @param x the number to take the absolute value of
     */
    constexpr int abs(const int x) {
        return x - (signed int)
                (((unsigned int)x << 1U) &
                 ((unsigned int)x >> 31U));
    }

    /**
     * A method to count the high bits in the given unsigned
     * long using an algorithm featured in Hacker's Delight.
     * This algorithm is based on the mathematical formula
     * high bit count = x - (SUM from n=0 to n=inf (x >> n))
     *
     * @param x the long which contains the bits to count
     * @return the number of high bits in the given ulong
     */
    constexpr int highBitCount(uint64_t x) {
        // Count bits in each 4-bit section.
        uint64_t n =
                (x >> 1U) & 0x7777777777777777UL;
        x -= n;
        n = (n >> 1U) & 0x7777777777777777UL;
        x -= n;
        n = (n >> 1U) & 0x7777777777777777UL;
        x -= n;
        // add 4-bit sums into byte sums.
        x = (x + (x >> 4U)) & 0x0F0F0F0F0F0F0F0FUL;
        // Add the byte sums.
        x *= 0x0101010101010101UL;
        return (short)(x >> 56U);
    }

    /**
     * A method to "scan" the given unsigned long
     * from least significant bit to most significant
     * bit, reporting the index of the fist encountered
     * high bit.
     *
     * @author Martin Läuter (1997),
     * @author Charles E. Leiserson,
     * @author Harald Prokop,
     * @author Keith H. Randall
     * @param l the long to scan
     * @return the integer index of the first high bit
     * starting from the least significant side.
     */
    constexpr int bitScanFwd(const uint64_t l) {
        return DeBruijnTable[(int)
                (((l & (uint64_t)-(int64_t)l) * DeBruijn64) >> 58U)
        ];
    }

}

#endif //BITCHECKERS_UTILITY_H
