#pragma once

#include <vector>
#include <curses.h>
#include "Piece.hpp"
#include <string>

using std::vector, std::pair, std::string;

class Piece;

struct Block {
  int x;
  int y;
  int intPieceType;
};

class Game {
  public:
    Game();
    ~Game();
    void initCurses();
    void handleInput();
    void handleMovement();
    void handleGravity();
    void newActivePiece();
    void handleLineClear();
    void displayGame();
    int getGridWidth();
    int getGridHeight();
    bool blockInPos(pair<int, int>);
    vector<vector<string>> getGrid();
    void setDefaultGrid();
    void incrementElapsedFrames();
    int getElapsedFrames();
    bool playing;
  private:
    int score;
    int level;
    int velocityX; // -1, 0, or 1
    int elapsedFrames;
    Piece* activePiece;
    vector<Block> blocks;
    vector<vector<pair<string, int>>> grid;
    vector<string> messages;
};

