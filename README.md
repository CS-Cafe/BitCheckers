# BitCheckers

This is a 64-bit checkers engine under construction! Please help make BitCheckers as fast as possible! (Also please help come up with a cool name... I suck at that lol)

### Development Strategy
BitCheckers is open-source, meaning that anybody can clone the repository, edit the code, and submit contributions.
Lots of work is needed in the following areas:
<ul>
 <li>
  movegen.cpp - A fast move generator is the cornerstone of every bitboard engine. The move generator for BitCheckers relies on a 64 bit representation of a 32-square board. This makes parallel move generation a synch with quick-and-easy mask/shift operations. This also limits the portability of BitCheckers when considering older machines, or machines with small RAM. 
 </li>
 <li>
  move.h - Move is currently 16 bits to help keep stack usage to a minimum during searches. However, what these bits represent is still undecided. Chess requires 6 bits for origin and destination squares. Checkers, on the other hand, may only require 5 bits to represent these squares (with some extra arithmetic). The move type is critical for do/undo-ing moves. This feild must occupy 2 bits. The remaining 2 (Or 4 if the alternative square representation is used) bits are currently unused.
 </li> 
 <li>
  board.h - Board is almost an exact replica of the board from my personal chess engine. It is an unholy mess. If you are brave enough... it could use some cleaning. Additionally, do/undo move functionality has yet to be implemented. (Undo move should rely on a stacked State object)
 </li>
 <li>
  Anything that you see out of place!
 </li>
</ol>
  
