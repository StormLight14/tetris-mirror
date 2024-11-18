#pragma once
#include <vector>

using std::vector;

class Piece {
  public:
    Piece(int pieceType);
    vector<vector<int>> getBlocks();
    short getColor(); // 1-8 is various ncurses color pairs
  private:
  vector<vector<int>> blocks;
};
