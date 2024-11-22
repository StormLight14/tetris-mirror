#pragma once

#include <vector>
#include <curses.h>
#include "Piece.hpp"

using std::vector;

class Game {
  public:
    Game();
    void initCurses();
    void handleInput();
    void handleGravity();
    void displayGame();
    int getGridWidth();
    int getGridHeight();
    vector<Piece> getPieces();
    vector<vector<char>> getGrid();
    void setDefaultGrid();
    bool playing;
  private:
    int score;
    int level;
    vector<Piece> pieces;
    vector<vector<char>> grid;
};

