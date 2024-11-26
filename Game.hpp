#pragma once

#include <vector>
#include <curses.h>
#include "Piece.hpp"

using std::vector;

class Game {
  public:
    Game();
    ~Game();
    void initCurses();
    void handleInput();
    void handleMovement();
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
    int velocityX; // -1, 0, or 1
    Piece* activePiece;
    vector<Piece> pieces;
    vector<vector<char>> grid;
};

