//
// Created by evcmo on 10/30/2021.
//

#ifndef BITCHECKERS_BOARD_H
#define BITCHECKERS_BOARD_H

#include "utility.h"

using std::ostream;

namespace checkers {
    using namespace utility;

    /**
     * <summary>
     * A struct to keep track of the board state, for use in
     * applying and retracting count.
     * </summary>
     *
     * @struct State
     */
    class State final {
    private:
        /**
         * @private
         * Board is State's best bud.
         */
        friend class Board;

        /**
         * @private
         * The previous State.
         */
        State* prevState;

        /**
         * @private
         * The captured piece for this State.
         */
        PieceType capturedPiece;
    public:

        /**
         * A default constructor for this State.
         */
        constexpr State() :
                prevState(nullptr),
                capturedPiece(NullPT)
        {  }
    };

    class Board final {
    private:

        /**
         * @private
         * Bitboard layers for the various piece types.
         */
        uint64_t pieces[2][3]{};

        /**
         * @private
         * All piece bitboards sandwiched together.
         */
        uint64_t allPieces;

        /**
         * @private
         * The alliance of the current player.
         */
        Alliance currentPlayerAlliance;

        /**
         * @private
         * A mailbox representation of this board.
         */
        PieceType mailbox[BoardLength]{
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT,
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT,
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT,
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT,
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT,
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT,
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT,
                NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT, NullPT
        };

        /**
         * @private
         * A pointer to an externally-allocated state
         * object to optimize move retraction.
         */
        State* currentState;

    public:
        /**
         * A method to expose the current player's alliance.
         *
         * @return the current player's alliance
         */
        [[nodiscard]]
        constexpr Alliance currentPlayer() const
        { return currentPlayerAlliance; }

        /**
         * A method to expose each piece bitboard.
         *
         * @tparam A the alliance of the bitboard
         * @tparam PT the piece type of the bitboard
         * @return a piece bitboard
         */
        template<Alliance A, PieceType PT>
        constexpr uint64_t getPieces()
        { return pieces[A][PT]; }

        /**
         * A method to expose a half-sandwich bitboard
         * of all piece bitboards belonging to the given
         * alliance.
         *
         * @tparam A the alliance of the bitboard
         * @return a bitboard of all pieces belonging
         * to the given alliance
         */
        template<Alliance A>
        constexpr uint64_t getPieces()
        { return pieces[A][NullPT]; }

        /**
         * A method to pop each bit off of the given bitboard,
         * inserting the given character into the corresponding
         * index of the given buffer.
         *
         * @param buffy the buffer to fill
         * @param b the bitboard to pop
         * @param c the character to use
         */
        static constexpr void
        popTo(char* const buffy, uint64_t b, const char c)
        { for (; b > 0; b &= b - 1) buffy[bitScanFwd(b)] = c; }

        /**
         * A method to represent this board with a string.
         *
         * @return a string representing this board
         */
        [[nodiscard]]
        inline std::string toString() const {
            char buffer[BoardLength]{};
            popTo(buffer, pieces[White][Pawn]  , 'P');
            popTo(buffer, pieces[White][King]  , 'K');
            popTo(buffer, pieces[Black][Pawn]  , 'p');
            popTo(buffer, pieces[Black][King]  , 'k');
            std::string sb;
            sb.reserve(136);
            sb.append("\n\t    H   G   F   E   D   C   B   A");
            sb.append(
                    "\n\t  +---+---+---+---+---+---+---+---+\n"
            );
            char* x = buffer;
            for(char i = '1'; i < '9'; ++i) {
                sb.push_back('\t');
                sb.push_back(i);
                sb.append(" | ");
                for(char j = '1'; j < '9'; ++j) {
                    char c = *x++;
                    sb.push_back(c == '\0' ? ' ' : c);
                    sb.append(" | ");
                }
                sb.push_back(i);
                sb.append(
                        "\n\t  +---+---+---+---+---+---+---+---+\n"
                );
            }
            sb.append("\t    H   G   F   E   D   C   B   A\n");
            /*sb.push_back('\n');
            for(int i = 0; i < BoardLength; ++i) {
                if(!(i & 7)) sb.push_back('\n');
                sb.append(PieceTypeToString[mailbox[i]]);
            }
            sb.push_back('\n');*/
            return sb;
        }

        /**
         * An overloaded insertion operator for use in printing
         * a string representation of this board.
         *
         * @param out the output stream to use
         * @param in the board to stringify and print
         * @return a reference to the output stream, for chaining
         * purposes
         */
        friend ostream& operator<<(ostream& out, const Board& in) {
            return out << in.toString();
        }

        /** @public Deleted copy constructor. */
        Board(const Board&) = default;

        /** @public Deleted move constructor. */
        Board(Board&&) = default;

        /**
         * <summary>
         *  <p><br/>
         * A builder pattern for the Board class to allow
         * the client flexibility and readability during
         * the instantiation of a Board Object.
         *  </p>
         * </summary>
         * @class Builder
         * @author Ellie Moore
         * @version 06.07.2021
         */
        class Builder final {
        private:

            /**
             * @private
             * Board is Builder's bestie.
             */
            friend class Board;

            /**
             * @private
             * The alliance of the player to start.
             */
            Alliance currentPlayerAlliance;

            /**
             * @private
             * An array to hold each piece bitboard.
             */
            uint64_t pieces[2][3]{{
                WhiteStartingPosition,
                0, 0
            },{
                BlackStartingPosition,
                0, 0
            }};

            /**
             * @private
             * The initial state of the board under
             * construction.
             */
            State* state;
        public:

            /**
             * @public
             * A public constructor for a Builder.
             *
             * @param s the initial state of the board
             * under construction.
             */
            explicit constexpr Builder(State& s) :
                    currentPlayerAlliance(White),
                    state(&s) { }

            /**
             * @public
             * A public constructor to copy a board into
             * this Builder.
             *
             * @param board the board to copy
             */
            explicit constexpr Builder(const Board& board) :
                    currentPlayerAlliance(~board.currentPlayerAlliance),
                    state(board.currentState) {
                pieces[White][Pawn]    = board.pieces[White][Pawn];
                pieces[White][King]    = board.pieces[White][King];
                pieces[Black][Pawn]    = board.pieces[Black][Pawn];
                pieces[Black][King]    = board.pieces[Black][King];
            }

            /**
             * A method to set the entire bitboard for a given
             * alliance and piece type.
             *
             * @tparam A the alliance of the bitboard to set
             * @tparam PT the piece type of the bitboard to set
             * @param p the piece bitboard to use
             * @return a reference to the instance
             */
            template <Alliance A, PieceType PT>
            constexpr Builder& setPieces(const uint64_t p)
            { pieces[A][PT] = p; return *this; }

            /**
             * A method to set a single piece onto the bitboard
             * of the given alliance and piece type.
             *
             * @tparam A the alliance of the piece to set
             * @tparam PT the type of the piece to set
             * @param sq the square on which to set the piece
             * @return a reference to the instance
             */
            template <Alliance A, PieceType PT>
            constexpr Builder& setPiece(const int sq)
            { pieces[A][PT] |= SquareToBitBoard[sq]; return *this; }

            /**
             * A method to set a single piece onto the bitboard
             * of the given alliance and piece type.
             *
             * @tparam A the alliance of the piece to set
             * @tparam PT the type of the piece to set
             * @param sq the square on which to set the piece
             * @return a reference to the instance
             */
            constexpr Builder&
            setPiece(const Alliance a, const PieceType pt, const int sq)
            { pieces[a][pt] |= SquareToBitBoard[sq]; return *this; }

            /**
             * A method to set the alliance of the initial
             * current player for the board under construction.
             *
             * @tparam A the alliance of the initial current
             * player
             * @return a reference to the instance
             */
            template <Alliance A>
            constexpr Builder& setCurrentPlayer()
            { currentPlayerAlliance = A; return *this; }

            /**
             * A method to set the alliance of the initial
             * current player for the board under construction.
             *
             * @param a the alliance of the initial current
             * player
             * @return a reference to the instance
             */
            constexpr Builder& setCurrentPlayer(const char c) {
                const bool b = c == 'w'; assert(b || c == 'b');
                currentPlayerAlliance = b? White: Black;
                return *this;
            }

            /**
             * @public
             * A method to instantiate a board from the data
             * stored in this Builder.
             *
             * @return a reference to the instance
             */
            [[nodiscard]]
            constexpr Board build() const { return Board(*this); }

            /** @public A deleted copy constructor. */
            Builder(const Builder&) = delete;

            /** @public A deleted move constructor. */
            Builder(Builder&&) = delete;
        };
    private:
        /**
         * @private
         * @static
         * A method to sandwich piece bitboards into a single
         * bitboard for the given alliance.
         *
         * @param b the Builder to use
         * @return a sandwich of the given Alliance's piece
         * boards.
         */
        template<Alliance A>
        static constexpr uint64_t sandwich(const Builder& b)
        { return b.pieces[A][Pawn] | b.pieces[A][King]; }

        /**
         * @private
         * @static
         * A method to initialize each piece bitboard for the
         * given alliance.
         *
         * @param b the Builder to use
         */
        template<Alliance A>
        static constexpr void
        initPieceBoards(uint64_t* const pieces,
                        const Builder& b) {
            pieces[Pawn]   = b.pieces[A][Pawn];
            pieces[King]   = b.pieces[A][King];
            pieces[NullPT] = sandwich<A>(b);
        }

        explicit constexpr Board(const Builder& b) :
                allPieces(0),
                currentPlayerAlliance(b.currentPlayerAlliance),
                currentState(b.state) {
            initPieceBoards<White>(pieces[White], b);
            initPieceBoards<Black>(pieces[Black], b);
            for (int j = Pawn; j < NullPT; ++j) {
                for (uint64_t x = b.pieces[White][j]; x; x &= x - 1)
                    mailbox[bitScanFwd(x)] = (PieceType) j;
                for (uint64_t x = b.pieces[Black][j]; x; x &= x - 1)
                    mailbox[bitScanFwd(x)] = (PieceType) j;
            }
            allPieces =
                    pieces[White][NullPT] | pieces[Black][NullPT];
        }
    public:

        [[nodiscard]]
        constexpr uint64_t getAllPieces() const
        { return allPieces; }

        [[nodiscard]]
        constexpr PieceType getPiece(const int square) const
        { return mailbox[square]; }
    };

}

#endif //BITCHECKERS_BOARD_H
