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
    vector<Piece> getPieces();
    bool playing;
  private:
    int score;
    int level;
    vector<Piece> pieces;
};

